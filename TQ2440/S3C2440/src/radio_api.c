
#include "config.h"

#define CHIP_DEVICE_ID		0x80

#define PARAM_FREQ_THREASHOLD  			150 
#define PARAM_LAST_FREQ_THREASHOLD 	100 
#define PARAM_RSSI_FM 		20
#define PARAM_SNR_FM		2
#define PARAM_RSSI_AM 		16 
#define PARAM_SNR_AM 		21 
#define PARAM_IMPUSE_COUNTER_FM 	14 
#define PARAM_TUNE_FM_DELAY 		35 
#define PARAM_TUNE_AM_DELAY 		65 

#define MAX_FREQ_DEVIATION 0x1ff
#define NEGATIVE_FREQ 0x100

//BK108X register map
#define REG0_DEVICE_ID		0x00
#define REG1_CHIP_ID  		0x01
#define REG2_POWER_CFG 		0x02
#define REG3_CHANNEL 		0x03
#define REG4_SYS_CONF1 		0x04
#define REG5_SYS_CONF2 		0x05
#define REG6_SYS_CONF3 		0x06
#define REG7_TEST1     			0x07
#define REG8_TEST2     			0x08
#define REG9_BOOT_CFG 			0x09
#define REG10_RSSI_STATUS			0x0a
#define REG11_READ_CHAN 		0x0b			
	
BYTE   StereoMonoMode=0;
BYTE   StereoMode=FALSE;
UINT16 g_last_freq_deviation_value = PARAM_LAST_FREQ_THREASHOLD;
/***************************************************
BK1086
****************************************************/
#ifdef D_BK1086_CHIP
#define REG_NUM 34
unsigned char BK1086_FM_initialization_reg[]=
#if 1
{
0x00,0x08, //REG0
0x10,0x80, //REG1
0X36,0X01,//0x10,0x01, //REG2         默认输出不静音;共用主控时钟; 0x1201独立配置32.768Khz晶体设置;
//REG2=0x4201         输出静音;共用主控时钟; 0x5201独立配置32.768Khz晶体设置;
0x00,0x00, //REG3
0X08,0XC0,//0x40,0xC0, //REG4
#ifdef FM_STEP_50K
0x0a,0x2f,
#else
0x0A,0x1F, //REG5          默认87.5~108Mhz频段; 100Khz步进; 默认输出音量最大0x0F.
#endif
//REG5=0x0A5F          76.0~108Mhz频段, 100Khz步进, 默认输出音量最大0x0F.
//REG5=0x0A2F          87.5~108Mhz频段,   50Khz步进,  默认输出音量最大0x0F.
0x00,0x2E, //REG6
0x0a,0xa3,//0x02,0xFF, //REG7	FREQD / SNR
0x5B,0x11, //REG8
0x00,0x00, //REG9
0x41,0x14,//0x41,0x1E, //REG10	
0x00,0x00, //REG11
0xCE,0x00, //REG12
0x00,0x00, //REG13
0x00,0x00, //REG14
0x10,0x00, //REG15
0x00,0x10, //REG16         默认配32.768Khz时钟;

//REG16= 0x16E3        配12Mhz时钟设置; 

//REG16= 0x2DC6       配24Mhz时钟设置
0x00,0x00, //REG17          默认配32.768Khz时钟;

//REG17=0x8000         配12/24Mhz时钟设置,
0x13,0xFF, //REG18
0x98,0x52, //REG19         默认天线外接匹配器件; 

//REG19=0x9C52       使能天线脚内部75Ω电阻匹配,天线不外接匹配(效果差于外接匹配,好于不接任何匹配)
0x00,0x00, //REG20
0x00,0x00, //REG21
0x00,0x08, //REG22
0x00,0x00, //REG23
0x51,0xE0, //REG24       默认天线从2脚输出; 

//REG24 =0x51E1     天线从4脚输入(仅适用于BK1080QB)
0x28,0xBC, //REG25      默认配32.768Khz/12Mhz时钟;

//REG25 = 0xA8BC    配24Mhz时钟设置,
0x26,0x45, //REG26
0x00,0xE4, //REG27
0x1C,0xD8, //REG28
0x3A,0x50, //REG29
0xEA,0xE0, //REG30      原为0xEAF0, 近期重要更改
0x30,0x00, //REG31
0x02,0x00, //REG32      原为0x0000, 近期重要更改

0x00,0x00, //REG33
};
#else
{
0x00,0x08, //REG0
0x10,0x80, //REG1
0X36,0X01,//0x10,0x01, //REG2         默认输出不静音;共用主控时钟; 0x1201独立配置32.768Khz晶体设置;
//REG2=0x4201         输出静音;共用主控时钟; 0x5201独立配置32.768Khz晶体设置;
0x00,0x00, //REG3
0X08,0XC0,//0x40,0xC0, //REG4
#ifdef FM_STEP_50K
0x0a,0x2f,
#else
0x0A,0x1F, //REG5          默认87.5~108Mhz频段; 100Khz步进; 默认输出音量最大0x0F.
#endif
//REG5=0x0A5F          76.0~108Mhz频段, 100Khz步进, 默认输出音量最大0x0F.
//REG5=0x0A2F          87.5~108Mhz频段,   50Khz步进,  默认输出音量最大0x0F.
0x00,0x2E, //REG6
0x0a,0xa3,//0x02,0xFF, //REG7	FREQD / SNR
0x5B,0x11, //REG8
0x00,0x00, //REG9
0x41,0x14,//0x41,0x1E, //REG10	
0x00,0x00, //REG11
0xCE,0x00, //REG12
0x00,0x00, //REG13
0x00,0x00, //REG14
0x10,0x00, //REG15
0x00,0x10, //REG16         默认配32.768Khz时钟;

//REG16= 0x16E3        配12Mhz时钟设置; 

//REG16= 0x2DC6       配24Mhz时钟设置
0x00,0x00, //REG17          默认配32.768Khz时钟;

//REG17=0x8000         配12/24Mhz时钟设置,
0x13,0xFF, //REG18
0x98,0x52, //REG19         默认天线外接匹配器件; 

//REG19=0x9C52       使能天线脚内部75Ω电阻匹配,天线不外接匹配(效果差于外接匹配,好于不接任何匹配)
0x00,0x00, //REG20
0x00,0x00, //REG21
0x00,0x08, //REG22
0x00,0x00, //REG23
0x51,0xE0, //REG24       默认天线从2脚输出; 

//REG24 =0x51E1     天线从4脚输入(仅适用于BK1080QB)
0x28,0xBC, //REG25      默认配32.768Khz/12Mhz时钟;

//REG25 = 0xA8BC    配24Mhz时钟设置,
0x26,0x45, //REG26
0x00,0xE4, //REG27
0x1C,0xD8, //REG28
0x3A,0x50, //REG29
0xEA,0xf0, //REG30      原为0xEAF0, 近期重要更改
0x30,0x00, //REG31
0x00,0x00, //REG32      原为0x0000, 近期重要更改

0x00,0x00, //REG33
};
#endif

unsigned char writeData8[REG_NUM*2];

void delay_us(UINT16 us)
{
	UINT16 i,j;
	for(i=us;i>0;i--);
	//for(j=3;j>0;j--);
}
void delay_ms(UINT16 ms)
{
	UINT16 i,k;
	for(i=0; i<ms;i++) 
		delay_us(1000);
/*	
	for(i=0; i<2000;i++)
	{    
		for(k=0; k<ms; k++) 
		{

		}
	}
*/
}

void tuner_mute(unsigned char mute)
{
	unsigned char TmpBuff[2];

	Radio_Reg_Read(REG2_POWER_CFG,&(TmpBuff[0]),2);

	if(mute)
		TmpBuff[0] |= 0x40;
	else
		TmpBuff[0] &= 0xbf;

	Radio_Reg_Write(REG2_POWER_CFG,&(TmpBuff[0]),2);
}

void Set_FM_StereoMono(void) //  1: MONO   0: Stereo
{
	unsigned char TmpBuff[2];

	Radio_Reg_Read(REG2_POWER_CFG,&(TmpBuff[0]),2);
	if(StereoMonoMode)
	{
		StereoMonoMode=0;
		StereoMode=FALSE;
		TmpBuff[0] |= 0x02;	//set MONO
 		Radio_Reg_Write(REG2_POWER_CFG,&(TmpBuff[0]),2);
	}
	else
	{
		StereoMonoMode=1;
		StereoMode=TRUE;
		TmpBuff[0] &= 0xdf;	//set Stereo
 		Radio_Reg_Write(REG2_POWER_CFG,&(TmpBuff[0]),2);
	}
	delay_ms(50);
}
void BK1086_POWER(UINT8 dir)
{
	unsigned char TmpBuff[2];

	Radio_Reg_Read(REG2_POWER_CFG,&(TmpBuff[0]),2);
	TmpBuff[1] &= 0xbe;
	if(dir)	//power up
		TmpBuff[1] |= 0x01;
	else
		TmpBuff[1] |= 0x40;
	Radio_Reg_Write(REG2_POWER_CFG,&(TmpBuff[0]),2);
	
	
}
unsigned int BK1086_FreqToChan(unsigned int frequency) 
{
	unsigned int channel=0;
//	if(FM_BAND == gps->RadioBand)		//FM
	{
#ifdef FM_STEP_50K
		channel = (frequency - 8750)/5;
#else // 100k
		channel = (frequency - 8750)/10;
#endif
	}
	return channel;
	
}

void BK1086_SetFreq( unsigned int curFreq )
{  
	unsigned char TmpBuff[2];
	unsigned int curChan;
	
//	Radio_Reg_Read(REG3_CHANNEL,TmpBuff,2);

	curChan=BK1086_FreqToChan(curFreq); 

/*	
	TmpBuff[0] = 0x00; 
	TmpBuff[1] = 0x00; 
	Radio_Reg_Write(REG3_CHANNEL,TmpBuff,2);
	delay_1ms(50);
	
	TmpBuff[0] |= (curChan>>8) & 0x7f;
	TmpBuff[1] = curChan & 0xff;
	Radio_Reg_Write(REG3_CHANNEL,TmpBuff,2);
	delay_1ms(50);
	
	TmpBuff[0] |= 0x80;
	TmpBuff[1] = curChan & 0xff;
	Radio_Reg_Write(REG3_CHANNEL,TmpBuff,2);
	delay_1ms(50);
*/
#if 0
	TmpBuff[0] &= 0x7c; 		//Tune Disable
	TmpBuff[0] |= (curChan>>8) & 0xff;
	TmpBuff[1] = curChan & 0xff;
	Radio_Reg_Write(REG3_CHANNEL,&(TmpBuff[0]),2); //write reg2,with 4 bytes

	delay_ms(20);
	TmpBuff[0] |= 0x80;//start tune
	Radio_Reg_Write(REG3_CHANNEL,&(TmpBuff[0]),2); //write reg2,3,with 4 bytes
	delay_ms(20);
#else
	TmpBuff[0] = 0x0;//reset tune
	TmpBuff[1] = curChan&0xff;
	Radio_Reg_Write(REG3_CHANNEL,&(TmpBuff[0]),2); 

//	Delay(60);

	TmpBuff[0] = (curChan>>8) & 0xff;
	TmpBuff[0] |= 0x80;//start tune
	TmpBuff[1] = curChan & 0xff;
	Radio_Reg_Write(REG3_CHANNEL,&(TmpBuff[0]),2);
#endif
}

unsigned char BK1086_ValidStop(UINT16 freq) 
{
	unsigned char falseStation = 0;
	unsigned char TmpBuff[10];
	unsigned char impuse_counter;
	unsigned int curChan;
	unsigned int retry_times=500;
	unsigned int CurFreqDeviation;
	unsigned int TempData;
	if((freq>=10780)&&(freq<=10800))		
		return 0;
	BK1086_SetFreq(freq);
	do
	{
		Radio_Reg_Read(REG10_RSSI_STATUS,&(TmpBuff[0]),2);
		delay_ms(10);
		if(TmpBuff[0] & 0x40)		//check STC
			break;
		if((retry_times--) == 0)
		{
			falseStation = 1;//false
			return 0;		
		}
	}while(1);
	
	if(TmpBuff[0] & 0x10)	//AFCRL
	{
		falseStation = 1;//false
		return 0;
	}

	Radio_Reg_Read(REG10_RSSI_STATUS,&(TmpBuff[0]),2);		
	TempData = TmpBuff[1];									//RSSI
//	MS_CallOperationScreen(MS_OP_MSG_SYS_NUMBER_INPUT, TempData);
	if(TempData < PARAM_RSSI_FM)
	{
		falseStation = 1;//false
		return 0;
	}
		
	Radio_Reg_Read(REG7_TEST1,&(TmpBuff[0]),2);	
	
	TempData = TmpBuff[1] & 0x0f;							//SNR
//	MS_CallOperationScreen(MS_OP_MSG_SYS_NUMBER_INPUT, TempData);
	if(TempData < PARAM_SNR_FM)
	{
		falseStation = 1;//false
		return 0;
	}
	
	TempData = ((TmpBuff[0]<<8) | TmpBuff[1])>>4;			//FREQD	
//	MS_CallOperationScreen(MS_OP_MSG_SYS_NUMBER_INPUT, TempData);
	if((TempData > PARAM_FREQ_THREASHOLD) && (TempData < (0xfff-PARAM_FREQ_THREASHOLD)))
	{
		falseStation = 1;//false
		return 0;
	}
	else
	{
		if((g_last_freq_deviation_value < PARAM_LAST_FREQ_THREASHOLD) )
		{
			falseStation = 1;//false
			return 0;
		}
	}
	g_last_freq_deviation_value = TempData;	
	return 1;
}

void Tuner_Init(void)
{
	UINT8 i;
	for(i=0;i<REG_NUM;i++)
	{
		Radio_Reg_Write(i,&(BK1086_FM_initialization_reg[i*2]),2);
		delay_ms(50);
	}
	delay_ms(50);
}

void Radio_Reg_Read(UINT8 reg,UINT8 *pBuf,UINT8 len)
{
    UINT8 i;
    UINT8 Addr;
        
    Addr=CHIP_DEVICE_ID;//device address.

    BEKEN_I2C_Start();

    BEKEN_I2C_sendbyte(Addr);   
    BEKEN_I2C_ReceiveACK();

    reg=reg<<1;
    reg|=0x01;
    BEKEN_I2C_sendbyte(reg);
    BEKEN_I2C_ReceiveACK();

    for(i=0;i<len-1;i++)
    {
        pBuf[i] = BEKEN_I2C_readbyte();
        BEKEN_I2C_ack();
    }
    pBuf[i] = BEKEN_I2C_readbyte();
    BEKEN_I2C_nack();
    
    BEKEN_I2C_Stop();
 
}
void Radio_Reg_Write(UINT8 reg,UINT8 *pBuf,UINT8 len)
{
    UINT8 i;
    UINT8 Addr;

    Addr=CHIP_DEVICE_ID;//device address.

    BEKEN_I2C_Start();

    BEKEN_I2C_sendbyte(Addr);
    BEKEN_I2C_ReceiveACK();

    reg=reg<<1;
    BEKEN_I2C_sendbyte(reg);   
    BEKEN_I2C_ReceiveACK();
	 
    for(i=0;i<len;i++)
    {
        BEKEN_I2C_sendbyte(pBuf[i]);
        BEKEN_I2C_ReceiveACK(); 
    }
    BEKEN_I2C_Stop();
}

void BK1086_SetVolumeLevel(unsigned char level)
{
	unsigned char TmpBuff[2];

	Radio_Reg_Read(REG5_SYS_CONF2,&(TmpBuff[0]),2);
	TmpBuff[1] &=0xf0;
	TmpBuff[1] |= (level & 0x0f);

	Radio_Reg_Write(REG5_SYS_CONF2,&(TmpBuff[0]),2);
}

#endif



