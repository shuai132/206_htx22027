#define  DRV_OPERATE_SUCCESS        		0x00000000     /*�����ɹ�*/

/*I2C�������*/
#define  DRV_ERRNO_IIC_NOT_EXIST          	0xFFFFF000     /*i2c�豸������*/
#define  DRV_ERRNO_IIC_PARARM_INVALID     	0xFFFFF001     /*����������Ϸ�*/
#define  DRV_ERRNO_IIC_INIT_FAILED        	0xFFFFF002     /*�豸��ʼ��ʧ��*/
#define  DRV_ERRNO_IIC_OPEN_FAILED        	0xFFFFF003     /*�豸��ʧ��*/
#define  DRV_ERRNO_IIC_CLOSE_FAILED       	0xFFFFF004     /*�豸�ر�ʧ��*/
#define  DRV_ERRNO_IIC_PARARM_SET_FAILED  	0xFFFFF005     /*��������ʧ��*/
#define  DRV_ERRNO_IIC_PARARM_GET_FAILED  	0xFFFFF006     /*������ȡʧ��*/
#define  DRV_ERRNO_IIC_WRITE_FAILED       	0xFFFFF007     /*i2cд����ʧ��*/
#define  DRV_ERRNO_IIC_READ_FAILED        	0xFFFFF008     /*i2c������ʧ��*/
#define  DRV_ERRNO_IIC_READ_BUF_NULL      	0xFFFFF009     /*i2c��������Ϊ��*/
#define  DRV_ERRNO_IIC_READ_BUF_LESS      	0xFFFFF00A     /*i2c�����������ݲ���*/
#define  DRV_ERRNO_IIC_READ_TIMEOUT       	0xFFFFF00B     /*i2c�����ݳ�ʱ*/
#define  DRV_ERRNO_IIC_BUS_DISCONNECT     	0xFFFFF00C     /*i2c���߲�ͨ*/
/*����æ*/

/*��̫���������*/
#define  DRV_ERRNO_NET_DEV_NOT_EXIST      	0xFFFFF100     /*�����豸������*/
#define  DRV_ERRNO_NET_INIT_FAILED        	0xFFFFF101     /*��̫����ʼ��ʧ��*/
#define  DRV_ERRNO_NET_PARARM_INVALID     	0xFFFFF102     /*����������Ϸ�*/
#define  DRV_ERRNO_NET_SET_ADDR_FAILED    	0xFFFFF103     /*IP��ַ����ʧ��*/
#define  DRV_ERRNO_NET_GET_ADDR_FAILED    	0xFFFFF104     /*IP��ַ��ȡʧ��*/
#define  DRV_ERRNO_ETH0_NO_LINK           	0xFFFFF105     /*����0��ͨ*/
#define  DRV_ERRNO_ETH1_NO_LINK           	0xFFFFF106     /*����1��ͨ*/
#define  DRV_ERRNO_ETH0_DOWN              	0xFFFFF107     /*����0û�д�*/
#define  DRV_ERRNO_ETH1_DOWN              	0xFFFFF108     /*����1û�д�*/

/*422�������*/
#define  DRV_ERRNO_UART_NOT_EXIST          	0xFFFFF200     /*uart�豸������*/
#define  DRV_ERRNO_UART_PARARM_INVALID     	0xFFFFF201     /*����������Ϸ�*/
#define  DRV_ERRNO_UART_OPEN_FAILED        	0xFFFFF202     /*�豸��ʧ��*/
#define  DRV_ERRNO_UART_CLOSE_FAILED       	0xFFFFF203     /*�豸�ر�ʧ��*/
#define  DRV_ERRNO_UART_PARARM_SET_FAILED  	0xFFFFF204     /*��������ʧ��*/
#define  DRV_ERRNO_UART_PARARM_GET_FAILED  	0xFFFFF205     /*������ȡʧ��*/
#define  DRV_ERRNO_UART_TXFIFO_NOT_EMPTY   	0xFFFFF206     /*uart����FIFO��Ϊ��*/
#define  DRV_ERRNO_UART_SEND_FAILED        	0xFFFFF207     /*uart��������ʧ��*/
#define  DRV_ERRNO_UART_READ_FAILED        	0xFFFFF208     /*uart������ʧ��*/
#define  DRV_ERRNO_UART_READ_BUF_NULL      	0xFFFFF209     /*uart��������Ϊ��*/
#define  DRV_ERRNO_UART_READ_BUF_LESS      	0xFFFFF20A     /*uart�����������ݲ���*/
#define  DRV_ERRNO_UART_READ_TIMEOUT       	0xFFFFF20B     /*uart�����ݳ�ʱ*/
#define  DRV_ERRNO_UART_BUS_DISCONNECT     	0xFFFFF20C     /*uart���߲�ͨ*/
#define  DRV_ERRNO_UART_CHECK_FAILED       	0xFFFFF20D     /*uart����ģ���Լ�ʧ��*/

/*BMC�������*/
#define  DRV_ERRNO_BMC_INFO_GET_FAILED    	0xFFFFF300     /*BMC��Ϣ��ȡʧ��*/
#define  DRV_ERRNO_BMC_PARARM_INVALID     	0xFFFFF301     /*BMC����������Ϸ�*/
#define  DRV_ERRNO_BMC_INFO_SET_FAILED    	0xFFFFF302     /*BMC��Ϣ����ʧ��*/
#define  DRV_ERRNO_BMC_INIT_FAILED        	0xFFFFF303     /*BMC��ʼ��ʧ��*/
#define  DRV_ERRNO_BMC_USER_NOT_EXIST     	0xFFFFF304     /*�û�������*/
#define  DRV_ERRNO_BMC_USER_NOT_ADMIN     	0xFFFFF305     /*�û�û�й���ԱȨ��*/
#define  DRV_ERRNO_BMC_USER_CREATE_FAILED 	0xFFFFF306     /*BMC��ʼ��ʧ��*/
#define  DRV_ERRNO_BMC_USER_ADD_FAILED    	0xFFFFF307     /*BMC���ʧ��*/
#define  DRV_ERRNO_BMC_CFG_READ_FAILED    	0xFFFFF308     /*BMC�������ļ�ʧ��*/
#define  DRV_ERRNO_BMC_USER_UPD_FAILED    	0xFFFFF309     /*BMC�û���Ϣ����ʧ��*/
#define  DRV_ERRNO_BMC_USER_DEL_FAILED    	0xFFFFF30a     /*BMC�û���Ϣɾ��ʧ��*/

/*ADC�������*/
#define  DRV_ERRNO_ADC_NOT_EXIST          	0xFFFFF400     /*ADC�豸������*/
#define  DRV_ERRNO_ADC_PARARM_INVALID     	0xFFFFF401     /*����������Ϸ�*/
#define  DRV_ERRNO_ADC_OPEN_FAILED        	0xFFFFF402     /*�豸��ʧ��*/
#define  DRV_ERRNO_ADC_PARARM_SET_FAILED  	0xFFFFF403     /*��������ʧ��*/
#define  DRV_ERRNO_ADC_PARARM_GET_FAILED  	0xFFFFF404     /*������ȡʧ��*/
#define  DRV_ERRNO_ADC_READ_FAILED        	0xFFFFF405     /*ADC����ֵ��ȡʧ��*/
#define  DRV_ERRNO_ADC_CLOSE_FAILED       	0xFFFFF406     /*ADC����ͨ���ر�ʧ��*/
#define  DRV_ERRNO_ADC_MODE_SET_FAILED    	0xFFFFF407     /*ADC��������ģʽ����ʧ��*/
#define  DRV_ERRNO_ADC_CHNO_SET_FAILED    	0xFFFFF408     /*ADC��������ͨ������ʧ��*/
#define  DRV_ERRNO_ADC_BAUD_SET_FAILED    	0xFFFFF409     /*ADC��������Ƶ������ʧ��*/
#define  DRV_ERRNO_ADC_CHECK_FAILED       	0xFFFFF40A     /*ADCģ���Լ�ʧ��*/
#define  DRV_ERRNO_ADC_ISRCB_FAILED       	0xFFFFF40B     /*ADC�ж���ں���ע��ʧ��*/

/*��ʱ���������*/
#define  DRV_ERRNO_CLK_NOT_EXIST          	0xFFFFF500     /*��ʱ���豸������*/
#define  DRV_ERRNO_CLK_INIT_FAILED        	0xFFFFF501     /*��ʱ����ʼ��ʧ��*/
#define  DRV_ERRNO_CLK_PARARM_INVALID     	0xFFFFF502     /*����������Ϸ�*/
#define  DRV_ERRNO_CLK_OPEN_FAILED        	0xFFFFF503     /*�豸��ʧ��*/
#define  DRV_ERRNO_CLK_CLOSE_FAILED       	0xFFFFF504     /*�豸�ر�ʧ��*/
#define  DRV_ERRNO_CLK_PARARM_SET_FAILED  	0xFFFFF505     /*��������ʧ��*/
#define  DRV_ERRNO_CLK_PARARM_GET_FAILED  	0xFFFFF506     /*������ȡʧ��*/
#define  DRV_ERRNO_CLK_READ_FAILED        	0xFFFFF507     /*��ʱ��״̬��ȡʧ��*/
#define  DRV_ERRNO_CLK_CHECK_FAILED       	0xFFFFF508     /*��ʱ��ģ���Լ�ʧ��*/

/*OTA�������*/
#define  DRV_ERRNO_OTA_NOT_EXIST          	0xFFFFF600     /*OTA���񲻴���*/
#define  DRV_ERRNO_OTA_PARARM_INVALID     	0xFFFFF601     /*����������Ϸ�*/
#define  DRV_ERRNO_OTA_INIT_FAILED        	0xFFFFF602     /*OTA�����ʼ��ʧ��*/
#define  DRV_ERRNO_OTA_OPEN_FAILED        	0xFFFFF603     /*OTA�����ʧ��*/
#define  DRV_ERRNO_OTA_CLOSE_FAILED       	0xFFFFF604     /*OTA����ر�ʧ��*/
#define  DRV_ERRNO_OTA_INSTALL_FAILED     	0xFFFFF605     /*OTA��������װʧ��*/
#define  DRV_ERRNO_OTA_VERIFY_FAILED      	0xFFFFF606     /*OTA������У��ʧ��*/

/*IO�������*/
#define  DRV_ERRNO_IO_NOT_EXIST          	0xFFFFF700     /*IO������*/
#define  DRV_ERRNO_IO_INIT_FAILED        	0xFFFFF701     /*IO��ʼ��ʧ��*/
#define  DRV_ERRNO_IO_PARARM_INVALID     	0xFFFFF702     /*����������Ϸ�*/
#define  DRV_ERRNO_IO_OPEN_FAILED        	0xFFFFF703     /*IO��ʧ��*/
#define  DRV_ERRNO_IO_CLOSE_FAILED       	0xFFFFF704     /*IO�ر�ʧ��*/
#define  DRV_ERRNO_IO_PARARM_SET_FAILED  	0xFFFFF705     /*��������ʧ��*/
#define  DRV_ERRNO_IO_PARARM_GET_FAILED  	0xFFFFF706     /*������ȡʧ��*/
#define  DRV_ERRNO_IO_WRITE_FAILED       	0xFFFFF707     /*IOд����ʧ��*/
#define  DRV_ERRNO_IO_READ_FAILED        	0xFFFFF708     /*IO������ʧ��*/
#define  DRV_ERRNO_IO_CHECK_FAILED       	0xFFFFF709     /*IOģ���Լ�ʧ��*/

/*�Լ�������*/
#define  DRV_ERRNO_COMPUT_INIT_FAILED           0xFFFFF800      /*���İ��ʼ��ʧ��*/
#define  DRV_ERRNO_COMPUT_DDR_ERRO              0xFFFFF801     	/*DDR��д����*/
#define  DRV_ERRNO_COMPUT_FLASH_ERRO            0xFFFFF802     	/*FLASH��д����*/
#define  DRV_ERRNO_COMPUT_TEMP_GET_FAILED       0xFFFFF803     	/*�¶Ȼ�ȡʧ��*/
#define  DRV_ERRNO_COMPUT_TEMP_OVER_RANGE       0xFFFFF804     	/*�¶ȳ�����Χ*/
#define  DRV_ERRNO_COMPUT_VCCINT_GET_FAILED     0xFFFFF805     	/*��ѹvccint��ȡʧ��*/
#define  DRV_ERRNO_COMPUT_VCCINT_OUT_RANGE      0xFFFFF806     	/*��ѹvccint������Χ*/
#define  DRV_ERRNO_COMPUT_VCPPAUX_GET_FAILED    0xFFFFF807     	/*��ѹvcppaux��ȡʧ��*/
#define  DRV_ERRNO_COMPUT_VCPPAUX_OUT_RANGE     0xFFFFF808     	/*��ѹvcppaux������Χ*/
#define  DRV_ERRNO_COMPUT_VBRAM_GET_FAILED      0xFFFFF809     	/*��ѹvbram��ȡʧ��*/
#define  DRV_ERRNO_COMPUT_VBRAM_OUT_RANGE       0xFFFFF80A     	/*��ѹvbram������Χ*/
#define  DRV_ERRNO_COMPUT_VCCAUX_GET_FAILED     0xFFFFF80B     	/*��ѹvccaux��ȡʧ��*/
#define  DRV_ERRNO_COMPUT_VCCAUX_OUT_RANGE      0xFFFFF80C     	/*��ѹvccaux������Χ*/
#define  DRV_ERRNO_COMPUT_VCCPINT_GET_FAILED    0xFFFFF80D     	/*��ѹvccpint��ȡʧ��*/
#define  DRV_ERRNO_COMPUT_VCCPINT_OUT_RANGE     0xFFFFF80E     	/*��ѹvccpint������Χ*/
#define  DRV_ERRNO_COMPUT_ETH0_PHY_GET_FAILED   0xFFFFF80F     	/*����0��дPHYʧ��*/
#define  DRV_ERRNO_COMPUT_ETH0_NO_LINK          0xFFFFF810     	/*����0û������*/
#define  DRV_ERRNO_COMPUT_ETH0_OPEN_FAILED      0xFFFFF811     	/*����0��ʧ��*/
#define  DRV_ERRNO_COMPUT_ETH1_PHY_GET_FAILED   0xFFFFF812     	/*����1��дPHYʧ��*/
#define  DRV_ERRNO_COMPUT_ETH1_NO_LINK          0xFFFFF813     	/*����1û������*/
#define  DRV_ERRNO_COMPUT_ETH1_OPEN_FAILED      0xFFFFF814     	/*����1��ʧ��*/

/*�����ڴ������*/
#define  DRV_ERRNO_GNET_NOT_EXIST          	0xFFFFF900     /*�������豸������*/
#define  DRV_ERRNO_GNET_PARARM_INVALID     	0xFFFFF901     /*����������Ϸ�*/
#define  DRV_ERRNO_GNET_OPEN_FAILED        	0xFFFFF902     /*�豸��ʧ��*/
#define  DRV_ERRNO_GNET_CLOSE_FAILED       	0xFFFFF903     /*�豸�ر�ʧ��*/
#define  DRV_ERRNO_GNET_PARARM_SET_FAILED  	0xFFFFF904     /*��������ʧ��*/
#define  DRV_ERRNO_GNET_PARARM_GET_FAILED  	0xFFFFF905     /*������ȡʧ��*/
#define  DRV_ERRNO_GNET_TXFIFO_NOT_EMPTY   	0xFFFFF906     /*GNET����FIFO��Ϊ��*/
#define  DRV_ERRNO_GNET_SEND_FAILED        	0xFFFFF907     /*GNET��������ʧ��*/
#define  DRV_ERRNO_GNET_READ_FAILED        	0xFFFFF908     /*GNET������ʧ��*/
#define  DRV_ERRNO_GNET_READ_BUF_NULL      	0xFFFFF909     /*GNET��������Ϊ��*/
#define  DRV_ERRNO_GNET_READ_BUF_LESS      	0xFFFFF90A     /*GNET�����������ݲ���*/
#define  DRV_ERRNO_GNET_READ_TIMEOUT       	0xFFFFF90B     /*GNET�����ݳ�ʱ*/
#define  DRV_ERRNO_GNET_BUS_DISCONNECT     	0xFFFFF90C     /*GNET���߲�ͨ*/
#define  DRV_ERRNO_GNET_INIT_FAILED	       	0xFFFFF90D     /*GNET���߳�ʼ��ʧ��*/

/*CAN�������*/
#define  DRV_ERRNO_CAN_NOT_EXIST          	0xFFFFFA00     /*uart�豸������*/
#define  DRV_ERRNO_CAN_PARARM_INVALID     	0xFFFFFA01     /*����������Ϸ�*/
#define  DRV_ERRNO_CAN_OPEN_FAILED        	0xFFFFFA02     /*�豸��ʧ��*/
#define  DRV_ERRNO_CAN_CLOSE_FAILED       	0xFFFFFA03     /*�豸�ر�ʧ��*/
#define  DRV_ERRNO_CAN_PARARM_SET_FAILED  	0xFFFFFA04     /*��������ʧ��*/
#define  DRV_ERRNO_CAN_TXFIFO_FULL        	0xFFFFFA05     /*����FIFO���*/

/*EMIFF�������*/
#define  DRV_ERRNO_EMIFF_ADDR_SET_FAILED  	0xFFFFFB01     /*emiffоƬվ��ַ����ʧ��*/
#define  DRV_ERRNO_EMIFF_PARAM_INVALIDE   	0xFFFFFB02     /*����������Ϸ�*/
#define  DRV_ERRNO_EMIFF_REG_WRITE_FAILED 	0xFFFFFB03     /*д�Ĵ���ʧ��*/