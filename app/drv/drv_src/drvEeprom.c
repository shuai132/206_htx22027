#include <stdio.h>
#include <string.h>
#include "drvDef.h"
#include "drvCfg.h"
#include "drvEeprom.h"
//#include "drvZynqIic.h"
#include "drvIic.h"
#include "drvErro.h"

#define  D_IIC_EEPROM_DEV      0		/*IIC设备编号*/
volatile UINT32 g_eepromAddr = 0;

INT32 drvEepromInit(UINT32 devAddr, UINT32 bps)
{
	if(drvIicInit(0))
	{
		printf("drvEepromInit->iic_%d init failed!\n", D_IIC_EEPROM_DEV);
		return ERRO;
	}
	else
	{
		printf("drvEepromInit->iic_%d init success!\n", D_IIC_EEPROM_DEV);
	}

	if(drvIicOpen(D_IIC_EEPROM_DEV))
	{
		printf("drvEepromInit->iic_%d open failed!\n", D_IIC_EEPROM_DEV);
		return ERRO;
	}
	else
	{
		printf("drvEepromInit->iic_%d open success!\n", D_IIC_EEPROM_DEV);
	}

	if(drvIicParamSet(D_IIC_EEPROM_DEV, bps))
	{
		printf("drvEepromInit->iic_%d braudrate set failed!\n", D_IIC_EEPROM_DEV);
		return ERRO;
	}
	else
	{
		printf("drvEepromInit->iic_%d braudrate set success!\n", D_IIC_EEPROM_DEV);
	}
	g_eepromAddr = devAddr;

	return OK;
}


/******************************************************
 * Func: EEPROM写数据函数
 * param1: 写数据起始地址
 * param2: 待发送的数据指针
 * param3: 待发送的数据长度
 * return：成功返回发送的数据长度，失败返回错误代码
 * ****************************************************/
INT32 drvEepromWriteData(UINT32 startAddr, UINT8 *pBuff, UINT32 ByteCount)
{
	int curPage, endPage, ret;
	int tempLen, dataPoint, i;
	UINT8 sendBuff[D_EEPROM_PAGE_SIZE+4] = {0};
	if(ByteCount == 0)
	{
		printf("drvEepromWriteData->ByteCount is 0!\n");
		return ERRO;
	}
	if((startAddr + ByteCount) > D_EEPROM_ADDR_MAX)
	{
		printf("drvEepromWriteData->Bytes need to write is out of range!\n");
		return ERRO;
	}
	if(pBuff == NULL)
	{
		printf("drvEepromWriteData->Bytes buffer need to send is NULL!\n");
		return ERRO;
	}

	curPage = startAddr / D_EEPROM_PAGE_SIZE + 1; 				/*判断起始页*/
	endPage = (startAddr + ByteCount) / D_EEPROM_PAGE_SIZE; 	/*判断结束页*/
	if((startAddr + ByteCount) % D_EEPROM_PAGE_SIZE)
	{
		endPage += 1;
	}

	dataPoint = 0;
	for(i=curPage; i<=endPage; i++)
	{
		sendBuff[0] = (startAddr + dataPoint) >> 8;
		sendBuff[1] = (startAddr + dataPoint) & 0xff;
		tempLen = i * D_EEPROM_PAGE_SIZE - (dataPoint + startAddr);
		if((dataPoint + tempLen) > ByteCount)		/*数据溢出*/
		{					
			tempLen = ByteCount - dataPoint;
		}
		memcpy(&sendBuff[2], pBuff + dataPoint, tempLen);

		dataPoint += tempLen;
		while(drvIicWrite(D_IIC_EEPROM_DEV, g_eepromAddr, sendBuff, tempLen+2) != (tempLen+2))
		{
#ifdef D_DEBUG_LOG
//			printf("drvEepromWriteData->Page %d write data failed\n", i);
#endif
		}
	}

	return OK;
}

/*****************************************************************************/
/**
* This function reads data from the IIC serial EEPROM into a specified buffer.
*
* @param	BufferPtr contains the address of the data buffer to be filled.
* @param	ByteCount contains the number of bytes in the buffer to be read.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
INT32 drvEepromReadData(UINT32 startAddr, UINT8 *pBuff, UINT32 ByteCount)
{
	int curPage, endPage;
	int tempLen, dataPoint, i;
	UINT8 sendBuff[2] = {0};
	if(ByteCount == 0)
	{
		return ERRO;
	}
	if((startAddr + ByteCount) > D_EEPROM_ADDR_MAX)
	{
		return ERRO;
	}
	if(pBuff == NULL)
	{
		return ERRO;
	}

	curPage = startAddr / D_EEPROM_PAGE_SIZE + 1; 				/*判断起始页*/
	endPage = (startAddr + ByteCount) / D_EEPROM_PAGE_SIZE; 	/*判断结束页*/
	if((startAddr + ByteCount) % D_EEPROM_PAGE_SIZE)
	{
		endPage += 1;
	}

	dataPoint = 0;
	for(i=curPage; i<=endPage; i++)
	{
		sendBuff[0] = (startAddr + dataPoint) >> 8;
		sendBuff[1] = (startAddr + dataPoint) & 0xff;
		tempLen = i * D_EEPROM_PAGE_SIZE - (dataPoint + startAddr);
		if((dataPoint + tempLen) > ByteCount)					/*数据溢出*/
		{					
			tempLen = ByteCount - dataPoint;
		}
		
		drvIicWrite(D_IIC_EEPROM_DEV, g_eepromAddr, sendBuff, 2);
		drvIicRead(D_IIC_EEPROM_DEV, g_eepromAddr, pBuff+dataPoint,  tempLen, 0);
		dataPoint += tempLen;
	}

	return OK;
}
