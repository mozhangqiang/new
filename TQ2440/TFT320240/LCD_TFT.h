/**************************************************************
The initial and control for TFT LCD
**************************************************************/
#include "font_def.h"

#define LCD35			1		// 3.5����(320X240)
#define LCDT35          2
#define LCD_Type		LCD35	//�趨��������

//#define S35					//ѡ��ʹ��������

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#ifdef S35
#define VBPD 		(12)		//��ֱͬ���źŵĺ��
#define VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(5)			//��ֱͬ���źŵ�����

#define HBPD 		(8)			//ˮƽͬ���źŵĺ��
#define HFPD 		(16)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(4)			//ˮƽͬ���źŵ�����
#define CLKVAL_TFT 	(6) 		//VCLK=HCLK / [(CLKVAL_TFT + 1) �� 2]
#else
//#define VBPD 		(3)			//��ֱͬ���źŵĺ��
//#define VFPD 		(5)			//��ֱͬ���źŵ�ǰ��
//#define VSPW 		(15)			//��ֱͬ���źŵ�����

//#define HBPD 		(5)			//ˮƽͬ���źŵĺ��
//#define HFPD 		(15)			//ˮƽͬ���źŵ�ǰ��
//#define HSPW 		(8)			//ˮƽͬ���źŵ�����

#define VBPD 		(12)			//��ֱͬ���źŵĺ��
#define VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(5)			//��ֱͬ���źŵ�����

#define HBPD 		(22)			//ˮƽͬ���źŵĺ��
#define HFPD 		(33)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(44)			//ˮƽͬ���źŵ�����
#define CLKVAL_TFT 	(6)			//����VCLK ��Ƶ�ʺ�CLKVAL[9:0]��TFT��VCLK = HCLK / [(CLKVAL + 1) �� 2]
#endif
	
#define HOZVAL_TFT	(LCD_XSIZE_TFT-1)		 //������LCD ����ˮƽ�ߴ�
#define LINEVAL_TFT	(LCD_YSIZE_TFT-1)		 //������LCD ���Ĵ�ֱ�ߴ�
//color
#define red 		0xf800		//��ɫ
#define orange		0xfd20		//��ɫ
#define yellow		0xffe0		//��ɫ
#define green		0x07e0		//��ɫ
#define cyan		0x07ff		//��ɫ
#define blue		0x001f		//��ɫ
#define purple		0xf81f		//��ɫ
#define black		0x0000		//��ɫ
#define white		0xffff		//��ɫ
#define gray		0x7bef		//��ɫ

/********************* ���� **************************************/
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

