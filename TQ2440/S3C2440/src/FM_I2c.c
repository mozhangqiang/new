#include "config.h"

void Set_Data_in(void)
{
	Set_GPIO_To_Input(I2C_DAT);
}
void Set_Data_out(void)
{
	Set_GPIO_To_Output(I2C_DAT);
}
void Set_Clk_out(void)
{
	Set_GPIO_To_Output(I2C_CLK);
}
void I2C_SDA_H(void)
{
	SetGPIO(I2C_DAT);
}
void I2C_SDA_L(void)
{
	ClearGPIO(I2C_DAT);
}
void I2C_SCL_H(void)
{
	SetGPIO(I2C_CLK);
}
void I2C_SCL_L(void)
{
	ClearGPIO(I2C_CLK);
}
UINT8 I2C_SDA_GET(void)
{
	GetGPIO(I2C_DAT);
}

void delay_i2c(UINT16 cnt)
{
	delay_us(cnt);
/*
	UINT16 i,j;
	for(i=cnt;i>0;i--)
		for(j=10;j>0;j--);
*/
}


#ifdef D_BK1086_CHIP
void BK1086_i2c_start_sig(void)
{	
	I2C_SDA_H();//sda=1;
	delay_i2c(1);//delay();
	I2C_SCL_H();//scl=1;
	delay_i2c(1);//delay();
	I2C_SDA_L();//sda=0;
	delay_i2c(1);//delay();
}
void BK1086_i2c_stop_sig(void)
{	
	I2C_SDA_L();//sda=0;
	delay_i2c(1);//delay();
	I2C_SCL_H();//scl=1;
	delay_i2c(1);//delay();
	I2C_SDA_H();//sda=1;
	delay_i2c(1);//delay();
}
void BK1086_i2c_ack(void)
{
	unsigned int time_out_cnt;
	
	I2C_SCL_H();//scl=1;
	delay_i2c(1);//delay();
	Set_Data_in();
	while((I2C_SDA_GET())&&(time_out_cnt<250))time_out_cnt++;
	I2C_SCL_L();//scl=0;
	delay_i2c(1);//delay();
}
/*
void BK1086_i2c_nack(void)
{
	I2C_SCL_L();
	I2C_SDA_H();
	delay_i2c(1);

	I2C_SCL_H();
	delay_i2c(1);
	I2C_SCL_L();
}

unsigned char BK1086_i2c_receive_ack(void)
{
	unsigned char ackflag;
	I2C_SDA_IN();
	delay_i2c(1);
	I2C_SCL_H();
	delay_i2c(1);
	ackflag = I2C_SDA_GET();
	I2C_SCL_L();
	delay_i2c(1);
	return ackflag;
}
*/
void BK1086_i2c_byte_w(unsigned char dat)
{
	unsigned char i,temp;
	temp=dat;

	for(i=0;i<8;i++)
	{
		I2C_SCL_L();//scl=0;
		delay_i2c(1);//delay();
		if(temp&0x80)
			I2C_SDA_H();//sda=1;
		else
			I2C_SDA_L();//sda=0;
		delay_i2c(1);//delay();
		I2C_SCL_H();//scl=1;
		delay_i2c(1);//delay();	
		temp=temp<<1;	
	}
	I2C_SCL_L();//scl=0;
	delay_i2c(1);//delay();
	I2C_SDA_H();//sda=1;
	delay_i2c(1);//delay();
}
unsigned char BK1086_i2c_byte_r()
{
	unsigned char i,temp;
	
	I2C_SCL_L();//scl=0;
	delay_i2c(1);//delay();
	I2C_SDA_H();//sda=1;
	delay_i2c(1);//delay();
	Set_Data_in();
	for(i=0;i<8;i++)
	{
		I2C_SCL_H();//scl=1;
		delay_i2c(1);//delay();
		if(I2C_SDA_GET())
			temp = (temp<<1) | 0x01;
		else
			temp = (temp<<1);
						//	temp=(temp<<1)|sda;
		I2C_SCL_L();//scl=0;
		delay_i2c(1);//delay();			
	}
	return temp;
}
#endif //D_BK1086_CHIP
#if 1
void BEKEN_I2C_init(void)
{
    Set_Data_out();                 //SDA output
    Set_Clk_out();				//SCL output
    I2C_SCL_H();
    I2C_SDA_H();
}
void BEKEN_I2C_Start(void)
{
    BEKEN_I2C_init();
    delay_i2c(1);
    I2C_SDA_L();
    delay_i2c(1);
    I2C_SCL_L();
    delay_i2c(1);
    I2C_SDA_H();
}
void BEKEN_I2C_Stop(void)
{
    Set_Data_out();
    I2C_SDA_L();
    delay_i2c(1);
    I2C_SCL_H();
    delay_i2c(1);
    I2C_SDA_H();
    delay_i2c(1);
}
void BEKEN_I2C_ack(void)
{
    Set_Data_out();

    I2C_SCL_L();
    I2C_SDA_L();
    
    delay_i2c(1);
    I2C_SCL_H();
    
	delay_i2c(1);
    I2C_SCL_L();
} 
void BEKEN_I2C_nack(void)
{
    Set_Data_out();

    I2C_SCL_L();
   I2C_SDA_H();
   delay_i2c(1);

    I2C_SCL_H();
    delay_i2c(1);
    I2C_SCL_L();
}
UINT8 BEKEN_I2C_ReceiveACK(void)
{
    UINT32 ackflag;
   Set_Data_in();
    delay_i2c(1);
    I2C_SCL_H();
    delay_i2c(1);
    ackflag = (UINT8)I2C_SDA_GET();
    I2C_SCL_L();
    delay_i2c(1);
    return ackflag;
}
void BEKEN_I2C_sendbyte(UINT8 I2CSendData)
{
   
    UINT8  i;
    Set_Data_out();
   
	delay_i2c(1);
    for(i = 0;i < 8;i++)
    {
        if(I2CSendData & 0x80)
        {
            I2C_SDA_H();    //if high bit is 1,SDA= 1
        }
        else
           I2C_SDA_L();                               //else SDA=0

       	
	delay_i2c(1);
       I2C_SCL_H();
       	
	delay_i2c(1);
        I2CSendData <<= 1;                          //shift left 1 bit
        I2C_SCL_L();
    }                       
}
UINT8 BEKEN_I2C_readbyte(void)
{
    UINT8 i;
    UINT8 ucRDData = 0;                     //return value
    
    Set_Data_in();
    delay_i2c(1);
    for(i = 0;i < 8;i++)
    {
        I2C_SCL_H();
        ucRDData <<= 1;
        delay_i2c(1);
        if(I2C_SDA_GET())
            ucRDData|=0x01;
        I2C_SCL_L();
        delay_i2c(1);
    }
    return(ucRDData);
}
#endif

