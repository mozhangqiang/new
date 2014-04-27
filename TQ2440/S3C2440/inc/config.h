/**************************************************
**	�ļ���:config.h
**	�汾��:V 1.0
**	�ļ�˵��:���ú�ϵͳ��صı��������ò�����
**		ͬʱ��ɶ������������õ�ͷ�ļ��ĵ��ã�
**		ʵ��ֻ��Ҫ���ø�ͷ�ļ��Ϳ�����ɸ�������������ĵ��á�
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

typedef unsigned char  uint8;                   // �޷���8λ���ͱ���
typedef signed   char  int8;                    // �з���8λ���ͱ���
typedef unsigned short uint16;                  // �޷���16λ���ͱ���
typedef signed   short int16;                   // �з���16λ���ͱ���
typedef unsigned int   uint32;                  // �޷���32λ���ͱ���
typedef signed   int   int32;                   // �з���32λ���ͱ���
typedef float          fp32;                    // �����ȸ�����(32λ����)
typedef double         fp64;                    // ˫���ȸ�����(64λ����)

typedef unsigned char  UINT8;                   // �޷���8λ���ͱ���
typedef signed   char  INT8;                    // �з���8λ���ͱ���
typedef unsigned short UINT16;                  // �޷���16λ���ͱ���
typedef signed   short INT16;                   // �з���16λ���ͱ���
typedef unsigned int   UINT32;                  // �޷���32λ���ͱ���
typedef signed   int   INT32;                   // �з���32λ���ͱ���
typedef float          FP32;                    // �����ȸ�����(32λ����)
typedef double         FP64;                    // ˫���ȸ�����(64λ����)
typedef unsigned char  BYTE;

#define U32 unsigned int
#define U16 unsigned short
#define S32 int
#define S16 short int
#define U8  unsigned char
#define	S8  char

/**********************��ARM�Ĵ��롿******************/
#include	"2440slib.h" 
#include	"2440addr.h"
#include	"option.h"
#include	"2440lib.h"
#include    "def.h"

void TargetInit(void);

// IRQ�ж�������ַ��
//extern  uint32 VICVectAddr[];


/**********************��Ӧ�ó������á�******************/
#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<string.h>

/******************���������Զ���ͷ�ļ���*****************/
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

/*******************���û��Զ��������*******************/
#define RGB(r,g,b)		(unsigned int)( (r << 16) + (g << 8) + b )
#define FROM_BCD(n)		((((n) >> 4) * 10) + ((n) & 0xf))
#define TO_BCD(n)		((((n) / 10) << 4) | ((n) % 10))

#endif
