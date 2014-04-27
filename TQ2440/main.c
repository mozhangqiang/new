#define	GLOBAL_CLK		1 
#include<string.h>
#include "config.h"
#include "image160120.h"
#include "image320240.h"

//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
extern char Image$$ER_ROM1$$RO$$Limit[];
extern char Image$$ER_ROM1$$RO$$Base[];
extern char Image$$RW_RAM1$$RW$$Limit[];
extern char Image$$RW_RAM1$$RW$$Base[];
extern char Image$$RW_RAM1$$ZI$$Limit[];
extern char Image$$RW_RAM1$$ZI$$Base[];

extern unsigned char timer0_flag;
extern unsigned char timer4_flag;
const U32 COLOR[7]={red,orange,yellow,green,cyan,blue,purple};
///************************************************///
void light(void)
{
	U32 i,temp;		 
	for(i=0,temp=0x100;i<4;i++)
	{
 		rGPBDAT=(rGPBDAT&0XFFFFFE1F)|(~temp);
		temp=temp>>1;
		delay_ms(500);
	}  
	for(i=0,temp=0x20;i<4;i++)
	{			
		rGPBDAT=(rGPBDAT&0XFFFFFE1F)|(~temp);
		temp=temp<<1;
		delay_ms(500);		
	} 
}

void bright(U8 dat)
{
	if(0==dat)
		rGPBDAT &=0XFFFFFE1F;
	else
		rGPBDAT |=0X1E0;
}

int Main(void)
{
	uint8 buff[34*2]={	0x00,0x08, //REG0
					0x10,0x80, //REG1
					0X36,0X01,};
	static U32 i,j,x,y,num,color,back,dir,tmp_x,tmp_y,temp;
	rGPBCON=rGPBCON|0x15400;		//GPB5~GPB8输出
	rGPBUP=rGPBUP|0X1E0;				//GPB5~GPB8禁止上拉 
 //	time_ISRInit();	
 //	Timer0Init();
 	Lcd_TFT_Init() ;
  	eint0_init();	
// 	Lcd_ClearScr(black);
//	delay_ms(20000);
//  	Paint_Bmp(0,0,320,240,image_320240_2); 
//	delay_ms(50000);
	PollUpGPIO(I2C_CLK,1);
	PollUpGPIO(I2C_DAT,1);
	delay_ms(50);
	Tuner_Init(); Tuner_Init();
	while(1) 
	{
/*	 PutPixel(0,0,green);
	 PutPixel(0,239,red);
	 PutPixel(319,0,blue);
	 PutPixel(319,239,purple);	*/
	 //for(i=0;i<240;i++)

		 
 	/*	if(0==timer0_flag)
			rGPBDAT=(rGPBDAT&0XFFFFFE1F)|0X1E0;
 		else
			rGPBDAT=(rGPBDAT&0XFFFFFE1F)|0X1C0;	
///////////////////////////////////////////////////////			    
 		if(0==timer4_flag)
			rGPBDAT=(rGPBDAT&0XFFFFFE1F)|0XA0;
 		else
 			rGPBDAT=(rGPBDAT&0XFFFFFE1F)|0X140;	 */
 		//	 {while(1){bright(0);delay_ms(10);bright(1);delay_ms(10);};timer0_flag=0;}
    //	if(timer4_flag)
 		//	 {while(1){light();};timer4_flag=0;}  
 	 
 	/*	for(i=0;i<240;i++)
		 	for(j=0;j<320;j++)	
			{
				while(0==timer4_flag);
	 			Glib_Rectangle(i,i,j,j,color);	
				timer4_flag=0;
			}   
	 */
/* 
  		Paint_Bmp(0,0,160,120,image_160120_0);
 	 	Paint_Bmp(0,120,160,120,image_160120_1);
  	 	Paint_Bmp(160,0,160,120,image_160120_2);
 	 	Paint_Bmp(160,120,160,120,image_160120_3);
 	delay_ms(40000); */
	/****************************************************/
	/*
 		Paint_Bmp(320*240*0,0,320,240,image_320240_0);
		Paint_Bmp(320*240*1,0,320,240,image_320240_1);
		Paint_Bmp(320*240*2,0,320,240,image_320240_2);
		Paint_Bmp(320*240*3,0,320,240,image_320240_3);
		Paint_Bmp(320*240*4,0,320,240,image_320240_4);
		Paint_Bmp(320*240*5,0,320,240,image_320240_5);
		Paint_Bmp(320*240*6,0,320,240,image_320240_6);
		Paint_Bmp(320*240*7,0,320,240,image_320240_7);
		Paint_Bmp(320*240*8,0,320,240,image_320240_8);
		Paint_Bmp(320*240*9,0,320,240,image_320240_9);
		Paint_Bmp(320*240*10,0,320,240,image_320240_10); 
		for(j=0;j<=240*10;j++)	
		{
 			Lcd_MoveViewPort(0,j);	
			delay_ms(200);
		} */

	 ///***********************************************************///
/* 	  Paint_Bmp(0,0,320,240,image_320240_0);
 	  delay_ms(20000); 
	  Paint_Bmp(0,0,320,240,image_320240_1);
	  delay_ms(20000);     
	  Paint_Bmp(0,0,320,240,image_320240_2);
	  delay_ms(20000);
	  Paint_Bmp(0,0,320,240,image_320240_3);
	  delay_ms(20000);
      Paint_Bmp(0,0,320,240,image_320240_4);
	  delay_ms(20000);     
	  Paint_Bmp(0,0,320,240,image_320240_5);
	  delay_ms(20000);
	  Paint_Bmp(0,0,320,240,image_320240_6);
	  delay_ms(20000);
	  Paint_Bmp(0,0,320,240,image_320240_7);
	  delay_ms(20000);
	  Paint_Bmp(0,0,320,240,image_320240_8);
	  delay_ms(20000);
	  Paint_Bmp(0,0,320,240,image_320240_9);
	  delay_ms(20000);
	  Paint_Bmp(0,0,320,240,image_320240_10);
	  delay_ms(20000); 	    
	 /***********************************************************/
 /*	  Glib_FilledRectangle(0,0,320,240,0x001f);
	  delay_ms(20000);
	  Glib_FilledRectangle(0,0,320,240,0x07e0);
	  delay_ms(20000);
	  Glib_FilledRectangle(0,0,320,240,0xf800);
	  delay_ms(20000);
	  Glib_FilledRectangle(0,0,320,240,0xffe0);
	  delay_ms(20000);
	  Glib_FilledRectangle(0,0,320,240,0xf81f);
	  delay_ms(20000);
	  Glib_FilledRectangle(0,0,320,240,0x07ff);
	  delay_ms(20000);	
 	//	Lcd_ClearScr(color);
		//	delay_ms(10);	 */
	  
	 		
	 
   
		 	/*
 			for(i=0;i<320;i+=4)
		 	for(j=0;j<240;j++)
			{
				while(0==timer4_flag);
				PutPixel(i,j,color);
				color+=1000;
				timer4_flag=0;
			}   */ 
  /*		w_hanzi_16(16*0,0,purple,qian,1); 
		w_hanzi_16(16*1,0,green,ru,1);
		w_hanzi_16(16*2,0,blue,shi,1);

		w_hanzi_16(16*12,0,purple,qian,1); 
		w_hanzi_16(16*13,0,green,ru,1);
		w_hanzi_16(16*14,0,blue,shi,1);

 		w_hanzi_16(16*0,SCR_XSIZE_TFT-16,purple,qian,1); 
		w_hanzi_16(16*1,SCR_XSIZE_TFT-16,green,ru,1);
		w_hanzi_16(16*2,SCR_XSIZE_TFT-16,blue,shi,1);

		w_hanzi_16(16*12,SCR_XSIZE_TFT-16,purple,qian,1); 
		w_hanzi_16(16*13,SCR_XSIZE_TFT-16,green,ru,1);
		w_hanzi_16(16*14,SCR_XSIZE_TFT-16,blue,shi,1); 	  */
/*******************************************************/
  	/*	w_hanzi_16(16*1,0,purple,qian,0); 
		w_hanzi_16(16*2,0,green,ru,0);
		w_hanzi_16(16*3,0,blue,shi,0);

		w_hanzi_16(16*16,0,purple,qian,0); 
		w_hanzi_16(16*17,0,green,ru,0);
		w_hanzi_16(16*18,0,blue,shi,0);

		w_hanzi_16(16*1,SCR_YSIZE_TFT-16,purple,qian,0); 
		w_hanzi_16(16*2,SCR_YSIZE_TFT-16,green,ru,0);
		w_hanzi_16(16*3,SCR_YSIZE_TFT-16,blue,shi,0);

		w_hanzi_16(16*16,SCR_YSIZE_TFT-16,purple,qian,0); 
		w_hanzi_16(16*17,SCR_YSIZE_TFT-16,green,ru,0);
		w_hanzi_16(16*18,SCR_YSIZE_TFT-16,blue,shi,0); 	*/	
			 

	 //	PutPixel(67,45,green);	
	//	PutPixel(0,50,green);
	//	PutPixel(0,239,purple);
	//	for(i=0;i<240;i++)
 	/*	for(j=0;j<320;j++)
			for(i=0;i<240;i++)
			{
				pixel(i,j,red);delay_ms(30);
			}	*/  
	//	pixel(0,0,red); pixel(10,0,red);
 /*	 	for(i=0,j=0;i<320;i++)
		{
 			PutPixel(i,45,COLOR[(j++)%7]); //画点
			if(0==i)
				back=319;
			else
				back=i-1;
			PutPixel(back,45,black);	//消点
			delay_ms(1000);		
		}*/	
		/*********** 点运动，遇界面反弹 *******************************/  
 /*		for(x=150,y=120,color=0,dir=1;;)
		{
			switch(dir)
			{
				case 1:x++;y++;tmp_x=x-1;tmp_y=y-1;break;	//右下
				case 2:x--;y++;tmp_x=x+1;tmp_y=y-1;break;	//左下
				case 3:x--;y--;tmp_x=x+1;tmp_y=y+1;break;	//左上
				case 4:x++;y--;tmp_x=x-1;tmp_y=y+1;break;	//右上
				default:break;
			}	
			PutPixel(x,y,COLOR[(color++)%7]); //画点
	 		PutPixel(tmp_x,tmp_y,black); 	  //消点
			if(0==x)
			{
				if(2==dir)
					dir=1;
				else if(3==dir)
					dir=4;
			}
			if(319==x)
			{
				if(1==dir)
					dir=2;
				else if(4==dir)
					dir=3;
			}
			if(0==y)
			{
				if(4==dir)
					dir=1;
				else if(3==dir)
					dir=2;
			}
			if(239==y)
			{
				if(1==dir)
					dir=4;
				else if(2==dir)
					dir=3;
			}
			delay_ms(300);
		} */
	//	PutPixel(67,45,green);
	/******************  写8*16字符  ************************/
/*	Lcd_ClearScr(black);
  	num=sizeof(symbol_8x16)/16;
	for(i=0;i<num;i++)
		w_symbol((8*i)%320,(16*((8*i)/320))%240,symbol_8x16,i,purple);
	delay_ms(50000);    */ 
	/****************** 写16*16字符 *****************************************/
/*	Lcd_ClearScr(black);
	num=sizeof(font_16x16)/32;
    	for(i=0,j=0;i<num;i++,j++)
 	{
  		w_symbol_16x16((16*i)%320,(16*((16*i)/320))%240,font_16x16,j,purple);
	 	if((299==i%300)||(i==num-1))
		{
	 	    delay_ms(50000);
	 		Lcd_ClearScr(black);	
		}
	   
	}	*/
	/*********************graph**************************/
	 /*	for(i=200;i<320;i++)
			draw_line(0,0,i,239,red);
		for(j=120;j<240;j++)
			draw_line(0,0,319,j,red);  */
	//	draw_line(0,239,239,0,green);
	//	draw_line(0,0,12,222,purple);
	//	draw_line(6,8,311,42,black);
	//	draw_Hline1(30,30,2+28,red);
	// 	draw_Hline2(30,31+28,26,red);
	//	draw_Hline2(31+28,30,22,red);
	
	//	draw_Vline1(40,40,2+28,purple);
	//	draw_Vline2(38,40,41+28,purple);
	//	draw_Vline2(36,40,41+28,purple);
	// 	draw_rect(50,50,200,200,red);
	//	draw_rect(40,60,300,150,purple);
	//	draw_FilledRect(41,61,299,149,blue);
	/******************** 画同心圆************************/
  /* 	rGPFCON=rGPFCON & 0XFFFC;
	if((rGPFDAT&0X1)==0)
	{
		while((rGPFDAT&0X1)==0)
		{
			Lcd_ClearScr(COLOR[(i++)%7]);delay_ms(100);
		}		
		num=1;
	}
		
		while(num==1)
		{ 
			for(i=0,j=0;;i++,j+=10)
			{
				draw_circle(160,120,j%200,COLOR[i%7]);
				delay_ms(10);
			}  	 
	 
		}    */  
 //  		for(i=0,j=0;;i++,j+=10)
		{
//			draw_circle(160,120,j%200,COLOR[i%7]);
//			delay_ms(10);
		} 
/*
		SetGPIO(I2C_CLK);
		SetGPIO(I2C_DAT);
		delay_ms(2000);delay_ms(2000);delay_ms(2000);delay_ms(2000);
		ClearGPIO(I2C_CLK);
		ClearGPIO(I2C_DAT);
		delay_ms(2000);delay_ms(2000);delay_ms(2000);delay_ms(2000); 
*/
	

//		Tuner_Init();
		Radio_Reg_Write(2,&(buff[2*2]),2);
		delay_ms(100);
		Radio_Reg_Read(2, &(buff[0]),2);
		delay_ms(100);
		temp=(buff[0]<<8) | buff[1];

		if(temp==13825)
			SetGPIO(LED1);
		else
			{
				SetGPIO(LED2);
				SetGPIO(LED3);
			}
		Radio_Reg_Read(1, &(buff[0]),2);
		temp=(buff[0]<<8) | buff[1];
		if(temp==4224)
			SetGPIO(LED4);
			
		BK1086_SetFreq(10430);

		while(1);
// 		SetGPIO(I2C_CLK);
// 		delay_ms(1000);
// 		ClearGPIO(I2C_CLK);
// 		delay_ms(1000);
	}
}
