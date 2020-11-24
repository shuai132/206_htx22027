#ifndef XPARAMETERS_H   /* prevent circular inclusions */
#define XPARAMETERS_H   /* by using protection macros */

/* Definition for CPU ID */
#define XPAR_CPU_ID 0U

/* Definitions for peripheral PS7_CORTEXA9_0 */
#define XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ 666666687


/******************************************************************/

/* Canonical definitions for peripheral PS7_CORTEXA9_0 */
#define XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ 666666687


/******************************************************************/

#include "xparameters_ps.h"

#define STDIN_BASEADDRESS 0xE0000000
#define STDOUT_BASEADDRESS 0xE0000000

/******************************************************************/

/* Platform specific definitions */
#define PLATFORM_ZYNQ
 
/* Definitions for sleep timer configuration */
#define XSLEEP_TIMER_IS_DEFAULT_TIMER
 
 
/******************************************************************/
/* Definitions for driver AXIETHERNET */
#define XPAR_XAXIETHERNET_NUM_INSTANCES 2U
/* Definitions related to PCS PMA PL IP*/
#define XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT 1U
#define XPAR_PCSPMA_1000BASEX_PHYADDR 1U

/******************************************************************/

/* Definitions for peripheral AXI_ETHERNET_0 */
#define XPAR_AXI_ETHERNET_0_DEVICE_ID 0U
#define XPAR_AXI_ETHERNET_0_BASEADDR 0x70100000U
#define XPAR_AXI_ETHERNET_0_HIGHADDR 0x7011FFFFU
#define XPAR_AXI_ETHERNET_0_TYPE 1U
#define XPAR_AXI_ETHERNET_0_TXCSUM 0U
#define XPAR_AXI_ETHERNET_0_RXCSUM 0U
#define XPAR_AXI_ETHERNET_0_PHY_TYPE 5U
#define XPAR_AXI_ETHERNET_0_TXVLAN_TRAN 0U
#define XPAR_AXI_ETHERNET_0_RXVLAN_TRAN 0U
#define XPAR_AXI_ETHERNET_0_TXVLAN_TAG 0U
#define XPAR_AXI_ETHERNET_0_RXVLAN_TAG 0U
#define XPAR_AXI_ETHERNET_0_TXVLAN_STRP 0U
#define XPAR_AXI_ETHERNET_0_RXVLAN_STRP 0U
#define XPAR_AXI_ETHERNET_0_MCAST_EXTEND 0U
#define XPAR_AXI_ETHERNET_0_STATS 1U
#define XPAR_AXI_ETHERNET_0_AVB 0U
#define XPAR_AXI_ETHERNET_0_Enable_1588 0U
#define XPAR_AXI_ETHERNET_0_SPEED 1000U
#define XPAR_AXI_ETHERNET_0_PHYADDR 1U

/* Canonical definitions for peripheral AXI_ETHERNET_0 */
#define XPAR_AXIETHERNET_0_DEVICE_ID 0U
#define XPAR_AXIETHERNET_0_BASEADDR 0x70100000U
#define XPAR_AXIETHERNET_0_HIGHADDR 0x7011FFFFU
#define XPAR_AXIETHERNET_0_TEMAC_TYPE 1U
#define XPAR_AXIETHERNET_0_TXCSUM 0U
#define XPAR_AXIETHERNET_0_RXCSUM 0U
#define XPAR_AXIETHERNET_0_PHY_TYPE 5U
#define XPAR_AXIETHERNET_0_TXVLAN_TRAN 0U
#define XPAR_AXIETHERNET_0_RXVLAN_TRAN 0U
#define XPAR_AXIETHERNET_0_TXVLAN_TAG 0U
#define XPAR_AXIETHERNET_0_RXVLAN_TAG 0U
#define XPAR_AXIETHERNET_0_TXVLAN_STRP 0U
#define XPAR_AXIETHERNET_0_RXVLAN_STRP 0U
#define XPAR_AXIETHERNET_0_MCAST_EXTEND 0U
#define XPAR_AXIETHERNET_0_STATS 1U
#define XPAR_AXIETHERNET_0_AVB 0U
#define XPAR_AXIETHERNET_0_ENABLE_SGMII_OVER_LVDS 0U
#define XPAR_AXIETHERNET_0_ENABLE_1588 0U
#define XPAR_AXIETHERNET_0_SPEED 1000U
#define XPAR_AXIETHERNET_0_NUM_TABLE_ENTRIES 4U
#define XPAR_AXIETHERNET_0_PHYADDR 1U
#define XPAR_AXIETHERNET_0_INTR 0xFFU


/* Definitions related to PCS PMA PL IP*/
#define XPAR_GIGE_PCS_PMA_1000BASEX_CORE_PRESENT 1U
#define XPAR_PCSPMA_1000BASEX_PHYADDR 1U

/******************************************************************/

/* Definitions for peripheral AXI_ETHERNET_1 */
#define XPAR_AXI_ETHERNET_1_DEVICE_ID 1U
#define XPAR_AXI_ETHERNET_1_BASEADDR 0x70120000U
#define XPAR_AXI_ETHERNET_1_HIGHADDR 0x7013FFFFU
#define XPAR_AXI_ETHERNET_1_TYPE 1U
#define XPAR_AXI_ETHERNET_1_TXCSUM 0U
#define XPAR_AXI_ETHERNET_1_RXCSUM 0U
#define XPAR_AXI_ETHERNET_1_PHY_TYPE 5U
#define XPAR_AXI_ETHERNET_1_TXVLAN_TRAN 0U
#define XPAR_AXI_ETHERNET_1_RXVLAN_TRAN 0U
#define XPAR_AXI_ETHERNET_1_TXVLAN_TAG 0U
#define XPAR_AXI_ETHERNET_1_RXVLAN_TAG 0U
#define XPAR_AXI_ETHERNET_1_TXVLAN_STRP 0U
#define XPAR_AXI_ETHERNET_1_RXVLAN_STRP 0U
#define XPAR_AXI_ETHERNET_1_MCAST_EXTEND 0U
#define XPAR_AXI_ETHERNET_1_STATS 1U
#define XPAR_AXI_ETHERNET_1_AVB 0U
#define XPAR_AXI_ETHERNET_1_Enable_1588 0U
#define XPAR_AXI_ETHERNET_1_SPEED 1000U
#define XPAR_AXI_ETHERNET_1_PHYADDR 1U

/* Canonical definitions for peripheral AXI_ETHERNET_1 */
#define XPAR_AXIETHERNET_1_DEVICE_ID 1U
#define XPAR_AXIETHERNET_1_BASEADDR 0x70120000U
#define XPAR_AXIETHERNET_1_HIGHADDR 0x7013FFFFU
#define XPAR_AXIETHERNET_1_TEMAC_TYPE 1U
#define XPAR_AXIETHERNET_1_TXCSUM 0U
#define XPAR_AXIETHERNET_1_RXCSUM 0U
#define XPAR_AXIETHERNET_1_PHY_TYPE 5U
#define XPAR_AXIETHERNET_1_TXVLAN_TRAN 0U
#define XPAR_AXIETHERNET_1_RXVLAN_TRAN 0U
#define XPAR_AXIETHERNET_1_TXVLAN_TAG 0U
#define XPAR_AXIETHERNET_1_RXVLAN_TAG 0U
#define XPAR_AXIETHERNET_1_TXVLAN_STRP 0U
#define XPAR_AXIETHERNET_1_RXVLAN_STRP 0U
#define XPAR_AXIETHERNET_1_MCAST_EXTEND 0U
#define XPAR_AXIETHERNET_1_STATS 1U
#define XPAR_AXIETHERNET_1_AVB 0U
#define XPAR_AXIETHERNET_1_ENABLE_SGMII_OVER_LVDS 0U
#define XPAR_AXIETHERNET_1_ENABLE_1588 0U
#define XPAR_AXIETHERNET_1_SPEED 1000U
#define XPAR_AXIETHERNET_1_NUM_TABLE_ENTRIES 4U
#define XPAR_AXIETHERNET_1_PHYADDR 1U
#define XPAR_AXIETHERNET_1_INTR 0xFFU


/* AxiEthernet TYPE Enumerations */
#define XPAR_AXI_FIFO    1U
#define XPAR_AXI_DMA     2U
#define XPAR_AXI_MCDMA   3U


/* Canonical Axi parameters for AXI_ETHERNET_0 */

/* Canonical Axi parameters for AXI_ETHERNET_1 */

/******************************************************************/

/* Definitions for driver CAN */
#define XPAR_XCAN_NUM_INSTANCES 1

/* Definitions for peripheral CAN_0 */
#define XPAR_CAN_0_DEVICE_ID 0
#define XPAR_CAN_0_BASEADDR 0x7002B000
#define XPAR_CAN_0_HIGHADDR 0x7002BFFF
#define XPAR_CAN_0_CAN_RX_DPTH 64
#define XPAR_CAN_0_CAN_TX_DPTH 64
#define XPAR_CAN_0_CAN_NUM_ACF 0


/******************************************************************/


/******************************************************************/


/* Definitions for peripheral PS7_DDR_0 */
#define XPAR_PS7_DDR_0_S_AXI_BASEADDR 0x00100000
#define XPAR_PS7_DDR_0_S_AXI_HIGHADDR 0x1FFFFFFF


/******************************************************************/

/* Definitions for driver DEVCFG */
#define XPAR_XDCFG_NUM_INSTANCES 1U

/* Definitions for peripheral PS7_DEV_CFG_0 */
#define XPAR_PS7_DEV_CFG_0_DEVICE_ID 0U
#define XPAR_PS7_DEV_CFG_0_BASEADDR 0xF8007000U
#define XPAR_PS7_DEV_CFG_0_HIGHADDR 0xF80070FFU


/******************************************************************/

/* Canonical definitions for peripheral PS7_DEV_CFG_0 */
#define XPAR_XDCFG_0_DEVICE_ID XPAR_PS7_DEV_CFG_0_DEVICE_ID
#define XPAR_XDCFG_0_BASEADDR 0xF8007000U
#define XPAR_XDCFG_0_HIGHADDR 0xF80070FFU


/******************************************************************/

/* Definitions for driver DMAPS */
#define XPAR_XDMAPS_NUM_INSTANCES 2

/* Definitions for peripheral PS7_DMA_NS */
#define XPAR_PS7_DMA_NS_DEVICE_ID 0
#define XPAR_PS7_DMA_NS_BASEADDR 0xF8004000
#define XPAR_PS7_DMA_NS_HIGHADDR 0xF8004FFF


/* Definitions for peripheral PS7_DMA_S */
#define XPAR_PS7_DMA_S_DEVICE_ID 1
#define XPAR_PS7_DMA_S_BASEADDR 0xF8003000
#define XPAR_PS7_DMA_S_HIGHADDR 0xF8003FFF


/******************************************************************/

/* Canonical definitions for peripheral PS7_DMA_NS */
#define XPAR_XDMAPS_0_DEVICE_ID XPAR_PS7_DMA_NS_DEVICE_ID
#define XPAR_XDMAPS_0_BASEADDR 0xF8004000
#define XPAR_XDMAPS_0_HIGHADDR 0xF8004FFF

/* Canonical definitions for peripheral PS7_DMA_S */
#define XPAR_XDMAPS_1_DEVICE_ID XPAR_PS7_DMA_S_DEVICE_ID
#define XPAR_XDMAPS_1_BASEADDR 0xF8003000
#define XPAR_XDMAPS_1_HIGHADDR 0xF8003FFF


/******************************************************************/

/* Definitions for driver EMACPS */
#define XPAR_XEMACPS_NUM_INSTANCES 2

/* Definitions for peripheral PS7_ETHERNET_0 */
#define XPAR_PS7_ETHERNET_0_DEVICE_ID 0
#define XPAR_PS7_ETHERNET_0_BASEADDR 0xE000B000
#define XPAR_PS7_ETHERNET_0_HIGHADDR 0xE000BFFF
#define XPAR_PS7_ETHERNET_0_ENET_CLK_FREQ_HZ 125000000
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_1000MBPS_DIV0 8
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_1000MBPS_DIV1 1
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_100MBPS_DIV0 8
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_100MBPS_DIV1 5
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_10MBPS_DIV0 8
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_10MBPS_DIV1 50
#define XPAR_PS7_ETHERNET_0_ENET_TSU_CLK_FREQ_HZ 0


/* Definitions for peripheral PS7_ETHERNET_1 */
#define XPAR_PS7_ETHERNET_1_DEVICE_ID 1
#define XPAR_PS7_ETHERNET_1_BASEADDR 0xE000C000
#define XPAR_PS7_ETHERNET_1_HIGHADDR 0xE000CFFF
#define XPAR_PS7_ETHERNET_1_ENET_CLK_FREQ_HZ 125000000
#define XPAR_PS7_ETHERNET_1_ENET_SLCR_1000MBPS_DIV0 1
#define XPAR_PS7_ETHERNET_1_ENET_SLCR_1000MBPS_DIV1 1
#define XPAR_PS7_ETHERNET_1_ENET_SLCR_100MBPS_DIV0 1
#define XPAR_PS7_ETHERNET_1_ENET_SLCR_100MBPS_DIV1 5
#define XPAR_PS7_ETHERNET_1_ENET_SLCR_10MBPS_DIV0 1
#define XPAR_PS7_ETHERNET_1_ENET_SLCR_10MBPS_DIV1 50
#define XPAR_PS7_ETHERNET_1_ENET_TSU_CLK_FREQ_HZ 0


/******************************************************************/

#define XPAR_PS7_ETHERNET_0_IS_CACHE_COHERENT 0
#define XPAR_XEMACPS_0_IS_CACHE_COHERENT 0
#define XPAR_PS7_ETHERNET_1_IS_CACHE_COHERENT 0
#define XPAR_XEMACPS_1_IS_CACHE_COHERENT 0
/* Canonical definitions for peripheral PS7_ETHERNET_0 */
#define XPAR_XEMACPS_0_DEVICE_ID XPAR_PS7_ETHERNET_0_DEVICE_ID
#define XPAR_XEMACPS_0_BASEADDR 0xE000B000
#define XPAR_XEMACPS_0_HIGHADDR 0xE000BFFF
#define XPAR_XEMACPS_0_ENET_CLK_FREQ_HZ 125000000
#define XPAR_XEMACPS_0_ENET_SLCR_1000Mbps_DIV0 8
#define XPAR_XEMACPS_0_ENET_SLCR_1000Mbps_DIV1 1
#define XPAR_XEMACPS_0_ENET_SLCR_100Mbps_DIV0 8
#define XPAR_XEMACPS_0_ENET_SLCR_100Mbps_DIV1 5
#define XPAR_XEMACPS_0_ENET_SLCR_10Mbps_DIV0 8
#define XPAR_XEMACPS_0_ENET_SLCR_10Mbps_DIV1 50
#define XPAR_XEMACPS_0_ENET_TSU_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PS7_ETHERNET_1 */
#define XPAR_XEMACPS_1_DEVICE_ID XPAR_PS7_ETHERNET_1_DEVICE_ID
#define XPAR_XEMACPS_1_BASEADDR 0xE000C000
#define XPAR_XEMACPS_1_HIGHADDR 0xE000CFFF
#define XPAR_XEMACPS_1_ENET_CLK_FREQ_HZ 125000000
#define XPAR_XEMACPS_1_ENET_SLCR_1000Mbps_DIV0 1
#define XPAR_XEMACPS_1_ENET_SLCR_1000Mbps_DIV1 1
#define XPAR_XEMACPS_1_ENET_SLCR_100Mbps_DIV0 1
#define XPAR_XEMACPS_1_ENET_SLCR_100Mbps_DIV1 5
#define XPAR_XEMACPS_1_ENET_SLCR_10Mbps_DIV0 1
#define XPAR_XEMACPS_1_ENET_SLCR_10Mbps_DIV1 50
#define XPAR_XEMACPS_1_ENET_TSU_CLK_FREQ_HZ 0


/******************************************************************/


/* Definitions for peripheral GMII_CTRL_0 */
#define XPAR_GMII_CTRL_0_BASEADDR 0x70000000
#define XPAR_GMII_CTRL_0_HIGHADDR 0x7000FFFF


/* Definitions for peripheral GMII_CTRL_1 */
#define XPAR_GMII_CTRL_1_BASEADDR 0x70010000
#define XPAR_GMII_CTRL_1_HIGHADDR 0x7001FFFF


/* Definitions for peripheral PS7_AFI_0 */
#define XPAR_PS7_AFI_0_S_AXI_BASEADDR 0xF8008000
#define XPAR_PS7_AFI_0_S_AXI_HIGHADDR 0xF8008FFF


/* Definitions for peripheral PS7_AFI_1 */
#define XPAR_PS7_AFI_1_S_AXI_BASEADDR 0xF8009000
#define XPAR_PS7_AFI_1_S_AXI_HIGHADDR 0xF8009FFF


/* Definitions for peripheral PS7_AFI_2 */
#define XPAR_PS7_AFI_2_S_AXI_BASEADDR 0xF800A000
#define XPAR_PS7_AFI_2_S_AXI_HIGHADDR 0xF800AFFF


/* Definitions for peripheral PS7_AFI_3 */
#define XPAR_PS7_AFI_3_S_AXI_BASEADDR 0xF800B000
#define XPAR_PS7_AFI_3_S_AXI_HIGHADDR 0xF800BFFF


/* Definitions for peripheral PS7_DDRC_0 */
#define XPAR_PS7_DDRC_0_S_AXI_BASEADDR 0xF8006000
#define XPAR_PS7_DDRC_0_S_AXI_HIGHADDR 0xF8006FFF


/* Definitions for peripheral PS7_GLOBALTIMER_0 */
#define XPAR_PS7_GLOBALTIMER_0_S_AXI_BASEADDR 0xF8F00200
#define XPAR_PS7_GLOBALTIMER_0_S_AXI_HIGHADDR 0xF8F002FF


/* Definitions for peripheral PS7_GPV_0 */
#define XPAR_PS7_GPV_0_S_AXI_BASEADDR 0xF8900000
#define XPAR_PS7_GPV_0_S_AXI_HIGHADDR 0xF89FFFFF


/* Definitions for peripheral PS7_INTC_DIST_0 */
#define XPAR_PS7_INTC_DIST_0_S_AXI_BASEADDR 0xF8F01000
#define XPAR_PS7_INTC_DIST_0_S_AXI_HIGHADDR 0xF8F01FFF


/* Definitions for peripheral PS7_IOP_BUS_CONFIG_0 */
#define XPAR_PS7_IOP_BUS_CONFIG_0_S_AXI_BASEADDR 0xE0200000
#define XPAR_PS7_IOP_BUS_CONFIG_0_S_AXI_HIGHADDR 0xE0200FFF


/* Definitions for peripheral PS7_L2CACHEC_0 */
#define XPAR_PS7_L2CACHEC_0_S_AXI_BASEADDR 0xF8F02000
#define XPAR_PS7_L2CACHEC_0_S_AXI_HIGHADDR 0xF8F02FFF


/* Definitions for peripheral PS7_OCMC_0 */
#define XPAR_PS7_OCMC_0_S_AXI_BASEADDR 0xF800C000
#define XPAR_PS7_OCMC_0_S_AXI_HIGHADDR 0xF800CFFF


/* Definitions for peripheral PS7_PL310_0 */
#define XPAR_PS7_PL310_0_S_AXI_BASEADDR 0xF8F02000
#define XPAR_PS7_PL310_0_S_AXI_HIGHADDR 0xF8F02FFF


/* Definitions for peripheral PS7_PMU_0 */
#define XPAR_PS7_PMU_0_S_AXI_BASEADDR 0xF8891000
#define XPAR_PS7_PMU_0_S_AXI_HIGHADDR 0xF8891FFF
#define XPAR_PS7_PMU_0_PMU1_S_AXI_BASEADDR 0xF8893000
#define XPAR_PS7_PMU_0_PMU1_S_AXI_HIGHADDR 0xF8893FFF


/* Definitions for peripheral PS7_QSPI_LINEAR_0 */
#define XPAR_PS7_QSPI_LINEAR_0_S_AXI_BASEADDR 0xFC000000
#define XPAR_PS7_QSPI_LINEAR_0_S_AXI_HIGHADDR 0xFCFFFFFF


/* Definitions for peripheral PS7_RAM_0 */
#define XPAR_PS7_RAM_0_S_AXI_BASEADDR 0x00000000
#define XPAR_PS7_RAM_0_S_AXI_HIGHADDR 0x0003FFFF


/* Definitions for peripheral PS7_RAM_1 */
#define XPAR_PS7_RAM_1_S_AXI_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_1_S_AXI_HIGHADDR 0xFFFFFFFF


/* Definitions for peripheral PS7_SCUC_0 */
#define XPAR_PS7_SCUC_0_S_AXI_BASEADDR 0xF8F00000
#define XPAR_PS7_SCUC_0_S_AXI_HIGHADDR 0xF8F000FC


/* Definitions for peripheral PS7_SLCR_0 */
#define XPAR_PS7_SLCR_0_S_AXI_BASEADDR 0xF8000000
#define XPAR_PS7_SLCR_0_S_AXI_HIGHADDR 0xF8000FFF


/* Definitions for peripheral TIMER_TOP_TIMER_0 */
#define XPAR_TIMER_TOP_TIMER_0_BASEADDR 0x70022000
#define XPAR_TIMER_TOP_TIMER_0_HIGHADDR 0x70022FFF


/* Definitions for peripheral TIMER_TOP_TIMER_1 */
#define XPAR_TIMER_TOP_TIMER_1_BASEADDR 0x70023000
#define XPAR_TIMER_TOP_TIMER_1_HIGHADDR 0x70023FFF


/* Definitions for peripheral TIMER_TOP_TIMER_2 */
#define XPAR_TIMER_TOP_TIMER_2_BASEADDR 0x70024000
#define XPAR_TIMER_TOP_TIMER_2_HIGHADDR 0x70024FFF


/* Definitions for peripheral TIMER_TOP_TIMER_3 */
#define XPAR_TIMER_TOP_TIMER_3_BASEADDR 0x70025000
#define XPAR_TIMER_TOP_TIMER_3_HIGHADDR 0x70025FFF


/* Definitions for peripheral TIMER_TOP_TIMER_4 */
#define XPAR_TIMER_TOP_TIMER_4_BASEADDR 0x70026000
#define XPAR_TIMER_TOP_TIMER_4_HIGHADDR 0x70026FFF


/* Definitions for peripheral TIMER_TOP_TIMER_5 */
#define XPAR_TIMER_TOP_TIMER_5_BASEADDR 0x70027000
#define XPAR_TIMER_TOP_TIMER_5_HIGHADDR 0x70027FFF


/* Definitions for peripheral TOP_IO_0 */
#define XPAR_TOP_IO_0_BASEADDR 0x70028000
#define XPAR_TOP_IO_0_HIGHADDR 0x70028FFF


/* Definitions for peripheral UART_UART_TOP_0 */
#define XPAR_UART_UART_TOP_0_BASEADDR 0x70020000
#define XPAR_UART_UART_TOP_0_HIGHADDR 0x70020FFF


/* Definitions for peripheral UART_UART_TOP_1 */
#define XPAR_UART_UART_TOP_1_BASEADDR 0x70021000
#define XPAR_UART_UART_TOP_1_HIGHADDR 0x70021FFF


/* Definitions for peripheral XADC_TOP_XADC_CTRL_0 */
#define XPAR_XADC_TOP_XADC_CTRL_0_BASEADDR 0x7002A000
#define XPAR_XADC_TOP_XADC_CTRL_0_HIGHADDR 0x7002AFFF


/******************************************************************/

/* Definitions for driver GPIOPS */
#define XPAR_XGPIOPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_GPIO_0 */
#define XPAR_PS7_GPIO_0_DEVICE_ID 0
#define XPAR_PS7_GPIO_0_BASEADDR 0xE000A000
#define XPAR_PS7_GPIO_0_HIGHADDR 0xE000AFFF


/******************************************************************/

/* Canonical definitions for peripheral PS7_GPIO_0 */
#define XPAR_XGPIOPS_0_DEVICE_ID XPAR_PS7_GPIO_0_DEVICE_ID
#define XPAR_XGPIOPS_0_BASEADDR 0xE000A000
#define XPAR_XGPIOPS_0_HIGHADDR 0xE000AFFF


/******************************************************************/

/* Definitions for driver IICPS */
#define XPAR_XIICPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_I2C_0 */
#define XPAR_PS7_I2C_0_DEVICE_ID 0
#define XPAR_PS7_I2C_0_BASEADDR 0xE0004000
#define XPAR_PS7_I2C_0_HIGHADDR 0xE0004FFF
#define XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ 111111115


/******************************************************************/

/* Canonical definitions for peripheral PS7_I2C_0 */
#define XPAR_XIICPS_0_DEVICE_ID XPAR_PS7_I2C_0_DEVICE_ID
#define XPAR_XIICPS_0_BASEADDR 0xE0004000
#define XPAR_XIICPS_0_HIGHADDR 0xE0004FFF
#define XPAR_XIICPS_0_I2C_CLK_FREQ_HZ 111111115


/******************************************************************/

/* Definitions for driver QSPIPS */
#define XPAR_XQSPIPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_QSPI_0 */
#define XPAR_PS7_QSPI_0_DEVICE_ID 0
#define XPAR_PS7_QSPI_0_BASEADDR 0xE000D000
#define XPAR_PS7_QSPI_0_HIGHADDR 0xE000DFFF
#define XPAR_PS7_QSPI_0_QSPI_CLK_FREQ_HZ 200000000
#define XPAR_PS7_QSPI_0_QSPI_MODE 0
#define XPAR_PS7_QSPI_0_QSPI_BUS_WIDTH 2


/******************************************************************/

/* Canonical definitions for peripheral PS7_QSPI_0 */
#define XPAR_XQSPIPS_0_DEVICE_ID XPAR_PS7_QSPI_0_DEVICE_ID
#define XPAR_XQSPIPS_0_BASEADDR 0xE000D000
#define XPAR_XQSPIPS_0_HIGHADDR 0xE000DFFF
#define XPAR_XQSPIPS_0_QSPI_CLK_FREQ_HZ 200000000
#define XPAR_XQSPIPS_0_QSPI_MODE 0
#define XPAR_XQSPIPS_0_QSPI_BUS_WIDTH 2


/******************************************************************/

/* Definitions for Fabric interrupts connected to ps7_scugic_0 */
#define XPAR_FABRIC_TIMER_TOP_TIMER_0_TIMER_INTR_INTR 65U
#define XPAR_FABRIC_TIMER_TOP_TIMER_1_TIMER_INTR_INTR 66U
#define XPAR_FABRIC_TIMER_TOP_TIMER_2_TIMER_INTR_INTR 67U
#define XPAR_FABRIC_TIMER_TOP_TIMER_3_TIMER_INTR_INTR 68U
#define XPAR_FABRIC_TIMER_TOP_TIMER_4_TIMER_INTR_INTR 84U
#define XPAR_FABRIC_TIMER_TOP_TIMER_5_TIMER_INTR_INTR 85U
#define XPAR_FABRIC_CAN_0_IP2BUS_INTREVENT_INTR 87U
#define XPAR_FABRIC_XADC_TOP_XADC_CTRL_0_AD_INTR_INTR 88U

/******************************************************************/

/* Canonical definitions for Fabric interrupts connected to ps7_scugic_0 */
#define XPAR_FABRIC_CAN_0_VEC_ID XPAR_FABRIC_CAN_0_IP2BUS_INTREVENT_INTR

/******************************************************************/

/* Definitions for driver SCUGIC */
#define XPAR_XSCUGIC_NUM_INSTANCES 1U

/* Definitions for peripheral PS7_SCUGIC_0 */
#define XPAR_PS7_SCUGIC_0_DEVICE_ID 0U
#define XPAR_PS7_SCUGIC_0_BASEADDR 0xF8F00100U
#define XPAR_PS7_SCUGIC_0_HIGHADDR 0xF8F001FFU
#define XPAR_PS7_SCUGIC_0_DIST_BASEADDR 0xF8F01000U


/******************************************************************/

/* Canonical definitions for peripheral PS7_SCUGIC_0 */
#define XPAR_SCUGIC_0_DEVICE_ID 0U
#define XPAR_SCUGIC_0_CPU_BASEADDR 0xF8F00100U
#define XPAR_SCUGIC_0_CPU_HIGHADDR 0xF8F001FFU
#define XPAR_SCUGIC_0_DIST_BASEADDR 0xF8F01000U


/******************************************************************/

/* Definitions for driver SCUTIMER */
#define XPAR_XSCUTIMER_NUM_INSTANCES 1

/* Definitions for peripheral PS7_SCUTIMER_0 */
#define XPAR_PS7_SCUTIMER_0_DEVICE_ID 0
#define XPAR_PS7_SCUTIMER_0_BASEADDR 0xF8F00600
#define XPAR_PS7_SCUTIMER_0_HIGHADDR 0xF8F0061F


/******************************************************************/

/* Canonical definitions for peripheral PS7_SCUTIMER_0 */
#define XPAR_XSCUTIMER_0_DEVICE_ID XPAR_PS7_SCUTIMER_0_DEVICE_ID
#define XPAR_XSCUTIMER_0_BASEADDR 0xF8F00600
#define XPAR_XSCUTIMER_0_HIGHADDR 0xF8F0061F


/******************************************************************/

/* Definitions for driver SCUWDT */
#define XPAR_XSCUWDT_NUM_INSTANCES 1

/* Definitions for peripheral PS7_SCUWDT_0 */
#define XPAR_PS7_SCUWDT_0_DEVICE_ID 0
#define XPAR_PS7_SCUWDT_0_BASEADDR 0xF8F00620
#define XPAR_PS7_SCUWDT_0_HIGHADDR 0xF8F006FF


/******************************************************************/

/* Canonical definitions for peripheral PS7_SCUWDT_0 */
#define XPAR_SCUWDT_0_DEVICE_ID XPAR_PS7_SCUWDT_0_DEVICE_ID
#define XPAR_SCUWDT_0_BASEADDR 0xF8F00620
#define XPAR_SCUWDT_0_HIGHADDR 0xF8F006FF


/******************************************************************/

/* Definitions for driver SDPS */
#define XPAR_XSDPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_SD_0 */
#define XPAR_PS7_SD_0_DEVICE_ID 0
#define XPAR_PS7_SD_0_BASEADDR 0xE0100000
#define XPAR_PS7_SD_0_HIGHADDR 0xE0100FFF
#define XPAR_PS7_SD_0_SDIO_CLK_FREQ_HZ 100000000
#define XPAR_PS7_SD_0_HAS_CD 0
#define XPAR_PS7_SD_0_HAS_WP 0
#define XPAR_PS7_SD_0_BUS_WIDTH 0
#define XPAR_PS7_SD_0_MIO_BANK 0
#define XPAR_PS7_SD_0_HAS_EMIO 0


/******************************************************************/

#define XPAR_PS7_SD_0_IS_CACHE_COHERENT 0
/* Canonical definitions for peripheral PS7_SD_0 */
#define XPAR_XSDPS_0_DEVICE_ID XPAR_PS7_SD_0_DEVICE_ID
#define XPAR_XSDPS_0_BASEADDR 0xE0100000
#define XPAR_XSDPS_0_HIGHADDR 0xE0100FFF
#define XPAR_XSDPS_0_SDIO_CLK_FREQ_HZ 100000000
#define XPAR_XSDPS_0_HAS_CD 0
#define XPAR_XSDPS_0_HAS_WP 0
#define XPAR_XSDPS_0_BUS_WIDTH 0
#define XPAR_XSDPS_0_MIO_BANK 0
#define XPAR_XSDPS_0_HAS_EMIO 0
#define XPAR_XSDPS_0_IS_CACHE_COHERENT 0


/******************************************************************/

/* Definitions for driver SYSMON */
#define XPAR_XSYSMON_NUM_INSTANCES 1U

/* Definitions for peripheral XADC_XADC_WIZ_0 */
#define XPAR_XADC_XADC_WIZ_0_IP_TYPE 0U
#define XPAR_XADC_XADC_WIZ_0_DEVICE_ID 0U
#define XPAR_XADC_XADC_WIZ_0_BASEADDR 0x00000000U
#define XPAR_XADC_XADC_WIZ_0_HIGHADDR 0x0000FFFFU
#define XPAR_XADC_XADC_WIZ_0_INCLUDE_INTR 1U


/******************************************************************/

/* Canonical definitions for peripheral XADC_XADC_WIZ_0 */
#define XPAR_SYSMON_0_IP_TYPE 0U
#define XPAR_SYSMON_0_DEVICE_ID XPAR_XADC_XADC_WIZ_0_DEVICE_ID
#define XPAR_SYSMON_0_BASEADDR 0x00000000U
#define XPAR_SYSMON_0_HIGHADDR 0x0000FFFFU
#define XPAR_SYSMON_0_INCLUDE_INTR 1U


/******************************************************************/

/* Definitions for driver UARTPS */
#define XPAR_XUARTPS_NUM_INSTANCES 2

/* Definitions for peripheral PS7_UART_0 */
#define XPAR_PS7_UART_0_DEVICE_ID 0
#define XPAR_PS7_UART_0_BASEADDR 0xE0000000
#define XPAR_PS7_UART_0_HIGHADDR 0xE0000FFF
#define XPAR_PS7_UART_0_UART_CLK_FREQ_HZ 100000000
#define XPAR_PS7_UART_0_HAS_MODEM 0


/* Definitions for peripheral PS7_UART_1 */
#define XPAR_PS7_UART_1_DEVICE_ID 1
#define XPAR_PS7_UART_1_BASEADDR 0xE0001000
#define XPAR_PS7_UART_1_HIGHADDR 0xE0001FFF
#define XPAR_PS7_UART_1_UART_CLK_FREQ_HZ 100000000
#define XPAR_PS7_UART_1_HAS_MODEM 0


/******************************************************************/

/* Canonical definitions for peripheral PS7_UART_0 */
#define XPAR_XUARTPS_0_DEVICE_ID XPAR_PS7_UART_0_DEVICE_ID
#define XPAR_XUARTPS_0_BASEADDR 0xE0000000
#define XPAR_XUARTPS_0_HIGHADDR 0xE0000FFF
#define XPAR_XUARTPS_0_UART_CLK_FREQ_HZ 100000000
#define XPAR_XUARTPS_0_HAS_MODEM 0

/* Canonical definitions for peripheral PS7_UART_1 */
#define XPAR_XUARTPS_1_DEVICE_ID XPAR_PS7_UART_1_DEVICE_ID
#define XPAR_XUARTPS_1_BASEADDR 0xE0001000
#define XPAR_XUARTPS_1_HIGHADDR 0xE0001FFF
#define XPAR_XUARTPS_1_UART_CLK_FREQ_HZ 100000000
#define XPAR_XUARTPS_1_HAS_MODEM 0


/******************************************************************/

/* Definitions for driver XADCPS */
#define XPAR_XADCPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_XADC_0 */
#define XPAR_PS7_XADC_0_DEVICE_ID 0
#define XPAR_PS7_XADC_0_BASEADDR 0xF8007100
#define XPAR_PS7_XADC_0_HIGHADDR 0xF8007120


/******************************************************************/

/* Canonical definitions for peripheral PS7_XADC_0 */
#define XPAR_XADCPS_0_DEVICE_ID XPAR_PS7_XADC_0_DEVICE_ID
#define XPAR_XADCPS_0_BASEADDR 0xF8007100
#define XPAR_XADCPS_0_HIGHADDR 0xF8007120


/******************************************************************/

#endif  /* end of protection macro */
