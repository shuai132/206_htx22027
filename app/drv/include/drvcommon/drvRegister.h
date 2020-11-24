/***************************************************************
*�ļ����ƣ�drvGjbRegister.h
*�ļ�˵����1553B IP�˼Ĵ�����ַ����
*�汾�ţ�1.00
*����������linux
****************************************************************/
#ifndef DRVREGISTER_H
#define DRVREGISTER_H
#include "drvCfg.h"

/*************************** UART *******************************/
#define PL_UART_CONFIG_ADDR         (PL_UART_BASE_ADDR + 0x00)
#define PL_UART_STATUS_ADDR         (PL_UART_BASE_ADDR + 0x04)
#define PL_UART_RX_RDATA_ADDR       (PL_UART_BASE_ADDR + 0x08)
#define PL_UART_INT_RDATA_ADDR      (PL_UART_BASE_ADDR + 0x0C)
#define PL_UART_TX_WRDA_ADDR        (PL_UART_BASE_ADDR + 0x10)
#define PL_UART_MODE_ADDR           (PL_UART_BASE_ADDR + 0x14)
#define PL_UART_SEND_ENABLE_ADDR 	(PL_UART_BASE_ADDR + 0x18)  /*����ʹ�ܣ���ЧֵΪ1*/
#define PL_UART_FIFO_RST_ADDR     	(PL_UART_BASE_ADDR + 0x1C)	/*FIFO��λ����ЧֵΪ1��bit0Ϊ���ո�λ��bit1Ϊ���͸�λ*/

/*************************** TIMER *******************************/
#define PL_TIMER_CONFIG_ADDR        (PL_TIMER_BASE_ADDR + 0x00)
#define PL_TIMER_STOP_CONFIG_ADDR   (PL_TIMER_BASE_ADDR + 0x04)
#define PL_TIMER_REG_ADDR           (PL_TIMER_BASE_ADDR + 0x08)

/*************************** IO *******************************/
// 0: IO interrupt disable, 
// 1: low_to_high, 
// 2: high_to_low, 
// 3: low_to_high or high_to_low
#define PL_IO_TRIGGER_MODE0_ADDR        (PL_IO_BASE_ADDR + 0x00)	//IO�жϴ�����ʽ�Ĵ���(group0:pin0~pin15)
#define PL_IO_TRIGGER_MODE1_ADDR        (PL_IO_BASE_ADDR + 0x04)	//IO�жϴ�����ʽ�Ĵ���(group0:pin16~pin31)
#define PL_IO_TRIGGER_MODE2_ADDR  		(PL_IO_BASE_ADDR + 0x08)	//IO�жϴ�����ʽ�Ĵ���(group1:pin0~pin15)
#define PL_IO_TRIGGER_MODE3_ADDR        (PL_IO_BASE_ADDR + 0x0C)	//IO�жϴ�����ʽ�Ĵ���(group1:pin16~pin31)
#define PL_IO_TRIGGER_MODE4_ADDR        (PL_IO_BASE_ADDR + 0x10)	//IO�жϴ�����ʽ�Ĵ���(group2:pin0~pin15)
#define PL_IO_TRIGGER_MODE5_ADDR  		(PL_IO_BASE_ADDR + 0x14)	//IO�жϴ�����ʽ�Ĵ���(group2:pin16~pin31)

#define PL_IO_CONTROL_0_ADDR            (PL_IO_BASE_ADDR + 0x18)	//��0�������������� 0-�����1-����
#define PL_IO_CONTROL_1_ADDR            (PL_IO_BASE_ADDR + 0x1C)	//��1�������������� 0-�����1-����
#define PL_IO_CONTROL_2_ADDR            (PL_IO_BASE_ADDR + 0x20)	//��2�������������� 0-�����1-����

#define PL_IO_REG_INOUT_OUT0_ADDR       (PL_IO_BASE_ADDR + 0x24)	//��0���״̬�Ĵ���
#define PL_IO_REG_INOUT_OUT1_ADDR  		(PL_IO_BASE_ADDR + 0x28)	//��1���״̬�Ĵ���
#define PL_IO_REG_INOUT_OUT2_ADDR  		(PL_IO_BASE_ADDR + 0x2C)	//��2���״̬�Ĵ���

#define PL_IO_OUT_REG0_ADDR             (PL_IO_BASE_ADDR + 0x30)	//��3���״̬�Ĵ���
#define PL_IO_OUT_REG1_ADDR             (PL_IO_BASE_ADDR + 0x34)	//��4���״̬�Ĵ���
#define PL_IO_OUT_REG2_ADDR           	(PL_IO_BASE_ADDR + 0x38)	//��5���״̬�Ĵ���
#define PL_IO_OUT_REG3_ADDR           	(PL_IO_BASE_ADDR + 0x3C)	//��6���״̬�Ĵ���
#define PL_IO_OUT_REG4_ADDR           	(PL_IO_BASE_ADDR + 0x40)	//��7���״̬�Ĵ���
#define PL_IO_OUT_REG5_ADDR           	(PL_IO_BASE_ADDR + 0x44)	//��8���״̬�Ĵ���
#define PL_IO_OUT_REG6_ADDR           	(PL_IO_BASE_ADDR + 0x48)	//��9���״̬�Ĵ���

#define PL_IO_REG_IN0_ADDR              (PL_IO_BASE_ADDR + 0x4C)	//��0����ʵʱ״̬�Ĵ���
#define PL_IO_REG_IN1_ADDR              (PL_IO_BASE_ADDR + 0x50)	//��1����ʵʱ״̬�Ĵ���
#define PL_IO_REG_IN2_ADDR              (PL_IO_BASE_ADDR + 0x54)	//��2����ʵʱ״̬�Ĵ���

#define PL_IO_STATE_IO_ADDR             (PL_IO_BASE_ADDR + 0x58)	//�ж�״̬�Ĵ�����������(GROUP)
#define PL_IO_REG_IN0_INTR_ADDR         (PL_IO_BASE_ADDR + 0x5C)	//��0�����ж�״̬�Ĵ���(PIN)
#define PL_IO_REG_IN1_INTR_ADDR         (PL_IO_BASE_ADDR + 0x60)	//��1�����ж�״̬�Ĵ���(PIN)
#define PL_IO_REG_IN2_INTR_ADDR         (PL_IO_BASE_ADDR + 0x64)	//��2�����ж�״̬�Ĵ���(PIN)

#define PL_IO_REG_IN0_STATE_ADDR        (PL_IO_BASE_ADDR + 0x68)	//��0�����ж�ֵ�Ĵ���(VALUE)
#define PL_IO_REG_IN1_STATE_ADDR        (PL_IO_BASE_ADDR + 0x6C)	//��1�����ж�ֵ�Ĵ���(VALUE)
#define PL_IO_REG_IN2_STATE_ADDR      	(PL_IO_BASE_ADDR + 0x70)	//��2�����ж�ֵ�Ĵ���(VALUE)
            
#define PL_IO_ISR_CLEAR                 (PL_IO_BASE_ADDR + 0x80)	//tell PL that deal done with interrupt, then PL will give interrupt
#define PL_IO_FIFO_RST_ADDR       		(PL_IO_BASE_ADDR + 0x84)	//FIFO��λ�Ĵ���


/*************************** ADC *******************************/
#define PL_VALUE_REG0_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x00)
#define PL_VALUE_REG1_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x04)
#define PL_VALUE_REG2_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x08)
#define PL_VALUE_REG3_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x0C)
#define PL_VALUE_REG4_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x10)
#define PL_VALUE_REG5_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x14)
#define PL_VALUE_REG6_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x18)
#define PL_VALUE_REG7_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x1C)
#define PL_VALUE_REG8_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x20)
#define PL_VALUE_REG9_ADDR          (PL_XADC_CTRL_BASE_ADDR + 0x24)
#define PL_VALUE_REG10_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x28)
#define PL_VALUE_REG11_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x2C)
#define PL_VALUE_REG12_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x30)
#define PL_VALUE_REG13_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x34)
#define PL_VALUE_REG14_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x38)
#define PL_VALUE_REG15_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x3C)
#define PL_AD_TIMER_SET0_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x40)
#define PL_AD_TIMER_SET1_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x44)
#define PL_AD_TIMER_SET2_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x48)
#define PL_AD_TIMER_SET3_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x4C)
#define PL_AD_TIMER_SET4_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x50)
#define PL_AD_TIMER_SET5_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x54)
#define PL_AD_TIMER_SET6_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x58)
#define PL_AD_TIMER_SET7_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x5C)
#define PL_AD_TIMER_SET8_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x60)
#define PL_AD_TIMER_SET9_ADDR       (PL_XADC_CTRL_BASE_ADDR + 0x64)
#define PL_AD_TIMER_SET10_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x68)
#define PL_AD_TIMER_SET11_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x6C)
#define PL_AD_TIMER_SET12_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x70)
#define PL_AD_TIMER_SET13_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x74)
#define PL_AD_TIMER_SET14_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x78)
#define PL_AD_TIMER_SET15_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x7C)

#define PL_COMPARE_REG_ADDR         (PL_XADC_CTRL_BASE_ADDR + 0x80)	
#define PL_COMPARE_START_REG_ADDR   (PL_XADC_CTRL_BASE_ADDR + 0x84)	

#define PL_AD_TIMER_GAP_ADDR		(PL_XADC_CTRL_BASE_ADDR + 0x90)	    /*�������ʱ��Ĵ�������λ1ms*/
#define PL_AD_CNT_ADDR   			(PL_XADC_CTRL_BASE_ADDR + 0x94)	    /*���������Ĵ���*/
#define PL_AD_FIFO_STATE_ADDR   	(PL_XADC_CTRL_BASE_ADDR + 0xA30)    /*FIFO״̬�Ĵ���*/
#define PL_AD_FIFO_REG_ADDR   		(PL_XADC_CTRL_BASE_ADDR + 0xA2C)    /*FIFO�Ĵ���*/
#define PL_AD_CHANNEL_ADDR  		(PL_XADC_CTRL_BASE_ADDR + 0x98)	    /*����ͨ���Ĵ���*/


#define PL_CFG_REG0_ADDR            (PL_XADC_BASE_ADDR + 0x300)
#define PL_CFG_REG1_ADDR            (PL_XADC_BASE_ADDR + 0x304)
#define PL_CFG_REG2_ADDR            (PL_XADC_BASE_ADDR + 0x308)
#define PL_SEQ_REG0_ADDR            (PL_XADC_BASE_ADDR + 0x320)
#define PL_SEQ_REG1_ADDR            (PL_XADC_BASE_ADDR + 0x324)
#define PL_AVG_CHNO_ADDR            (PL_XADC_BASE_ADDR + 0x32C)

#define PL_TEMP_REG_ADDR            (PL_XADC_BASE_ADDR + 0x200)
#define PL_VCCINT_REG_ADDR          (PL_XADC_BASE_ADDR + 0x204)
#define PL_VCCAUX_REG_ADDR          (PL_XADC_BASE_ADDR + 0x208)
#define PL_VBRAM_REG_ADDR           (PL_XADC_BASE_ADDR + 0x218)
#define PL_VCCPINT_REG_ADDR         (PL_XADC_BASE_ADDR + 0x234)
#define PL_VCPPAUX_REG_ADDR         (PL_XADC_BASE_ADDR + 0x238)
#define PL_VAUXP_REG0_ADDR          (PL_XADC_BASE_ADDR + 0x240)
#define PL_VAUXP_REG1_ADDR          (PL_XADC_BASE_ADDR + 0x244)
#define PL_VAUXP_REG2_ADDR          (PL_XADC_BASE_ADDR + 0x248)
#define PL_VAUXP_REG3_ADDR          (PL_XADC_BASE_ADDR + 0x24C)
#define PL_VAUXP_REG4_ADDR          (PL_XADC_BASE_ADDR + 0x250)
#define PL_VAUXP_REG5_ADDR          (PL_XADC_BASE_ADDR + 0x254)
#define PL_VAUXP_REG6_ADDR          (PL_XADC_BASE_ADDR + 0x258)
#define PL_VAUXP_REG7_ADDR          (PL_XADC_BASE_ADDR + 0x25C)
#define PL_VAUXP_REG8_ADDR          (PL_XADC_BASE_ADDR + 0x260)
#define PL_VAUXP_REG9_ADDR          (PL_XADC_BASE_ADDR + 0x264)
#define PL_VAUXP_REG10_ADDR         (PL_XADC_BASE_ADDR + 0x268)
#define PL_VAUXP_REG11_ADDR         (PL_XADC_BASE_ADDR + 0x26C)
#define PL_VAUXP_REG12_ADDR         (PL_XADC_BASE_ADDR + 0x270)
#define PL_VAUXP_REG13_ADDR         (PL_XADC_BASE_ADDR + 0x274)
#define PL_VAUXP_REG14_ADDR         (PL_XADC_BASE_ADDR + 0x278)
#define PL_VAUXP_REG15_ADDR         (PL_XADC_BASE_ADDR + 0x27C)

#define PL_BIGDATA_CFG1_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0x0)       /*�����ݲɼ�����1*/
#define PL_BIGDATA_CFG2_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0x4)       /*�����ݲɼ�����2*/
#define PL_BIGDATA_CFG3_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0x8)       /*�����ݲɼ�����3*/
#define PL_AVG_CFG_ADDR             (PL_XADC_CTRL_BASE_ADDR + 0xC)       /*��ƽ�����üĴ���*/
#define PL_FIFO_STA_CLEAR_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x10)      /*FIFO״̬����Ĵ���*/

#define PL_AVERAGE_DATA_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0xA00)     /*��ƽ������*/

/*************************** GNET *******************************/
#define PL_GNET_STATUS_ADDR   		(PL_GNET_BASE_ADDR + 0x4)    	//д�������״̬
#define PL_GNET_CFG1_ADDR     		(PL_GNET_BASE_ADDR + 0x8)    	//0x20
#define PL_GNET_CFG2_ADDR    		(PL_GNET_BASE_ADDR + 0x10)    	//0x80

#define PL_GNET_SFIFO_DATA_ADDR 	(PL_GNET_BASE_ADDR + 0x0)
#define PL_GNET_FIFO_STATE_ADDR 	(PL_GNET_BASE_ADDR + 0x1C)
#define PL_GNET_RFIFO_LEN_ADDR  	(PL_GNET_BASE_ADDR + 0x18)
#define PL_GNET_RFIFO_DATA_ADDR		(PL_GNET_BASE_ADDR + 0x14)
#define PL_GNET_FIFO_RST_ADDR		(PL_GNET_BASE_ADDR + 0x20)  	//bit31:�ж�ʹ��, bit0:RX FIFO��λ,bit1:TX FIFO��λ

#define PL_GNET_IP_CFG1				(PL_GNETIP_BASE_ADDR + 0x500)   //0x53
#define PL_GNET_IP_CFG2				(PL_GNETIP_BASE_ADDR + 0x508)   //0x140
#define PL_GNET_IP_CFG3				(PL_GNETIP_BASE_ADDR + 0x504)	//0x1004800 -> delay_ms(2)
#define PL_GNET_IP_CFG4				(PL_GNETIP_BASE_ADDR + 0x404)	//0x90000000
#define PL_GNET_IP_CFG5				(PL_GNETIP_BASE_ADDR + 0x408)	//0x92000000
#define PL_GNET_IP_CFG6				(PL_GNETIP_BASE_ADDR + 0x008)	//0x20

/*************************** CAN ******************************/
#define		PL_CAN_SRR				(PL_CAN_BASE_ADDR + 0x000)		// Software Reset Register 
#define		PL_CAN_MSR				(PL_CAN_BASE_ADDR + 0x004)		// Mode Select Register
#define		PL_CAN_BRPR				(PL_CAN_BASE_ADDR + 0x008)		// Baud Rate Prescaler Register
#define		PL_CAN_BTR				(PL_CAN_BASE_ADDR + 0x00C)		// Bit Timing Register
#define		PL_CAN_ECR				(PL_CAN_BASE_ADDR + 0x010)		// Error Counter Register
#define		PL_CAN_ESR				(PL_CAN_BASE_ADDR + 0x014)		// Error Status Register
#define		PL_CAN_SR				(PL_CAN_BASE_ADDR + 0x018)		// Status Register
#define		PL_CAN_ISR				(PL_CAN_BASE_ADDR + 0x01C)		// Interrupt Status Register
#define		PL_CAN_IER				(PL_CAN_BASE_ADDR + 0x020)		// Interrupt Enable Register
#define		PL_CAN_ICR				(PL_CAN_BASE_ADDR + 0x024)		// Interrupt Clear Register
#define		PL_CAN_ID_TX			(PL_CAN_BASE_ADDR + 0x030)		// Transmit Message FIFO (TX FIFO)
#define		PL_CAN_DLC_TX			(PL_CAN_BASE_ADDR + 0x034)		// Transmit Message FIFO (TX FIFO)
#define		PL_CAN_DW1_TX			(PL_CAN_BASE_ADDR + 0x038)		// Transmit Message FIFO (TX FIFO)
#define		PL_CAN_DW2_TX			(PL_CAN_BASE_ADDR + 0x03C)		// Transmit Message FIFO (TX FIFO)
#define		PL_CAN_ID_TX_HPB		(PL_CAN_BASE_ADDR + 0x040)		// Transmit High Priority Buffer (TX HPB)
#define		PL_CAN_DLC_TX_HPB		(PL_CAN_BASE_ADDR + 0x044)		// Transmit High Priority Buffer (TX HPB)
#define		PL_CAN_DW1_TX_HPB		(PL_CAN_BASE_ADDR + 0x048)		// Transmit High Priority Buffer (TX HPB)
#define		PL_CAN_DW2_TX_HPB		(PL_CAN_BASE_ADDR + 0x04C)		// Transmit High Priority Buffer (TX HPB)
#define		PL_CAN_ID_RX			(PL_CAN_BASE_ADDR + 0x050)		// Receive Message FIFO (RX FIFO)
#define		PL_CAN_DLC_RX			(PL_CAN_BASE_ADDR + 0x054)		// Receive Message FIFO (RX FIFO)
#define		PL_CAN_DW1_RX			(PL_CAN_BASE_ADDR + 0x058)		// Receive Message FIFO (RX FIFO)
#define		PL_CAN_DW2_RX			(PL_CAN_BASE_ADDR + 0x05C)		// Receive Message FIFO (RX FIFO)
#define		PL_CAN_AFR				(PL_CAN_BASE_ADDR + 0x060)		// Acceptance Filter Register
#define		PL_CAN_AFMR1			(PL_CAN_BASE_ADDR + 0x064)		// Acceptance Filter Mask Register 1
#define		PL_CAN_AFIR1			(PL_CAN_BASE_ADDR + 0x068)		// Acceptance Filter ID Register 1
#define		PL_CAN_AFMR2			(PL_CAN_BASE_ADDR + 0x06C)		// Acceptance Filter Mask Register 2
#define		PL_CAN_AFIR2			(PL_CAN_BASE_ADDR + 0x070)		// Acceptance Filter ID Register 2
#define		PL_CAN_AFMR3			(PL_CAN_BASE_ADDR + 0x074)		// Acceptance Filter Mask Register 3
#define		PL_CAN_AFIR3			(PL_CAN_BASE_ADDR + 0x078)		// Acceptance Filter ID Register 3
#define		PL_CAN_AFMR4			(PL_CAN_BASE_ADDR + 0x07C)		// Acceptance Filter Mask Register 4
#define		PL_CAN_AFIR4			(PL_CAN_BASE_ADDR + 0x080)		// Acceptance Filter ID Register 4


/*************************** EMIFF ******************************/
#define		PL_EMIFF_RST			(PL_EMIFF_BASE_ADDR + 0x00)		// ��λ���жϼĴ�����bit0����оƬ�жϣ�bit1����pl FIFO��
#define		PL_EMIFF_WCFG			(PL_EMIFF_BASE_ADDR + 0x04)		// д���üĴ�����bit0~bit11��д����reg�ĵ�ַ��bit16~bit23��д����reg��ֵ��
#define		PL_EMIFF_RCFG			(PL_EMIFF_BASE_ADDR + 0x08)		// �����üĴ�����bit0~bit11��������reg�ĵ�ַ��bit16~bit23��������reg��ֵ��
#define		PL_EMIFF_WDATA			(PL_EMIFF_BASE_ADDR + 0x0C)		// д���ݼĴ�����bit0~bit11��д����reg�ĵ�ַ��bit16~bit23��д����reg��ֵ��
#define		PL_EMIFF_RDATA			(PL_EMIFF_BASE_ADDR + 0x10)		// �����ݼĴ�����bit0~bit11��������reg�ĵ�ַ��bit16~bit23��������reg��ֵ��
#define		PL_EMIFF_ISR_RDATA		(PL_EMIFF_BASE_ADDR + 0x14)		// ���ж����ݼĴ�����bit0~bit7����Ч����λ��
#define		PL_EMIFF_ISR_STATE	    (PL_EMIFF_BASE_ADDR + 0x20)		// �ж�״̬�Ĵ�����bit0~bit10�����ݳ��ȣ�bit11��FIFO�ձ�־λ��bit31������ready��־��

#endif  // TX11905_REGISTER_DEF_H
