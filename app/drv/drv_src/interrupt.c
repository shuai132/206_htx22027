/*
 * main.c
 *
 *  Created on: 2020/06/01
 *      Author: liny
 */
#include "interrupt.h"

#include "xil_printf.h"
#include "xparameters.h"
#include "xstatus.h"
#include "stdio.h"

// interrupt library
#include "xil_io.h"
#include "xscugic.h"
#include "xil_exception.h"


#define INTR_CTRL_DEVICE_ID XPAR_SCUGIC_0_DEVICE_ID

#define EN_INTR_0  0x0001
#define EN_INTR_1  0x0002
#define EN_INTR_2  0x0004
#define EN_INTR_3  0x0008
#define EN_INTR_4  0x0010
#define EN_INTR_5  0x0020
#define EN_INTR_6  0x0040
#define EN_INTR_7  0x0080
#define EN_INTR_8  0x0100
#define EN_INTR_9  0x0200
#define EN_INTR_10 0x0400
#define EN_INTR_11 0x0800
#define EN_INTR_12 0x0100
#define EN_INTR_13 0x0200
#define EN_INTR_14 0x0400
#define EN_INTR_15 0x0800

XScuGic IntrCtrller; 	     		 /* Instance of the Interrupt Controller */
static XScuGic_Config *GicConfig;    /* The configuration parameters of the controller */

/******************************************************
 * Func: 中断控制初始化
 * param1：无
 * return：初始化结果
 * ****************************************************/
int drvIntrCtrlInit(void)
{
	int Status ;
	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	GicConfig = XScuGic_LookupConfig(INTR_CTRL_DEVICE_ID);
	if (NULL == GicConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(&IntrCtrller, GicConfig,
					GicConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	printf("intr initial end \n");

	/*
	 * Perform a self-test to ensure that the hardware was built
	 * correctly
	 */
	Status = XScuGic_SelfTest(&IntrCtrller);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	printf("intr selftest end \n");

/*
 * Connect the interrupt controller interrupt handler to the hardware
 * interrupt handling logic in the ARM processor.
 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler,
			&IntrCtrller);
/*
 * Enable interrupts in the ARM
 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

/******************************************************
 * Func: 中断入口函数注册函数
 * param1：PL中断号
 * param1：PL中断入口函数
 * param1：PL参数指针
 * return：执行结果
 * ****************************************************/
int intConnect(UINT32 Intr_Id, void *Handler, void *param)
{
	int Status ;
	/*
	 * Connect a device driver handler that will be called when an
	 * interrupt for the device occurs, the device driver handler performs
	 * the specific interrupt processing for the device
	 */

	Status = XScuGic_Connect(&IntrCtrller, Intr_Id ,
                            (Xil_ExceptionHandler)Handler,
							param);

	if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

	XScuGic_SetPriorityTriggerType(&IntrCtrller, Intr_Id, D_INTR_PRIORITY, EN_INTR_RASING);

	return XST_SUCCESS;
}

/******************************************************
 * Func: 中断入口函数销毁函数
 * param1：PL中断号
 * param1：PL中断入口函数
 * param1：PL参数指针
 * return：执行结果
 * ****************************************************/
int intDisconnect(UINT32 Intr_Id, void *Handler, void *param)
{
	XScuGic_Disconnect(&IntrCtrller, Intr_Id);
	return XST_SUCCESS;
}

/******************************************************
 * Func: 中断使能控制函数
 * param1：PL中断号
 * return：执行结果
 * ****************************************************/
int intEnable(UINT32 intrId)
{
	XScuGic_Enable(&IntrCtrller, intrId );
	return XST_SUCCESS;
}

/******************************************************
 * Func: 中断关闭控制函数
 * param1：PL中断号
 * return：执行结果
 * ****************************************************/
int intDisable(UINT32 intrId)
{
	XScuGic_Disable(&IntrCtrller, intrId );
	return XST_SUCCESS;
}

