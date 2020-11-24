#ifndef __DRVIIC_H_
#define __DRVIIC_H_
#include "drvDef.h"

enum EN_IIC_SPEED{
	DRV_IIC_SPEED_100K = 100000,
	DRV_IIC_SPEED_400K = 400000,
};

/************************** Function Prototypes ******************************/
INT32 drvIicInit(UINT32 reserve);
INT32 drvIicOpen(INT32 devIndex);
INT32 drvIicClose(INT32 devIndex);
INT32 drvIicParamSet(INT32 devIndex, UINT32  bps);
INT32 drvIicParamGet(INT32 devIndex, UINT32 * bps);
INT32 drvIicWrite(INT32 devIndex,UINT32 dev_addr, UINT8 *pBuff, UINT16 len);
INT32 drvIicRead(INT32 devIndex,  UINT32 addr, UINT8 * pBuff,  UINT16 len, INT32 waitTime);
INT32 drvIicCheck();

#endif
