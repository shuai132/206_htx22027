/***************************************************************
*�ļ����ƣ�drvAdc.c
*�ļ�˵����AD�����ӿ�ʵ��
*�汾�ţ�1.00
*����������workbench3.3
****************************************************************/
#include <stdio.h>
#include <string.h>
#include "drvAdc.h"
#include "drvErro.h"
#include "drvRegister.h"
#include "drvCfg.h"

#ifdef D_OS_ALONE
#include "interrupt.h"
#include "drvCommon.h"
#endif

volatile UINT32 g_baudrate = DRV_AD_BRAD_20K;

enum DRV_AD_FIFO_STA_EN{
	DRV_AD_BIGDATA_STA = 0x80000000,	/*�����ݲ�����ɱ�־*/
	DRV_AD_AVERAGE_STA = 0x40000000		/*��ƽ��������ɱ�־*/
};

FUNCPAD g_routine = NULL;
UINT16 g_adSampVla[6000] = {0};

/******************************************************
 * Func: ad�����ݲɼ��ж���ں���
 * param1����ʱ�����
 * return��ִ�н��
 * ****************************************************/
LOCAL void usrAdIsr(int index)
{
    UINT32 len, result=0;
    len = drvAdBigDataRead(g_adSampVla, 0);
    if(len <= 0)
    {
        result = 1;
    }
    if(g_routine != NULL)
    {
        g_routine(result, len, g_adSampVla);
    }
}

/*����Ƶ������*/
LOCAL INT32 drvAdBaudrateSet(UINT32 baud)
{
    UINT32 baudrate, chnoCnt, ret, i;
    if((baud < DRV_AD_BRAD_10K) || (baud > DRV_AD_BRAD_50K))
    {
 #ifdef D_DEBUG_LOG
        printf("drvAdBaudrateSet->ad sampling baud is invalid!\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;       
    }

    ret = (UINT16)pl_reg_read(PL_SEQ_REG1_ADDR);    /*��ͨ��ʹ��״̬*/
    chnoCnt = 0;
    for(i=0;i<16;i++)
    {
        if(ret & (1 << i))
            chnoCnt++;
    }
    ret = (UINT16)pl_reg_read(PL_SEQ_REG0_ADDR);    /*���¶ȵ�ͨ����״̬*/
    for(i=0;i<16;i++)
    {
        if(ret & (1 << i))
            chnoCnt++;
    }

    ret = pl_reg_read(PL_CFG_REG2_ADDR);
    baudrate = 100000000/(26 * baud * chnoCnt);   //n=100/(26*f), f of unit m
    baudrate = (baudrate & 0xff) << 8;
    baudrate |= (ret & 0xFFFF00FF);
    pl_reg_write(PL_CFG_REG2_ADDR, baudrate);           //set the baudrate
    if(baudrate != pl_reg_read(PL_CFG_REG2_ADDR))
    {
        return DRV_ERRNO_ADC_BAUD_SET_FAILED;
    }
    g_baudrate = baud;
    return DRV_OPERATE_SUCCESS;
}

LOCAL INT32 drvAdChnoSet(UINT16 chno)
{
    UINT16 tmpChno;
    tmpChno = chno | 0x8000;        /*Ĭ�ϴ򿪵�16��ͨ��*/
    pl_reg_write(PL_SEQ_REG1_ADDR, tmpChno);
    if(pl_reg_read(PL_SEQ_REG1_ADDR) != tmpChno)
    {
#ifdef D_DEBUG_LOG
        printf("drvAdChnoSet->AD sampling channel config failed[%04x]\n", tmpChno);
#endif
        return DRV_ERRNO_ADC_CHNO_SET_FAILED;
    }
    return DRV_OPERATE_SUCCESS;
}

/*����ģʽ����*/
LOCAL INT32 drvAdModeSet(UINT32 mode)
{
    INT32 ret;
    ret = pl_reg_read(PL_CFG_REG1_ADDR);
    ret = ret&0xFFFF0FFF;
    ret = ret|0x00003000;
    pl_reg_write(PL_CFG_REG1_ADDR, ret);
    drv_delay_ms(1);
    if(mode == 0)                /*��ѡͨ�����β���*/
    {
        ret = ret&0xFFFF0FFF;
        ret = ret|0x00001000;
    }
    else if(mode == 1)           /*��ѡͨ��ѭ������*/ 
    {
        ret = ret&0xFFFF0FFF;
        ret = ret|0x00002000;
    }
    else 
    {
#ifdef D_DEBUG_LOG
        printf("drvAdModeSet->Illegal parameter mode[%d]\n", mode);
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }
    pl_reg_write(PL_CFG_REG1_ADDR, ret);
    if(ret != pl_reg_read(PL_CFG_REG1_ADDR))
    {
#ifdef D_DEBUG_LOG
        printf("drvAdModeSet->sampling mode set failed!\n");
#endif
        return DRV_ERRNO_ADC_MODE_SET_FAILED;
    }
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: AD��ʼ������
 * param1��Ԥ������
 * return��ִ�н��
 * ****************************************************/
INT32 drvAdInit(UINT32  reserve)
{
    g_baudrate = DRV_AD_BRAD_10K;
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: AD�������ú���
 * param1�����ò����ṹ��ָ��
 * return��ִ�н��
 * ****************************************************/
INT32 drvAdParamSet(DRV_AD_CFG_ST *pCfg)
{
    INT32 ret;

    if(pCfg == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvAdParamSet->param ptr pCfg is NULL\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }

/*����ģʽ����*/
    ret = drvAdModeSet(pCfg->mode);
    if(ret != OK)
    {
        return ret;
    }

/*����ͨ������*/
    ret = drvAdChnoSet(pCfg->chnobits);
    if(ret != OK)
    {
        return ret;
    }

/*����Ƶ������*/
    ret = drvAdBaudrateSet(pCfg->baudrate);
    if(ret != OK)
    {
        return ret;
    }

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: AD�����жϻص�����ע�ắ��
 * param1����ʱ�����
 * param2���û��ص�����
 * param3���ص�����
 * return��ִ�н��
 * ****************************************************/
INT32 drvAdIntConnect(FUNCPAD routine)
{
    int ad_isrNum;
    if(routine == NULL) 
    {
#ifdef D_DEBUG_LOG
        printf("drvAdIntConnect->callback ptr is NULL!\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }

    g_routine = routine;
    ad_isrNum = isrTab[E_PL_ISR_AD];
#ifdef D_OS_ALONE
    intDisconnect(ad_isrNum, (void*)usrAdIsr, (void*)0);
    intDisable(ad_isrNum);
    intConnect(ad_isrNum, (void*)usrAdIsr, (void*)0);
#else
    intDisconnect(ad_isrNum, (VOIDFUNCPTR)usrAdIsr, 0);
    intDisable(ad_isrNum);
    intConnect(ad_isrNum, (VOIDFUNCPTR)usrAdIsr, 0);
#endif
    if(intEnable(ad_isrNum) != OK)
    {
        return DRV_ERRNO_ADC_ISRCB_FAILED;
    }
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: AD����ֵ������
 * param1������ͨ��
 * param2��������ֵ����ָ��
 * return��ִ�гɹ�����0�����󷵻ش������
 * ****************************************************/
INT32 drvAdRead(UINT16 chno, UINT16 *pBuff)
{
	int i;
	if(pBuff == NULL)
		return DRV_ERRNO_ADC_PARARM_INVALID;
	if(chno == 0){
		printf("drvAdRead->ad channel select param invalid!\n");
		return DRV_ERRNO_ADC_PARARM_INVALID;
	}

    for(i=0;i<16;i++){
        if(chno & (1 << i))
            break;
    }
    *pBuff = pl_reg_read(PL_VAUXP_REG0_ADDR + i * 4);
    *pBuff = ((*pBuff) >> 4) & 0x0fff;

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: AD�����ݲ�����������
 * param1�������ݲ��������ṹ��
 * return���ɹ�����0��ʧ�ܷ��ش�����
 * ****************************************************/
INT32 drvAdBigDataSet(DRV_AD_BIGDATA_ST *pCfg)
{
    INT32 ret, chno, i;
    DRV_AD_CFG_ST config = {0};
    if(pCfg == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvAdBigDataSet->parameter ptr pCfg is NULL!\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }

    chno = pl_reg_read(PL_SEQ_REG1_ADDR);   /*ͨ��ѡ��*/
    config.baudrate = g_baudrate;
    config.chnobits = pCfg->m_chno1 | pCfg->m_chno2 | pCfg->m_chno3 | chno;
    config.mode = 1;                        /*ѭ������*/
    drvAdParamSet(&config);

    pl_reg_write(PL_FIFO_STA_CLEAR_ADDR, 0x03);     /*��λ�����ݲ���FIFO*/

    ret = 0;
    for(i=0;i<11;i++)
    {
        if(pCfg->m_chno1 & (1 << i))
        {
            ret = i + 1;
        }
    }
    if(ret == 0)
    {
#ifdef D_DEBUG_LOG
        printf("drvAdBigDataSet->reg0 not select chno!\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }
    ret += (pCfg->m_cnt1 << 8);
    pl_reg_write(PL_BIGDATA_CFG1_ADDR, ret);
    if(ret != pl_reg_read(PL_BIGDATA_CFG1_ADDR))
    {
        return DRV_ERRNO_ADC_PARARM_SET_FAILED;
    }

    ret = 0;
    for(i=0;i<11;i++)
    {
        if(pCfg->m_chno2 & (1 << i))
        {
            ret = i + 1;
        }
    }
    ret += (pCfg->m_cnt2 << 8);
    pl_reg_write(PL_BIGDATA_CFG2_ADDR, ret); 
    if(ret != pl_reg_read(PL_BIGDATA_CFG2_ADDR))
    {
        return DRV_ERRNO_ADC_PARARM_SET_FAILED;
    }

    ret = 0;
    for(i=0;i<11;i++)
    {
        if(pCfg->m_chno3 & (1 << i))
        {
            ret = i + 1;
        }
    }
    ret += (pCfg->m_cnt3 << 8) + 0x80000000;
    pl_reg_write(PL_BIGDATA_CFG3_ADDR, ret); 
    if(ret != pl_reg_read(PL_BIGDATA_CFG3_ADDR))
    {
        return DRV_ERRNO_ADC_PARARM_SET_FAILED;
    }
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: AD�����ݲ���ֵ������
 * param1�������ݻ�����ָ��
 * param2�������ݳ���
 * param3�������ݳ�ʱʱ��
 * return���ɹ����ض����ݳ��ȣ�ʧ�ܷ��ش�����
 * ****************************************************/
INT32 drvAdBigDataRead(UINT16 *pData, INT32 timeout)
{
    INT32 ret, tmpLen, i;
    if(pData == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvAdBigDataRead->parameter ptr pData is NULL!\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }

    drv_delay_ms(1000);
    tmpLen = 0;
    ret = pl_reg_read(PL_AD_FIFO_STATE_ADDR);
    if(ret & DRV_AD_BIGDATA_STA)    /*�����ݲɼ����*/
    {   
        tmpLen = ret & 0xffff;
    }
    else if(timeout == -1)          /*�����ȴ������ݲɼ����*/
    { 
        while(1)
        {
            drv_delay_ms(1);
            ret = pl_reg_read(PL_AD_FIFO_STATE_ADDR);
            if(ret & DRV_AD_BIGDATA_STA)
            {
                tmpLen = ret & 0xffff;
                break;
            }
        }
    }
    else if(timeout)               /*����timeout�ȴ������ݲɼ����*/
    {
        while(timeout--)
        {
            drv_delay_ms(1);
            ret = pl_reg_read(PL_AD_FIFO_STATE_ADDR);
            if(ret & DRV_AD_BIGDATA_STA)
            {
                tmpLen = ret & 0xffff;
                break;
            }
        }
        if(!(ret & DRV_AD_BIGDATA_STA))
        {
            return DRV_ERRNO_ADC_READ_FAILED;
        }
    }
    for(i=0;i<tmpLen;i++)
    {
        pData[i] = pl_reg_read(PL_AD_FIFO_REG_ADDR);
    }

    pl_reg_write(PL_FIFO_STA_CLEAR_ADDR, (1 << 1)); /*���������״̬*/
    return tmpLen;
}

/******************************************************
 * Func: AD����ƽ��ֵ����
 * param1��ͨ��ѡ��
 * param2����ƽ��ֵ��������
 * param3������ƽ���������
 * param3����ʱʱ�䣬��λms
 * return���ɹ�����0��ʧ�ܷ��ش�����
 * ****************************************************/
INT32 drvAdAverageRead(DRV_AD_CHNOSEL_EN chno, DRV_AD_AVG_EN times, \
                        UINT16 *pData, INT32 timeout)
{
    INT32 ret, tmpChno, i;
    if((chno > DRV_AD_CHNO_All) || (chno == 0))
    {
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }
    if(pData == NULL)
    {
#ifdef D_DEBUG_LOG
        printf("drvAdBigDataSet->parameter ptr pData is NULL!\n");
#endif
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }
    if(timeout == 0)
    {
        return DRV_ERRNO_ADC_PARARM_INVALID;
    }

    tmpChno = pl_reg_read(PL_SEQ_REG1_ADDR); /*ͨ��ѡ��*/
    if((tmpChno & chno) == 0)
    {
        ret = drvAdChnoSet(chno | tmpChno);
        if(ret != OK)
        {
            return ret;
        }      
    }
    ret = drvAdModeSet(1);                  /*����Ϊѭ������ģʽ*/
    if(ret != OK)
    {
        return ret;
    }

    pl_reg_write(PL_AVG_CHNO_ADDR, chno);               /*ʹ����ƽ��ͨ��*/
    pl_reg_write(PL_CFG_REG0_ADDR, times);              /*������ƽ���ɼ�����*/
    
    pl_reg_write(PL_AVG_CFG_ADDR, chno | 0x80000000);   /*������ƽ��ͨ��*/

    if(timeout < 0)
    {
        while(1){
            drv_delay_ms(1);
            ret = pl_reg_read(PL_AD_FIFO_STATE_ADDR);
            if(ret & DRV_AD_AVERAGE_STA)
            {  
                break;  
            }
        }
    }
    else
    {
        while(timeout--)
        {
            drv_delay_ms(1);
            ret = pl_reg_read(PL_AD_FIFO_STATE_ADDR);
            if(ret & DRV_AD_AVERAGE_STA)
            {  
                break;  
            }
        }
    }
    if(ret & DRV_AD_AVERAGE_STA)
    {  
        for(i=0;i<16;i++)
        {
            if(chno & (1 << i))
            {
                break;
            }
        }
        *pData = pl_reg_read(PL_AVERAGE_DATA_ADDR + i * 4);
        pl_reg_write(PL_AVG_CHNO_ADDR, 0);              /*�ر�ad��ƽ��ͨ��*/
        pl_reg_write(PL_FIFO_STA_CLEAR_ADDR, 0x04);     /*����ƽ��״̬*/
        pl_reg_write(PL_CFG_REG0_ADDR, 0x8000);         /*�ر���ƽ��*/
        return 0;
    }
    return DRV_ERRNO_ADC_READ_FAILED;
}

INT32 drvAdClose(DRV_AD_CHNOSEL_EN chno)
{
    INT32 tmpChno;
    tmpChno = pl_reg_read(PL_SEQ_REG1_ADDR); /*ͨ��ѡ��*/
    tmpChno &= (~chno);
    pl_reg_write(PL_SEQ_REG1_ADDR, tmpChno);
    if(tmpChno != pl_reg_read(PL_SEQ_REG1_ADDR))
    {
#ifdef D_DEBUG_LOG
        printf("drvAdClose->chno-0x%x close failed!\n", chno);
#endif
        return DRV_ERRNO_ADC_CLOSE_FAILED;  
    }
    return DRV_OPERATE_SUCCESS;
}

/*
func drvAdCheck is to initialize the ADC block
 NULL
*/
INT32 drvAdCheck(void)
{
    DRV_AD_CFG_ST cfg;
    cfg.baudrate = DRV_AD_BRAD_20K;
    cfg.bits = 12;
    cfg.chnobits = DRV_AD_CHNO_All;
    cfg.mode = 0;
    if(drvAdInit(0) != OK)
    {
        return DRV_ERRNO_ADC_CHECK_FAILED;
    }
    if(drvAdParamSet(&cfg) != OK)
    {
        return DRV_ERRNO_ADC_CHECK_FAILED;
    }
    return DRV_OPERATE_SUCCESS;
}

INT32 drvAdDevicInfoGet(DRV_AD_DEVINFO_ST *pInfo)
{
    int ret;
    if(pInfo == NULL)
        return DRV_ERRNO_ADC_PARARM_INVALID;

    ret = pl_reg_read(PL_TEMP_REG_ADDR);
    float temp = ((ret >> 4) & 0x0fff) * 503.975 / 4096 - 273.15;
    pInfo->m_tempture = temp;

    ret = pl_reg_read(PL_VCCINT_REG_ADDR);
    float vcc_f = ((ret >> 4) & 0x0fff) * 300 / 4096;
    pInfo->m_vccint = vcc_f/100;

    ret = pl_reg_read(PL_VCCAUX_REG_ADDR);
    vcc_f = ((ret >> 4) & 0x0fff) * 300 / 4096;
    pInfo->m_vccaux = vcc_f/100;

    ret = pl_reg_read(PL_VBRAM_REG_ADDR);
    vcc_f = ((ret >> 4) & 0x0fff) * 300 / 4096;
    pInfo->m_vbram = vcc_f/100;

    ret = pl_reg_read(PL_VCCPINT_REG_ADDR);
    vcc_f = ((ret >> 4) & 0x0fff) * 300 / 4096;
    pInfo->m_vccpint = vcc_f/100;

    ret = pl_reg_read(PL_VCPPAUX_REG_ADDR);
    vcc_f = ((ret >> 4) & 0x0fff) * 300 / 4096;
    pInfo->m_vcppaux = vcc_f/100;

    return DRV_OPERATE_SUCCESS;
}
