#ifndef __DRVZYNQIIC_H_
#define __DRVZYNQIIC_H_
#include "xil_assert.h"
#include "drvDef.h"
#include "drvIicReg.h"

/* Maximum transfer size */
#define XIICPS_MAX_TRANSFER_SIZE	(unsigned int)(255U - 3U)

#define XIicPs_In32 Xil_In32
#define XIicPs_Out32 Xil_Out32


#define XIL_COMPONENT_IS_READY     0x11111111U  /**< component has been initialized */
#define XIL_COMPONENT_IS_STARTED   0x22222222U  /**< component has been started */


/** @name Role constants
 *
 * These constants are used to pass into the device setup routines to
 * set up the device according to transfer direction.
 */
#define SENDING_ROLE		1  /**< Transfer direction is sending */
#define RECVING_ROLE		0  /**< Transfer direction is receiving */


/* Definitions for driver IICPS */
#define XPAR_XIICPS_NUM_INSTANCES 2

/* Definitions for peripheral PS7_I2C_0 */
#define XPAR_PS7_I2C_0_DEVICE_ID 0
#define XPAR_PS7_I2C_0_BASEADDR 0xE0004000
#define XPAR_PS7_I2C_0_HIGHADDR 0xE0004FFF
#define XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ 111111115


/* Definitions for peripheral PS7_I2C_1 */
#define XPAR_PS7_I2C_1_DEVICE_ID 1
#define XPAR_PS7_I2C_1_BASEADDR 0xE0005000
#define XPAR_PS7_I2C_1_HIGHADDR 0xE0005FFF
#define XPAR_PS7_I2C_1_I2C_CLK_FREQ_HZ 111111115


/************************** Constant Definitions *****************************/

/** @name Configuration options
 *
 * The following options may be specified or retrieved for the device and
 * enable/disable additional features of the IIC.  Each of the options
 * are bit fields, so more than one may be specified.
 *
 * @{
 */
#define XIICPS_7_BIT_ADDR_OPTION	0x01U  /**< 7-bit address mode */
#define XIICPS_10_BIT_ADDR_OPTION	0x02U  /**< 10-bit address mode */
#define XIICPS_SLAVE_MON_OPTION		0x04U  /**< Slave monitor mode */
#define XIICPS_REP_START_OPTION		0x08U  /**< Repeated Start */

/************************** Variable Definitions *****************************/
/*
 * Create the table of options which are processed to get/set the device
 * options. These options are table driven to allow easy maintenance and
 * expansion of the options.
 */
typedef struct {
		unsigned int Option;
		unsigned int Mask;
} OptionsMap;

static OptionsMap OptionsTable[] = {
		{XIICPS_7_BIT_ADDR_OPTION, XIICPS_CR_NEA_MASK},
		{XIICPS_10_BIT_ADDR_OPTION, XIICPS_CR_NEA_MASK},
		{XIICPS_SLAVE_MON_OPTION, XIICPS_CR_SLVMON_MASK},
		{XIICPS_REP_START_OPTION, XIICPS_CR_HOLD_MASK},
};

#define XIICPS_NUM_OPTIONS      (sizeof(OptionsTable) / sizeof(OptionsMap))

/****************************************************************************/
/**
* Read an IIC register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to select the specific register.
*
* @return	The value read from the register.
*
* @note		C-Style signature:
*		unsigned int XIicPs_ReadReg(unsigned int BaseAddress. int RegOffset)
*
******************************************************************************/
#define XIicPs_ReadReg(BaseAddress, RegOffset) \
	XIicPs_In32((BaseAddress) + (unsigned int)(RegOffset))

/***************************************************************************/
/**
* Write an IIC register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to select the specific register.
* @param	RegisterValue is the value to be written to the register.
*
* @return	None.
*
* @note	C-Style signature:
*	void XIicPs_WriteReg(unsigned int BaseAddress, int RegOffset, unsigned int RegisterValue)
*
******************************************************************************/
#define XIicPs_WriteReg(BaseAddress, RegOffset, RegisterValue) \
	XIicPs_Out32((BaseAddress) + (unsigned int)(RegOffset), (unsigned int)(RegisterValue))

/***************************************************************************/

/**
* The handler data type allows the user to define a callback function to
* respond to interrupt events in the system. This function is executed
* in interrupt context, so amount of processing should be minimized.
*
* @param	CallBackRef is the callback reference passed in by the upper
*		layer when setting the callback functions, and passed back to
*		the upper layer when the callback is invoked. Its type is
*		not important to the driver, so it is a void pointer.
* @param	StatusEvent indicates one or more status events that occurred.
*/
typedef void (*XIicPs_IntrHandler) (void *CallBackRef, unsigned int StatusEvent);

/**
 * This typedef contains configuration information for the device.
 */
typedef struct {
	unsigned short DeviceId;     /**< Unique ID  of device */
	unsigned int BaseAddress;  /**< Base address of the device */
	unsigned int InputClockHz; /**< Input clock frequency */
} XIicPs_Config;

/**
 * The XIicPs driver instance data. The user is required to allocate a
 * variable of this type for each IIC device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
typedef struct {
	XIicPs_Config Config;	/* Configuration structure */
	unsigned int IsReady;		/* Device is initialized and ready */
	unsigned int Options;		/* Options set in the device */

	unsigned char *SendBufferPtr;	/* Pointer to send buffer */
	unsigned char *RecvBufferPtr;	/* Pointer to recv buffer */
	int SendByteCount;	/* Number of bytes still expected to send */
	int RecvByteCount;	/* Number of bytes still expected to receive */
	int CurrByteCount;	/* No. of bytes expected in current transfer */

	int UpdateTxSize;	/* If tx size register has to be updated */
	int IsSend;		/* Whether master is sending or receiving */
	int IsRepeatedStart;	/* Indicates if user set repeated start */

	XIicPs_IntrHandler StatusHandler;  /* Event handler function */
	void *CallBackRef;	/* Callback reference for event handler */
} XIicPs;



XIicPs_Config *XIicPs_LookupConfig(unsigned short DeviceId);

int XIicPs_CfgInitialize(XIicPs *InstancePtr, XIicPs_Config *ConfigPtr, unsigned int EffectiveAddr);

unsigned int Xil_In32(unsigned int Addr);
void Xil_Out32(unsigned int Addr, unsigned int Value);

void XIicPs_Reset(XIicPs *InstancePtr);
unsigned int XIicPs_GetOptions(XIicPs *InstancePtr);
int XIicPs_BusIsBusy(XIicPs *InstancePtr);


extern XIicPs_Config XIicPs_ConfigTable[XPAR_XIICPS_NUM_INSTANCES];

XIicPs_Config *XIicPs_LookupConfig(unsigned short DeviceId);

int drvIicPs_SetSClk(XIicPs *InstancePtr, unsigned int FsclHz);

int XIicPs_SelfTest(XIicPs *InstancePtr);

void XIicPs_SendByte(XIicPs *InstancePtr);

void XIicPs_RecvByte(XIicPs *InstancePtr);

int TransmitFifoFill(XIicPs *InstancePtr);

int XIicPs_MasterRecvPolled(XIicPs *InstancePtr, unsigned char *MsgPtr, int ByteCount, unsigned short SlaveAddr);

int XIicPs_MasterSendPolled(XIicPs *InstancePtr, unsigned char *MsgPtr, int ByteCount, unsigned short SlaveAddr);

#endif
