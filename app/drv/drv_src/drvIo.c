#include <stdio.h>
#include "drvIo.h"
#include "drvRegister.h"
#include "drvErro.h"

#ifdef D_OS_ALONE
#include "interrupt.h"
#include "drvCommon.h"
#endif

typedef struct
{
    UINT32      ioMode[E_PL_IO_GROUP_NUM];
    FUNCPIO     routine;
}ST_IO_STATE;
ST_IO_STATE  IoConfig = {0};

/******************************************************
 * Func: IO�����ж���ں���
 * param1: Ԥ������
 * return����
 * ****************************************************/
LOCAL void usrIoIsr(int index)
{
    UINT32 chno, num, value, ret;
    ret = pl_reg_read(PL_IO_STATE_IO_ADDR);
    if(ret & 1) 
	{
        chno = 0;
        num = pl_reg_read(PL_IO_REG_IN0_INTR_ADDR);
        value = pl_reg_read(PL_IO_REG_IN0_STATE_ADDR);
    }
    else if(ret & 2) 
	{
        chno = 1;
        num = pl_reg_read(PL_IO_REG_IN1_INTR_ADDR);
        value = pl_reg_read(PL_IO_REG_IN1_STATE_ADDR);
    }
    else if(ret & 0x4) 
	{
        chno = 2;
        num = pl_reg_read(PL_IO_REG_IN2_INTR_ADDR);
        value = pl_reg_read(PL_IO_REG_IN2_STATE_ADDR);
    }
#ifdef D_OS_ALONE
#ifdef D_DEBUG_LOG
    printf("IO isr: chno-%d, pin-%x, value-%x\n", chno, num, value);
#endif
#else
#ifdef D_DEBUG_LOG
    logMsg("IoIsr->chno-%d, pin-%x, value-%x\n", chno, num, value, 4, 5, 6);
#endif
#endif
    if(IoConfig.routine)
        IoConfig.routine(chno, num, value);
    pl_reg_write(PL_IO_ISR_CLEAR, 1);
}

/******************************************************
 * Func: IOģ���ʼ������
 * param1: Ԥ������
 * return���ӿ�ִ�н��
 * ****************************************************/
INT32 drvIoInit(UINT32 reserve)
{
	int i;
	int isr_num = isrTab[E_PL_ISR_IO];
#ifdef D_OS_ALONE
    intDisconnect(isr_num, (void*)usrIoIsr, 0);
    intDisable(isr_num);
    intConnect(isr_num, (void*)usrIoIsr, 0);
#else
    intDisconnect(isr_num, (VOIDFUNCPTR)usrIoIsr, 0);
    intDisable(isr_num);
    intConnect(isr_num, (VOIDFUNCPTR)usrIoIsr, 0);
#endif
    if(intEnable(isr_num) != OK)
		printf("drvIoInit->IO enable error\n");
    
    /*Ĭ������INOUT��Ϊ�����*/
	if(drvIoModeSet(DRV_IO_INOUT_GROUP_0, (UINT32)DRV_IO_PIN_ALL) < 0)
		return DRV_ERRNO_IO_INIT_FAILED;
	if(drvIoModeSet(DRV_IO_INOUT_GROUP_1, (UINT32)DRV_IO_PIN_ALL) < 0)
		return DRV_ERRNO_IO_INIT_FAILED;
	if(drvIoModeSet(DRV_IO_INOUT_GROUP_2, (UINT32)DRV_IO_PIN_ALL) < 0)
		return DRV_ERRNO_IO_INIT_FAILED;
	
	for(i=0;i<E_PL_IO_GROUP_NUM;i++){
		IoConfig.ioMode[i] = 0;
	}
	IoConfig.ioMode[DRV_IO_INOUT_GROUP_0] = (UINT32)DRV_IO_PIN_ALL;
	IoConfig.ioMode[DRV_IO_INOUT_GROUP_1] = (UINT32)DRV_IO_PIN_ALL;
	IoConfig.ioMode[DRV_IO_INOUT_GROUP_2] = (UINT32)DRV_IO_PIN_ALL;
	
    drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE0_ADDR, ISR_MODE_NONE);
	drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE1_ADDR, ISR_MODE_NONE);
	drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE2_ADDR, ISR_MODE_NONE);
    drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE3_ADDR, ISR_MODE_NONE);
	drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE4_ADDR, ISR_MODE_NONE);
	drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE5_ADDR, ISR_MODE_NONE);

	pl_reg_write(PL_IO_OUT_REG0_ADDR, 0xfffffff8); 	/*ʹ�������0 En�ܽ�*/
	pl_reg_write(PL_IO_OUT_REG1_ADDR, 0xfffffff8); 	/*ʹ�������1 En�ܽ�*/
	pl_reg_write(PL_IO_OUT_REG2_ADDR, 0xfffffffe); 	/*ʹ�������2 En�ܽ�*/

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: �û��ص�����ע��ӿ�
 * param1: �û��ص�����ָ��
 * return���ӿ�ִ�н��
 * ****************************************************/
INT32 drvIoIntrConnect(FUNCPIO routine)
{
    if(routine != NULL)
        IoConfig.routine = routine;
    else
    	return DRV_ERRNO_IO_PARARM_INVALID;
    
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IOģ��򿪽ӿ�
 * return���ӿ�ִ�н��
 * ****************************************************/
INT32 drvIoOpen(void)
{
	pl_reg_write(PL_IO_ISR_CLEAR, 1);		//�嵱ǰ�ж�
	pl_reg_write(PL_IO_FIFO_RST_ADDR, 1);  	//fifo��λ
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IO����������ƽӿ�
 * param1��IO��ţ�ȡֵ��Χ7~9
 * param2��IO���������־λ��0-�����1-����
 * return���ӿ�ִ�н��
 * ****************************************************/
INT32 drvIoModeSet(UINT32 chnoNum, UINT32 type)
{
    if(chnoNum >= E_PL_IO_GROUP_NUM){
#ifdef D_DEBUG_LOG
		printf("drvIoModeSet->input io group value is not at range: 7~9\n");
#endif
		return DRV_ERRNO_IO_PARARM_INVALID;
    }
	
    pl_reg_write(PL_IO_CONTROL_0_ADDR + 4 * chnoNum, type);
    if(pl_reg_read(PL_IO_CONTROL_0_ADDR + 4 * chnoNum) != type){
#ifdef D_DEBUG_LOG
		printf("drvIoModeSet->drvIoModeSet write reg failed!\n");
#endif
		return DRV_ERRNO_IO_PARARM_SET_FAILED;
    }
    
    IoConfig.ioMode[chnoNum] = type;
    drv_delay_ms(5);
	pl_reg_write(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum, 0);		/*�������жϷ�ʽ*/
	pl_reg_write(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum + 4, 0);	/*�������жϷ�ʽ*/
    
    pl_reg_write(PL_IO_ISR_CLEAR, 1);
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IO����������ƽӿ�
 * param1��IO��ţ�ȡֵ��Χ7~9
 * param2��IO���������־λ��0-�����1-����
 * return���ӿ�ִ�н��
 * ****************************************************/
INT32 drvIoParamSet(UINT32 chnoNum, DRV_IO_CFG_ST *cfg)
{
	UINT32 i, ioctl, isr1, isr2;
	if(cfg == NULL){
#ifdef D_DEBUG_LOG
		printf("drvIoParamSet->param cfg is a NULL ptr\n");
#endif
		return DRV_ERRNO_IO_PARARM_INVALID;
	}
	
    if(chnoNum >= E_PL_IO_GROUP_NUM){
		return DRV_ERRNO_IO_PARARM_INVALID;
    }
    
    if(cfg->pin == 0){
		return DRV_ERRNO_IO_PARARM_INVALID;
    }
	
    ioctl = pl_reg_read(PL_IO_CONTROL_0_ADDR + 4 * chnoNum); 
    isr1 = pl_reg_read(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum);
    isr2 = pl_reg_read(PL_IO_TRIGGER_MODE1_ADDR + 8 * chnoNum);
    
    
	if(cfg->mode){			/*����*/
		if(cfg->group > DRV_IO_INOUT_GROUP_2){
#ifdef D_DEBUG_LOG
			printf("drvIoParamSet->input group must be at range: 0~2\n");
#endif
			return DRV_ERRNO_IO_PARARM_SET_FAILED;
		}
		for(i=0;i<32;i++){
			if(cfg->pin & (1 << i)){		/*���������������*/
				ioctl |= (1 << i);
			}
			
			if(i<16){						/*���������жϿ���*/
				isr1 &= ~(3 << i * 2);
				isr1 |= (cfg->isr << i * 2);
			}
			else{
				isr2 &= ~(3 << (i - 16) * 2);
				isr2 |= (cfg->isr << (i - 16) * 2);
			}
		}
		pl_reg_write(PL_IO_CONTROL_0_ADDR + 4 * chnoNum, ioctl);
		if(ioctl != pl_reg_read(PL_IO_CONTROL_0_ADDR + 4 * chnoNum))
		{
			return DRV_ERRNO_IO_PARARM_SET_FAILED;
		}
#ifdef D_DEBUG_LOG
		printf("drvIoParamSet->input pin: 0x%08x, mode: 0x%08x\n", cfg->pin, ioctl);
#endif
	}
	else{					/*���*/
		for(i=0;i<32;i++){
			if(cfg->pin & (1 << i)){
				ioctl &= (~(1 << i));
			}
			
			if(i<16){						/*���жϿ���*/
				isr1 &= ~(3 << i * 2);
			}
			else{
				isr2 &= ~(3 << (i - 16) * 2);
			}
		}
		pl_reg_write(PL_IO_CONTROL_0_ADDR + 4 * chnoNum, ioctl);
		if(ioctl != pl_reg_read(PL_IO_CONTROL_0_ADDR + 4 * chnoNum)){
			return DRV_ERRNO_IO_PARARM_SET_FAILED;
		}
#ifdef D_DEBUG_LOG
		printf("drvIoParamSet-> output pin: 0x%08x, value: 0x%08x\n", cfg->pin, ioctl);
#endif
	}
	IoConfig.ioMode[chnoNum] = ioctl;
	
	pl_reg_write(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum, isr1);
	if(pl_reg_read(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum) != isr1){
		return DRV_ERRNO_IO_PARARM_SET_FAILED;
	}
	
	pl_reg_write(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum + 4, isr2);
	if(pl_reg_read(PL_IO_TRIGGER_MODE0_ADDR + 8 * chnoNum + 4) != isr2){
		return DRV_ERRNO_IO_PARARM_SET_FAILED;
	}
#ifdef D_DEBUG_LOG
		printf("drvIoParamSet->group %d isr1: 0x%08x, isr2: 0x%08x\n", chnoNum, isr1, isr2);
#endif
    pl_reg_write(PL_IO_ISR_CLEAR, 1);
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IO������ƽӿ�
 * param1�����IO���
 * param2�����IO PIN
 * param3���������ֵ��0-�͵�ƽ��1-�ߵ�ƽ
 * return���������״̬
 * ****************************************************/
INT32 drvIoWrite(UINT32 chnoNum, UINT32 pin, UINT32 outData)
{
	UINT32 ioValue;
    if(chnoNum >= E_PL_IO_GROUP_NUM){
#ifdef D_DEBUG_LOG
    	printf("drvIoWrite->param chnoNum[%d] is out of range\n", chnoNum);
#endif
		return DRV_ERRNO_IO_PARARM_INVALID;
    }  
    
    if(pin == 0)
    	return DRV_ERRNO_IO_PARARM_INVALID;
    
    if((IoConfig.ioMode[chnoNum] & pin)){
#ifdef D_DEBUG_LOG
    	printf("drvIoWrite->param pin[%08x] has been config in input mode\n", pin);
#endif
		return DRV_ERRNO_IO_PARARM_INVALID;	
    }
    
    ioValue = pl_reg_read(PL_IO_REG_INOUT_OUT0_ADDR + chnoNum * 4);
    if(outData)
	{
		ioValue &= ~pin;
    }
    else
	{
    	ioValue |= pin;
    } 
	// ioValue ^= 0xffffffff;				/*ȡ�������������ЧʱΪ�͵�ƽ*/

	// printf("----->group:%d, pin:%x, value:%x\n", chnoNum, pin, ioValue);
    pl_reg_write(PL_IO_REG_INOUT_OUT0_ADDR + chnoNum * 4, ioValue);
    if(pl_reg_read(PL_IO_REG_INOUT_OUT0_ADDR + chnoNum * 4) == outData)
	{
    	return DRV_ERRNO_IO_WRITE_FAILED;
    }

    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IO����״̬��ѯ�ӿ�
 * param1������IO��ţ�ȡֵ��Χ7~9
 * param2������״ֵָ̬�룬0-�͵�ƽ��1-�ߵ�ƽ
 * return���������״̬
 * ***************************************************/
INT32 drvIoRead(UINT32 chnoNum, UINT32 pin, UINT32 *inData, INT32  waitTime)
{
	static UINT32 input_bk = 0;
    UINT32 read_value, ioctl = 0;
    if(chnoNum >= E_PL_IO_GROUP_NUM){
#ifdef D_DEBUG_LOG
    	printf("drvIoRead->param chnoNum[%d] is out of range\n", chnoNum);
#endif
		return DRV_ERRNO_IO_PARARM_INVALID;
    }  
    
    if(pin == 0)
    	return DRV_ERRNO_IO_PARARM_INVALID;
    
    if(chnoNum <= DRV_IO_INOUT_GROUP_2){
		if(IoConfig.ioMode[chnoNum]){
			ioctl = IoConfig.ioMode[chnoNum] & pin;
			if(ioctl == pin){
				ioctl = pin;
			}
			else if(ioctl == 0){
				ioctl = 0;
			}
			else{
				return DRV_ERRNO_IO_PARARM_INVALID;
			}	
		}
		else
			ioctl = 0;
    }
    else
    	ioctl = 0;
    
    if(ioctl){   	/*������IO״̬*/
		read_value = pl_reg_read(PL_IO_REG_IN0_ADDR + chnoNum * 4);
		input_bk = read_value & pin;
		
		if(waitTime == -1){
			do{
				drv_delay_ms(1);
				read_value = pl_reg_read(PL_IO_REG_IN0_ADDR + chnoNum * 4) & pin;
			}while(input_bk == read_value);
		}
		else if(waitTime){
			do{
				drv_delay_ms(1);
				read_value = pl_reg_read(PL_IO_REG_IN0_ADDR + chnoNum * 4);
				if(input_bk != read_value)
					break;
			}while(waitTime--);
		}
    }
    else{			/*�����IO״̬*/
		read_value = pl_reg_read(PL_IO_REG_INOUT_OUT0_ADDR + chnoNum * 4);
		read_value ^= 0xffffffff;
    }
    
    *inData = read_value & pin;    
    return DRV_OPERATE_SUCCESS;
}

/******************************************************
 * Func: IO�ӿ��Լ�ӿ�
 * param1��Ԥ������
 * return������ִ�н��
 * ***************************************************/
INT32 drvIoCheck(UINT32 reserve)
{
    if(drvIoInit(0) != OK)
		return DRV_ERRNO_IO_CHECK_FAILED;
	if(drvIoOpen() != OK)
    	return DRV_ERRNO_IO_CHECK_FAILED;
	return DRV_OPERATE_SUCCESS;
}

