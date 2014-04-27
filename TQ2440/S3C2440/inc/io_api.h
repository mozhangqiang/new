#ifndef _IO_API_H_
#define _IO_API_H_
typedef enum
{
	PIOA_INDEX,
	PIOB_INDEX,
	PIOC_INDEX,
	PIOD_INDEX,
	PIOE_INDEX,
	PIOF_INDEX,
	PIOG_INDEX,
	PIOH_INDEX,
	PIOJ_INDEX,

	NUM_OF_PIO
}PIO_INDEX;

typedef enum
{
	LED1,
	LED2,
	LED3,
	LED4,
	I2C_CLK,
	I2C_DAT,
	
	NUM_OF_GPIO
}GPIO;

static struct
{
	BYTE   bIndex;
	BYTE uiGPIOBit;
}GPIO_LUT[NUM_OF_GPIO] = {
							{PIOB_INDEX,5},	//LED1
							{PIOB_INDEX,6},	//LED1
							{PIOB_INDEX,7},	//LED1
							{PIOB_INDEX,8},	//LED1
							{PIOE_INDEX,14},	//I2C_CLK
							{PIOE_INDEX,15},	//I2C_DAT
						 };
#endif //_IO_API_H_
