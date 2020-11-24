#pragma once

#include <unordered_map>

#include "Hardware.h"

class FrameParser : noncopyable {
public:
    explicit FrameParser(std::shared_ptr<Hardware> hardware);

    /**
     * 根据消息协议CMD/CO 注册消息处理
     * @param cmd 对应协议中的CO
     * @param handle
     */
    void subscribeCmd(uint8_t cmd, std::function<void(MacFrame)> handle);
    void unsubscribeCmd(const uint8_t& cmd);

    /**
     * 解析数据包（一个MAC帧）
     * @param frame
     */
    void parseFrame(const Frame& frame);

    /**
     * 发送一帧数据
     * @param local
     * @param remote
     * @param ST
     * @param SP
     */
    void sendFrame(MacAddr local, MacAddr remote, uint8_t ST, Frame SP);
    void sendFrame(uint8_t ST, Frame SP);

    /**
     * 在主循环/任务调用
     * @return 是否处理了一帧数据
     */
    bool parseOnce();

private:
    std::unordered_map<uint8_t, std::function<void(MacFrame)>> _unorderedMap;
    std::shared_ptr<Hardware> _hardware;
    std::unique_ptr<FrameQueue> _frameQueue;
};
