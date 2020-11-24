#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "drvErro.h"
#include "drvRegister.h"
#include "drvCfg.h"
#include "drvUart.h"

#ifdef D_OS_ALONE
#include "interrupt.h"
#include "drvCommon.h"
#endif

#define D_RXFIFO_RST   			0x01
#define D_TXFIFO_RST   			0x02

#define DRV_BRAUD_MIN         	9600 
#define DRV_BRAUD_MAX         	460800 


typedef struct tag_STRU_UART_CTRL_REG_CONFIG
{
	UINT32 u32bps_cnt 		: 24;
	UINT32 u32parity_even 	: 1;
	UINT32 u32fixed_parity 	: 1;
	UINT32 u32use_parity 	: 1;
	UINT32 u32dblstop 		: 1;
	UINT32 u32data_bits 	: 2;
	UINT32 u32int_enable 	: 1;
	UINT32 u32Reserved 		: 1;
}DRV_RS_CFG_ST_R;

typedef struct tag_STRU_UART_CTRL_REG_STATUS
{
	UINT32 u32rx_parity_err 	: 1;
	UINT32 u32rx_frame_err 		: 1;
	UINT32 u32rx_fifo_empty 	: 1;
	UINT32 u32rx_wr_data_count 	: 12;
	UINT32 u32tx_full 			: 1;
	UINT32 u32tx_empty 			: 1;
	UINT32 u32tx_busy 			: 1;
	UINT32 u32tx_wr_data_count 	: 12;
	UINT32 u32Reserved 			: 1;
	UINT32 u32rx_fifo_full 		: 1;
}STRU_UART_CTRL_REG_STATUS;


typedef struct
{
    int  mode[E_PL_UART_NUM];	 
    BOOL isOpen[E_PL_UART_NUM];
    BOOL intrEnable[E_PL_UART_NUM];
    DRV_RS_CFG_ST cfg[E_PL_UART_NUM];
    FUNCPUART routine;
}ST_UART_STATE;

ST_UART_STATE uartCfg = {0};  

/******************************************************
 * Func: UART接收中断服务入口函数
 * param1：串口号
 * return：无
 * ****************************************************/
LOCAL void usrUartIsr(int index)
{
    UINT32 rByte_num, ret, i, state = 0;
    UINT8 buffer[1025] = {0};
    
    ret = pl_reg_read(PL_UART_STATUS_ADDR + 0x1000 * index);
//    logMsg("Uart_%d recv status: 0x%x\n", index, ret, 2, 3, 4, 5, 6);
    if(!(ret & (1<<30)))                    /*接收长度FIFO不为空*/
    {
        if(ret & 0x80000000)                /*FIFO溢出*/
        { 			
            state |= DRV_RX_FIFO_FULL;
        } 
        
        rByte_num = pl_reg_read(PL_UART_INT_RDATA_ADDR + 0x1000 * index);
        if(rByte_num & 0x80000000)			/*奇偶校验没有通过*/
        {
            state |= DRV_RX_PARITY_ERRO;
            rByte_num &= 0x7fffffff;
        } 

        if(uartCfg.routine)
        {
            for(i=0;i<rByte_num;i++)
            {
                buffer[i] = (UINT8)pl_reg_read(PL_UART_RX_RDATA_ADDR + 0x1000 * index);
            }
            uartCfg.routine(index, state, buffer, rByte_num);
        }
    }
}

/******************************************************
 * Func: UART FIFO复位函数
 * param1：预留参数
 * return：执行结果
 * ****************************************************/
INT32 drvUartFifoRst(UINT32 comNum, UINT32 cmd)
{
	UINT32 rst = 0;
	rst |= (cmd & 0x03);
	pl_reg_write(comNum * 0x1000 + PL_UART_FIFO_RST_ADDR, rst);
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422初始化函数
 * param1：预留参数
 * return：执行结果
 * ****************************************************/
INT32 drvRsComInit(UINT32 reserve)
{
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422用户中断处理注册函数
 * param1：用户中断服务函数指针
 * return：执行结果
 * ****************************************************/
INT32 drvRsIntrConnect(FUNCPUART routine)
{
    if(routine != NULL)
    	uartCfg.routine = routine;
    else
    	return DRV_ERRNO_IO_PARARM_INVALID;
    
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422打开函数
 * param1：RS422设备编号
 * return：执行结果
 * ****************************************************/
INT32 drvRsOpen(UINT32 comNum,UINT16 mode)
{
	int isr_num;
    if(comNum >= E_PL_UART_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsOpen->invalid uart num input\n");
#endif
        return DRV_ERRNO_UART_NOT_EXIST;
    }
    
	isr_num = isrTab[E_PL_ISR_UART0 + comNum];
#ifdef D_OS_ALONE
	intDisconnect(isr_num, (void*)usrUartIsr, (void*)comNum);
#else
	intDisconnect(isr_num, (VOIDFUNCPTR)usrUartIsr, comNum);
#endif
	intDisable(isr_num);
    uartCfg.isOpen[comNum] = TRUE;
    if(mode)
    {
        pl_reg_write(comNum * 0x1000 + PL_UART_MODE_ADDR, 1);
        uartCfg.mode[comNum] = 1;
        return DRV_OPERATE_SUCCESS;
    }
#ifdef D_OS_ALONE
	intConnect(isr_num, (void*)usrUartIsr, (void*)comNum);
#else
	intConnect(isr_num, (VOIDFUNCPTR)usrUartIsr, comNum);
#endif
	if(intEnable(isr_num) != OK)
    {
#ifdef D_DEBUG_LOG
		printf("drvRsOpen->IO enable error\n");
#endif
	}
	
	drvUartFifoRst(comNum, D_RXFIFO_RST|D_TXFIFO_RST);
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422关闭函数
 * param1：RS422设备编号
 * return：执行结果
 * ****************************************************/
INT32 drvRsClose(UINT32 comNum)
{
    if(comNum >= E_PL_UART_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsClose->invalid uart num input\n");
#endif
        return DRV_ERRNO_UART_NOT_EXIST;
    }
    if(uartCfg.mode[comNum])
    {
        pl_reg_write(comNum*0x1000+PL_UART_MODE_ADDR, 0);
        uartCfg.mode[comNum] = 0;
    }
    uartCfg.isOpen[comNum] = FALSE;
    uartCfg.routine = NULL;
#ifdef D_OS_ALONE
    intDisconnect(isrTab[E_PL_ISR_UART0 + comNum], (void*)usrUartIsr, (void*)comNum);
#else
	intDisconnect(isrTab[E_PL_ISR_UART0 + comNum], (VOIDFUNCPTR)usrUartIsr, comNum);
#endif
	intDisable(isrTab[E_PL_ISR_UART0 + comNum]);
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422工作参数设置函数
 * param1：RS422设备编号
 * param2：RS422参数结构体指针
 * return：执行结果
 * ****************************************************/
INT32 drvRsParamSet(UINT32 comNum, DRV_RS_CFG_ST cfg)
{
    DRV_RS_CFG_ST_R cfg_r;
    if(comNum >= E_PL_UART_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamSet->invalid uart num input\n");
#endif
        return DRV_ERRNO_UART_NOT_EXIST;
    }
    if((cfg.baudarate < DRV_BRAUD_MIN)||(cfg.baudarate > DRV_BRAUD_MAX))
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamSet->baudrate is not at range of 4800~921600\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    if((cfg.async_parity < DRV_PARITY_NONE)||(cfg.async_parity > DRV_PARITY_EVEN))
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamSet->invalid uart parity param input\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    if((cfg.data_bits_num < DRV_DATA_BITS_6)||(cfg.data_bits_num > DRV_DATA_BITS_8))
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamSet->invalid uart data bits num param input\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    if((cfg.stop_bits_num < DRV_STOP_BITS_1)||(cfg.stop_bits_num > DRV_STOP_BITS_2))
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamSet->invalid uart stop bits num param input\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }

    memset(&cfg_r,0,sizeof(DRV_RS_CFG_ST_R));
    cfg_r.u32bps_cnt = 1000*1000*100/cfg.baudarate;
    switch(cfg.async_parity)
    {
        case DRV_PARITY_NONE://async_parity is none 
            cfg_r.u32use_parity = 0;
            cfg_r.u32fixed_parity = 0;
            cfg_r.u32parity_even = 0;
            break;
        case DRV_PARITY_ODD://async_parity is ODD  
            cfg_r.u32use_parity = 1;
            cfg_r.u32fixed_parity = 0;
            cfg_r.u32parity_even = 1;
            break;
        case DRV_PARITY_EVEN://async_parity is EVEN 
            cfg_r.u32use_parity = 1;
            cfg_r.u32fixed_parity = 0;
            cfg_r.u32parity_even = 0;
            break;
        default:
            break;
    }
    switch(cfg.data_bits_num)
    {
        case DRV_DATA_BITS_6://DATA_BITS is 6 
            cfg_r.u32data_bits = 2;
            break;
        case DRV_DATA_BITS_7://DATA_BITS is 7 
            cfg_r.u32data_bits = 1;
            break;
        case DRV_DATA_BITS_8://DATA_BITS is 8 
            cfg_r.u32data_bits = 0;
            break;
        default:
            break;
    }
    switch(cfg.stop_bits_num)
    {
        case DRV_STOP_BITS_1://STOP_BITS is 1 
            cfg_r.u32dblstop = 0;
            break;
        case DRV_STOP_BITS_2://STOP_BITS is 2
            cfg_r.u32dblstop = 1;
            break;
        default:
            break;
    }

    if(cfg.isr_enable)				/*使能uart中断*/
    	cfg_r.u32int_enable = 1; 
    
    UINT32 regValue = *((UINT32 *)&cfg_r);
    pl_reg_write(comNum*0x1000+PL_UART_CONFIG_ADDR, regValue);
    if(pl_reg_read(comNum*0x1000+PL_UART_CONFIG_ADDR) != regValue)
    {
#ifdef D_DEBUG_LOG
    	printf("drvRsParamSet->param set failed\n");
    	return DRV_ERRNO_UART_PARARM_SET_FAILED;
#endif
    }
    uartCfg.cfg[comNum].baudarate = cfg.baudarate;
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422工作参数获取函数
 * param1：RS422设备编号
 * param2：RS422参数结构体指针
 * return：执行结果
 * ****************************************************/
INT32 drvRsParamGet(UINT32 comNum, DRV_RS_CFG_ST *pCfg)
{
    DRV_RS_CFG_ST_R Cfg_r;
    if(comNum >= E_PL_UART_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamGet->invalid uart num input\n");
#endif
        return DRV_ERRNO_UART_NOT_EXIST;
    }
    if(pCfg == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsParamGet->param ptr pCfg is NULL\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    
    UINT32 ret = pl_reg_read(comNum*0x1000 + PL_UART_CONFIG_ADDR);
    Cfg_r = *((DRV_RS_CFG_ST_R *)&ret);
    pCfg->baudarate = uartCfg.cfg[comNum].baudarate;
    pCfg->isr_enable = Cfg_r.u32int_enable;
    if(Cfg_r.u32use_parity == 1 && Cfg_r.u32parity_even == 1)
    {
        pCfg->async_parity = DRV_PARITY_ODD;//async_parity is ODD 
    }
    else if(Cfg_r.u32use_parity == 1 && Cfg_r.u32parity_even == 0)
    {
        pCfg->async_parity = DRV_PARITY_EVEN;//async_parity is EVEN 
    }
    else
    {
        pCfg->async_parity = DRV_PARITY_NONE;//async_parity is none 
    }

    switch(Cfg_r.u32data_bits)
    {
        case 2:
            pCfg->data_bits_num = DRV_DATA_BITS_6;//DATA_BITS is 6 
            break;
        case 1:
            pCfg->data_bits_num = DRV_DATA_BITS_7;//DATA_BITS is 7 
            break;
        case 0:
            pCfg->data_bits_num = DRV_DATA_BITS_8;//DATA_BITS is 8 
            break;
        default:
            break;
    }
    switch(Cfg_r.u32dblstop)
    {
        case 0:
            pCfg->stop_bits_num = DRV_STOP_BITS_1;//STOP_BITS is 1 
            break;
        case 1:
            pCfg->stop_bits_num = DRV_STOP_BITS_2;//STOP_BITS is 2
            break;
        default:
            break;
    }
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: RS422发送函数
 * param1：RS422设备编号
 * param2：要发送的数据指针
 * param3：要发送的数据长度
 * return：发送字节长度
 * ****************************************************/
INT32 drvRsSend(UINT32 comNum, UINT8 *pBuff, UINT32 len)
{
    UINT32 regValue, send_cnt = 0;
    STRU_UART_CTRL_REG_STATUS status_st;

    if(comNum >= E_PL_UART_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsSend->invalid uart num input\n");
#endif
        return DRV_ERRNO_UART_NOT_EXIST;
    }
    if(pBuff == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsSend->param ptr pBuff is NULL\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    if((len == 0)||(len>SFIFO_LEN_MAX))
    {
#ifdef D_DEBUG_LOG
        printf("drvRsSend->param len is out of range\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    if(uartCfg.mode[comNum])
    {
#ifdef D_DEBUG_LOG
        printf("drvRsSend->uart%d run in second pulse mode\n", comNum);
#endif
        return DRV_ERRNO_UART_SEND_FAILED;
    }
    
    regValue = pl_reg_read(comNum * 0x1000 + PL_UART_STATUS_ADDR);
    status_st = *((STRU_UART_CTRL_REG_STATUS*)&regValue);
    if((SFIFO_LEN_MAX - status_st.u32tx_wr_data_count) < len)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsSend->uart%d sFIFO space not enough[%x]\n", comNum, regValue);
#endif
    	return DRV_ERRNO_UART_TXFIFO_NOT_EMPTY;
    }
    
    while(send_cnt < len)
    {
        regValue = *(pBuff + send_cnt);
        pl_reg_write(comNum*0x1000 + PL_UART_TX_WRDA_ADDR, regValue);
        if(pl_reg_read(comNum*0x1000 + PL_UART_TX_WRDA_ADDR) == regValue)
        	send_cnt++;
        else
        {
#ifdef D_DEBUG_LOG
            printf("drvRsSend->send fifo addr-%d write data failed\n", send_cnt);
#endif
        }
    }
    /*写本次发送数据长度，并启动发送*/
    pl_reg_write(comNum*0x1000 + PL_UART_SEND_ENABLE_ADDR, send_cnt);
    return send_cnt;
}

/******************************************************
 * Func: RS422数据接收函数
 * param1：RS422设备编号
 * param2：要接收的数据缓冲区数据指针
 * param3：要接收的数据长度
 * param4：数据接收超时阻塞时间
 * return：数据接收字节长度
 * ****************************************************/
INT32 drvRsRecv(UINT32 comNum, UINT8 *pBuff, UINT32 len, INT32 waitTime)
{
    UINT32 lentmp, i;
    if(comNum >= E_PL_UART_NUM)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsRecv->invalid uart num input\n");
#endif
        return DRV_ERRNO_UART_NOT_EXIST;
    }
    if(pBuff == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvRsRecv->param ptr pBuff is NULL\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }
    if((len == 0)||(len > SFIFO_LEN_MAX))
    {
#ifdef D_DEBUG_LOG
        printf("drvRsRecv->param len is out of range\n");
#endif
        return DRV_ERRNO_UART_PARARM_INVALID;
    }

    lentmp = 0;
    if(len > 0)
    {
    	UINT32 status_read;
        STRU_UART_CTRL_REG_STATUS status_st;
        status_read = pl_reg_read(comNum*0x1000 + PL_UART_STATUS_ADDR);
        status_st = *((STRU_UART_CTRL_REG_STATUS *)&status_read);

		//阻塞处理
		if(status_st.u32rx_wr_data_count < len)
        {
			if(waitTime == -1)
            {
				while(1)
                {
					drv_delay_ms(1);
					
					status_read = pl_reg_read(comNum*0x1000 + PL_UART_STATUS_ADDR);
					status_st = *((STRU_UART_CTRL_REG_STATUS *)&status_read);
					if(status_st.u32rx_wr_data_count >= len)
                    {
						lentmp = len;
						break;
					}	
				}
			}
			else if(waitTime > 0)
            {
                while(waitTime--)
                {
                    drv_delay_ms(1);
                    status_read = pl_reg_read(comNum*0x1000 + PL_UART_STATUS_ADDR); 
                    status_st = *((STRU_UART_CTRL_REG_STATUS *)&status_read);
                    if(status_st.u32rx_wr_data_count >= len)
                    {
                        lentmp = len;
                        break;
                    }	
                }

				if(status_st.u32rx_wr_data_count < len)
                {
					lentmp = status_st.u32rx_wr_data_count;
				}
			}
			else if(waitTime == 0)
            {
				lentmp = status_st.u32rx_wr_data_count;
			}
		}
		else
        {
			lentmp = len;
		}
		
        for(i=0;i<lentmp;i++)
        {   //读数据
        	pBuff[i] = (UINT8)pl_reg_read(comNum*0x1000 + PL_UART_RX_RDATA_ADDR);
        }
    }
    
    return lentmp;
}

/******************************************************
 * Func: RS422模块自检函数
 * param1：RS422设备编号
 * param2：自检模式
 * return：自检结果
 * ****************************************************/
INT32 drvRsCheck(UINT32 comNum)
{
    if(drvRsComInit(0) != OK)
    {
        return DRV_ERRNO_UART_CHECK_FAILED;
    }
    if(drvRsOpen(comNum, 0) != OK)
    {
        return DRV_ERRNO_UART_CHECK_FAILED;
    }
    if (drvRsClose(comNum) != DRV_ERRNO_UART_CHECK_FAILED)
    {
        return DRV_ERRNO_UART_CHECK_FAILED;
    }
    
	return DRV_OPERATE_SUCCESS;
}

