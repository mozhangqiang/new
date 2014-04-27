//#ifndef lcd_h
//#define lcd_h



//#define s240320

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

#define VBPD 		(12)		//垂直同步信号的后肩
#define VFPD 		(4)			//垂直同步信号的前肩
#define VSPW 		(5)			//垂直同步信号的脉宽
#define HBPD 		(22)		//水平同步信号的后肩
#define HFPD 		(33)		//水平同步信号的前肩
#define HSPW 		(44)		//水平同步信号的脉宽

#define CLKVAL_TFT 	(6)			//决定VCLK 的频率和CLKVAL[9:0]。TFT：VCLK = HCLK / [(CLKVAL + 1) × 2]

#ifdef s240320				 
#define LCD_XSIZE_TFT 	(240)	//	
#define LCD_YSIZE_TFT 	(320)	//竖屏的实际屏幕尺寸

#define SCR_XSIZE_TFT 	(240)	//
#define SCR_YSIZE_TFT 	(320)  	//竖屏的显示尺寸

#else
#define LCD_XSIZE_TFT 	(320)	//
#define LCD_YSIZE_TFT 	(240)	//横屏的实际屏幕尺寸

#define SCR_XSIZE_TFT 	(320)	//
#define SCR_YSIZE_TFT 	(240)	//横屏的显示尺寸
#endif

#define HOZVAL_TFT	(LCD_XSIZE_TFT-1)		 //决定了LCD 面板的水平尺寸
#define LINEVAL_TFT	(LCD_YSIZE_TFT-1)		 //决定了LCD 面板的垂直尺寸

//******************** color ******************************//
#define red 		0xf800		//红色
#define yellow		0xffe0		//黄色
#define green		0x07e0		//绿色
#define cyan		0x07ff		//青色
#define blue		0x001f		//蓝色
#define purple		0xf81f		//紫色
#define black		0x0000		//黑色
#define white		0xffff		//白色
#define gray		0x7bef		//灰色
//******************** 声明 ******************************//
void Lcd_Init(void);
void Lcd_EnvidOnOff(int onoff);
static void Lcd_PowerEnable(int invpwren,int pwren);
void PutPixel(U32 x,U32 y, U32 c );
void Lcd_ClearScr( U32 c);
void Glib_Line(int x1,int y1,int x2,int y2,int color);
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color);
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color);
void Paint_Bmp(int x0,int y0,int h,int l,const unsigned char bmp[]);
void Lcd_TFT_Init(void);
void w_hanzi_16(U32 x,U32 y,U32 color,const U8 ch[],U8 type);

//#endif /*lcd_h*/
