#include "config.h"
#define M5D(n)	((n) & 0x1fffff)	// To get lower 21bits

volatile unsigned short LCD_BUFFER0[SCR_YSIZE_TFT][SCR_XSIZE_TFT]; //240*320
volatile unsigned short LCD_BUFFER1[SCR_YSIZE_TFT][SCR_XSIZE_TFT]; //320*240

void Lcd_Init(void)
{	
 	rGPCUP  = 0x00000000;		//C口上拉
  	rGPCCON = 0xaaaa02a9; 
  	rGPDUP  = 0x00000000;
  	rGPDCON=0xaaaaaaaa; //Initialize VD[15:8]
 	rLCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
 	rLCDCON2=(VBPD<<24)|(LINEVAL_TFT<<14)|(VFPD<<6)|(VSPW);		//
  	rLCDCON3=(HBPD<<19)|(HOZVAL_TFT<<8)|(HFPD);
  	rLCDCON4=(MVAL<<8)|(HSPW);
 	rLCDCON5 = (1<<11) | (1<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6) | (1<<3)  |(BSWP<<1) | (HWSWP);
/**************************************************/
	#ifdef s240320
	rLCDSADDR1=(((U32)LCD_BUFFER0>>22)<<21)|M5D((U32)LCD_BUFFER0>>1);
	rLCDSADDR2=M5D( ((U32)LCD_BUFFER0+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT-LCD_XSIZE_TFT)/1)<<11)|(LCD_XSIZE_TFT/1);
	#else
	rLCDSADDR1=(((U32)LCD_BUFFER1>>22)<<21)|M5D((U32)LCD_BUFFER1>>1);
	rLCDSADDR2=M5D( ((U32)LCD_BUFFER1+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT-LCD_XSIZE_TFT)/1)<<11)|(LCD_XSIZE_TFT/1);
	#endif
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
  	rTCONSEL &= (~7) ;     // Disable LPC3480
  	rTPAL=0; // Disable Temp Palette */	
}

//********** LCD视频和控制信号输出或者停止，1开启视频输出 ***************//
void Lcd_EnvidOnOff(int onoff)
{
	if(onoff==1)
		rLCDCON1|=1; // ENVID=ON
	else
		rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
}

//************** TFT LCD 电源控制引脚使能 *******************************//
static void Lcd_PowerEnable(int invpwren,int pwren)
{
	rGPGUP = rGPGUP & ( ~(1 << 4)) |(1 << 4); // Pull-up disable
	rGPGCON = rGPGCON & ( ~(3 << 8)) |(3 << 8); //GPG4=LCD_PWREN
	rGPGDAT = rGPGDAT | (1 << 4) ;
	rLCDCON5 = rLCDCON5 & ( ~(1 << 3)) |(pwren << 3);   // PWREN
	rLCDCON5 = rLCDCON5 & ( ~(1 << 5)) |(invpwren << 5);   // INVPWREN
}

//***************** LCD单个象素的显示数据输出 ****************************//
void PutPixel(U32 x,U32 y, U32 c )
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
	{
		#ifdef s240320
			LCD_BUFFER0[(y)][(x)] = c;
		#else
			LCD_BUFFER1[(y)][(x)] = c;
		#endif
	}
		
}

//*************** LCD单个象素的显示数据输出 *******************************//
void Lcd_ClearScr( U32 c)
{
	unsigned int x,y ;
		
    for( y = 0 ; y < SCR_YSIZE_TFT ; y++ )
    {
    	for( x = 0 ; x < SCR_XSIZE_TFT ; x++ )
    	{
			#ifdef s240320
				LCD_BUFFER0[y][x] = c ;
			#else
				LCD_BUFFER1[y][x] = c ;
			#endif
    	}
    }
}
/**************************************************************
LCD屏幕显示垂直翻转
// LCD display is flipped vertically
// But, think the algorithm by mathematics point.
//   3I2
//   4 I 1
//  --+--   <-8 octants  mathematical cordinate
//   5 I 8
//   6I7
**************************************************************/
void Glib_Line(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

/**************************************************************
在LCD屏幕上画一个矩形
**************************************************************/
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}

/**************************************************************
在LCD屏幕上用颜色填充一个矩形
**************************************************************/
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}

/**************************************************************
在LCD屏幕上指定坐标点画一个指定大小的图片
**************************************************************/
void Paint_Bmp(int x0,int y0,int h,int l,const unsigned char bmp[])
{
	int x,y;
	U32 c;
	int p = 0;
	
    for( y = y0 ; y <y0+l ; y++ )
    {
    	for( x = x0 ; x <x0+h ; x++ )
    	{
    		c = (bmp[p+1]<<8)|(bmp[p]);

 	//	 	if ( ( (x0+x) <= SCR_XSIZE_TFT) && ( (y0+y) <= SCR_YSIZE_TFT) )
			#ifdef s240320
				LCD_BUFFER0[y][x] = c ;
			#else
				LCD_BUFFER1[y][x] = c ;
			#endif
    		p = p + 2 ;
    	}
    }
}

/**************************************************************
**************************************************************/
void Lcd_TFT_Init(void)
{
	Lcd_Init();
	LcdBkLtSet( 70 ) ;
	Lcd_PowerEnable(0, 1);	//允许PWREN 信号   极性正常
	Lcd_EnvidOnOff(1);		//turn on vedio

 	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00) );  

	#define LCD_BLANK		0
	#define C_UP		( LCD_XSIZE_TFT - LCD_BLANK*2 )
	#define C_RIGHT		( LCD_XSIZE_TFT - LCD_BLANK*2 )
	#define V_BLACK		( ( LCD_YSIZE_TFT - LCD_BLANK*4 ) / 6 )
	Glib_FilledRectangle( LCD_BLANK, LCD_BLANK, ( LCD_XSIZE_TFT - LCD_BLANK ), ( LCD_YSIZE_TFT - LCD_BLANK ),0x0000);		//fill a Rectangle with some color

	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*0), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*1),0x001f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*1), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*2),0x07e0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*2), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*3),0xf800);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*3), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*4),0xffe0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*4), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*5),0xf81f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*5), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*6),0x07ff);		//fill a Rectangle with some color

	Glib_Line( LCD_BLANK,LCD_BLANK, (LCD_XSIZE_TFT-LCD_BLANK), (LCD_YSIZE_TFT-LCD_BLANK), 0x0000 ) ;
	Glib_Line( LCD_BLANK,(LCD_YSIZE_TFT-LCD_BLANK), (LCD_XSIZE_TFT-LCD_BLANK), LCD_BLANK, 0x0000 ) ;
	Glib_Line( (LCD_XSIZE_TFT/2),(LCD_BLANK*2 + V_BLACK*0), (LCD_XSIZE_TFT/2), (LCD_BLANK*2 + V_BLACK*6), 0x0000 ) ;
	
}

/******************** 写16*16汉字 ************************************/
/*type:0--横屏；其他--竖屏*/
void w_hanzi_16(U32 x,U32 y,U32 color,const U8 ch[],U8 type)
{
	U8 mask,buffer;
	U16 i,j;
	for(i=0;i<16;i++)
	{
	 	mask=0x80;		//掩码
		buffer=ch[i*2]; //提取一行的第一个字节
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
			{
				if(0==type)
					PutPixel(x+j,y+i,color);
				else
					PutPixel(y+i,240-x-j,color);
				//	PutPixel(319-(y+i),x+j,color);
			}
			mask=mask>>1;
		}
		mask=0x80;
		buffer=ch[i*2+1];
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
			{
				if(0==type)
			  		PutPixel(x+j+8,y+i,color);
			    else
		 			PutPixel(y+i,240-x-j-8,color);
				//	PutPixel(319-(y+i),x+j+8,color);
			}
			mask=mask>>1;
		}
	}
}
