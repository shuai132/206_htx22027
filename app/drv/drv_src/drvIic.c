#include <stdint.h>
#include <stdio.h>
#include "drvDef.h"
#include "drvIic.h"
#include "drvErro.h"
#include "drvZynqIic.h"
#include "drvCfg.h"

#define MAX_I2C_UNIT  	2
UINT32  g_iicBps[2];
XIicPs	Iic[E_PS_IIC_NUM];			/* Instance of the IIC Device */

/******************************************************
 * Func: IIC设备初始化函数
 * param1: 预留参数
 * return：成功返回0，失败返回错误代码
 * ****************************************************/
INT32 drvIicInit(UINT32 reserve)
{
	int Status, devIndex;
	XIicPs_Config *Config;
	g_iicBps[0] = DRV_IIC_SPEED_100K;
	g_iicBps[1] = DRV_IIC_SPEED_100K;

	/*
	 * Initialize the IIC driver so that it's ready to use
	 * Look up the configuration in the config table,
	 * then initialize it.
	 */
	for(devIndex=0; devIndex<E_PS_IIC_NUM; devIndex++)
	{
		Config = XIicPs_LookupConfig(devIndex);
		if (NULL == Config) 
		{
			return DRV_ERRNO_IIC_INIT_FAILED;
		}

		Status = XIicPs_CfgInitialize(&Iic[devIndex], Config, Config->BaseAddress);
		if (Status != OK) 
		{
			return DRV_ERRNO_IIC_INIT_FAILED;
		}

		/*
		 * Perform a self-test to ensure that the hardware was built correctly.
		 */
		Status = XIicPs_SelfTest(&Iic[devIndex]);
		if (Status != OK) 
		{
			return DRV_ERRNO_IIC_INIT_FAILED;
		}
	}

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IIC设备打开函数
 * param1: IIC设备号（0—1）
 * return：成功返回0，失败返回错误代码
 * ****************************************************/
INT32 drvIicOpen(INT32 devIndex)
{
	int Status;
	XIicPs_Config *Config;

    if(devIndex >= E_PS_IIC_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvIicOpen->iic device number invalid\n");
#endif
        return DRV_ERRNO_IIC_NOT_EXIST;
    }

	/*
	 * Initialize the IIC driver so that it's ready to use
	 * Look up the configuration in the config table,
	 * then initialize it.
	 */
	Config = XIicPs_LookupConfig(devIndex);
	if (NULL == Config) 
	{
		return DRV_ERRNO_IIC_OPEN_FAILED;
	}

	Status = XIicPs_CfgInitialize(&Iic[devIndex], Config, Config->BaseAddress);
	if (Status != OK) 
	{
		return DRV_ERRNO_IIC_OPEN_FAILED;
	}

	/*
	 * Set the IIC serial clock rate.
	 */
	if(drvIicPs_SetSClk(&Iic[devIndex], g_iicBps[devIndex]) != OK)
	{
#ifdef D_DEBUG_LOG
		printf("drvIicOpen->IIC braudrate set failed\n");
#endif
		return DRV_ERRNO_IIC_OPEN_FAILED;
	}

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IIC设备关闭函数
 * param1: IIC设备号（0—1）
 * return：成功返回0，失败返回错误代码
 * ****************************************************/
INT32 drvIicClose(INT32 devIndex)
{
    if(devIndex >= E_PS_IIC_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvIicParamSet->iic device number invalid\n");
#endif
        return DRV_ERRNO_IIC_PARARM_INVALID;
    }

	XIicPs_Reset(&Iic[devIndex]);
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IIC设备参数设置函数
 * param1: IIC设备号（0—1）
 * param2: clk读写时钟频率
 * return：成功返回0，失败返回错误代码
 * ****************************************************/
INT32 drvIicParamSet(INT32 devIndex, UINT32 bps)
{
    if(devIndex >= 2)
	{
#ifdef D_DEBUG_LOG
        printf("drvIicParamSet->iic device number invalid\n");
#endif
        return DRV_ERRNO_IIC_NOT_EXIST;
    }

    if((bps > DRV_IIC_SPEED_400K) || (bps < DRV_IIC_SPEED_100K))
	{
#ifdef D_DEBUG_LOG
        printf("drvIicParamSet->iic device bps param invalid\n");
#endif
        return DRV_ERRNO_IIC_PARARM_INVALID;
    }

	/*
	 * Set the IIC serial clock rate.
	 */
	if(drvIicPs_SetSClk(&Iic[devIndex], bps) != OK)
	{
#ifdef D_DEBUG_LOG
		printf("drvIicParamSet->IIC braudrate set failed\n");
#endif
		return DRV_ERRNO_IIC_PARARM_SET_FAILED;
	}

	g_iicBps[devIndex] = bps;

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IIC设备参数设置函数
 * param1: IIC设备号（0—1）
 * param2: clk读写时钟频率指针
 * return：成功返回0，失败返回错误代码
 * ****************************************************/
INT32 drvIicParamGet(INT32 devIndex, UINT32 *bps)
{
    if(devIndex >= 2)
	{
#ifdef D_DEBUG_LOG
        printf("drvIicParamGet->iic device number invalid\n");
#endif
        return DRV_ERRNO_IIC_NOT_EXIST;
    }

    if(bps == NULL){
#ifdef D_DEBUG_LOG
        printf("drvIicParamGet->bps ptr param invalid\n");
#endif
        return DRV_ERRNO_IIC_PARARM_INVALID;
    }

    *bps = g_iicBps[devIndex];
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IIC总线发送数据函数
 * param1: IIC设备号（0—1）
 * param2: 设备地址
 * param3: 待发送的数据指针
 * param4: 待发送的数据长度
 * return：成功返回发送的数据长度，失败返回错误代码
 * ****************************************************/
INT32 drvIicWrite(INT32 devIndex, UINT32 dev_addr, UINT8 *pBuff, UINT16 len)
{
	INT32 Status;

	while (XIicPs_BusIsBusy(&Iic[devIndex]));		//总线忙判断
	Status = XIicPs_MasterSendPolled(&Iic[devIndex], pBuff, len, dev_addr);
	if (Status != OK) 
	{
		return DRV_ERRNO_IIC_WRITE_FAILED;
	}
    return len;
}

/******************************************************
 * Func: IIC总线读数据函数
 * param1: IIC设备号（0—1）
 * param2: 设备地址
 * param3: 待接收的数据指针
 * param4: 待接收的数据长度
 * param5: 总线接收数据超时时间
 * return：成功返回接收的数据长度，失败返回错误代码
 * ****************************************************/
INT32 drvIicRead(INT32 devIndex, UINT32 dev_addr, UINT8 *pBuff,  UINT16 len, INT32 waitTime)
{
	INT32 Status;

	while (XIicPs_BusIsBusy(&Iic[devIndex]));		//总线忙判断
	Status = XIicPs_MasterRecvPolled(&Iic[devIndex], pBuff, len, dev_addr);
	if (Status != OK) {
		return DRV_ERRNO_IIC_READ_FAILED;
	}
    return len;
}

/******************************************************
 * Func: IIC设备自检函数
 * param1: 无
 * return：成功返回0，失败返回错误代码
 * ****************************************************/
INT32 drvIicCheck(void)
{
    return DRV_OPERATE_SUCCESS;
}
