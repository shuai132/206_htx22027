#define  DRV_OPERATE_SUCCESS        		0x00000000     /*操作成功*/

/*I2C错误代码*/
#define  DRV_ERRNO_IIC_NOT_EXIST          	0xFFFFF000     /*i2c设备不存在*/
#define  DRV_ERRNO_IIC_PARARM_INVALID     	0xFFFFF001     /*输入参数不合法*/
#define  DRV_ERRNO_IIC_INIT_FAILED        	0xFFFFF002     /*设备初始化失败*/
#define  DRV_ERRNO_IIC_OPEN_FAILED        	0xFFFFF003     /*设备打开失败*/
#define  DRV_ERRNO_IIC_CLOSE_FAILED       	0xFFFFF004     /*设备关闭失败*/
#define  DRV_ERRNO_IIC_PARARM_SET_FAILED  	0xFFFFF005     /*参数设置失败*/
#define  DRV_ERRNO_IIC_PARARM_GET_FAILED  	0xFFFFF006     /*参数获取失败*/
#define  DRV_ERRNO_IIC_WRITE_FAILED       	0xFFFFF007     /*i2c写数据失败*/
#define  DRV_ERRNO_IIC_READ_FAILED        	0xFFFFF008     /*i2c读数据失败*/
#define  DRV_ERRNO_IIC_READ_BUF_NULL      	0xFFFFF009     /*i2c读缓冲区为空*/
#define  DRV_ERRNO_IIC_READ_BUF_LESS      	0xFFFFF00A     /*i2c读缓冲区数据不够*/
#define  DRV_ERRNO_IIC_READ_TIMEOUT       	0xFFFFF00B     /*i2c读数据超时*/
#define  DRV_ERRNO_IIC_BUS_DISCONNECT     	0xFFFFF00C     /*i2c总线不通*/
/*总线忙*/

/*以太网错误代码*/
#define  DRV_ERRNO_NET_DEV_NOT_EXIST      	0xFFFFF100     /*网卡设备不存在*/
#define  DRV_ERRNO_NET_INIT_FAILED        	0xFFFFF101     /*以太网初始化失败*/
#define  DRV_ERRNO_NET_PARARM_INVALID     	0xFFFFF102     /*输入参数不合法*/
#define  DRV_ERRNO_NET_SET_ADDR_FAILED    	0xFFFFF103     /*IP地址设置失败*/
#define  DRV_ERRNO_NET_GET_ADDR_FAILED    	0xFFFFF104     /*IP地址获取失败*/
#define  DRV_ERRNO_ETH0_NO_LINK           	0xFFFFF105     /*网卡0不通*/
#define  DRV_ERRNO_ETH1_NO_LINK           	0xFFFFF106     /*网卡1不通*/
#define  DRV_ERRNO_ETH0_DOWN              	0xFFFFF107     /*网卡0没有打开*/
#define  DRV_ERRNO_ETH1_DOWN              	0xFFFFF108     /*网卡1没有打开*/

/*422错误代码*/
#define  DRV_ERRNO_UART_NOT_EXIST          	0xFFFFF200     /*uart设备不存在*/
#define  DRV_ERRNO_UART_PARARM_INVALID     	0xFFFFF201     /*输入参数不合法*/
#define  DRV_ERRNO_UART_OPEN_FAILED        	0xFFFFF202     /*设备打开失败*/
#define  DRV_ERRNO_UART_CLOSE_FAILED       	0xFFFFF203     /*设备关闭失败*/
#define  DRV_ERRNO_UART_PARARM_SET_FAILED  	0xFFFFF204     /*参数设置失败*/
#define  DRV_ERRNO_UART_PARARM_GET_FAILED  	0xFFFFF205     /*参数获取失败*/
#define  DRV_ERRNO_UART_TXFIFO_NOT_EMPTY   	0xFFFFF206     /*uart发送FIFO不为空*/
#define  DRV_ERRNO_UART_SEND_FAILED        	0xFFFFF207     /*uart发送数据失败*/
#define  DRV_ERRNO_UART_READ_FAILED        	0xFFFFF208     /*uart读数据失败*/
#define  DRV_ERRNO_UART_READ_BUF_NULL      	0xFFFFF209     /*uart读缓冲区为空*/
#define  DRV_ERRNO_UART_READ_BUF_LESS      	0xFFFFF20A     /*uart读缓冲区数据不够*/
#define  DRV_ERRNO_UART_READ_TIMEOUT       	0xFFFFF20B     /*uart读数据超时*/
#define  DRV_ERRNO_UART_BUS_DISCONNECT     	0xFFFFF20C     /*uart总线不通*/
#define  DRV_ERRNO_UART_CHECK_FAILED       	0xFFFFF20D     /*uart驱动模块自检失败*/

/*BMC错误代码*/
#define  DRV_ERRNO_BMC_INFO_GET_FAILED    	0xFFFFF300     /*BMC信息获取失败*/
#define  DRV_ERRNO_BMC_PARARM_INVALID     	0xFFFFF301     /*BMC输入参数不合法*/
#define  DRV_ERRNO_BMC_INFO_SET_FAILED    	0xFFFFF302     /*BMC信息设置失败*/
#define  DRV_ERRNO_BMC_INIT_FAILED        	0xFFFFF303     /*BMC初始化失败*/
#define  DRV_ERRNO_BMC_USER_NOT_EXIST     	0xFFFFF304     /*用户不存在*/
#define  DRV_ERRNO_BMC_USER_NOT_ADMIN     	0xFFFFF305     /*用户没有管理员权限*/
#define  DRV_ERRNO_BMC_USER_CREATE_FAILED 	0xFFFFF306     /*BMC初始化失败*/
#define  DRV_ERRNO_BMC_USER_ADD_FAILED    	0xFFFFF307     /*BMC添加失败*/
#define  DRV_ERRNO_BMC_CFG_READ_FAILED    	0xFFFFF308     /*BMC读配置文件失败*/
#define  DRV_ERRNO_BMC_USER_UPD_FAILED    	0xFFFFF309     /*BMC用户信息更新失败*/
#define  DRV_ERRNO_BMC_USER_DEL_FAILED    	0xFFFFF30a     /*BMC用户信息删除失败*/

/*ADC错误代码*/
#define  DRV_ERRNO_ADC_NOT_EXIST          	0xFFFFF400     /*ADC设备不存在*/
#define  DRV_ERRNO_ADC_PARARM_INVALID     	0xFFFFF401     /*输入参数不合法*/
#define  DRV_ERRNO_ADC_OPEN_FAILED        	0xFFFFF402     /*设备打开失败*/
#define  DRV_ERRNO_ADC_PARARM_SET_FAILED  	0xFFFFF403     /*参数设置失败*/
#define  DRV_ERRNO_ADC_PARARM_GET_FAILED  	0xFFFFF404     /*参数获取失败*/
#define  DRV_ERRNO_ADC_READ_FAILED        	0xFFFFF405     /*ADC采样值读取失败*/
#define  DRV_ERRNO_ADC_CLOSE_FAILED       	0xFFFFF406     /*ADC采样通道关闭失败*/
#define  DRV_ERRNO_ADC_MODE_SET_FAILED    	0xFFFFF407     /*ADC采样采样模式配置失败*/
#define  DRV_ERRNO_ADC_CHNO_SET_FAILED    	0xFFFFF408     /*ADC采样采样通道配置失败*/
#define  DRV_ERRNO_ADC_BAUD_SET_FAILED    	0xFFFFF409     /*ADC采样采样频率配置失败*/
#define  DRV_ERRNO_ADC_CHECK_FAILED       	0xFFFFF40A     /*ADC模块自检失败*/
#define  DRV_ERRNO_ADC_ISRCB_FAILED       	0xFFFFF40B     /*ADC中断入口函数注册失败*/

/*定时器错误代码*/
#define  DRV_ERRNO_CLK_NOT_EXIST          	0xFFFFF500     /*定时器设备不存在*/
#define  DRV_ERRNO_CLK_INIT_FAILED        	0xFFFFF501     /*定时器初始化失败*/
#define  DRV_ERRNO_CLK_PARARM_INVALID     	0xFFFFF502     /*输入参数不合法*/
#define  DRV_ERRNO_CLK_OPEN_FAILED        	0xFFFFF503     /*设备打开失败*/
#define  DRV_ERRNO_CLK_CLOSE_FAILED       	0xFFFFF504     /*设备关闭失败*/
#define  DRV_ERRNO_CLK_PARARM_SET_FAILED  	0xFFFFF505     /*参数设置失败*/
#define  DRV_ERRNO_CLK_PARARM_GET_FAILED  	0xFFFFF506     /*参数获取失败*/
#define  DRV_ERRNO_CLK_READ_FAILED        	0xFFFFF507     /*定时器状态读取失败*/
#define  DRV_ERRNO_CLK_CHECK_FAILED       	0xFFFFF508     /*定时器模块自检失败*/

/*OTA错误代码*/
#define  DRV_ERRNO_OTA_NOT_EXIST          	0xFFFFF600     /*OTA服务不存在*/
#define  DRV_ERRNO_OTA_PARARM_INVALID     	0xFFFFF601     /*输入参数不合法*/
#define  DRV_ERRNO_OTA_INIT_FAILED        	0xFFFFF602     /*OTA服务初始化失败*/
#define  DRV_ERRNO_OTA_OPEN_FAILED        	0xFFFFF603     /*OTA服务打开失败*/
#define  DRV_ERRNO_OTA_CLOSE_FAILED       	0xFFFFF604     /*OTA服务关闭失败*/
#define  DRV_ERRNO_OTA_INSTALL_FAILED     	0xFFFFF605     /*OTA升级包安装失败*/
#define  DRV_ERRNO_OTA_VERIFY_FAILED      	0xFFFFF606     /*OTA升级包校验失败*/

/*IO错误代码*/
#define  DRV_ERRNO_IO_NOT_EXIST          	0xFFFFF700     /*IO不存在*/
#define  DRV_ERRNO_IO_INIT_FAILED        	0xFFFFF701     /*IO初始化失败*/
#define  DRV_ERRNO_IO_PARARM_INVALID     	0xFFFFF702     /*输入参数不合法*/
#define  DRV_ERRNO_IO_OPEN_FAILED        	0xFFFFF703     /*IO打开失败*/
#define  DRV_ERRNO_IO_CLOSE_FAILED       	0xFFFFF704     /*IO关闭失败*/
#define  DRV_ERRNO_IO_PARARM_SET_FAILED  	0xFFFFF705     /*参数设置失败*/
#define  DRV_ERRNO_IO_PARARM_GET_FAILED  	0xFFFFF706     /*参数获取失败*/
#define  DRV_ERRNO_IO_WRITE_FAILED       	0xFFFFF707     /*IO写数据失败*/
#define  DRV_ERRNO_IO_READ_FAILED        	0xFFFFF708     /*IO读数据失败*/
#define  DRV_ERRNO_IO_CHECK_FAILED       	0xFFFFF709     /*IO模块自检失败*/

/*自检错误代码*/
#define  DRV_ERRNO_COMPUT_INIT_FAILED           0xFFFFF800      /*核心板初始化失败*/
#define  DRV_ERRNO_COMPUT_DDR_ERRO              0xFFFFF801     	/*DDR读写错误*/
#define  DRV_ERRNO_COMPUT_FLASH_ERRO            0xFFFFF802     	/*FLASH读写错误*/
#define  DRV_ERRNO_COMPUT_TEMP_GET_FAILED       0xFFFFF803     	/*温度获取失败*/
#define  DRV_ERRNO_COMPUT_TEMP_OVER_RANGE       0xFFFFF804     	/*温度超出范围*/
#define  DRV_ERRNO_COMPUT_VCCINT_GET_FAILED     0xFFFFF805     	/*电压vccint获取失败*/
#define  DRV_ERRNO_COMPUT_VCCINT_OUT_RANGE      0xFFFFF806     	/*电压vccint超出范围*/
#define  DRV_ERRNO_COMPUT_VCPPAUX_GET_FAILED    0xFFFFF807     	/*电压vcppaux获取失败*/
#define  DRV_ERRNO_COMPUT_VCPPAUX_OUT_RANGE     0xFFFFF808     	/*电压vcppaux超出范围*/
#define  DRV_ERRNO_COMPUT_VBRAM_GET_FAILED      0xFFFFF809     	/*电压vbram获取失败*/
#define  DRV_ERRNO_COMPUT_VBRAM_OUT_RANGE       0xFFFFF80A     	/*电压vbram超出范围*/
#define  DRV_ERRNO_COMPUT_VCCAUX_GET_FAILED     0xFFFFF80B     	/*电压vccaux获取失败*/
#define  DRV_ERRNO_COMPUT_VCCAUX_OUT_RANGE      0xFFFFF80C     	/*电压vccaux超出范围*/
#define  DRV_ERRNO_COMPUT_VCCPINT_GET_FAILED    0xFFFFF80D     	/*电压vccpint获取失败*/
#define  DRV_ERRNO_COMPUT_VCCPINT_OUT_RANGE     0xFFFFF80E     	/*电压vccpint超出范围*/
#define  DRV_ERRNO_COMPUT_ETH0_PHY_GET_FAILED   0xFFFFF80F     	/*网卡0读写PHY失败*/
#define  DRV_ERRNO_COMPUT_ETH0_NO_LINK          0xFFFFF810     	/*网卡0没有连接*/
#define  DRV_ERRNO_COMPUT_ETH0_OPEN_FAILED      0xFFFFF811     	/*网卡0打开失败*/
#define  DRV_ERRNO_COMPUT_ETH1_PHY_GET_FAILED   0xFFFFF812     	/*网卡1读写PHY失败*/
#define  DRV_ERRNO_COMPUT_ETH1_NO_LINK          0xFFFFF813     	/*网卡1没有连接*/
#define  DRV_ERRNO_COMPUT_ETH1_OPEN_FAILED      0xFFFFF814     	/*网卡1打开失败*/

/*光网口错误代码*/
#define  DRV_ERRNO_GNET_NOT_EXIST          	0xFFFFF900     /*光网口设备不存在*/
#define  DRV_ERRNO_GNET_PARARM_INVALID     	0xFFFFF901     /*输入参数不合法*/
#define  DRV_ERRNO_GNET_OPEN_FAILED        	0xFFFFF902     /*设备打开失败*/
#define  DRV_ERRNO_GNET_CLOSE_FAILED       	0xFFFFF903     /*设备关闭失败*/
#define  DRV_ERRNO_GNET_PARARM_SET_FAILED  	0xFFFFF904     /*参数设置失败*/
#define  DRV_ERRNO_GNET_PARARM_GET_FAILED  	0xFFFFF905     /*参数获取失败*/
#define  DRV_ERRNO_GNET_TXFIFO_NOT_EMPTY   	0xFFFFF906     /*GNET发送FIFO不为空*/
#define  DRV_ERRNO_GNET_SEND_FAILED        	0xFFFFF907     /*GNET发送数据失败*/
#define  DRV_ERRNO_GNET_READ_FAILED        	0xFFFFF908     /*GNET读数据失败*/
#define  DRV_ERRNO_GNET_READ_BUF_NULL      	0xFFFFF909     /*GNET读缓冲区为空*/
#define  DRV_ERRNO_GNET_READ_BUF_LESS      	0xFFFFF90A     /*GNET读缓冲区数据不够*/
#define  DRV_ERRNO_GNET_READ_TIMEOUT       	0xFFFFF90B     /*GNET读数据超时*/
#define  DRV_ERRNO_GNET_BUS_DISCONNECT     	0xFFFFF90C     /*GNET总线不通*/
#define  DRV_ERRNO_GNET_INIT_FAILED	       	0xFFFFF90D     /*GNET总线初始化失败*/

/*CAN错误代码*/
#define  DRV_ERRNO_CAN_NOT_EXIST          	0xFFFFFA00     /*uart设备不存在*/
#define  DRV_ERRNO_CAN_PARARM_INVALID     	0xFFFFFA01     /*输入参数不合法*/
#define  DRV_ERRNO_CAN_OPEN_FAILED        	0xFFFFFA02     /*设备打开失败*/
#define  DRV_ERRNO_CAN_CLOSE_FAILED       	0xFFFFFA03     /*设备关闭失败*/
#define  DRV_ERRNO_CAN_PARARM_SET_FAILED  	0xFFFFFA04     /*参数设置失败*/
#define  DRV_ERRNO_CAN_TXFIFO_FULL        	0xFFFFFA05     /*发送FIFO溢出*/

/*EMIFF错误代码*/
#define  DRV_ERRNO_EMIFF_ADDR_SET_FAILED  	0xFFFFFB01     /*emiff芯片站地址设置失败*/
#define  DRV_ERRNO_EMIFF_PARAM_INVALIDE   	0xFFFFFB02     /*输入参数不合法*/
#define  DRV_ERRNO_EMIFF_REG_WRITE_FAILED 	0xFFFFFB03     /*写寄存器失败*/