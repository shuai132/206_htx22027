#ifndef __DRVEEPROM_H_
#define __DRVEEPROM_H_
#include "drvIic.h"
#include "drvDef.h"

#define D_EEPROM_ADDR_MAX   	(0x10000)  		/*AT24C512-> 512*1024*/
#define D_EEPROM_PAGE_SIZE		(128)
#define D_EEPROM_PAGE_MAX    	(D_EEPROM_ADDR_MAX / D_EEPROM_PAGE_SIZE)

#define D_EEPROM_ADDR  		    0x50            /*eeprom?ииб└?????*/

INT32 drvEepromInit(UINT32 devAddr, UINT32 bps);
INT32 drvEepromWriteData(UINT32 startAddr, UINT8 *pBuff, UINT32 ByteCount);
INT32 drvEepromReadData(UINT32 startAddr, UINT8 *pBuff, UINT32 ByteCount);

#endif
