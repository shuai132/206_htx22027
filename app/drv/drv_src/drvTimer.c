#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "drvErro.h"
#include "drvTimer.h"
#include "drvRegister.h"
#include "drvCfg.h"

#ifdef D_OS_ALONE
#include "interrupt.h"
#include "drvCommon.h"
#endif

/**************************** Type Definitions *******************************/
typedef struct
{
	UINT32 u32timer_cnt : 24;
	UINT32 u32Reserved : 5;
	UINT32 u32one_roll : 2;
	UINT32 u32start : 1;
}ST_DRV_TIMER_CFG;

typedef struct
{
    BOOL        timer_ring;
    int         mode;
    BOOL        isOpen;
    FUNCPTIMER  routine;
    void *      param;
}ST_TIMER_STATE;
ST_TIMER_STATE config[6] = {0};

/******************************************************
 * Func: 计时器中断入口函数
 * param1：计时器编号
 * return：执行结果
 * ****************************************************/
LOCAL void usrClkIsr(int index)
{
    if(config[index].isOpen)
    {
        config[index].timer_ring = TRUE;
        if(config[index].routine)
        {
            config[index].routine(config[index].param);
        }

        config[index].timer_ring = FALSE;
        if(config[index].mode == 1)
        	config[index].isOpen = FALSE;
    }
}

/******************************************************
 * Func: 计时器初始化
 * param1：预留参数
 * return：执行结果
 * ****************************************************/
INT32 drvClkInit(void *pvReserve)
{
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 计时器驱动中断回调函数注册函数
 * param1：计时器编号
 * param2：用户回调函数
 * param3：回调参数
 * return：执行结果
 * ****************************************************/
INT32 drvClkIntConnect(UINT32 timerIndex, FUNCPTIMER routine, void *arg)
{
    if(timerIndex >= E_PL_TIMER_NUM) 
    {
#ifdef D_DEBUG_LOG
        printf("drvClkIntConnect->timer num input is not exist!\n");
#endif
        return DRV_ERRNO_CLK_NOT_EXIST;
    }

    int timer_isrNum;
    timer_isrNum = isrTab[timerIndex + E_PL_ISR_TIMER0];
    config[timerIndex].routine = routine;
    config[timerIndex].param = arg;
#ifdef D_OS_ALONE
    intDisconnect(timer_isrNum, (void*)usrClkIsr, (void*)timerIndex);
    intDisable(timer_isrNum);
    intConnect(timer_isrNum, (void*)usrClkIsr, (void*)timerIndex);
#else
    intDisconnect(timer_isrNum, (VOIDFUNCPTR)usrClkIsr, timerIndex);
    intDisable(timer_isrNum);
    intConnect(timer_isrNum, (VOIDFUNCPTR)usrClkIsr, timerIndex);
#endif

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 计时器打开函数
 * param1：计时器编号
 * return：执行结果
 * ****************************************************/
INT32 drvClkOpen(UINT32 timerIndex)
{
    if(timerIndex >= E_PL_TIMER_NUM) 
    {
#ifdef D_DEBUG_LOG
        printf("drvClkOpen->timer num input is not exist!\n");
#endif
        return DRV_ERRNO_CLK_NOT_EXIST;
    }

    UINT32 ret = pl_reg_read(timerIndex*0x1000 + PL_TIMER_CONFIG_ADDR);
    ret = ret | 0x80000000;
    

    config[timerIndex].isOpen = TRUE;
    config[timerIndex].timer_ring = FALSE;
    if(intEnable(isrTab[timerIndex + E_PL_ISR_TIMER0]) != OK)
    {
#ifdef D_DEBUG_LOG
        printf("drvClkOpen->isr enable erro\n");
#endif
        return DRV_ERRNO_CLK_OPEN_FAILED;
    }
    pl_reg_write(timerIndex*0x1000 + PL_TIMER_CONFIG_ADDR, ret);

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 计时器关闭函数
 * param1：计时器编号
 * return：执行结果
 * ****************************************************/
INT32 drvClkClose(UINT32 timerIndex)
{
    if(timerIndex >= E_PL_TIMER_NUM) 
    {
#ifdef D_DEBUG_LOG
        printf("drvClkClose->timer num input is not exist!\n");
#endif
        return DRV_ERRNO_CLK_NOT_EXIST;
    }

    if(intDisable(isrTab[timerIndex + E_PL_ISR_TIMER0]) != OK)
    {
#ifdef D_DEBUG_LOG
         printf("drvClkClose->isr enable erro\n");
#endif
    }

    if(config[timerIndex].isOpen == TRUE)
    {
#ifdef D_OS_ALONE
    	intDisconnect(isrTab[timerIndex + E_PL_ISR_TIMER0], (void*)usrClkIsr, (void*)timerIndex);
#else
		intDisconnect(isrTab[timerIndex + E_PL_ISR_TIMER0], (VOIDFUNCPTR)usrClkIsr, timerIndex);
#endif
		pl_reg_write(timerIndex*0x1000 + PL_TIMER_STOP_CONFIG_ADDR, 1);
		config[timerIndex].isOpen = FALSE;
    }


    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 计时器计时长度设置函数
 * param1：计时器编号
 * param2：计时器长度（精度10us）
 * return：执行结果
 * ****************************************************/
INT32 drvClkPeriodSet (UINT32 timerIndex,UINT32 ticksCount)
{
    if(timerIndex >= E_PL_TIMER_NUM) 
    {
#ifdef D_DEBUG_LOG
        printf("drvClkPeriodSet->timer num input is not exist!\n");
#endif
        return DRV_ERRNO_CLK_NOT_EXIST;
    }
    if(ticksCount > (100000*60))
    {
        ticksCount = 100000*60;
    }
    ST_DRV_TIMER_CFG regValue;
    UINT32 ret = pl_reg_read(timerIndex*0x1000 + PL_TIMER_CONFIG_ADDR);
    regValue = *((ST_DRV_TIMER_CFG *)&ret);
    regValue.u32timer_cnt = ticksCount;
    ret = *((UINT32 * )&regValue);
    pl_reg_write(timerIndex*0x1000 + PL_TIMER_CONFIG_ADDR, ret);

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 计时器工作参数设置函数
 * param1：计时器编号
 * param2：工作模式：2-循环计时，1-单次计时
 * return：执行结果
 * ****************************************************/
INT32 drvClkModeSet(UINT32 timerIndex,UINT32 mode)
{
    if(timerIndex >= E_PL_TIMER_NUM) 
    {
#ifdef D_DEBUG_LOG
        printf("drvClkModeSet->timer num input is not exist!\n");
#endif
        return DRV_ERRNO_CLK_NOT_EXIST;
    }

    ST_DRV_TIMER_CFG regValue;
    UINT32 ret = pl_reg_read(timerIndex*0x1000 + PL_TIMER_CONFIG_ADDR);
    regValue = *((ST_DRV_TIMER_CFG * )&ret);
    regValue.u32one_roll = mode;
    config[timerIndex].mode = mode;
    ret = *((UINT32 * )&regValue);
    pl_reg_write(timerIndex*0x1000 + PL_TIMER_CONFIG_ADDR, ret);
    
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 计时器状态获取函数
 * param1：计时器编号
 * param2：状态指针
 * return：执行结果
 * ****************************************************/
INT32 drvClkQurey(UINT32 timerIndex, UINT16 *pState)
{
    if(timerIndex > 5) 
    {
#ifdef D_DEBUG_LOG
        printf("drvClkQurey->timer num input is not exist!\n");
#endif
        return DRV_ERRNO_CLK_NOT_EXIST;
    }

	if(config[timerIndex].routine)
    {
		if(config[timerIndex].isOpen == TRUE)
        {
			if(config[timerIndex].timer_ring)
            {
				*pState = 3; //connect to the interrupt call , timer is opened , timer_ring is setted.
			}
			else
            {
				*pState = 2; //connect to the interrupt call , timer is opened , timer_ring is not setted.
			}
		}
		else
        {
			*pState = 1; //connect to the interrupt call , timer is closed , timer_ring is not setted.
		}
	}
	else
    {
		*pState = 0; //not connect to the interrupt call , timer is closed , timer_ring is not setted.
	}
    
    return DRV_OPERATE_SUCCESS;
}


/******************************************************
 * Func: 计时器自检函数
 * return：执行结果
 * ****************************************************/
INT32 drvClkCheck(void)
{
    if(drvClkInit(0) != OK)
        return DRV_ERRNO_CLK_CHECK_FAILED;
    return DRV_OPERATE_SUCCESS;
}

