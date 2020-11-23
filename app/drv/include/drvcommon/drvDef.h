/***************************************************************
*文件名称：drvDef.h
*文件说明：预定义数据类型头文件
*版本号：1.00
*开发环境：workbench3.3
****************************************************************/
#ifndef _DRVDEF_H_
#define _DRVDEF_H_

#ifndef BOOL
typedef int  BOOL;
#endif

#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#ifndef NULL
#define NULL  0
#endif

#ifndef OK
#define OK  0
#endif

#ifndef ERRO
#define ERRO  -1
#endif

#ifndef LOCAL
#define LOCAL	static
#endif

#ifndef INT8
typedef signed char     		INT8;
#endif
#ifndef UINT8
typedef unsigned char           UINT8;
#endif

#ifndef INT16
typedef signed short     		INT16;
#endif
#ifndef UINT16
typedef unsigned short			UINT16;
#endif

#ifndef INT32
typedef signed int     			INT32;
#endif
#ifndef UINT32
typedef unsigned int			UINT32;
#endif

#ifndef INT16
typedef signed long long     	INT64;
#endif
#ifndef UINT16
typedef unsigned long long		UINT64;
#endif

#endif
