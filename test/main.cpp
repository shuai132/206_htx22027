#include "typedef.h"
#include "mock_data.h"
#include "FrameParser.h"
#include "Hardware.h"
#include "frame_process.h"
#include "defer.h"

void test_defer() {
    LOG("defer test...");
    defer []{
        LOG("defer:1");
    };
    {
        defer []{
            LOG("defer:2");
        };
    }
    defer []{
        LOG("defer:3");
    };
}
int main() {
    test_defer();

    const MacAddr MAC_LOCAL  = {0x06, 0x05, 0x04, 0x03, 0x02, 0xDA};
    const MacAddr MAC_REMOTE = {0x06, 0x05, 0x04, 0x03, 0x02, 0xCA};
    auto hardware = std::make_shared<Hardware>(MAC_LOCAL, MAC_REMOTE);
    auto frameParser = std::make_shared<FrameParser>(hardware);
    initProcess(frameParser, hardware);

    {
        /// 硬件相关配置
        hardware->sendFrame = [](uint8_t* data, size_t size) {
            LOGD("发送MAC帧");
        };
        // 当接收到数据帧时 调用下面的函数
        // hardware->onRecvFrame(...);
        // 参数开关检测
        hardware->paramNormal = []{
            // 通过GPIO检测
            return true;
        };
        // 实现一个互斥锁
        hardware->dataLock = []{};
        hardware->dataUnLock = []{};
        // 延时实现
        hardware->delayMs = [](uint32_t ms){};
        // 主循环/任务里循环调用下面的函数
        // frameParser->parseOnce();
    }

    {
        /// 模拟使用场景
        // 1. 硬件收到MAC帧
        auto frame = getMockFrame();
        // 2. 通知保存数据帧
        hardware->onRecvFrame(frame.data(), frame.size());
        // 3. 主循环/任务里循环调用
        frameParser->parseOnce();
    }
    return 0;
}

