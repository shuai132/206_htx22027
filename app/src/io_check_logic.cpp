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

#define DEFINE_IOR_FUNC(NAME)   \
static bool NAME(int num) { \
    return ioRead(IO_##NAME[num*2], IO_##NAME[num*2 + 1]); \
}

DEFINE_IOR_FUNC(DaoDanGongDian)
DEFINE_IOR_FUNC(JieChuBaoXianJianCe)
DEFINE_IOR_FUNC(ZhuDianChiJiHuo)
DEFINE_IOR_FUNC(DuoDianChiJiHuo)
DEFINE_IOR_FUNC(DianHuoDianChiJiHuo)
DEFINE_IOR_FUNC(TanSheZhuangZhiDianHuo)
DEFINE_IOR_FUNC(ZongCeKaiGuan)
DEFINE_IOR_FUNC(FuWeiKaiGuan)

static IOType IO_H1LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_7,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_7};
static IOType IO_H2LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_15,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_15};
static IOType IO_H3LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_13,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_13};
static IOType IO_H4LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_14,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_14};
static IOType IO_H5LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_8,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_8};
static IOType IO_H6LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_9,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_9};
static IOType IO_H7LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_10,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_10};
static IOType IO_H8LED[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_12,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_12};
static IOType IO_LiJiaKongZhi[] =
        {DRV_IO_OUT_GROUP_2, DRV_IO_PIN_11,
         DRV_IO_OUT_GROUP_3, DRV_IO_PIN_11};

enum {
    ON  = true,
    OFF = false,
};

// LED亮灭对应的IO值
#define LED_ON_VALUE  0
#define LED_OFF_VALUE 1

#define DEFINE_IOW_FUNC(NAME)        \
static void NAME(int num, bool on) { \
    drvIoWrite(IO_##NAME[num*2], IO_##NAME[num*2 + 1], on == ON ? LED_ON_VALUE : LED_OFF_VALUE); \
}

DEFINE_IOW_FUNC(H1LED)
DEFINE_IOW_FUNC(H2LED)
DEFINE_IOW_FUNC(H3LED)
DEFINE_IOW_FUNC(H4LED)
DEFINE_IOW_FUNC(H5LED)
DEFINE_IOW_FUNC(H6LED)
DEFINE_IOW_FUNC(H7LED)
DEFINE_IOW_FUNC(H8LED)
DEFINE_IOW_FUNC(LiJiaKongZhi)

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
            H1LED(num, ON);
            s.yigongdian = true;
            drv_delay_ms(1000);
            if (FuWeiKaiGuan(num)) {
                auto& data = RESET_OK_MSG;
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
            LiJiaKongZhi(num, true);
            H6LED(num, ON);
        }
    }
}

void ioCheckInit(SendFrameImpl sendFrame, bool hwInit) {
    SendFrame = std::move(sendFrame);
    if (hwInit) {
        drvCommon_Init();
        drvIoInit(0);
        drvIoOpen();
    }

    /*
    drvClkInit(nullptr);

    const UINT32 ticksCount = IoPeriodCheckMs * 1000 / 10;

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
    */
}

void ioCheckClose() {
    drvClkClose(E_PL_ISR_TIMER0);
    drvClkClose(E_PL_ISR_TIMER1);
}

void ioCheck() {
    ioCheck(0);
    ioCheck(1);
}
