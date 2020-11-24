/***************************************************************
*�ļ����ƣ�drvCfg.h
*�ļ�˵��������ͷ�ļ�
*�汾�ţ�1.00
*����������workbench3.3
****************************************************************/
#ifndef _DRVCFG_H_
#define _DRVCFG_H_

#include "drvDef.h"

#if 1			/*������־��Ϣ�궨��*/
#define D_DEBUG_LOG					
#endif 

#define  DRV_BMC_ADMINISTRATOR_ID   0xFF8729ED      /*����Ա�û�ID*/

/*�豸����ַ����*/
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
/*PL�жϺ�ӳ���*/
volatile INT32 isrTab[16]={61,62,63,64,65,66,67,68,84,85,86,87,88,89,90,91};
#endif

/*ö��PL�豸�ж�ӳ�����0~15*/
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

/*ö���豸����*/
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
 * ����������Ϣ.
 */
typedef struct {
	UINT32 m_IsrNum;    /*�жϺ�*/
	UINT32 m_BaseAddr;  /*�������ַ*/
	UINT32 m_Offset;	/*����ƫ�Ƶ�ַ*/
	UINT32 m_DevNum;  	/*��������*/
} ST_DEV_CONFIG;

enum En_Dev_Offset{
	E_PL_CAN_OFFSET = 0x1000,
};

/*BMC�������������޶���*/
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
