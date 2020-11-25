#include <cassert>
#include <utility>

#include "typedef.h"
#include "FrameParser.h"
#include "Hardware.h"
#include "frame_process.h"
#include "utils.h"
#include "io_check_logic.h"
#include "defer.h"
#include "config.h"

extern "C" {
#include "drvIo.h"
#include "drvGnet.h"
#include "drvTimer.h"
#include "drvCommon.h"
#include "drvErro.h"
#include "interrupt.h"
}

static std::shared_ptr<Hardware> hardWares[HW_NUM] = {};
static std::shared_ptr<FrameParser> frameParsers[HW_NUM] = {};

static void configMac(int num, const MacAddr& local, const MacAddr& remote) {
    assert(0 <= num and num < HW_NUM);
    auto hardware = std::make_shared<Hardware>(local, remote);
    auto frameParser = std::make_shared<FrameParser>(hardware);
    hardWares[num] = hardware;
    frameParsers[num] = frameParser;
    initProcess(frameParser, hardware);

    auto macHex2Str = [](const MacAddr& mac) -> std::string {
        if (mac.size() > 6) return "";
        char macStr[13];
        size_t len;
        auto success = utils::hex2string(mac.data(), mac.size(), macStr, &len);
        if (not success) return "";
        return macStr;
    };
    drvGnetOpen(0, (UINT8*)macHex2Str(local).c_str());

    {
        /// 硬件相关配置
        hardware->sendFrame = [num, mac = macHex2Str(remote)](uint8_t* data, size_t size) {
            LOGD("发送MAC帧");
            drvGnetWrite(num, (uint8_t*)mac.c_str(), data, size);
        };
        // 当接收到数据帧时 调用下面的函数
        // hardware->onRecvFrame(...);
        // 参数开关检测
        hardware->paramNormal = []{
            // 通过GPIO检测
            UINT32 data;
            auto ret = drvIoRead(DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_8, &data, 0);
            assert(ret == DRV_OPERATE_SUCCESS);
            return data == 0;
        };
        // 实现一个互斥锁
        hardware->dataLock = [num]{
            intDisable(isrTab[E_PL_ISR_GNET0 + num]);
        };
        hardware->dataUnLock = [num]{
            intEnable(isrTab[E_PL_ISR_GNET0 + num]);
        };
        // 延时实现
        hardware->delayMs = [](uint32_t ms){
            drv_delay_ms(ms);
        };
        // 主循环/任务里循环调用下面的函数
        // frameParser->parseOnce();
    }
}

bool deviceCheck() {
    if (drvGnetCheck(0, 0) != 0) {
        return false;
    }
    if (drvIoCheck(0) != 0) {
        return false;
    }
    if (drvClkCheck() != 0) {
        return false;
    }

    return true;
}

int main() {
    std::set_new_handler([] {
        FATAL("out of memory");
    });

    // 设备自检
    if (!deviceCheck()) {
        cb::error("自检失败");
    }

    drvCommon_Init();
    drvIoInit(0);
    drvIoOpen();

    ioCheckInit([](int num, uint8_t ST, Frame SP) {
        assert(0 <= num and num < HW_NUM);
        frameParsers[num]->sendFrame(ST, std::move(SP));
    });
    defer []{
        ioCheckClose();
    };

    drvGnetInit();
    drvGnetIntrConnect([](UINT32 num, UINT32 state, ST_DATA_BUFF* stDataBuff, UINT32 size){
        assert(0 <= num and num < HW_NUM);
        if (state == 1) {
            cb::warn("接收FIFO溢出");
        }
        hardWares[num]->onRecvFrame(stDataBuff->ubuf, size + 6*2);
    });
    configMac(0, MAC_LOCAL_0, MAC_REMOTE_0);
    configMac(1, MAC_LOCAL_1, MAC_REMOTE_1);
    defer []{
        drvGnetClose(0);
        drvGnetClose(1);
    };

    for(;;) {
        for(auto& parser : frameParsers) {
            parser->parseOnce();
        }
    }

    return 0;
}
