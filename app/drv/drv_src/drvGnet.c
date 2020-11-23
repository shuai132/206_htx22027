#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "drvGnet.h"
#include "drvRegister.h"
#include "drvErro.h"

#ifdef D_OS_ALONE
#include "interrupt.h"
#include "drvCommon.h"
#endif

typedef struct{
	BOOL isOpen[E_PL_GNET_NUM];
	UINT8 srcMac[E_PL_GNET_NUM][12];
	FUNCPGNET  routline;
}ST_GNET_STATE;

ST_DATA_BUFF *gNetsBuf[E_PL_GNET_NUM];
ST_DATA_BUFF *gNetrBuf[E_PL_GNET_NUM];
ST_GNET_STATE m_gnet_sta;

/******************************************************
 * Func: 光网口驱动中断入口函数
 * param1：光网口编号
 * return：无
 * ****************************************************/
LOCAL void usrGnetIsr(int index)
{	
	UINT32 result, tmpData, ret, u8len, u32len, i;
    if(gNetrBuf[index] == NULL){
        return;
    }
	memset(gNetrBuf[index], 0, sizeof(ST_DATA_BUFF));
    
	if(m_gnet_sta.routline)
	{	
	    ret = pl_reg_read(PL_GNET_FIFO_STATE_ADDR + 0x10000 * index); 		
		if(ret & 0x02){
			return;
		}
		if(ret & 0x80000000)
			result = 1;
		else
			result = 0;
		
		u8len = pl_reg_read(PL_GNET_RFIFO_LEN_ADDR + 0x10000 * index);
		if(u8len == 0){
			return;
		}
		else if(u8len%4)
			u32len = u8len/4 + 1;
		else
			u32len = u8len/4;
		
		for(i=0;i<u32len;i++){
			tmpData = pl_reg_read(PL_GNET_RFIFO_DATA_ADDR + 0x10000 * index);
			gNetrBuf[index]->ubuf[(i << 2) + 0] = (tmpData >> 24) & 0xff;
			gNetrBuf[index]->ubuf[(i << 2) + 1] = (tmpData >> 16) & 0xff;
			gNetrBuf[index]->ubuf[(i << 2) + 2] = (tmpData >> 8) & 0xff;
			gNetrBuf[index]->ubuf[(i << 2) + 3] = (tmpData) & 0xff;
//			logMsg("%08x\n", tmpData, 3, 4, 5, 6);
		}
#ifndef PORT		
		u8len = *(UINT16*)gNetrBuf[index]->st_data.data_len;	
#else
		u8len = gNetrBuf[index]->st_data.data_len[1];
#endif
	//	logMsg("data len: %d\n", u8len, 3, 4, 5, 6);	
		result = 0;
		m_gnet_sta.routline(index, result, gNetrBuf[index], u8len);
	}
}


/******************************************************
 * Func: 光网口初始化函数
 * param1：无
 * return：初始化结果
 * ****************************************************/
INT32 drvGnetInit(void)
{
	int i;
	for(i=0;i<E_PL_GNET_NUM;i++){
		pl_reg_write(PL_GNET_IP_CFG1 + 0x20000 * i, 0x53);
		drv_delay_ms(5);
		pl_reg_write(PL_GNET_IP_CFG2 + 0x20000 * i, 0x140);
		drv_delay_ms(5);
		pl_reg_write(PL_GNET_IP_CFG3 + 0x20000 * i, 0x1004800);
		drv_delay_ms(5);
		pl_reg_write(PL_GNET_IP_CFG4 + 0x20000 * i, 0x90000000);
		drv_delay_ms(5);
		pl_reg_write(PL_GNET_IP_CFG5 + 0x20000 * i, 0x92000000);
		drv_delay_ms(5);
		pl_reg_write(PL_GNET_IP_CFG6 + 0x20000 * i, 0x20);
		
		m_gnet_sta.isOpen[i] = FALSE;
	}
	m_gnet_sta.routline = NULL;
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 光网口用户中断处理注册函数
 * param1：用户中断服务函数指针
 * return：执行结果
 * ****************************************************/
INT32 drvGnetIntrConnect(FUNCPGNET routine)
{
    if(routine != NULL)
    	m_gnet_sta.routline = routine;
    else
    	return DRV_ERRNO_GNET_PARARM_INVALID;
    
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 光网口打开函数
 * param1：广网口编号，取值范围0~1
 * param2：源mac地址
 * return：初始化结果
 * ****************************************************/
INT32 drvGnetOpen(UINT32 num, UINT8 *src_mac)
{	
	int isr_num;
    if(num >= E_PL_GNET_NUM){
#ifdef D_DEBUG_LOG
        printf("drvGnetOpen->invalid gnet num input\n");
#endif
        return DRV_ERRNO_GNET_NOT_EXIST;
    }
    if(src_mac == NULL){
#ifdef D_DEBUG_LOG
        printf("drvGnetOpen->invalid param src_mac input\n");
#endif
        return DRV_ERRNO_GNET_PARARM_INVALID;
    }
    
    if(gNetsBuf[num] == NULL){
        gNetsBuf[num] = (ST_DATA_BUFF*)malloc(sizeof(ST_DATA_BUFF));
    	if(gNetsBuf[num] == NULL){
    		printf("drvGnetOpen->ram space is not enough!\n");
    		return DRV_ERRNO_GNET_INIT_FAILED;
    	}
    }
    if(gNetrBuf[num] == NULL){
        gNetrBuf[num] = (ST_DATA_BUFF*)malloc(sizeof(ST_DATA_BUFF));
    	if(gNetrBuf[num] == NULL){
    		printf("erro: ram space is not enough!\n");
    		return DRV_ERRNO_GNET_INIT_FAILED;
    	}
    }
	memset(gNetsBuf[num], 0, sizeof(ST_DATA_BUFF));
	
	pl_reg_write(PL_GNET_CFG1_ADDR + 0x10000 * num, 0x20);
	drv_delay_ms(5);
	pl_reg_write(PL_GNET_CFG2_ADDR + 0x10000 * num, 0x1040);
	
	memcpy(m_gnet_sta.srcMac[num], src_mac, 12);
	m_gnet_sta.isOpen[num] = TRUE;
	
	pl_reg_write(num*0x10000+PL_GNET_FIFO_RST_ADDR, (0x00|0x80000000)); //FIFO 复位+中断使能
	
	isr_num = isrTab[E_PL_ISR_GNET0 + num];
#ifdef D_OS_ALONE
    intDisconnect(isr_num, (void*)usrGnetIsr, (void*)num);
    intDisable(isr_num);
    intConnect(isr_num, (void*)usrGnetIsr, (void*)num);
#else
    intDisconnect(isr_num, (VOIDFUNCPTR)usrGnetIsr, num);
    intDisable(isr_num);
    intConnect(isr_num, (VOIDFUNCPTR)usrGnetIsr, num);
#endif
	if(intEnable(isrTab[E_PL_ISR_GNET0 + num]) != OK){
#ifdef D_DEBUG_LOG
		printf("drvGnetOpen->isr enable erro\n");
#endif
		return DRV_ERRNO_GNET_INIT_FAILED;
	}
		
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 光网口关闭函数
 * param1：光网口设备编号
 * return：执行结果
 * ****************************************************/
INT32 drvGnetClose(UINT32 num)
{
    if(num >= E_PL_GNET_NUM){
#ifdef D_DEBUG_LOG
        printf("drvGnetClose->invalid gnet num input\n");
#endif
        return DRV_ERRNO_GNET_NOT_EXIST;
    }

    pl_reg_write(num*0x10000+PL_GNET_FIFO_RST_ADDR, 0x00); //FIFO 复位

    m_gnet_sta.isOpen[num] = FALSE;
    m_gnet_sta.routline = NULL;
    
#ifdef D_OS_ALONE
    intDisconnect(isrTab[E_PL_ISR_GNET0 + num], (void*)usrGnetIsr, (void*)num);
#else
	intDisconnect(isrTab[E_PL_ISR_GNET0 + num], (VOIDFUNCPTR)usrGnetIsr, num);
#endif
	intDisable(isrTab[E_PL_ISR_GNET0 + num]);
	
	free(gNetsBuf[num]);
	gNetsBuf[num] = NULL;
	free(gNetrBuf[num]);
	gNetrBuf[num] = NULL;
	
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: 光网口读数据函数
 * param1：广网口编号，取值范围0~1
 * param2：取数据缓冲区
 * param3：读数据超时时间,精度1us
 * return：读数据长度或错误码
 * ****************************************************/
INT32 drvGnetRead(UINT32 num, ST_DATA_BUFF *pBuff, INT32 waitTime)
{
	UINT32 tmpData, ret, u8len, u32len, cnt, i;
    if(num >= E_PL_GNET_NUM){
#ifdef D_DEBUG_LOG
        printf("drvGnetRead->invalid gnet num input\n");
#endif
        return DRV_ERRNO_GNET_NOT_EXIST;
    }
    if(pBuff == NULL){
#ifdef D_DEBUG_LOG
        printf("drvGnetRead->invalid param pBuff input\n");
#endif
        return DRV_ERRNO_GNET_PARARM_INVALID;
    }

    ret = pl_reg_read(PL_GNET_FIFO_STATE_ADDR + 0x10000 * num); 
	if(waitTime == -1){			//判断FIFO是否为空
		while((ret & 0x02)){
			drv_delay_us(10);
			ret = pl_reg_read(PL_GNET_FIFO_STATE_ADDR + 0x10000 * num); 
		}
	}
	else if(waitTime > 0){
		if(waitTime < 10)
			cnt = 1;
		else
			cnt = waitTime/10;
		while(cnt--){
			if((ret & 0x02) == 0)
				break;
			drv_delay_us(10);
			ret = pl_reg_read(PL_GNET_FIFO_STATE_ADDR + 0x10000 * num); 
		}
		if(ret & 0x02){
			return DRV_ERRNO_GNET_READ_BUF_NULL;
		}
	}
	else if(ret & 0x02){
		return DRV_ERRNO_GNET_READ_BUF_NULL;
	}

	u8len = pl_reg_read(PL_GNET_RFIFO_LEN_ADDR + 0x10000 * num);
#ifdef D_DEBUG_LOG
	printf("drvGnetRead->recv len: %d\n", u8len);
#endif
	if(u8len == 0){
		return DRV_ERRNO_GNET_READ_FAILED;
	}
	else if(u8len%4)
		u32len = u8len/4 + 1;
	else
		u32len = u8len/4;
	
	memset(pBuff, 0, sizeof(ST_DATA_BUFF));
	for(i=0;i<u32len;i++)
	{
		tmpData = pl_reg_read(PL_GNET_RFIFO_DATA_ADDR + 0x10000 * num);
		pBuff->ubuf[(i << 2)]     = (tmpData >> 24) & 0xff;
		pBuff->ubuf[(i << 2) + 1] = (tmpData >> 16) & 0xff;
		pBuff->ubuf[(i << 2) + 2] = (tmpData >> 8) & 0xff;
		pBuff->ubuf[(i << 2) + 3] = (tmpData) & 0xff;
		printf("%08x ", tmpData);
	}
	printf("\n");

#ifndef PORT
	u8len = *(UINT16*)pBuff->st_data.data_len;
#else
	u8len = pBuff->st_data.data_len[0];
#endif
    return u8len;
}

/******************************************************
 * Func: 光网口发送数据函数
 * param1：广网口编号，取值范围0~1
 * param2：待发送数据缓冲区
 * param3：待发送数据长度
 * return：发送数据长度或错误码
 * ****************************************************/
INT32 drvGnetWrite(UINT32 num, UINT8 *dst_mac, UINT8 *pBuff, UINT32 len)
{
	UINT32 i, u32len, Data = 0;
    if(num >= E_PL_GNET_NUM){
#ifdef D_DEBUG_LOG
        printf("drvGnetWrite->invalid gnet num input\n");
#endif
        return DRV_ERRNO_GNET_NOT_EXIST;
    }
    if((dst_mac == NULL) || (pBuff == NULL)){
#ifdef D_DEBUG_LOG
        printf("drvGnetWrite->invalid param pBuff or dst_mac input\n");
#endif
        return DRV_ERRNO_GNET_PARARM_INVALID;
    }
    if((len <= 0) || (len > D_GNET_DATALEN_MAX)){
#ifdef D_DEBUG_LOG
        printf("drvGnetWrite->invalid range of send byte lenth\n");
#endif
        return DRV_ERRNO_GNET_PARARM_INVALID;
    }
    
    u32len = (len + 14)/4;
	if((len + 14) % 4)
		u32len++;

	stringtohex(&m_gnet_sta.srcMac[num][0], gNetsBuf[num]->st_data.src_mac, 12);
	stringtohex(dst_mac, gNetsBuf[num]->st_data.dst_mac, 12);

#ifndef PORT			//数据长度大端
	gNetsBuf[num]->st_data.data_len[1] = ((len >> 8) & 0xff);
	gNetsBuf[num]->st_data.data_len[0] = ((len >> 0) & 0xff);
#else					//数据长度小端
	gNetsBuf[num]->st_data.data_len[0] = ((len >> 8) & 0xff);
	gNetsBuf[num]->st_data.data_len[1] = ((len >> 0) & 0xff);
#endif
	memset(gNetsBuf[num]->st_data.sbuf, 0, D_GNET_DATALEN_MAX);
	memcpy(gNetsBuf[num]->st_data.sbuf, pBuff, len);

#ifdef D_DEBUG_LOG
        printf("drvGnetWrite->gnet data send:");
#endif
	for(i=0;i<u32len;i++)
	{
		Data  = gNetsBuf[num]->ubuf[i*4]   << 24;
		Data |= gNetsBuf[num]->ubuf[i*4+1] << 16;
		Data |= gNetsBuf[num]->ubuf[i*4+2] << 8;
		Data |= gNetsBuf[num]->ubuf[i*4+3];
		pl_reg_write(PL_GNET_SFIFO_DATA_ADDR + 0x10000 * num, Data);
#ifdef D_DEBUG_LOG
		printf("%08x ", Data);
#endif
	}
#ifdef D_DEBUG_LOG
	printf("\n");
#endif
	pl_reg_write(PL_GNET_STATUS_ADDR + num * 0x10000, 1);
    return len;
}

/******************************************************
 * Func: 光网口模块自检函数
 * param1：光网口设备编号
 * param2：自检模式
 * return：自检结果
 * ****************************************************/
INT32 drvGnetCheck(UINT16 comNum_in, INT32 testMod)
{
	return 0;
}



