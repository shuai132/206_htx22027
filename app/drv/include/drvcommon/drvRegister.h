/***************************************************************
*文件名称：drvGjbRegister.h
*文件说明：1553B IP核寄存器地址定义
*版本号：1.00
*开发环境：linux
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
#define PL_UART_SEND_ENABLE_ADDR 	(PL_UART_BASE_ADDR + 0x18)  /*发送使能，有效值为1*/
#define PL_UART_FIFO_RST_ADDR     	(PL_UART_BASE_ADDR + 0x1C)	/*FIFO复位，有效值为1，bit0为接收复位，bit1为发送复位*/

/*************************** TIMER *******************************/
#define PL_TIMER_CONFIG_ADDR        (PL_TIMER_BASE_ADDR + 0x00)
#define PL_TIMER_STOP_CONFIG_ADDR   (PL_TIMER_BASE_ADDR + 0x04)
#define PL_TIMER_REG_ADDR           (PL_TIMER_BASE_ADDR + 0x08)

/*************************** IO *******************************/
// 0: IO interrupt disable, 
// 1: low_to_high, 
// 2: high_to_low, 
// 3: low_to_high or high_to_low
#define PL_IO_TRIGGER_MODE0_ADDR        (PL_IO_BASE_ADDR + 0x00)	//IO中断触发方式寄存器(group0:pin0~pin15)
#define PL_IO_TRIGGER_MODE1_ADDR        (PL_IO_BASE_ADDR + 0x04)	//IO中断触发方式寄存器(group0:pin16~pin31)
#define PL_IO_TRIGGER_MODE2_ADDR  		(PL_IO_BASE_ADDR + 0x08)	//IO中断触发方式寄存器(group1:pin0~pin15)
#define PL_IO_TRIGGER_MODE3_ADDR        (PL_IO_BASE_ADDR + 0x0C)	//IO中断触发方式寄存器(group1:pin16~pin31)
#define PL_IO_TRIGGER_MODE4_ADDR        (PL_IO_BASE_ADDR + 0x10)	//IO中断触发方式寄存器(group2:pin0~pin15)
#define PL_IO_TRIGGER_MODE5_ADDR  		(PL_IO_BASE_ADDR + 0x14)	//IO中断触发方式寄存器(group2:pin16~pin31)

#define PL_IO_CONTROL_0_ADDR            (PL_IO_BASE_ADDR + 0x18)	//组0输入输出方向控制 0-输出，1-输入
#define PL_IO_CONTROL_1_ADDR            (PL_IO_BASE_ADDR + 0x1C)	//组1输入输出方向控制 0-输出，1-输入
#define PL_IO_CONTROL_2_ADDR            (PL_IO_BASE_ADDR + 0x20)	//组2输入输出方向控制 0-输出，1-输入

#define PL_IO_REG_INOUT_OUT0_ADDR       (PL_IO_BASE_ADDR + 0x24)	//组0输出状态寄存器
#define PL_IO_REG_INOUT_OUT1_ADDR  		(PL_IO_BASE_ADDR + 0x28)	//组1输出状态寄存器
#define PL_IO_REG_INOUT_OUT2_ADDR  		(PL_IO_BASE_ADDR + 0x2C)	//组2输出状态寄存器

#define PL_IO_OUT_REG0_ADDR             (PL_IO_BASE_ADDR + 0x30)	//组3输出状态寄存器
#define PL_IO_OUT_REG1_ADDR             (PL_IO_BASE_ADDR + 0x34)	//组4输出状态寄存器
#define PL_IO_OUT_REG2_ADDR           	(PL_IO_BASE_ADDR + 0x38)	//组5输出状态寄存器
#define PL_IO_OUT_REG3_ADDR           	(PL_IO_BASE_ADDR + 0x3C)	//组6输出状态寄存器
#define PL_IO_OUT_REG4_ADDR           	(PL_IO_BASE_ADDR + 0x40)	//组7输出状态寄存器
#define PL_IO_OUT_REG5_ADDR           	(PL_IO_BASE_ADDR + 0x44)	//组8输出状态寄存器
#define PL_IO_OUT_REG6_ADDR           	(PL_IO_BASE_ADDR + 0x48)	//组9输出状态寄存器

#define PL_IO_REG_IN0_ADDR              (PL_IO_BASE_ADDR + 0x4C)	//组0输入实时状态寄存器
#define PL_IO_REG_IN1_ADDR              (PL_IO_BASE_ADDR + 0x50)	//组1输入实时状态寄存器
#define PL_IO_REG_IN2_ADDR              (PL_IO_BASE_ADDR + 0x54)	//组2输入实时状态寄存器

#define PL_IO_STATE_IO_ADDR             (PL_IO_BASE_ADDR + 0x58)	//中断状态寄存器，区分组(GROUP)
#define PL_IO_REG_IN0_INTR_ADDR         (PL_IO_BASE_ADDR + 0x5C)	//组0输入中断状态寄存器(PIN)
#define PL_IO_REG_IN1_INTR_ADDR         (PL_IO_BASE_ADDR + 0x60)	//组1输入中断状态寄存器(PIN)
#define PL_IO_REG_IN2_INTR_ADDR         (PL_IO_BASE_ADDR + 0x64)	//组2输入中断状态寄存器(PIN)

#define PL_IO_REG_IN0_STATE_ADDR        (PL_IO_BASE_ADDR + 0x68)	//组0输入中断值寄存器(VALUE)
#define PL_IO_REG_IN1_STATE_ADDR        (PL_IO_BASE_ADDR + 0x6C)	//组1输入中断值寄存器(VALUE)
#define PL_IO_REG_IN2_STATE_ADDR      	(PL_IO_BASE_ADDR + 0x70)	//组2输入中断值寄存器(VALUE)
            
#define PL_IO_ISR_CLEAR                 (PL_IO_BASE_ADDR + 0x80)	//tell PL that deal done with interrupt, then PL will give interrupt
#define PL_IO_FIFO_RST_ADDR       		(PL_IO_BASE_ADDR + 0x84)	//FIFO复位寄存器


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

#define PL_AD_TIMER_GAP_ADDR		(PL_XADC_CTRL_BASE_ADDR + 0x90)	    /*采样间隔时间寄存器，单位1ms*/
#define PL_AD_CNT_ADDR   			(PL_XADC_CTRL_BASE_ADDR + 0x94)	    /*采样次数寄存器*/
#define PL_AD_FIFO_STATE_ADDR   	(PL_XADC_CTRL_BASE_ADDR + 0xA30)    /*FIFO状态寄存器*/
#define PL_AD_FIFO_REG_ADDR   		(PL_XADC_CTRL_BASE_ADDR + 0xA2C)    /*FIFO寄存器*/
#define PL_AD_CHANNEL_ADDR  		(PL_XADC_CTRL_BASE_ADDR + 0x98)	    /*采样通道寄存器*/


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

#define PL_BIGDATA_CFG1_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0x0)       /*大数据采集配置1*/
#define PL_BIGDATA_CFG2_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0x4)       /*大数据采集配置2*/
#define PL_BIGDATA_CFG3_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0x8)       /*大数据采集配置3*/
#define PL_AVG_CFG_ADDR             (PL_XADC_CTRL_BASE_ADDR + 0xC)       /*求平均配置寄存器*/
#define PL_FIFO_STA_CLEAR_ADDR      (PL_XADC_CTRL_BASE_ADDR + 0x10)      /*FIFO状态清除寄存器*/

#define PL_AVERAGE_DATA_ADDR        (PL_XADC_CTRL_BASE_ADDR + 0xA00)     /*求平均数据*/

/*************************** GNET *******************************/
#define PL_GNET_STATUS_ADDR   		(PL_GNET_BASE_ADDR + 0x4)    	//写数据完成状态
#define PL_GNET_CFG1_ADDR     		(PL_GNET_BASE_ADDR + 0x8)    	//0x20
#define PL_GNET_CFG2_ADDR    		(PL_GNET_BASE_ADDR + 0x10)    	//0x80

#define PL_GNET_SFIFO_DATA_ADDR 	(PL_GNET_BASE_ADDR + 0x0)
#define PL_GNET_FIFO_STATE_ADDR 	(PL_GNET_BASE_ADDR + 0x1C)
#define PL_GNET_RFIFO_LEN_ADDR  	(PL_GNET_BASE_ADDR + 0x18)
#define PL_GNET_RFIFO_DATA_ADDR		(PL_GNET_BASE_ADDR + 0x14)
#define PL_GNET_FIFO_RST_ADDR		(PL_GNET_BASE_ADDR + 0x20)  	//bit31:中断使能, bit0:RX FIFO复位,bit1:TX FIFO复位

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
#define		PL_EMIFF_RST			(PL_EMIFF_BASE_ADDR + 0x00)		// 复位清中断寄存器（bit0：清芯片中断，bit1：清pl FIFO）
#define		PL_EMIFF_WCFG			(PL_EMIFF_BASE_ADDR + 0x04)		// 写配置寄存器（bit0~bit11：写配置reg的地址，bit16~bit23：写配置reg的值）
#define		PL_EMIFF_RCFG			(PL_EMIFF_BASE_ADDR + 0x08)		// 读配置寄存器（bit0~bit11：读配置reg的地址，bit16~bit23：读配置reg的值）
#define		PL_EMIFF_WDATA			(PL_EMIFF_BASE_ADDR + 0x0C)		// 写数据寄存器（bit0~bit11：写数据reg的地址，bit16~bit23：写数据reg的值）
#define		PL_EMIFF_RDATA			(PL_EMIFF_BASE_ADDR + 0x10)		// 读数据寄存器（bit0~bit11：读数据reg的地址，bit16~bit23：读数据reg的值）
#define		PL_EMIFF_ISR_RDATA		(PL_EMIFF_BASE_ADDR + 0x14)		// 读中断数据寄存器（bit0~bit7：有效数据位）
#define		PL_EMIFF_ISR_STATE	    (PL_EMIFF_BASE_ADDR + 0x20)		// 中断状态寄存器（bit0~bit10：数据长度，bit11：FIFO空标志位，bit31：数据ready标志）

#endif  // TX11905_REGISTER_DEF_H
