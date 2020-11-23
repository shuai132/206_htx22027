#include <cassert>

#include "typedef.h"
#include "mock_data.h"
#include "FrameParser.h"
#include "Hardware.h"
#include "frame_process.h"

extern "C" {
#include "drvGnet.h"
#include "drvCommon.h"
#include "interrupt.h"
}

static std::shared_ptr<Hardware> hardWares[2] = {};
static std::shared_ptr<FrameParser> frameParsers[2] = {};

int configMac(int num, MacAddr local, MacAddr remote) {
    assert(0 <= num and num <= 1);
    auto hardware = std::make_shared<Hardware>(local, remote);
    auto frameParser = std::make_shared<FrameParser>(hardware);
    hardWares[num] = hardware;
    frameParsers[num] = frameParser;
    initProcess(frameParser, hardware);

    drvGnetOpen(0, local.data());//todo

    {
        /// 硬件相关配置
        hardware->sendFrame = [=](uint8_t* data, size_t size) {
            LOGD("发送MAC帧");
            drvGnetWrite(num, (uint8_t*)remote.data(), data, size);//todo
        };
        // 当接收到数据帧时 调用下面的函数
        // hardware->onRecvFrame(...);
        // 参数开关检测
        hardware->paramNormal = []{
            // 通过GPIO检测
            return true;
        };
        // 实现一个互斥锁
        hardware->dataLock = [=]{
            intDisable(isrTab[E_PL_ISR_GNET0 + num]);
        };
        hardware->dataUnLock = [=]{
            intEnable(isrTab[E_PL_ISR_GNET0 + num]);
        };
        // 延时实现
        hardware->delayMs = [](uint32_t ms){
            drv_delay_ms(ms);
        };
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
}

int main() {
    drvCommon_Init();

    MacAddr MAC_LOCAL_0  = {0x06, 0x05, 0x04, 0x03, 0x02, 0xDA};
    MacAddr MAC_REMOTE_0 = {0x06, 0x05, 0x04, 0x03, 0x02, 0xCA};
    MacAddr MAC_LOCAL_1  = {0x06, 0x05, 0x04, 0x03, 0x02, 0xDA};
    MacAddr MAC_REMOTE_1 = {0x06, 0x05, 0x04, 0x03, 0x02, 0xCA};
    drvGnetInit();
    configMac(0, MAC_LOCAL_0, MAC_REMOTE_0);
    configMac(1, MAC_LOCAL_1, MAC_REMOTE_1);
    drvGnetIntrConnect([](UINT32 num, UINT32, ST_DATA_BUFF* stDataBuff, UINT32 size){
        assert(0 <= num and num <= 1);
        hardWares[num]->onRecvFrame(stDataBuff->ubuf, size);
    });

    for(;;) {
        for(auto& parser : frameParsers) {
            parser->parseOnce();
        }
    }

    return 0;
}
