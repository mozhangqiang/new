#include "config.h"	
static U32 key_val;
/****************************************************
˵    ��:��ʼ��EINT0
��ڲ���:��
���ڲ���:��
****************************************************/ 
void __irq EINT0_ISR(void)
{
	U16 temp; 
// 	rSRCPND |=BIT_EINT0;				
 //	rINTPND |=BIT_EINT0;
	 	temp=rGPFCON;
	 	rGPFCON =0; 
	//	rGPFCON =0; 
	 	rGPFUP =0;
	//	delay_ms(10);
//	if(0==rGPFDAT&0X1)
	{
	//	delay_ms(10);
	//	rGPFCON=temp;
//		if(0==rGPFDAT&0X1)
		{
		//	rINTPND |=BIT_EINT0;
		//	rSRCPND |=BIT_EINT0;
			key_val++;
//			temp=rGPFCON;
//			rGPFCON &=0XFFFC; 
 			while(rGPFDAT&0X1==0) 
				Lcd_ClearScr(white);
 		 	rGPFCON=temp;
	//		rINTPND |=BIT_EINT0;rSRCPND |=BIT_EINT0;
	 		rSRCPND |=BIT_EINT0;				
 			rINTPND |=BIT_EINT0;
			switch (key_val%5)
			{
				case 0:Lcd_ClearScr(purple);break;
				case 1:Lcd_ClearScr(red);break; 
				case 2:Lcd_ClearScr(blue);break;
				case 3:Lcd_ClearScr(green);break;
				case 4:Lcd_ClearScr(yellow);break;	
				default:Lcd_ClearScr(black);break;	
			}
	//	rGPFCON=temp;
		}	
	}
/*	rINTPND |=BIT_EINT0;
	rSRCPND |=BIT_EINT0;
	key_val++;
	temp=rGPFCON;
	rGPFCON &=0XFFFC; 
	while(0==rGPFDAT&0X1);
	rGPFCON=temp;
	switch (key_val%5)
	{
		case 0:Lcd_ClearScr(white);break;
		case 1:Lcd_ClearScr(red);break;
		case 2:Lcd_ClearScr(blue);break;
		case 3:Lcd_ClearScr(green);break;
		case 4:Lcd_ClearScr(yellow);break;
		default:Lcd_ClearScr(black);break;	
	} */
}
/****************************************************
˵    ��:��ʼ��EINT0
��ڲ���:��
���ڲ���:��
****************************************************/ 
void eint0_init(void)
{
 	rINTMSK |=BIT_EINT0;					//��ʼ��ǰ�����ж�
  	rGPFCON=rGPFCON & 0XFFFC | (0x0002);	//EINT0
 	rINTMOD	&=0XFFFFFFFE;					//IRQ

 	rEXTINT0=( rEXTINT0 & 0XFFFFFFF8 )| 0X02;//�½��ش���
//	rEXTINT0=( rEXTINT0 & 0XFFFFFFF8 )| 0X0;											//���ȼ�Ĭ��
	pISR_EINT0=(U32)EINT0_ISR;
	rSRCPND |=BIT_EINT0;				
	rINTPND |=BIT_EINT0;

 	rINTMSK &=0XFFFFFFFE;					//�ɷ���
}
