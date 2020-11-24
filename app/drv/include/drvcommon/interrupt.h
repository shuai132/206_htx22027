/***************************************************************
*filename: interrupt.h
*Ad block include file
*version: 1.00
*platform: sdk
****************************************************************/
#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "drvDef.h"
#include "drvCfg.h"

#define D_INTR_PRIORITY     0xa0


enum EN_INTR_MODE{
	EN_INTR_NONE = 0,
	EN_INTR_HIGH,
	EN_INTR_LOW,
	EN_INTR_RASING,
	EN_INTR_FALLING
};


int drvIntrCtrlInit(void);
int intConnect(UINT32 Intr_Id, void *Handler, void *param);
int intDisconnect(UINT32 Intr_Id, void *Handler, void *param);
int intEnable(UINT32 intrId);
int intDisable(UINT32 intrId);


#endif
