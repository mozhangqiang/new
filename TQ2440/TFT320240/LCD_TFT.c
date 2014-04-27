/**************************************************************
The initial and control for 16Bpp TFT LCD
**************************************************************/

#include "config.h"

//#define *LCDFRAMEBUFFER		0x33E00000			//LCD�Դ����ʼ��ַ�� 


#define M5D(n)				((n) & 0x1fffff)	// To get lower 21bits

volatile unsigned short LCD_BUFFER[SCR_YSIZE_TFT][SCR_XSIZE_TFT];

/**************************************************************
320��240 16Bpp TFT LCD����ģ���ʼ��
**************************************************************/
void Lcd_Init(void)
{
 	rGPCUP  = 0x00000000;		//C������
  	rGPCCON = 0xaaaa02a9; 
/////////////////////////////////////////////////////////////
//  rGPCCON = 0xaaaaaaaa;       
//  rGPCUP  = 0xffff;     // The pull up function is disabled GPC[15:0] 
//////////////////////////////////////////////////////////////
//    rGPDCON = 0xaaaaaaaa;       
//    rGPDUP  = 0xffff;     // The pull up function is disabled GPD[15:0]

////////////////////////////////////////////////////////////////	 
  	rGPDUP  = 0x00000000;
  	rGPDCON=0xaaaaaaaa; //Initialize VD[15:8]
 
 	rLCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
    	// TFT LCD panel,16 bpp TFT,ENVID=off   VMÿ֡���� ��ֹ��Ƶ�����LCD �����ź�
 	rLCDCON2=(VBPD<<24)|(LINEVAL_TFT<<14)|(VFPD<<6)|(VSPW);
		//
  	rLCDCON3=(HBPD<<19)|(HOZVAL_TFT<<8)|(HFPD);
  	rLCDCON4=(MVAL<<8)|(HSPW);
 	rLCDCON5 = (1<<11) | (1<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6) | (1<<3)  |(BSWP<<1) | (HWSWP);
	//5:6:5 ��ʽ   VCLK ������ȡ��Ƶ����   VLINE/HSYNC ���弫��--��ת VFRAME/VSYNC ���弫��--��ת
	//VD����Ƶ���ݣ����弫��--����  VDEN �źż���--����	 ����PWREN �ź�	 ���ֽڽ�������λ--����ʹ��
//	rLCDCON5=(1<<11)|(1<<9)|(1<<8)|(1<<6);	//FRM5:6:5,HSYNC and VSYNC are inverted
/////////////////////////////////////////////////////////////////////////////////////
  	rLCDSADDR1=(((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
	/*****************************************************************************/
	/*�����������ģ�ϵͳ�ڴ��ַA[30:22]����Bankλ��Ϊͼ�񻺳�*/
	/*LCDSADDR1��LCDBANK[29:21]��ֵΪA[30:22],��A[30:22]=((U32)*/
	/*LCD_BUFFER>>22);*/
	/*LCDSADDR1��LCDBASEU[20:0]��ֵλA[21:1],��A[21:1]=((U32)LCD_BUFFER>>1) */
	/*&0x1fffff  //ȡ��21 bits ��M5D���ͱ�ʾ&0x1fffff;*/	
	/*���ԣ�rLCDSADDR1=(LCDBANK)|(LCDBASEU)=(A[30:22]<<21)|(LCDBASEU)=(((U32)LCD_BUFFER>>22)<<21)|(((U32)LCD_BUFFER>>1) &0x1fffff) ;*/
	/************************************************************************************************************/
   	rLCDSADDR2=M5D( ((U32)LCD_BUFFER+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1 );
 	rLCDSADDR3=(((SCR_XSIZE_TFT-LCD_XSIZE_TFT)/1)<<11)|(LCD_XSIZE_TFT/1);
 	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
  	rTCONSEL &= (~7) ;     // Disable LPC3480
  	rTPAL=0; // Disable Temp Palette */	
}

/**************************************************************
LCD��Ƶ�Ϳ����ź��������ֹͣ��1������Ƶ���
**************************************************************/
void Lcd_EnvidOnOff(int onoff)
{
	if(onoff==1)
		rLCDCON1|=1; // ENVID=ON
	else
		rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
}

/**************************************************************

320��240 16Bpp TFT LCD ��Դ��������ʹ��
**************************************************************/
static void Lcd_PowerEnable(int invpwren,int pwren)
{
    //GPG4 is setted as LCD_PWREN
       rGPGUP = rGPGUP & ( ~(1 << 4)) |(1 << 4); // Pull-up disable
       rGPGCON = rGPGCON & ( ~(3 << 8)) |(3 << 8); //GPG4=LCD_PWREN
       rGPGDAT = rGPGDAT | (1 << 4) ;
//	invpwren=pwren;
    //Enable LCD POWER ENABLE Function
       rLCDCON5 = rLCDCON5 & ( ~(1 << 3)) |(pwren << 3);   // PWREN
       rLCDCON5 = rLCDCON5 & ( ~(1 << 5)) |(invpwren << 5);   // INVPWREN
}
/**************************************************************
320��240 16Bpp TFT LCD�ƶ��۲촰��
**************************************************************/
void Lcd_MoveViewPort(int vx,int vy)
{
	U32 addr;

	SET_IF(); 
	#if (LCD_XSIZE_TFT<32)
		while((rLCDCON1>>18)<=1); // if x<32
	#else	
		while((rLCDCON1>>18)==0); // if x>32
	#endif
    
	addr=(U32)LCD_BUFFER+(vx*2)+vy*(SCR_XSIZE_TFT*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1));
	CLR_IF();
}    

/**************************************************************
320��240 16Bpp TFT LCD�ƶ��۲촰��
**************************************************************/


/**************************************************************
320��240 16Bpp TFT LCD�������ص���ʾ�������
**************************************************************/
void PutPixel(U32 x,U32 y, U32 c )
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
		LCD_BUFFER[(y)][(x)] = c;
}
/*========����==================*/
/*void pixel(U32 x,U32 y,U32 color)
{
	U32 i,j;
// 	i=319-y;
// 	j=x;
	i=x;
	j=239-y;
	LCD_BUFFER[j][i] =color;	
} */
/**************************************************************
320��240 16Bpp TFT LCDȫ������ض���ɫ��Ԫ������
**************************************************************/
void Lcd_ClearScr( U32 c)
{
	unsigned int x,y ;
		
    for( y = 0 ; y < SCR_YSIZE_TFT ; y++ )
    {
    	for( x = 0 ; x < SCR_XSIZE_TFT ; x++ )
    	{
			LCD_BUFFER[y][x] = c ;
    	}
    }
}

/**************************************************************
LCD��Ļ��ʾ��ֱ��ת
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
��LCD��Ļ�ϻ�һ������
**************************************************************/
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}

/**************************************************************
��LCD��Ļ������ɫ���һ������
**************************************************************/
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}

/**************************************************************
��LCD��Ļ��ָ������㻭һ��ָ����С��ͼƬ
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
				LCD_BUFFER[y][x] = c ;
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
	Lcd_PowerEnable(0, 1);	//����PWREN �ź�   ��������
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

/******************** д16*16���� ************************************/
/*type:0--����������--����*/
void w_hanzi_16(U32 x,U32 y,U32 color,const U8 ch[],U8 type)
{
	U8 mask,buffer;
	U16 i,j;
	for(i=0;i<16;i++)
	{
	 	mask=0x80;		//����
		buffer=ch[i*2]; //��ȡһ�еĵ�һ���ֽ�
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
			{
				if(0==type)
					PutPixel(x+j,y+i,color);
				else
				//	PutPixel(y+i,240-x-j,color);
					PutPixel(319-(y+i),x+j,color);
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
			//		PutPixel(y+i,240-x-j-8,color);
					PutPixel(319-(y+i),x+j+8,color);
			}
			mask=mask>>1;
		}
	}
};
/****************************************************
˵    ��:д8x16�ַ�
��ڲ���:(x,y)--���Ͻ�����, ch[]--�ַ�����,symbol--��symbol���ַ�, color--��ɫ��
���ڲ���:��
****************************************************/
void w_symbol(U32 x,U32 y,const U8 ch[],U32 symbol,U16 color)
{
	U8 mask,buffer;
	U16 i,j;
	for(i=0;i<16;i++)
	{
		mask=0x80;
		buffer=ch[16*symbol+i];
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
				PutPixel(x+j,y+i,color);
			mask=mask>>1;
		}
		
	}
}
/****************************************************
˵    ��:д16x16�ַ�
��ڲ���:(x,y)--���Ͻ�����, ch[]--�ַ�����, symbol--��symbol���ַ�, color--��ɫ��
���ڲ���:��
****************************************************/
/*void w_symbol_16x16(U32 x,U32 y,const U8 ch[],U32 symbol,U16 color)
{
	U8 mask,buffer;
	U16 i,j;
	for(i=0;i<32;i++)
	{
		mask=0x80;
		buffer=ch[32*symbol+i];
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
				PutPixel(x+j+8*(i%2),y+i,color);
			mask=mask>>1;
		}
		
	}
} */
void w_symbol_16x16(U32 x,U32 y,const U8 ch[],U32 symbol,U16 color)
{
	U8 mask,buffer;
	U16 i,j;
	for(i=0;i<16;i++)
	{
	 	mask=0x80;		//����
		buffer=ch[symbol*32+i*2]; //��ȡһ�еĵ�һ���ֽ�
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
			{
		//		if(0==type)
	 				PutPixel(x+j,y+i,color);
		//		else
		 		//	PutPixel(y+i,240-x-j,color);
				//	PutPixel(319-(y+i),x+j,color);
			}
			mask=mask>>1;
		}
		mask=0x80;
		buffer=ch[symbol*32+i*2+1];
		for(j=0;j<8;j++)
		{
			if(buffer&mask)
			{
		//		if(0==type)
		 	  		PutPixel(x+j+8,y+i,color);
		//	    else
			//		PutPixel(y+i,240-x-j-8,color);
			//		PutPixel(319-(y+i),x+j+8,color);
			}
			mask=mask>>1;
		}
	}
}
