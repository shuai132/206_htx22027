/***************************************************************
*filename: drvAdc.h
*Ad block include file
*version: 1.00
*platform: vxworks
****************************************************************/
#ifndef _DRVADC_H_
#define _DRVADC_H_

#include "drvDef.h"

/*AD采样频率典型值，取值范围10k~50k*/
enum DRV_AD_SPEED_EN 
{
	DRV_AD_BRAD_10K = 10000,
	DRV_AD_BRAD_20K = 20000,
	DRV_AD_BRAD_30K = 30000,
	DRV_AD_BRAD_40K = 40000,
	DRV_AD_BRAD_50K = 50000
};

/*AD采样通道选择*/
typedef enum  
{
	DRV_AD_CHNO_0 	= 0x0001,
	DRV_AD_CHNO_1 	= 0x0002,
	DRV_AD_CHNO_2 	= 0x0004,
	DRV_AD_CHNO_3 	= 0x0008,
	DRV_AD_CHNO_4 	= 0x0010,
	DRV_AD_CHNO_5 	= 0x0020,
	DRV_AD_CHNO_6 	= 0x0040,
	DRV_AD_CHNO_7 	= 0x0080,
	DRV_AD_CHNO_8 	= 0x0100,
	DRV_AD_CHNO_9 	= 0x0200,
	DRV_AD_CHNO_10	= 0x0400,
	DRV_AD_CHNO_All	= 0x07ff
}DRV_AD_CHNOSEL_EN;

/*AD求平均采样点数*/
typedef enum  
{
	DRV_AD_AVG_16 	= 0x1000,
	DRV_AD_AVG_64 	= 0x2000,
	DRV_AD_AVG_256 	= 0x3000
}DRV_AD_AVG_EN;

typedef struct st_Drv_Ad_Cfg
{
	INT32 bits;					/*采样分辨率*/
	INT32 chnobits;				/*通道使能配置，bit0~bit15*/
	INT32 baudrate;				/*采样频率*/
	INT32 mode;					/*采样模式：1-循环采样，0-单次采 */
} DRV_AD_CFG_ST;

typedef struct st_Drv_Ad_Cfg1
{
	INT16 m_chno1;					/*第一个采样通道,按bit位有效*/
	INT16 m_cnt1;					/*第一个通道采样次数*/
	INT16 m_chno2;					/*第二个采样通道,按bit位有效*/
	INT16 m_cnt2;					/*第二个通道采样次数*/
	INT16 m_chno3;					/*第三个采样通道,按bit位有效*/
	INT16 m_cnt3;					/*第三个通道采样次数*/
} DRV_AD_BIGDATA_ST;


typedef struct st_Drv_Ad_Info
{
	float m_tempture;			/*FPGA 温度*/
	float m_vccint;				/*vccint*/
	float m_vccaux;				/*vccaux*/
	float m_vbram;				/*vccbram*/
	float m_vccpint;			/*vccpint*/
	float m_vcppaux;			/*vcppaux*/
}DRV_AD_DEVINFO_ST;

typedef void(*FUNCPAD)(UINT32, UINT32, UINT16*);   /*param：采样结果、采样数量值、采样结果值*/

/************************** Function Prototypes ******************************/

INT32 drvAdInit(UINT32  reserve);
INT32 drvAdParamSet(DRV_AD_CFG_ST *pCfg);
INT32 drvAdIntConnect(FUNCPAD routine);
INT32 drvAdRead(UINT16 chno, UINT16 *pBuff);
INT32 drvAdBigDataSet(DRV_AD_BIGDATA_ST *pCfg);
INT32 drvAdBigDataRead(UINT16 *pData, INT32 timeout);
INT32 drvAdAverageRead(DRV_AD_CHNOSEL_EN chno, DRV_AD_AVG_EN times, UINT16 *pData, INT32 timeout);
INT32 drvAdCheck(void);

INT32 drvAdDevicInfoGet(DRV_AD_DEVINFO_ST *pInfo);

#endif
