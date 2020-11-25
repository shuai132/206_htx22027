#include <cassert>
#include <cstring>

#include "io_check_logic.h"
#include "config.h"

extern "C" {
#include "drvIo.h"
#include "drvErro.h"
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

static bool ioRead(int group, int pin) {
    UINT32 data;
    auto ret = drvIoRead(group, pin, &data, 0);
    assert(ret == DRV_OPERATE_SUCCESS);
    return data == 0;
}

using IOType = int;
static IOType IO_DaoDanGongDian[] =
        {DRV_IO_INOUT_GROUP_5, DRV_IO_PIN_3,
         DRV_IO_INOUT_GROUP_5, DRV_IO_PIN_5};
static IOType IO_JieChuBaoXianJianCe[] =
        {DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_27,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_28};
static IOType IO_ZhuDianChiJiHuo[] =
        {DRV_IO_INOUT_GROUP_5, DRV_IO_PIN_4,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_27};
static IOType IO_DuoDianChiJiHuo[] =
        {DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_4,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_4};
static IOType IO_DianHuoDianChiJiHuo[] =
        {DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_0,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_0};
static IOType IO_TanSheZhuangZhiDianHuo[] =
        {DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_1,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_1};
static IOType IO_ZongCeKaiGuan[] =
        {DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_10,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_10};
static IOType IO_FuWeiKaiGuan[] =
        {DRV_IO_INOUT_GROUP_0, DRV_IO_PIN_9,
         DRV_IO_INOUT_GROUP_1, DRV_IO_PIN_9};


#define DEFINE_FUNC(FUNCNAME)   \
static bool FUNCNAME(int num) { \
    return ioRead(IO_##FUNCNAME[num*2], IO_##FUNCNAME[num*2]); \
}

DEFINE_FUNC(DaoDanGongDian)
DEFINE_FUNC(JieChuBaoXianJianCe)
DEFINE_FUNC(ZhuDianChiJiHuo)
DEFINE_FUNC(DuoDianChiJiHuo)
DEFINE_FUNC(DianHuoDianChiJiHuo)
DEFINE_FUNC(TanSheZhuangZhiDianHuo)
DEFINE_FUNC(ZongCeKaiGuan)
DEFINE_FUNC(FuWeiKaiGuan)

static void H1LED(int num, bool on)
{
    // H9
}
static void H2LED(int num, bool on)
{
    // H10
}
static void H3LED(int num, bool on)
{
    // H11
}
static void H4LED(int num, bool on)
{
    // H12
}
static void H5LED(int num, bool on)
{
    // H13
}
static void H6LED(int num, bool on)
{
    // H14
}
static void LiJiaKongZhi(bool on)
{
}

enum {
    ON  = true,
    OFF = false,
};

static void ioCheck(int num) {
    assert(0 <= num and num < HW_NUM);
    auto& s = state[num];

    if (s.yigongdian) {
        if (DaoDanGongDian(num)) {
            H1LED(num, OFF);
            s.yigongdian = false;
        }
    } else {
        if (DaoDanGongDian(num)) {
            drv_delay_ms(10);
            H2LED(num, ON);
            s.yigongdian = true;
            if (FuWeiKaiGuan(num)) {
                // todo
                auto data = "XXXXXX Reset OK";
                SendFrame(num, 0x00, Frame(data, data + strlen(data)));
            }
        }
    }

    if (JieChuBaoXianJianCe(num)) {
        H2LED(num, ON);
        s.jiebao = true;
    }

    if (ZhuDianChiJiHuo(num)) {
        H3LED(num, ON);
        s.zhudianchijihuo = true;
    }

    if (DuoDianChiJiHuo(num)) {
        H4LED(num, ON);
        s.duodianchijihuo = true;
    }

    if (DianHuoDianChiJiHuo(num)) {
        H5LED(num, ON);
        s.dianhuodianchijihuo = true;
    }

    if (TanSheZhuangZhiDianHuo(num)) {
        if (ZongCeKaiGuan(num)) {
            drv_delay_ms(20);
            LiJiaKongZhi(true);
            H6LED(num, ON);
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
    drvClkModeSet(E_PL_ISR_TIMER0, 2);
    drvClkModeSet(E_PL_ISR_TIMER1, 2);

    auto ioCheck0 = [](void*){
        ioCheck(0);
    };
    auto ioCheck1 = [](void*){
        ioCheck(1);
    };
    drvClkIntConnect(E_PL_ISR_TIMER0, ioCheck0, nullptr);
    drvClkIntConnect(E_PL_ISR_TIMER1, ioCheck1, nullptr);

    drvClkOpen(E_PL_ISR_TIMER0);
    drvClkOpen(E_PL_ISR_TIMER1);
}

void ioCheckClose() {
    drvClkClose(E_PL_ISR_TIMER0);
    drvClkClose(E_PL_ISR_TIMER1);
}
