#include <cassert>

#include "frame_process.h"
#include "utils.h"
#include "log/log.h"

using namespace utils;

void initProcess(const std::shared_ptr<FrameParser>& frameParser,
                 const std::shared_ptr<Hardware>& hardware) {
    frameParser->subscribeCmd(0x13, [=](MacFrame frame) {
        LOGD("C1: 设备自检");
        assert(frame.dataFrame.len - DataFrame::HEAD_LEN == 5);
        // 原样发送SP帧
        Frame sp = std::move(frame.dataFrame.xp);
        printHex(sp);
        frameParser->sendFrame(frame.dataFrame.cmd, sp);
    });
    frameParser->subscribeCmd(0x15, [=](const MacFrame& frame) {
        LOGD("C2: 自检结果下传");
        assert(frame.dataFrame.len - DataFrame::HEAD_LEN == 0);
        Frame sp;
        sp.resize(85, 0x00);
        printHex(sp);
        frameParser->sendFrame(frame.dataFrame.cmd, sp);
    });
    frameParser->subscribeCmd(0x15, [=](const MacFrame& frame) {
        LOGD("C2: 自检结果下传");
        assert(frame.dataFrame.len - DataFrame::HEAD_LEN == 0);
        Frame sp;
        sp.resize(85, 0x00);
        printHex(sp);
        frameParser->sendFrame(frame.dataFrame.cmd, sp);
    });
    frameParser->subscribeCmd(0x4C, [=](MacFrame frame) {
        LOGD("L: 装订参数");
        assert(frame.dataFrame.len - DataFrame::HEAD_LEN == 108);
        // 原样发送SP帧（后面补零）
        Frame sp = std::move(frame.dataFrame.xp);
        sp.resize(144); // 补零
        if (not hardware->paramNormal()) {
            // 把收到的第一个字节取反
            sp[0] = ~sp[0];
        }
        printHex(sp);
        frameParser->sendFrame(frame.dataFrame.cmd, sp);
    });
    frameParser->subscribeCmd(0x99, [=](const MacFrame& frame) {
        LOGD("F: 启动飞控程序");
        Frame sp(0);
        printHex(sp);
        frameParser->sendFrame(frame.dataFrame.cmd, sp); // 原样发送SP帧
    });
    frameParser->subscribeCmd(0x35, [=](const MacFrame& frame) {
        LOGD("N: 静态导航");
        assert(frame.dataFrame.len - DataFrame::HEAD_LEN == 12);
        Frame sp(0);
        printHex(sp);
        frameParser->sendFrame(frame.dataFrame.cmd, sp); // 原样发送SP帧
    });
}
