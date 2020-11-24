/***************************************************************
*filename: drvAdc.h
*Ad block include file
*version: 1.00
*platform: vxworks
****************************************************************/
#ifndef _DRVGNET_H_
#define _DRVGNET_H_
#include "drvDef.h"

//#define  PORT   /*�л����ݳ��ȴ�С��*/

#define D_GNET_DATALEN_MAX    (1500)

typedef union{ 
	struct _st_data{
		UINT8 dst_mac[6];
		UINT8 src_mac[6];
		UINT8 data_len[2];
		UINT8 sbuf[D_GNET_DATALEN_MAX];
	}st_data;
	UINT8 ubuf[D_GNET_DATALEN_MAX+14];
}ST_DATA_BUFF;

typedef void(*FUNCPGNET)(UINT32, UINT32, ST_DATA_BUFF*, UINT32); //1.���ڱ�ţ� 2.֡״̬��3.����ָ�룬4.���ݳ���

INT32 drvGnetInit(void);
INT32 drvGnetIntrConnect(FUNCPGNET routine);
INT32 drvGnetOpen(UINT32 num, UINT8 *src_mac);
INT32 drvGnetClose(UINT32 num);
INT32 drvGnetRead(UINT32 num, ST_DATA_BUFF *pBuff, INT32 waitTime);
INT32 drvGnetWrite(UINT32 num, UINT8 *dst_mac, UINT8 *pBuff, UINT32 len);
INT32 drvGnetCheck(UINT16 comNum_in, INT32 testMod);

#endif
