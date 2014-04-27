/**************************************************
**	�ļ���:Timer.c
**	�汾��:V 1.0
**	�ļ�˵��:��ʱ������
***************************************************/

#include "config.h"

/*********************************************************************************************************
Timer_Isr() //�տ�ʼ�����ж���,����ϵͳ������
********************************************************************************************************/
U8 timer0_flag; 
U8 timer4_flag;
void __irq Timer0_ISR(void)
{
   	static  U32 i=0;
	rSRCPND |=BIT_TIMER0;
	rINTPND |=BIT_TIMER0;
 
 	 i++;
//	 bright(i%2);
   	if(10==i)
  	{
	  	i=0;
		timer0_flag=~timer0_flag;
		//timer0_flag=1;  //	while(1)light(); 
 	}
} 
void __irq Timer4_ISR(void)
{
 	 
   	static  U32 i,j;
	rSRCPND |=BIT_TIMER4;
	rINTPND |=BIT_TIMER4;
 	i++;
	if(3==i)
	{
		i=0;
	 	j++;
		rGPBDAT=(rGPBDAT&0XFFFFFE1F)|((~((j%16)<<5)&0x1E0));
	}

//	if(0==timer4_flag)
//	{
 //		color++;
//		timer4_flag=1; 
//	}
//	 	 bright(i%2);
 //  if(10==i)
 	{
//  		i=0;
// 		timer4_flag=~timer4_flag;  //	while(1)light(); 
 	}
} 
/*********************************************************************************************************
Initial Timer0 use for ucos time tick
********************************************************************************************************/
void Timer0Init(void)
{
	// ��ʱ������

////********************** TIME0 **************************///	
	rTCON = rTCON & (~0xf) ;			//Timer 0 clear manual update bit, stop Timer0	
	rTCFG0 	&= 0xffffff00;					// set Timer 0&1 prescaler 0
	rTCFG0 |= 15;							//prescaler = 15+1
	rTCFG1 	&= 0xfffffff0;					// set Timer 0 MUX 1/4
	rTCFG1  |= 0x00000001;					// set Timer 0 MUX 1/4
    rTCNTB0 = (PCLK / (4 *15* 10)) - 1;  
    rTCON = rTCON & (~0xf) |0x02;              // updata 		
 //	rTCON = rTCON & (~0xf) |0x09; 	// star
////********************** TIME4 **************************///
 	rTCON &=0X0FFFFF;	  // Timer 4 ����̬	�޲��� ֹͣ��ʱ��4
   	rTCFG0 	&= 0xFFFF00FF;					// set Timer 2&3&4 prescaler 1
 	rTCFG0 |=0X0F00;							//prescaler = 15+1
 	rTCFG1 	&= 0xfff0ffff;				 
 	rTCFG1  |= 0x00010000;					// set Timer 4 MUX 1/4
	rTCNTB4 =(PCLK / (4 *15* 10)) - 1;
 	rTCON = (rTCON&0xFF8FFFFF) | 0x00200000;    // updata 		
 	rTCON = (rTCON&0xFF8FFFFF) | 0x00500000; 	// star
   
 }

/*********************************************************************************************************
system IsrInit
********************************************************************************************************/
void time_ISRInit(void)
{
	// �����жϿ�����
	rPRIORITY = 0x00000000;		// ʹ��Ĭ�ϵĹ̶������ȼ�
	rINTMOD = 0x00000000;		// �����жϾ�ΪIRQ�ж�
	pISR_TIMER0= (U32) Timer0_ISR;
	pISR_TIMER4= (U32) Timer4_ISR;
 // 	rINTMSK &= ~BIT_TIMER0;			// ��TIMER0�ж�����
 	rINTMSK &= ~BIT_TIMER4;			// ��TIMER4�ж�����
	rINTMSK &= ~0x00004000;    //intmask_timer4 = 1;
/*
//////////////////////////////////////////////////////////////////////////
rINTMSK &= ~0x00004000;    //intmask_timer4 = 1;						//
																		//
         rTCFG0 = 0x0000C700;     //pre_CLK = PCLK/200 = 320Khz		 	//
																	    //
         rTCFG1 = 0x00030000;     //MUX_CLK = pre_CLK/16 = 20Khz		//
																		//
    rTCNTB4 = 20000;          //f_INT_timer4 = MUX_CLK/20000 = 1hz 		//
																		//
        rTCON  = 0x00200000;//timer4:EN_UPDATE   						//
																		//
    rTCON  = 0x00500000;//timer4 start,DIS_UPDATE						//
 /////////////////////////////////////////////////////////////////////////
 */
 }
