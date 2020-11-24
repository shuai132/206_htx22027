#include <cassert>

#include "io_check_logic.h"
#include "config.h"

extern "C" {
#include "drvIo.h"
#include "drvCommon.h"
#include "drvCfg.h"
#include "drvTimer.h"
}

// 架位状态
struct State {
    bool yigongdian;            // 已供电
    bool jiebao;                // 解保
    bool zhudianchijihuo;       // 主电池激活
    bool duodianchijihuo;       // 舵电池激活
    bool dianhuodianchijihuo;   // 点火电池激活
};

static State state[HW_NUM];
static SendFrameImpl SendFrame;

/**
 * @param num 架位
 * @return
 */
static bool PositionPower(int num)
{
    return true;
}

static bool MissilePower(int num)
{
    return true;
}
static bool JieChuBaoXianJiance(int num)
{
    return true;
}
static bool ZhuDianChiJiHuo(int num)
{
    return true;
}
static bool DuoDianChiJiHuo(int num)
{
    return true;
}
static bool DianHuoDianChiJiHuo(int num)
{
    return true;
}
static bool TanSheZhuangZhiDianHuo(int num)
{
    return true;
}
static bool ZongCeKaiGuan(int num)
{
    return true;
}
static void H1LED(bool on)
{
}
static void H2LED(bool on)
{
}
static void H3LED(bool on)
{
}
static void H4LED(bool on)
{
}
static void H5LED(bool on)
{
}
static void H6LED(bool on)
{
}
static void LiJiaKongZhi(bool on)
{
}
static bool ResetSwOk()
{
    return true;
}

enum {
    ON  = true,
    OFF = false,
};

static void ioCheck(int num) {
    assert(0 <= num and num < HW_NUM);
    auto& s = state[num];

    if (s.yigongdian) {
        if (MissilePower(num)) {
            H1LED(ON);
            s.yigongdian = false;
        }
    } else {
        if (MissilePower(num)) {
            drv_delay_ms(10);
            H2LED(ON);
            s.yigongdian = true;
            if (ResetSwOk()) {
                // todo
                auto data = "XXXXXX Reset OK";
                SendFrame(num, 0x00, Frame(data, data + strlen(data)));
            }
        }
    }

    if (JieChuBaoXianJiance(num)) {
        H2LED(ON);
        s.jiebao = true;
    }

    if (ZhuDianChiJiHuo(num)) {
        H3LED(ON);
        s.zhudianchijihuo = true;
    }

    if (DuoDianChiJiHuo(num)) {
        H4LED(ON);
        s.duodianchijihuo = true;
    }

    if (DianHuoDianChiJiHuo(num)) {
        H5LED(ON);
        s.dianhuodianchijihuo = true;
    }

    if (TanSheZhuangZhiDianHuo(num)) {
        if (ZongCeKaiGuan(num)) {
            drv_delay_ms(20);
            LiJiaKongZhi(true);
            H6LED(ON);
        }
    }
}

/**
 * 使用定时器 循环检测IO
 */
void ioCheckInit(SendFrameImpl sendFrame, bool hwInit) {
    SendFrame = std::move(sendFrame);
    if (hwInit) {
        drvCommon_Init();
        drvIoInit(0);
        drvIoOpen();
    }

    drvClkInit(nullptr);

    const UINT32 periodMs = 100;
    const UINT32 ticksCount = periodMs * 1000 / 10;

    drvClkPeriodSet(E_PL_ISR_TIMER0, ticksCount);
    drvClkPeriodSet(E_PL_ISR_TIMER1, ticksCount);

    auto ioCheck0 = [](void*){
        ioCheck(0);
    };
    auto ioCheck1 = [](void*){
        ioCheck(1);
    };
    drvClkIntConnect(E_PL_ISR_TIMER0, ioCheck0, nullptr);
    drvClkIntConnect(E_PL_ISR_TIMER1, ioCheck1, nullptr);
}
