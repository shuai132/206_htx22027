#include "drvZynqIic.h"
#include "drvDef.h"
#include <stdio.h>
#include "drvIicReg.h"

#define REG_TEST_VALUE    0x00000005U


unsigned int Xil_In32(unsigned int Addr)
{
	return *(volatile unsigned int *) Addr;
}

void Xil_Out32(unsigned int Addr, unsigned int Value)
{
	unsigned int *LocalAddr = (unsigned int *)Addr;
	*LocalAddr = Value;
}


/*****************************************************************************/
/**
*
* Looks up the device configuration based on the unique device ID. A table
* contains the configuration info for each device in the system.
*
* @param	DeviceId contains the ID of the device to look up the
*		configuration for.
*
* @return	A pointer to the configuration found or NULL if the specified
*		device ID was not found. See xiicps.h for the definition of
*		XIicPs_Config.
*
* @note		None.
*
******************************************************************************/
XIicPs_Config *XIicPs_LookupConfig(unsigned short DeviceId)
{
	XIicPs_Config *CfgPtr = NULL;
	int Index;

	for (Index = 0; Index < 2; Index++) {
		if (XIicPs_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XIicPs_ConfigTable[Index];
			break;
		}
	}

	return (XIicPs_Config *)CfgPtr;
}


/*****************************************************************************/
/**
*
* Aborts a transfer in progress by resetting the FIFOs. The byte counts are
* cleared.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XIicPs_Abort(XIicPs *InstancePtr)
{
	unsigned int IntrMaskReg;
	unsigned int IntrStatusReg;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);

	/*
	 * Enter a critical section, so disable the interrupts while we clear
	 * the FIFO and the status register.
	 */
	IntrMaskReg = XIicPs_ReadReg(InstancePtr->Config.BaseAddress, XIICPS_IMR_OFFSET);
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress, XIICPS_IDR_OFFSET, XIICPS_IXR_ALL_INTR_MASK);

	/*
	 * Reset the settings in config register and clear the FIFOs.
	 */
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress,
			XIICPS_CR_OFFSET, XIICPS_CR_RESET_VALUE | XIICPS_CR_CLR_FIFO_MASK);

	/*
	 * Read, then write the interrupt status to make sure there are no
	 * pending interrupts.
	 */
	IntrStatusReg = XIicPs_ReadReg(InstancePtr->Config.BaseAddress, XIICPS_ISR_OFFSET);
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress,
			  XIICPS_ISR_OFFSET, IntrStatusReg);

	/*
	 * Restore the interrupt state.
	 */
	IntrMaskReg = XIICPS_IXR_ALL_INTR_MASK & (~IntrMaskReg);
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress,
			  XIICPS_IER_OFFSET, IntrMaskReg);

}


/*****************************************************************************/
/**
*
* Resets the IIC device. Reset must only be called after the driver has been
* initialized. The configuration of the device after reset is the same as its
* configuration after initialization.  Any data transfer that is in progress is
* aborted.
*
* The upper layer software is responsible for re-configuring (if necessary)
* and reenabling interrupts for the IIC device after the reset.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XIicPs_Reset(XIicPs *InstancePtr)
{

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);

	/*
	 * Abort any transfer that is in progress.
	 */
	XIicPs_Abort(InstancePtr);

	/*
	 * Reset any values so the software state matches the hardware device.
	 */
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress, XIICPS_CR_OFFSET,
			  XIICPS_CR_RESET_VALUE);
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress,
			  XIICPS_TIME_OUT_OFFSET, XIICPS_TO_RESET_VALUE);
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress, XIICPS_IDR_OFFSET,
			  XIICPS_IXR_ALL_INTR_MASK);

}

/*****************************************************************************/
/**
*
* This function gets the options for the IIC device. The options control how
* the device behaves relative to the IIC bus.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return	32 bit mask of the options, where a 1 means the option is on,
*		and a 0 means to the option is off. One or more bit values may
*		be contained in the mask. See the bit definitions named
* 		XIICPS_*_OPTION in the file xiicps.h.
*
* @note		None.
*
******************************************************************************/
unsigned int XIicPs_GetOptions(XIicPs *InstancePtr)
{
	unsigned int OptionsFlag = 0U;
	unsigned int ControlReg;
	unsigned int Index;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);

	/*
	 * Read control register to find which options are currently set.
	 */
	ControlReg = XIicPs_ReadReg(InstancePtr->Config.BaseAddress,
				      XIICPS_CR_OFFSET);

	/*
	 * Loop through the options table to determine which options are set.
	 */
	for (Index = 0U; Index < 1; Index++) {
		if ((ControlReg & OptionsTable[Index].Mask) != (unsigned int)0x0U) {
			OptionsFlag |= OptionsTable[Index].Option;
		}
		if ((ControlReg & XIICPS_CR_NEA_MASK) == (unsigned int)0x0U) {
			OptionsFlag |= XIICPS_10_BIT_ADDR_OPTION;
		}
	}

	if (InstancePtr->IsRepeatedStart != 0 ) {
		OptionsFlag |= XIICPS_REP_START_OPTION;
	}
	return OptionsFlag;
}

/*****************************************************************************/
/**
*
* Initializes a specific XIicPs instance such that the driver is ready to use.
*
* The state of the device after initialization is:
*   - Device is disabled
*   - Slave mode
*
* @param	InstancePtr is a pointer to the XIicPs instance.
* @param	ConfigPtr is a reference to a structure containing information
*		about a specific IIC device. This function initializes an
*		InstancePtr object for a specific device specified by the
*		contents of Config.
* @param	EffectiveAddr is the device base address in the virtual memory
*		address space. The caller is responsible for keeping the address
*		mapping from EffectiveAddr to the device physical base address
*		unchanged once this function is invoked. Unexpected errors may
*		occur if the address mapping changes after this function is
*		called. If address translation is not used, use
*		ConfigPtr->BaseAddress for this parameter, passing the physical
*		address instead.
*
* @return	The return value is XST_SUCCESS if successful.
*
* @note		None.
*
******************************************************************************/
int XIicPs_CfgInitialize(XIicPs *InstancePtr, XIicPs_Config *ConfigPtr,
				  unsigned int EffectiveAddr)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(ConfigPtr != NULL);

	/*
	 * Set some default values.
	 */
	InstancePtr->Config.DeviceId = ConfigPtr->DeviceId;
	InstancePtr->Config.BaseAddress = EffectiveAddr;
	InstancePtr->Config.InputClockHz = ConfigPtr->InputClockHz;
//	InstancePtr->StatusHandler = StubHandler;
	InstancePtr->CallBackRef = NULL;

	InstancePtr->IsReady = (unsigned int)XIL_COMPONENT_IS_READY;

	/*
	 * Reset the IIC device to get it into its initial state. It is expected
	 * that device configuration will take place after this initialization
	 * is done, but before the device is started.
	 */
	XIicPs_Reset(InstancePtr);

	/*
	 * Keep a copy of what options this instance has.
	 */
	InstancePtr->Options = XIicPs_GetOptions(InstancePtr);

	/* Initialize repeated start flag to 0 */
	InstancePtr->IsRepeatedStart = 0;

	return (int)OK;
}


/*****************************************************************************/
/**
* Check whether the I2C bus is busy
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return
* 		- TRUE if the bus is busy.
*		- FALSE if the bus is not busy.
*
* @note		None.
*
******************************************************************************/
int XIicPs_BusIsBusy(XIicPs *InstancePtr)
{
	unsigned int StatusReg;
	int	Status;

	StatusReg = XIicPs_ReadReg(InstancePtr->Config.BaseAddress,
					   XIICPS_SR_OFFSET);
	if ((StatusReg & XIICPS_SR_BA_MASK) != 0x0U) {
		Status = (int)TRUE;
	}else {
		Status = (int)FALSE;
	}
	return Status;
}

/*
* The configuration table for devices
*/

XIicPs_Config XIicPs_ConfigTable[] =
{
	{
		XPAR_PS7_I2C_0_DEVICE_ID,
		XPAR_PS7_I2C_0_BASEADDR,
		XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ
	},
	{
		XPAR_PS7_I2C_1_DEVICE_ID,
		XPAR_PS7_I2C_1_BASEADDR,
		XPAR_PS7_I2C_1_I2C_CLK_FREQ_HZ
	}
};


/*****************************************************************************/
/**
*
* Runs a self-test on the driver/device. The self-test is destructive in that
* a reset of the device is performed in order to check the reset values of
* the registers and to get the device into a known state.
*
* Upon successful return from the self-test, the device is reset.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_REGISTER_ERROR indicates a register did not read or write
*		correctly
*
* @note		None.
*
******************************************************************************/
int XIicPs_SelfTest(XIicPs *InstancePtr)
{

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);

	/*
	 * All the IIC registers should be in their default state right now.
	 */
	if ((XIICPS_CR_RESET_VALUE !=
		 XIicPs_ReadReg(InstancePtr->Config.BaseAddress, XIICPS_CR_OFFSET)) ||
		(XIICPS_IXR_ALL_INTR_MASK !=
		 XIicPs_ReadReg(InstancePtr->Config.BaseAddress,
				  XIICPS_IMR_OFFSET))) {
		return (int)ERRO;
	}

	XIicPs_Reset(InstancePtr);

	/*
	 * Write, Read then write a register
	 */
	XIicPs_WriteReg(InstancePtr->Config.BaseAddress,
			  XIICPS_SLV_PAUSE_OFFSET, REG_TEST_VALUE);

	if (REG_TEST_VALUE != XIicPs_ReadReg(InstancePtr->Config.BaseAddress,
						   XIICPS_SLV_PAUSE_OFFSET)) {
		return (int)ERRO;
	}

	XIicPs_WriteReg(InstancePtr->Config.BaseAddress,
			  XIICPS_SLV_PAUSE_OFFSET, 0U);

	XIicPs_Reset(InstancePtr);

	return (int)OK;
}


/*****************************************************************************/
/**
*
* This function sets the serial clock rate for the IIC device. The device
* must be idle rather than busy transferring data before setting these device
* options.
*
* The data rate is set by values in the control register. The formula for
* determining the correct register values is:
* Fscl = Fpclk/(22 x (divisor_a+1) x (divisor_b+1))
* See the hardware data sheet for a full explanation of setting the serial
* clock rate.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
* @param	FsclHz is the clock frequency in Hz. The two most common clock
*		rates are 100KHz and 400KHz.
*
* @return
*		- XST_SUCCESS if options are successfully set.
*		- XST_DEVICE_IS_STARTED if the device is currently transferring
*		data. The transfer must complete or be aborted before setting
*		options.
*		- XST_FAILURE if the Fscl frequency can not be set.
*
* @note		The clock can not be faster than the input clock divide by 22.
*
******************************************************************************/
int drvIicPs_SetSClk(XIicPs *InstancePtr, unsigned int FsclHz)
{
	unsigned int Div_a;
	unsigned int Div_b;
	unsigned int ActualFscl;
	unsigned int Temp;
	unsigned int TempLimit;
	unsigned int LastError;
	unsigned int BestError;
	unsigned int CurrentError;
	unsigned int ControlReg;
	unsigned int CalcDivA;
	unsigned int CalcDivB;
	unsigned int BestDivA = 0;
	unsigned int BestDivB = 0;
	unsigned int FsclHzVar = FsclHz;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(FsclHzVar > 0U);

	if (0U != XIicPs_In32((InstancePtr->Config.BaseAddress) +
					XIICPS_TRANS_SIZE_OFFSET)) {
		return (int)ERRO;
	}

	/*
	 * Assume Div_a is 0 and calculate (divisor_a+1) x (divisor_b+1).
	 */
	Temp = (InstancePtr->Config.InputClockHz) / ((unsigned int)22U * FsclHzVar);

	/*
	 * If the answer is negative or 0, the Fscl input is out of range.
	 */
	if ((unsigned int)(0U) == Temp) {
		return (int)ERRO;
	}

	/*
	 * If frequency 400KHz is selected, 384.6KHz should be set.
	 * If frequency 100KHz is selected, 90KHz should be set.
	 * This is due to a hardware limitation.
	 */
	if(FsclHzVar > 384600U) {
		FsclHzVar = 384600U;
	}

	if((FsclHzVar <= 100000U) && (FsclHzVar > 90000U)) {
		FsclHzVar = 90000U;
	}

	/*
	 * TempLimit helps in iterating over the consecutive value of Temp to
	 * find the closest clock rate achievable with divisors.
	 * Iterate over the next value only if fractional part is involved.
	 */
	TempLimit = (((InstancePtr->Config.InputClockHz) %
			((unsigned int)22 * FsclHzVar)) != 	(unsigned int)0x0U) ?
						Temp + (unsigned int)1U : Temp;
	BestError = FsclHzVar;

	BestDivA = 0U;
	BestDivB = 0U;
	for ( ; Temp <= TempLimit ; Temp++)
	{
		LastError = FsclHzVar;
		CalcDivA = 0U;
		CalcDivB = 0U;

		for (Div_b = 0U; Div_b < 64U; Div_b++) {

			Div_a = Temp / (Div_b + 1U);

			if (Div_a != 0U){
				Div_a = Div_a - (unsigned int)1U;
			}
			if (Div_a > 3U){
				continue;
			}
			ActualFscl = (InstancePtr->Config.InputClockHz) /
						(22U * (Div_a + 1U) * (Div_b + 1U));

			if (ActualFscl > FsclHzVar){
				CurrentError = (ActualFscl - FsclHzVar);}
			else{
				CurrentError = (FsclHzVar - ActualFscl);}

			if (LastError > CurrentError) {
				CalcDivA = Div_a;
				CalcDivB = Div_b;
				LastError = CurrentError;
			}
		}

		/*
		 * Used to capture the best divisors.
		 */
		if (LastError < BestError) {
			BestError = LastError;
			BestDivA = CalcDivA;
			BestDivB = CalcDivB;
		}
	}


	/*
	 * Read the control register and mask the Divisors.
	 */
	ControlReg = XIicPs_ReadReg(InstancePtr->Config.BaseAddress,
					  (unsigned int)XIICPS_CR_OFFSET);
	ControlReg &= ~((unsigned int)XIICPS_CR_DIV_A_MASK | (unsigned int)XIICPS_CR_DIV_B_MASK);
	ControlReg |= (BestDivA << XIICPS_CR_DIV_A_SHIFT) |
		(BestDivB << XIICPS_CR_DIV_B_SHIFT);

	XIicPs_WriteReg(InstancePtr->Config.BaseAddress, (unsigned int)XIICPS_CR_OFFSET,
			  ControlReg);

	return (int)OK;
}


/*****************************************************************************/
/**
* This function enables the slave monitor mode.
*
* It enables slave monitor in the control register and enables
* slave ready interrupt. It then does an address transfer to slave.
* Interrupt handler will signal the caller if slave responds to
* the address transfer.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
* @param	SlaveAddr is the address of the slave we want to contact.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void XIicPs_EnableSlaveMonitor(XIicPs *InstancePtr, unsigned short SlaveAddr)
{
	unsigned int BaseAddr;
	unsigned int ConfigReg;

//	Xil_AssertVoid(InstancePtr != NULL);

	BaseAddr = InstancePtr->Config.BaseAddress;

	/* Clear transfer size register */
	XIicPs_WriteReg(BaseAddr, (unsigned int)XIICPS_TRANS_SIZE_OFFSET, 0x0U);

	/*
	 * Enable slave monitor mode in control register.
	 */
	ConfigReg = XIicPs_ReadReg(BaseAddr, (unsigned int)XIICPS_CR_OFFSET);
	ConfigReg |= (unsigned int)XIICPS_CR_MS_MASK | (unsigned int)XIICPS_CR_NEA_MASK |
			(unsigned int)XIICPS_CR_CLR_FIFO_MASK | (unsigned int)XIICPS_CR_SLVMON_MASK;
	ConfigReg &= (unsigned int)(~XIICPS_CR_RD_WR_MASK);

	XIicPs_WriteReg(BaseAddr, (unsigned int)XIICPS_CR_OFFSET, ConfigReg);

	/*
	 * Set up interrupt flag for slave monitor interrupt.
	 * Dont enable NACK.
	 */
//	XIicPs_EnableInterrupts(BaseAddr, (unsigned int)XIICPS_IXR_SLV_RDY_MASK);
	XIicPs_WriteReg(BaseAddr, XIICPS_IER_OFFSET, (unsigned int)XIICPS_IXR_SLV_RDY_MASK);

	/*
	 * Initialize the slave monitor register.
	 */
	XIicPs_WriteReg(BaseAddr, (unsigned int)XIICPS_SLV_PAUSE_OFFSET, 0xFU);

	/*
	 * Set the slave address to start the slave address transmission.
	 */
	XIicPs_WriteReg(BaseAddr, (unsigned int)XIICPS_ADDR_OFFSET, (unsigned int)SlaveAddr);

	return;
}


/*****************************************************************************/
/**
* This function disables slave monitor mode.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void XIicPs_DisableSlaveMonitor(XIicPs *InstancePtr)
{
	unsigned int BaseAddr;

//	Xil_AssertVoid(InstancePtr != NULL);

	BaseAddr = InstancePtr->Config.BaseAddress;

	/*
	 * Clear slave monitor control bit.
	 */
	XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET,
		XIicPs_ReadReg(BaseAddr, XIICPS_CR_OFFSET)
			& (~XIICPS_CR_SLVMON_MASK));

	/*
	 * Clear interrupt flag for slave monitor interrupt.
	 */
//	XIicPs_DisableInterrupts(BaseAddr, XIICPS_IXR_SLV_RDY_MASK);
	XIicPs_WriteReg(BaseAddr, (unsigned int)XIICPS_IDR_OFFSET, (unsigned int)XIICPS_IXR_SLV_RDY_MASK);

	return;
}


/*****************************************************************************/
/*
* This function prepares a device to transfers as a master.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @param	Role specifies whether the device is sending or receiving.
*
* @return
*		- XST_SUCCESS if everything went well.
*		- XST_FAILURE if bus is busy.
*
* @note		Interrupts are always disabled, device which needs to use
*		interrupts needs to setup interrupts after this call.
*
****************************************************************************/
static int XIicPs_SetupMaster(XIicPs *InstancePtr, int Role)
{
	unsigned int ControlReg;
	unsigned int BaseAddr;
	unsigned int EnabledIntr = 0x0U;

//	Xil_AssertNonvoid(InstancePtr != NULL);

	BaseAddr = InstancePtr->Config.BaseAddress;
	ControlReg = XIicPs_ReadReg(BaseAddr, XIICPS_CR_OFFSET);


	/*
	 * Only check if bus is busy when repeated start option is not set.
	 */
	if ((ControlReg & XIICPS_CR_HOLD_MASK) == 0U) {
		if (XIicPs_BusIsBusy(InstancePtr) == (int)1) {
			return (int)ERRO;
		}
	}

	/*
	 * Set up master, AckEn, nea and also clear fifo.
	 */
	ControlReg |= (unsigned int)XIICPS_CR_ACKEN_MASK | (unsigned int)XIICPS_CR_CLR_FIFO_MASK |
			(unsigned int)XIICPS_CR_NEA_MASK | (unsigned int)XIICPS_CR_MS_MASK;

	if (Role == RECVING_ROLE) {
		ControlReg |= (unsigned int)XIICPS_CR_RD_WR_MASK;
		EnabledIntr = (unsigned int)XIICPS_IXR_DATA_MASK |(unsigned int)XIICPS_IXR_RX_OVR_MASK;
	}else {
		ControlReg &= (unsigned int)(~XIICPS_CR_RD_WR_MASK);
	}
	EnabledIntr |= (unsigned int)XIICPS_IXR_COMP_MASK | (unsigned int)XIICPS_IXR_ARB_LOST_MASK;

	XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET, ControlReg);

//	XIicPs_DisableAllInterrupts(BaseAddr);
	XIicPs_WriteReg((BaseAddr), XIICPS_IDR_OFFSET, \
			XIICPS_IXR_ALL_INTR_MASK);

	return (int)OK;
}


/****************************************************************************/
/*
*
* Place one byte into the transmit FIFO.
*
* @param	InstancePtr is the instance of IIC
*
* @return	None.
*
* @note		C-Style signature:
*		void XIicPs_SendByte(XIicPs *InstancePtr)
*
*****************************************************************************/
void XIicPs_SendByte(XIicPs *InstancePtr)
{
	unsigned char Data;
	Data = *((InstancePtr)->SendBufferPtr);
	 XIicPs_Out32((InstancePtr)->Config.BaseAddress + (unsigned int)(XIICPS_DATA_OFFSET), (unsigned int)(Data));
	(InstancePtr)->SendBufferPtr += 1;
	(InstancePtr)->SendByteCount -= 1;
}


/****************************************************************************/
/*
*
* Receive one byte from FIFO.
*
* @param	InstancePtr is the instance of IIC
*
* @return	None.
*
* @note		C-Style signature:
*		unsigned char XIicPs_RecvByte(XIicPs *InstancePtr)
*
*****************************************************************************/
void XIicPs_RecvByte(XIicPs *InstancePtr)
{
	unsigned char *Data, Value;
	Value = (unsigned char)(XIicPs_In32((InstancePtr)->Config.BaseAddress + (unsigned int)XIICPS_DATA_OFFSET));
	Data = &Value;
	*(InstancePtr)->RecvBufferPtr = *Data;
	(InstancePtr)->RecvBufferPtr += 1;
	(InstancePtr)->RecvByteCount --;
}


/*****************************************************************************/
/**
* Put more data into the transmit FIFO, number of bytes is ether expected
* number of bytes for this transfer or available space in FIFO, which ever
* is less.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
*
* @return	Number of bytes left for this instance.
*
* @note		This is function is shared by master and slave.
*
******************************************************************************/
int TransmitFifoFill(XIicPs *InstancePtr)
{
	unsigned char AvailBytes;
	int LoopCnt;
	int NumBytesToSend;

	/*
	 * Determine number of bytes to write to FIFO.
	 */
	AvailBytes = (unsigned char)XIICPS_FIFO_DEPTH -
		(unsigned char)XIicPs_ReadReg(InstancePtr->Config.BaseAddress,
					   XIICPS_TRANS_SIZE_OFFSET);

	if (InstancePtr->SendByteCount > (int)AvailBytes) {
		NumBytesToSend = (int)AvailBytes;
	} else {
		NumBytesToSend = InstancePtr->SendByteCount;
	}

	/*
	 * Fill FIFO with amount determined above.
	 */
	for (LoopCnt = 0; LoopCnt < NumBytesToSend; LoopCnt++) {
		XIicPs_SendByte(InstancePtr);
	}

	return InstancePtr->SendByteCount;
}


/*****************************************************************************/
/**
* This function initiates a polled mode send in master mode.
*
* It sends data to the FIFO and waits for the slave to pick them up.
* If slave fails to remove data from FIFO, the send fails with
* time out.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
* @param	MsgPtr is the pointer to the send buffer.
* @param	ByteCount is the number of bytes to be sent.
* @param	SlaveAddr is the address of the slave we are sending to.
*
* @return
*		- XST_SUCCESS if everything went well.
*		- XST_FAILURE if timed out.
*
* @note		This send routine is for polled mode transfer only.
*
****************************************************************************/
int XIicPs_MasterSendPolled(XIicPs *InstancePtr, unsigned char *MsgPtr, int ByteCount, unsigned short SlaveAddr)
{
	unsigned int IntrStatusReg;
	unsigned int StatusReg;
	unsigned int BaseAddr;
	unsigned int Intrs;
	unsigned int Value;

	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(MsgPtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(XIICPS_ADDR_MASK >= SlaveAddr);

	BaseAddr = InstancePtr->Config.BaseAddress;
	InstancePtr->SendBufferPtr = MsgPtr;
	InstancePtr->SendByteCount = ByteCount;

	if (((InstancePtr->IsRepeatedStart) != 0) ||
		((ByteCount > XIICPS_FIFO_DEPTH) != 0U)) {
		XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET,
				XIicPs_ReadReg(BaseAddr, (unsigned int)XIICPS_CR_OFFSET) |
						(unsigned int)XIICPS_CR_HOLD_MASK);
	}

	(void)XIicPs_SetupMaster(InstancePtr, SENDING_ROLE);

	/*
	 * Intrs keeps all the error-related interrupts.
	 */
	Intrs = (unsigned int)XIICPS_IXR_ARB_LOST_MASK | (unsigned int)XIICPS_IXR_TX_OVR_MASK |
		(unsigned int)XIICPS_IXR_NACK_MASK;

	/*
	 * Clear the interrupt status register before use it to monitor.
	 */
	IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
	XIicPs_WriteReg(BaseAddr, XIICPS_ISR_OFFSET, IntrStatusReg);

	/*
	 * Transmit first FIFO full of data.
	 */
	(void)TransmitFifoFill(InstancePtr);

	XIicPs_WriteReg(BaseAddr, XIICPS_ADDR_OFFSET, (unsigned int)SlaveAddr);

	IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);

	/*
	 * Continue sending as long as there is more data and
	 * there are no errors.
	 */
	Value = ((InstancePtr->SendByteCount > (int)0) &&
		((IntrStatusReg & Intrs) == (unsigned int)0U));
	while (Value != (unsigned int)0x00U) {
		StatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_SR_OFFSET);

		/*
		 * Wait until transmit FIFO is empty.
		 */
		if ((StatusReg & XIICPS_SR_TXDV_MASK) != 0U) {
			IntrStatusReg = XIicPs_ReadReg(BaseAddr,
					XIICPS_ISR_OFFSET);
			Value = ((InstancePtr->SendByteCount > (int)0) &&
				((IntrStatusReg & Intrs) == (unsigned int)0U));
			continue;
		}

		/*
		 * Send more data out through transmit FIFO.
		 */
		(void)TransmitFifoFill(InstancePtr);
		Value = ((InstancePtr->SendByteCount > (int)0) &&
			((IntrStatusReg & Intrs) == (unsigned int)0U));
	}

	/*
	 * Check for completion of transfer.
	 */
	while ((IntrStatusReg & XIICPS_IXR_COMP_MASK) != XIICPS_IXR_COMP_MASK){

		IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
		/*
		 * If there is an error, tell the caller.
		 */
		if ((IntrStatusReg & Intrs) != 0U) {
			return (int)ERRO;
		}
	}

	if ((!(InstancePtr->IsRepeatedStart)) != 0) {
		XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET,
				XIicPs_ReadReg(BaseAddr,XIICPS_CR_OFFSET) &
						(~XIICPS_CR_HOLD_MASK));
	}

	return (int)OK;
}


/*****************************************************************************/
/**
* This function initiates a polled mode receive in master mode.
*
* It repeatedly sets the transfer size register so the slave can
* send data to us. It polls the data register for data to come in.
* If slave fails to send us data, it fails with time out.
*
* @param	InstancePtr is a pointer to the XIicPs instance.
* @param	MsgPtr is the pointer to the receive buffer.
* @param	ByteCount is the number of bytes to be received.
* @param	SlaveAddr is the address of the slave we are receiving from.
*
* @return
*		- XST_SUCCESS if everything went well.
*		- XST_FAILURE if timed out.
*
* @note		This receive routine is for polled mode transfer only.
*
****************************************************************************/
int XIicPs_MasterRecvPolled(XIicPs *InstancePtr, unsigned char *MsgPtr,
				int ByteCount, unsigned short SlaveAddr)
{
	unsigned int IntrStatusReg;
	unsigned int Intrs;
	unsigned int StatusReg;
	unsigned int BaseAddr;
	int Result;
	int IsHold = 0;
	int UpdateTxSize = 0;
	int ByteCountVar = ByteCount;

	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(MsgPtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == (unsigned int)XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(XIICPS_ADDR_MASK >= SlaveAddr);

	BaseAddr = InstancePtr->Config.BaseAddress;
	InstancePtr->RecvBufferPtr = MsgPtr;
	InstancePtr->RecvByteCount = ByteCountVar;

	if((ByteCountVar > XIICPS_FIFO_DEPTH) ||
		((InstancePtr->IsRepeatedStart) !=0))
	{
		XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET,
				XIicPs_ReadReg(BaseAddr, (unsigned int)XIICPS_CR_OFFSET) |
						(unsigned int)XIICPS_CR_HOLD_MASK);
		IsHold = 1;
	}

	(void)XIicPs_SetupMaster(InstancePtr, RECVING_ROLE);

	/*
	 * Clear the interrupt status register before use it to monitor.
	 */
	IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
	XIicPs_WriteReg(BaseAddr, XIICPS_ISR_OFFSET, IntrStatusReg);


	XIicPs_WriteReg(BaseAddr, XIICPS_ADDR_OFFSET, SlaveAddr);

	/*
	 * Set up the transfer size register so the slave knows how much
	 * to send to us.
	 */
	if (ByteCountVar > XIICPS_MAX_TRANSFER_SIZE) {
		XIicPs_WriteReg(BaseAddr, XIICPS_TRANS_SIZE_OFFSET,
				XIICPS_MAX_TRANSFER_SIZE);
		ByteCountVar = (int)XIICPS_MAX_TRANSFER_SIZE;
		UpdateTxSize = 1;
	}else {
		XIicPs_WriteReg(BaseAddr, XIICPS_TRANS_SIZE_OFFSET,
			 ByteCountVar);
	}

	/*
	 * Intrs keeps all the error-related interrupts.
	 */
	Intrs = (unsigned int)XIICPS_IXR_ARB_LOST_MASK | (unsigned int)XIICPS_IXR_RX_OVR_MASK |
			(unsigned int)XIICPS_IXR_RX_UNF_MASK | (unsigned int)XIICPS_IXR_NACK_MASK;
	/*
	 * Poll the interrupt status register to find the errors.
	 */
	IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
	while ((InstancePtr->RecvByteCount > 0) &&
			((IntrStatusReg & Intrs) == 0U)) {
		StatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_SR_OFFSET);

	    while ((StatusReg & XIICPS_SR_RXDV_MASK) != 0U) {
		    if (((InstancePtr->RecvByteCount <
			    XIICPS_DATA_INTR_DEPTH) != 0U) && (IsHold != 0) &&
			    ((!(InstancePtr->IsRepeatedStart)) != 0)) {
				IsHold = 0;
				XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET,
						XIicPs_ReadReg(BaseAddr,
						XIICPS_CR_OFFSET) &
						(~XIICPS_CR_HOLD_MASK));
			}
			XIicPs_RecvByte(InstancePtr);
		    ByteCountVar --;

		    if ((UpdateTxSize != 0) &&
			    ((ByteCountVar == (XIICPS_FIFO_DEPTH + 1)) != 0U)) {
			    break;
			}

			StatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_SR_OFFSET);
		}

	    if ((UpdateTxSize != 0) && ((ByteCountVar == (XIICPS_FIFO_DEPTH + 1)) != 0U)) {
		    /*
		     * wait while fifo is full
		     */
		    while(XIicPs_ReadReg(BaseAddr,
			    XIICPS_TRANS_SIZE_OFFSET) !=
			    (unsigned int)(ByteCountVar - XIICPS_FIFO_DEPTH)) { ;
			}

			if ((InstancePtr->RecvByteCount - XIICPS_FIFO_DEPTH) >
				XIICPS_MAX_TRANSFER_SIZE) {

				XIicPs_WriteReg(BaseAddr,
					XIICPS_TRANS_SIZE_OFFSET,
					XIICPS_MAX_TRANSFER_SIZE);
			    ByteCountVar = (int)XIICPS_MAX_TRANSFER_SIZE +
						XIICPS_FIFO_DEPTH;
			}else {
				XIicPs_WriteReg(BaseAddr,
					XIICPS_TRANS_SIZE_OFFSET,
					InstancePtr->RecvByteCount -
					XIICPS_FIFO_DEPTH);
				UpdateTxSize = 0;
			    ByteCountVar = InstancePtr->RecvByteCount;
			}
		}

		IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
	}

	if ((!(InstancePtr->IsRepeatedStart)) != 0) {
		XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET,
				XIicPs_ReadReg(BaseAddr,XIICPS_CR_OFFSET) &
						(~XIICPS_CR_HOLD_MASK));
	}
	if ((IntrStatusReg & Intrs) != 0x0U) {
		Result = (int)ERRO;
	}
	else {
		Result =  (int)OK;
	}

	return Result;
}
