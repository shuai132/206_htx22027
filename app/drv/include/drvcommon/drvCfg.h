/***************************************************************
*文件名称：drvCfg.h
*文件说明：配置头文件
*版本号：1.00
*开发环境：workbench3.3
****************************************************************/
#ifndef _DRVCFG_H_
#define _DRVCFG_H_

#include "drvDef.h"

#if 1			/*调试日志信息宏定义*/
#define D_DEBUG_LOG					
#endif 

#define  DRV_BMC_ADMINISTRATOR_ID   0xFF8729ED      /*管理员用户ID*/

/*设备基地址定义*/
#define PL_GNETIP_BASE_ADDR         (0x70100000)  	//128K->0x20000
#define PL_GNET_BASE_ADDR     		(0x70000000)	//4K->0x1000
#define PL_UART_BASE_ADDR  			(0x70020000)
#define PL_TIMER_BASE_ADDR          (0x70022000)
#define PL_IO_BASE_ADDR       		(0x70028000)
#define PL_XADC_BASE_ADDR           (0x70029000)
#define PL_XADC_CTRL_BASE_ADDR      (0x7002A000)
#define PL_CAN_BASE_ADDR     		(0x7002B000)
#define PL_EMIFF_BASE_ADDR     		(0x7002C000)

#ifndef D_OS_ALONE
/*PL中断号映射表*/
volatile INT32 isrTab[16]={61,62,63,64,65,66,67,68,84,85,86,87,88,89,90,91};
#endif

/*枚举PL设备中断映射序号0~15*/
enum En_DevIsrNum {
	E_PL_ISR_GNET0 = 0,
	E_PL_ISR_GNET1,
	E_PL_ISR_UART0,
	E_PL_ISR_UART1,
	E_PL_ISR_TIMER0,
	E_PL_ISR_TIMER1,
	E_PL_ISR_TIMER2,
	E_PL_ISR_TIMER3,
	E_PL_ISR_TIMER4,
	E_PL_ISR_TIMER5,
	E_PL_ISR_IO,
	E_PL_ISR_CAN,
	E_PL_ISR_AD,
	E_PL_ISR_EMIFF

};

/*枚举设备个数*/
enum En_Dev_Num{
	E_PL_GNET_NUM = 2,
	E_PL_UART_NUM = 2,
	E_PL_TIMER_NUM = 6,
	E_PL_IO_GROUP_NUM = 6,
	E_PL_CAN_NUM = 1,
	E_PS_IIC_NUM = 2,
	E_PS_EMIFF_NUM
};

/**
 * 基本外设信息.
 */
typedef struct {
	UINT32 m_IsrNum;    /*中断号*/
	UINT32 m_BaseAddr;  /*外设基地址*/
	UINT32 m_Offset;	/*外设偏移地址*/
	UINT32 m_DevNum;  	/*外设数量*/
} ST_DEV_CONFIG;

enum En_Dev_Offset{
	E_PL_CAN_OFFSET = 0x1000,
};

/*BMC触发报警上下限定义*/
#define D_CPU_USR_MAX   	80
#define D_TEMPTURE_MIN   	20
#define D_TEMPTURE_MAX   	80
#define D_VLT_VCCINT_MIN 	0.9
#define D_VLT_VCCINT_MAX 	1.1
#define D_VLT_VCCAUX_MIN 	1.7
#define D_VLT_VCCAUX_MAX 	1.9
#define D_VLT_VBRAM_MIN 	0.9
#define D_VLT_VBRAM_MAX 	1.1
#define D_VLT_VCCPINT_MIN 	0.8
#define D_VLT_VCCPINT_MAX 	1.1
#define D_VLT_VCPPAUX_MIN 	1.7
#define D_VLT_VCPPAUX_MAX 	1.9


#endif
