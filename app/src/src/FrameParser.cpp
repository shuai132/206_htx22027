#include "FrameParser.h"

#include <utility>
#include "Hardware.h"
#include "crc/crc16.h"
#include "utils.h"
#include "log/log.h"

using namespace utils;

FrameParser::FrameParser(std::shared_ptr<Hardware> hardware)
        : _hardware(std::move(hardware)) {
    _frameQueue = std::make_unique<FrameQueue>();
    _hardware->onRecvFrame = [this](uint8_t* data, size_t size){
        auto frame = Frame(data, data + size);
        Hardware::DataLockGuard lockGuard(_hardware);
        _frameQueue->push(std::move(frame));
    };
}

void FrameParser::subscribeCmd(uint8_t cmd, std::function<void(MacFrame)> handle) {
    _unorderedMap[cmd] = std::move(handle);
}

void FrameParser::unsubscribeCmd(const uint8_t& cmd) {
    auto it = _unorderedMap.find(cmd);
    if (it != _unorderedMap.cend()) {
        _unorderedMap.erase(it);
    } else {
        LOGD("not register cmd for: %d", cmd);
    }
}

void FrameParser::sendFrame(MacAddr local, MacAddr remote, uint8_t ST, Frame SP) {
    Frame frame;
    auto pushBack = [&](std::vector<uint8_t> data){
        frame.insert(frame.end(), data.begin(), data.end());
    };
    pushBack(std::move(remote));
    pushBack(std::move(local));
    // len
    uint16_t validDataLen = 2 + 2 + 1 + SP.size();
    uint16_t frameLen = validDataLen + 2;
    frame.push_back(frameLen);
    frame.push_back(frameLen >> 8u);
    void* crcBegin = frame.end().base();    // record for crc
    // head
    pushBack({0x7E, 0x7E});
    frame.push_back(validDataLen);
    frame.push_back(validDataLen >> 8u);
    frame.push_back(ST);
    // sp
    pushBack(std::move(SP));
    // crc
    uint16_t crc = crc16(crcBegin, validDataLen);
    frame.push_back(crc);
    frame.push_back(crc>>8u);
    LOGD("crc:0x%04X", crc);

    LOGD("sendFrame: ");
    printHex(frame);
    _hardware->sendFrame(frame.data(), frame.size());
}

void FrameParser::sendFrame(uint8_t ST, Frame SP) {
    sendFrame(_hardware->local, _hardware->remote, ST, std::move(SP));
}

/**
 * 数据包结构和字节数：
 * | 目的MAC | 源MAC | 有效数据长度 | 有效数据 |  FCS  |
 *     6        2     2（<=1500）   <=1500  4(CRC32)
 * 有效数据部分数据包有两种：
 *  命令数据包格式：
 *  | FLAG | 帧长 | CO | CP | CRC |
 *   0x7E7E   2     1    x    2
 *  应答数据包格式：
 *  | FLAG | 帧长 | ST | SP | CRC |
 *   0x7E7E   2     1    x    2
 *  其中：1. 帧长为除CRC外的所有字节数
 *       2. 所以CP/SP字节数为：帧长-2-2-1
 *       3. CO/ST八位二进制整数
 * 数据都是低位在前，高位在后。
 * @param frame 数据包
 */
void FrameParser::parseFrame(const Frame& frame) {
    LOGD("parseFrame:");
    printHex(frame);
    MacFrame macFrame;
    DataFrame& dataFrame = macFrame.dataFrame;
    auto* p = const_cast<uint8_t*>(frame.data());
    macFrame.macTo.assign(p, p+6);
    p+=6;
    macFrame.macFrom.assign(p, p+6);
    p+=6;
    macFrame.len = raw<uint16_t>(p);
    p+=2;
    void* dataFrameBegin = p;
    // 处理有效数据
    {
        auto flag = raw<uint16_t>(p);
        if (flag != 0x7E7E) {
            cb::error("WRONG FLAG!");
        }
        p+=2;
        auto frameLen = raw<uint16_t>(p);
        dataFrame.len = frameLen;
        p+=2;
        dataFrame.cmd = *p;
        p+=1;
        size_t cpLen = frameLen-2-2-1;
        dataFrame.xp.assign(p, p + cpLen);
        p+=cpLen;
        auto crcRaw = raw<uint16_t>(p);
        dataFrame.crc = crcRaw;
        uint16_t crcExcepted = crc16(dataFrameBegin, dataFrame.len);
        //printHex(dataFrameBegin, dataFrame.len);
        LOGD("crc: raw:0x%X, expected:0x%X", crcRaw, crcExcepted);
        if (crcExcepted != crcRaw) {
            LOGE("error for crc check error!");
            return;
        } else {
            auto& co = dataFrame.cmd;
            LOGD("收到命令帧 CO:%02XH", co);
            auto it = _unorderedMap.find(co);
            if (it == _unorderedMap.cend()) {
                LOGD("not register co for: %d", co);
                cb::warn("Unsupported CO!");
            } else {
                const auto& fn = (*it).second;
                fn(std::move(macFrame));
            }
        }
    }
}

bool FrameParser::parseOnce() {
    bool empty;
    Frame frame;
    {
        Hardware::DataLockGuard lockGuard(_hardware);
        empty = _frameQueue->empty();
        if (not empty) {
            frame = std::move(_frameQueue->front());
            _frameQueue->pop();
        }
    }
    if (not empty) {
        parseFrame(frame);
    }
    return !empty;
}
