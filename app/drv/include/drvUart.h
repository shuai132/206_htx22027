/***************************************************************
*filename: drvUart.h
*uart block include file
*version: 1.00
*platform: vxworks
****************************************************************/

#ifndef _DRVUART_H_
#define _DRVUART_H_
#include "drvDef.h"

#define  SFIFO_LEN_MAX   2048 	/*最大发送FIFO长度*/
#define  RFIFO_LEN_MAX   2048 	/*最大接收FIFO长度*/

typedef enum {
	DRV_BRAUD_9600 = 9600,
	DRV_BRAUD_19200 = 19200,
	DRV_BRAUD_38400 = 38400,
	DRV_BRAUD_115200 = 115200,
	DRV_BRAUD_230400 = 230400,
	DRV_BRAUD_460800 = 460800
}DRV_RS_BRADERATE_EN;

typedef enum {
	DRV_PARITY_NONE = 0,
	DRV_PARITY_ODD = 1,
	DRV_PARITY_EVEN = 2,
}DRV_RS_PARITY_EN;

typedef enum {
	DRV_DATA_BITS_6 = 6,
	DRV_DATA_BITS_7 = 7,
	DRV_DATA_BITS_8 = 8,
}DRV_RS_DATA_BITS_EN;

enum DRV_RS_STOP_BITS_EN{
	DRV_STOP_BITS_1 = 1,
	DRV_STOP_BITS_2 = 2,
};

typedef struct st_Drv_Rs_Cfg{
	INT32 baudarate;	
	INT32 async_parity;	
	INT32 data_bits_num;
	INT32 stop_bits_num;
	BOOL isr_enable;
}DRV_RS_CFG_ST;

enum DRV_RS_RECV_STATE_EN{
	DRV_RX_OK = 0,				/*数据ok*/
	DRV_RX_FIFO_FULL = 0x01,	/*接收FIFO溢出*/
	DRV_RX_PARITY_ERRO = 0x02,	/*帧数据奇偶校验错误*/
};

typedef void(*FUNCPUART)(UINT32, UINT32, UINT8*, UINT32); //1.串口编号， 2.帧状态，3.数据指针，4.数据长度

INT32 drvRsComInit(UINT32 reserve);
INT32 drvRsOpen(UINT32 comNum, UINT16 mode);
INT32 drvRsClose(UINT32 comNum);
INT32 drvRsIntrConnect(FUNCPUART routine);
INT32 drvRsParamSet(UINT32 comNum, DRV_RS_CFG_ST cfg);
INT32 drvRsParamGet(UINT32 comNum, DRV_RS_CFG_ST *pCfg);
INT32 drvRsSend(UINT32 comNum, UINT8 *pBuff, UINT32 len);
INT32 drvRsRecv(UINT32 comNum,UINT8 *pBuff, UINT32 len, INT32 waitTime);
INT32 drvRsCheck(UINT32 comNum);

#endif
