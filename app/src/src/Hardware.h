#pragma once

#include <functional>
#include <memory>

#include "typedef.h"
#include "noncopyable.h"
#include "log/log.h"

/**
 * 需要硬件实现的部分
 */
class Hardware : noncopyable {
    using FrameTransfer = std::function<void(uint8_t* data, size_t size)>;
public:
    /**
     * 发送MAC数据帧
     */
    FrameTransfer sendFrame;
    /**
     * 硬件接收到MAC帧后调用此函数
     */
    FrameTransfer onRecvFrame;

    /**
     * 参数开关检测
     */
    std::function<bool()> paramNormal;

    /**
     * 延时实现
     */
    std::function<void(uint32_t ms)> delayMs;

    /**
     * 数据上锁和解锁
     * 裸机时使用开关硬件中断的方式
     * RTOS可根据场景选择合适的API
     */
    std::function<void()> dataLock;
    std::function<void()> dataUnLock;
    class DataLockGuard : public noncopyable {
    public:
        explicit DataLockGuard(Hardware* hardware) : _hardware(hardware) {_hardware->dataLock();}
        explicit DataLockGuard(const std::shared_ptr<Hardware>& hardware):_hardware(hardware.get()) {}
        ~DataLockGuard() {_hardware->dataUnLock();}
    private:
        Hardware* _hardware = nullptr;
    };
public:
    explicit Hardware(MacAddr local, MacAddr remote);

    MacAddr local;
    MacAddr remote;
};

namespace cb {
    void error(const char* msg);
    void warn(const char* msg);
}

