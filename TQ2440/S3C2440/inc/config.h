/**************************************************
**	文件名:config.h
**	版本号:V 1.0
**	文件说明:设置和系统相关的变量和配置参数，
**		同时完成对其他参数设置的头文件的调用，
**		实现只需要调用该头文件就可以完成各个参数或变量的调用。
***************************************************/

#ifndef  CONFIG_H
#define  CONFIG_H

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  		0
#endif

#ifndef OK
#define OK		1
#endif

#ifndef FAIL
#define FAIL		0
#endif

typedef unsigned char  uint8;                   // 无符号8位整型变量
typedef signed   char  int8;                    // 有符号8位整型变量
typedef unsigned short uint16;                  // 无符号16位整型变量
typedef signed   short int16;                   // 有符号16位整型变量
typedef unsigned int   uint32;                  // 无符号32位整型变量
typedef signed   int   int32;                   // 有符号32位整型变量
typedef float          fp32;                    // 单精度浮点数(32位长度)
typedef double         fp64;                    // 双精度浮点数(64位长度)

typedef unsigned char  UINT8;                   // 无符号8位整型变量
typedef signed   char  INT8;                    // 有符号8位整型变量
typedef unsigned short UINT16;                  // 无符号16位整型变量
typedef signed   short INT16;                   // 有符号16位整型变量
typedef unsigned int   UINT32;                  // 无符号32位整型变量
typedef signed   int   INT32;                   // 有符号32位整型变量
typedef float          FP32;                    // 单精度浮点数(32位长度)
typedef double         FP64;                    // 双精度浮点数(64位长度)
typedef unsigned char  BYTE;

#define U32 unsigned int
#define U16 unsigned short
#define S32 int
#define S16 short int
#define U8  unsigned char
#define	S8  char

/**********************【ARM的代码】******************/
#include	"2440slib.h" 
#include	"2440addr.h"
#include	"option.h"
#include	"2440lib.h"
#include    "def.h"

void TargetInit(void);

// IRQ中断向量地址表
//extern  uint32 VICVectAddr[];


/**********************【应用程序配置】******************/
#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<string.h>

/******************【其它及自定义头文件】*****************/
#include	"mmu.h" 
#include	"timer.h"
#include	"mmu.h"
//#include 	"font_def.h"
#include    "LCD_TFT.h"
#include	"graph.h"
//#include	"symbol_def.h"
//#include	"font_16x16.h"
#include	"Eint.h"
#include 	"io_api.h"
#include	"config_cust.h"
#include	"radio_api.h"

/*******************【用户自定义变量】*******************/
#define RGB(r,g,b)		(unsigned int)( (r << 16) + (g << 8) + b )
#define FROM_BCD(n)		((((n) >> 4) * 10) + ((n) & 0xf))
#define TO_BCD(n)		((((n) / 10) << 4) | ((n) % 10))

#endif
