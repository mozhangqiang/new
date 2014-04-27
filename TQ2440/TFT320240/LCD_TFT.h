/**************************************************************
The initial and control for TFT LCD
**************************************************************/
#include "font_def.h"

#define LCD35			1		// 3.5寸屏(320X240)
#define LCDT35          2
#define LCD_Type		LCD35	//设定屏的类型

//#define S35					//选择使用三星屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#ifdef S35
#define VBPD 		(12)		//垂直同步信号的后肩
#define VFPD 		(4)			//垂直同步信号的前肩
#define VSPW 		(5)			//垂直同步信号的脉宽

#define HBPD 		(8)			//水平同步信号的后肩
#define HFPD 		(16)			//水平同步信号的前肩
#define HSPW 		(4)			//水平同步信号的脉宽
#define CLKVAL_TFT 	(6) 		//VCLK=HCLK / [(CLKVAL_TFT + 1) × 2]
#else
//#define VBPD 		(3)			//垂直同步信号的后肩
//#define VFPD 		(5)			//垂直同步信号的前肩
//#define VSPW 		(15)			//垂直同步信号的脉宽

//#define HBPD 		(5)			//水平同步信号的后肩
//#define HFPD 		(15)			//水平同步信号的前肩
//#define HSPW 		(8)			//水平同步信号的脉宽

#define VBPD 		(12)			//垂直同步信号的后肩
#define VFPD 		(4)			//垂直同步信号的前肩
#define VSPW 		(5)			//垂直同步信号的脉宽

#define HBPD 		(22)			//水平同步信号的后肩
#define HFPD 		(33)			//水平同步信号的前肩
#define HSPW 		(44)			//水平同步信号的脉宽
#define CLKVAL_TFT 	(6)			//决定VCLK 的频率和CLKVAL[9:0]。TFT：VCLK = HCLK / [(CLKVAL + 1) × 2]
#endif
	
#define HOZVAL_TFT	(LCD_XSIZE_TFT-1)		 //决定了LCD 面板的水平尺寸
#define LINEVAL_TFT	(LCD_YSIZE_TFT-1)		 //决定了LCD 面板的垂直尺寸
//color
#define red 		0xf800		//红色
#define orange		0xfd20		//橙色
#define yellow		0xffe0		//黄色
#define green		0x07e0		//绿色
#define cyan		0x07ff		//青色
#define blue		0x001f		//蓝色
#define purple		0xf81f		//紫色
#define black		0x0000		//黑色
#define white		0xffff		//白色
#define gray		0x7bef		//灰色

/********************* 声明 **************************************/
void Lcd_Init(void);
void Lcd_EnvidOnOff(int onoff);
static void Lcd_PowerEnable(int invpwren,int pwren);
void Lcd_MoveViewPort(int vx,int vy);
void PutPixel(U32 x,U32 y, U32 c );
void Lcd_ClearScr( U32 c);
void Glib_Line(int x1,int y1,int x2,int y2,int color);
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color);
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color);
void Paint_Bmp(int x0,int y0,int h,int l,const unsigned char bmp[]);
void Lcd_TFT_Init(void);
void w_hanzi_16(U32 x,U32 y,U32 color,const U8 ch[],U8 type);
void w_symbol(U32 x,U32 y,const U8 ch[],U32 symbol,U16 color);
void w_symbol_16x16(U32 x,U32 y,const U8 ch[],U32 symbol,U16 color);

