/***************************************************************
*filename: drvTimer.h
*Timer block include file
*version: 1.00
*platform: vxworks
****************************************************************/

#ifndef _DRVTIMER_H_
#define _DRVTIMER_H_

#include "drvDef.h"


typedef void(*FUNCPTIMER)(void*);   /*param£º¶¨Ê±Æ÷±àºÅ*/

/************************** Function Prototypes ******************************/
INT32 drvClkInit(void *pvReserve);

INT32 drvClkPeriodSet (UINT32 timerIndex, UINT32 ticksCount);
INT32 drvClkModeSet(UINT32 timerIndex,UINT32 mode);
INT32 drvClkIntConnect(UINT32 timerIndex,FUNCPTIMER routine, void *arg);

INT32 drvClkOpen(UINT32 timerIndex);
INT32 drvClkClose(UINT32 timerIndex);
INT32 drvClkQurey(UINT32 timerIndex, UINT16 *pState);
INT32 drvClkCheck(void);


#endif
