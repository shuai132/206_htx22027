#ifndef _DRVCOMMON_H_
#define _DRVCOMMON_H_

#ifdef D_OS_ALONE
volatile signed int isrTab[16];
extern void isr_TabInit();
#endif

int make_crc32_table(void);

unsigned int getCRC(unsigned char* buf, int nLength);

int stringtohex(unsigned char *str, unsigned char *hex, int len);

void pl_reg_write(unsigned int addr, unsigned int value);

unsigned int pl_reg_read(unsigned int addr);

void drv_delay_us(unsigned int waitTime);

void drv_delay_ms(unsigned int waitTime);

void drv_delay_s(unsigned int waitTime);

void drvCommon_Init(void);

#endif
