/***************************************************************
*filename: drvIo.h
*IO block include file
*version: 1.00
*platform: vxworks
****************************************************************/
#ifndef _DRVIO_H_
#define _DRVIO_H_

#ifdef D_OS_ALONE
#include "drvDef.h"			/*add 2020.11.3*/
#endif

#include "drvDef.h"
#ifndef D_OS_ALONE
#include <vxWorks.h>
#endif

typedef enum {
	ISR_MODE_NONE = 0,		/*��ʹ���ж�*/
	ISR_MODE_UP = 1,   		/*�����ش���*/
	ISR_MODE_FALLING = 2,   /*�½��ش���*/
	ISR_MODE_TRIGGER = 3   	/*�����ػ��½��ش���*/
}DRV_IO_ISR_TYPE_EN;

typedef enum {
	DRV_IO_INOUT_GROUP_0 = 0,
	DRV_IO_INOUT_GROUP_1,
	DRV_IO_INOUT_GROUP_2,
	DRV_IO_OUT_GROUP_0,
	DRV_IO_OUT_GROUP_1,
	DRV_IO_OUT_GROUP_2
}DRV_IO_GROUP_EN;

typedef enum{
	DRV_IO_PIN_ALL = 0xffffffff,
	DRV_IO_PIN_0 = 0x01,
	DRV_IO_PIN_1 = 0x02,
	DRV_IO_PIN_2 = 0x04,
	DRV_IO_PIN_3 = 0x08,
	DRV_IO_PIN_4 = 0x10,
	DRV_IO_PIN_5 = 0x20,
	DRV_IO_PIN_6 = 0x40,
	DRV_IO_PIN_7 = 0x80,
	DRV_IO_PIN_8 = 0x100,
	DRV_IO_PIN_9 = 0x200,
	DRV_IO_PIN_10 = 0x400,
	DRV_IO_PIN_11 = 0x800,
	DRV_IO_PIN_12 = 0x1000,
	DRV_IO_PIN_13 = 0x2000,
	DRV_IO_PIN_14 = 0x4000,
	DRV_IO_PIN_15 = 0x8000,
	DRV_IO_PIN_16 = 0x10000,
	DRV_IO_PIN_17 = 0x20000,
	DRV_IO_PIN_18 = 0x40000,
	DRV_IO_PIN_19 = 0x80000,
	DRV_IO_PIN_20 = 0x100000,
	DRV_IO_PIN_21 = 0x200000,
	DRV_IO_PIN_22 = 0x400000,
	DRV_IO_PIN_23 = 0x800000,
	DRV_IO_PIN_24 = 0x1000000,
	DRV_IO_PIN_25 = 0x2000000,
	DRV_IO_PIN_26 = 0x4000000,
	DRV_IO_PIN_27 = 0x8000000,
	DRV_IO_PIN_28 = 0x10000000,
	DRV_IO_PIN_29 = 0x20000000,
	DRV_IO_PIN_30 = 0x40000000,
	DRV_IO_PIN_31 = 0x80000000
}DRV_IO_PIN_EN;

typedef struct st_Drv_Io_Cfg{
	DRV_IO_GROUP_EN group;		/*IO ���*/
	UINT32 pin;					/*IO pin��*/
	UINT32 mode;				/*IO�������ģʽ*/
	UINT32 isr;					/*IO�жϷ�ʽѡ��*/
} DRV_IO_CFG_ST;

typedef void(*FUNCPIO)(DRV_IO_GROUP_EN, DRV_IO_PIN_EN, UINT32); //1.��ţ�2.PIN��3.״ֵ̬

INT32 drvIoInit(UINT32 reserve);
INT32 drvIoOpen(void);
INT32 drvIoIntrConnect(FUNCPIO routine);
INT32 drvIoModeSet(UINT32 chnoNum, UINT32 type);
INT32 drvIoParamSet(UINT32 chnoNum, DRV_IO_CFG_ST *cfg);
INT32 drvIoWrite(UINT32 chnoNum, UINT32 pin, UINT32 outData);
INT32 drvIoRead(UINT32 chnoNum, UINT32 pin, UINT32 *inData, INT32  waitTime);
INT32 drvIoCheck(UINT32 reserve);

#endif
