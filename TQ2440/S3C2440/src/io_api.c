#include "config.h"

void Set_GPIO_To_Input(GPIO gpio)
{
	BYTE gpio_bit;
	PIO_INDEX pio_index;

	gpio_bit = GPIO_LUT[gpio].uiGPIOBit;
	pio_index = GPIO_LUT[gpio].bIndex;

	switch(pio_index)
	{
		case PIOA_INDEX:
			rGPACON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOB_INDEX:
			rGPBCON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOC_INDEX:
			rGPCCON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOD_INDEX:
			rGPDCON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOE_INDEX:
			rGPECON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOF_INDEX:
			rGPFCON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOG_INDEX:
			rGPGCON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOH_INDEX:
			rGPHCON &= ~(0X03<<(2*gpio_bit));
			break;
		case PIOJ_INDEX:
			rGPJCON &= ~(0X03<<(2*gpio_bit));
			break;
		default:break;
	}
}

void Set_GPIO_To_Output(GPIO gpio)
{
	BYTE gpio_bit;
	PIO_INDEX pio_index;

	gpio_bit = GPIO_LUT[gpio].uiGPIOBit;
	pio_index = GPIO_LUT[gpio].bIndex;

	switch(pio_index)
	{
		case PIOA_INDEX:
			rGPACON &= ~(0X03<<(2*gpio_bit));
			rGPACON |= 0X01<<(2*gpio_bit); 
			break;
		case PIOB_INDEX:
			rGPBCON &= ~(0X03<<(2*gpio_bit));
			rGPBCON |= 0X01<<(2*gpio_bit);
			break;
		case PIOC_INDEX:
			rGPCCON &= ~(0X03<<(2*gpio_bit));
			rGPCCON |= 0X01<<(2*gpio_bit);
			break;
		case PIOD_INDEX:
			rGPDCON &= ~(0X03<<(2*gpio_bit));
			rGPDCON |= 0X01<<(2*gpio_bit);
			break;
		case PIOE_INDEX:
			rGPECON &= ~(0X03<<(2*gpio_bit));
			rGPECON |= 0X01<<(2*gpio_bit);
			break;
		case PIOF_INDEX:
			rGPFCON &= ~(0X03<<(2*gpio_bit));
			rGPFCON |= 0X01<<(2*gpio_bit);
			break;
		case PIOG_INDEX:
			rGPGCON &= ~(0X03<<(2*gpio_bit));
			rGPGCON |= 0X01<<(2*gpio_bit);
			break;
		case PIOH_INDEX:
			rGPHCON &= ~(0X03<<(2*gpio_bit));
			rGPHCON |= 0X01<<(2*gpio_bit);
			break;
		case PIOJ_INDEX:
			rGPJCON &= ~(0X03<<(2*gpio_bit));
			rGPJCON |= 0X01<<(2*gpio_bit);
			break;
		default:break;
	}
}
void SetGPIO(GPIO gpio)
{
	BYTE gpio_bit;
	PIO_INDEX pio_index;

	gpio_bit = GPIO_LUT[gpio].uiGPIOBit;
	pio_index = GPIO_LUT[gpio].bIndex;

	Set_GPIO_To_Output(gpio);
	switch(pio_index)
	{
		case PIOA_INDEX:
			rGPADAT |= 1<<gpio_bit;
			break;
		case PIOB_INDEX:
			rGPBDAT |= 1<<gpio_bit;
			break;
		case PIOC_INDEX:
			rGPCDAT |= 1<<gpio_bit;
			break;
		case PIOD_INDEX:
			rGPDDAT |= 1<<gpio_bit;
			break;
		case PIOE_INDEX:
			rGPEDAT |= 1<<gpio_bit;
			break;
		case PIOF_INDEX:
			rGPFDAT |= 1<<gpio_bit;
			break;
		case PIOG_INDEX:
			rGPGDAT |= 1<<gpio_bit;
			break;
		case PIOH_INDEX:
			rGPHDAT |= 1<<gpio_bit;
			break;
		case PIOJ_INDEX:
			rGPJDAT |= 1<<gpio_bit;
			break;
		default:break;	
	}
}

void ClearGPIO(GPIO gpio)
{
	BYTE gpio_bit;
	PIO_INDEX pio_index;

	gpio_bit = GPIO_LUT[gpio].uiGPIOBit;
	pio_index = GPIO_LUT[gpio].bIndex;

	Set_GPIO_To_Output(gpio);
	switch(pio_index)
	{
		case PIOA_INDEX:
			rGPADAT &= ~(1<<gpio_bit);
			break;
		case PIOB_INDEX:
			rGPBDAT &= ~(1<<gpio_bit);
			break;
		case PIOC_INDEX:
			rGPCDAT &= ~(1<<gpio_bit);
			break;
		case PIOD_INDEX:
			rGPDDAT &= ~(1<<gpio_bit);
			break;
		case PIOE_INDEX:
			rGPEDAT &= ~(1<<gpio_bit);
			break;
		case PIOF_INDEX:
			rGPFDAT &= ~(1<<gpio_bit);
			break;
		case PIOG_INDEX:
			rGPGDAT &= ~(1<<gpio_bit);
			break;
		case PIOH_INDEX:
			rGPHDAT &= ~(1<<gpio_bit);
			break;
		case PIOJ_INDEX:
			rGPJDAT &= ~(1<<gpio_bit);
			break;
		default:break;	
	}
}

UINT16 GetGPIO(GPIO gpio)
{
	BYTE gpio_bit;
	PIO_INDEX pio_index;

	gpio_bit = GPIO_LUT[gpio].uiGPIOBit;
	pio_index = GPIO_LUT[gpio].bIndex;

	Set_GPIO_To_Input(gpio);
	switch(pio_index)
	{
		case PIOA_INDEX:
			return ((rGPADAT & (1<<gpio_bit))==0?0:1);
		case PIOB_INDEX:
			return ((rGPBDAT & (1<<gpio_bit))==0?0:1);
		case PIOC_INDEX:
			return ((rGPCDAT & (1<<gpio_bit))==0?0:1);
		case PIOD_INDEX:
			return ((rGPDDAT & (1<<gpio_bit))==0?0:1);
		case PIOE_INDEX:
			return ((rGPEDAT & (1<<gpio_bit))==0?0:1);
		case PIOF_INDEX:
			return ((rGPFDAT & (1<<gpio_bit))==0?0:1);
		case PIOG_INDEX:
			return ((rGPGDAT & (1<<gpio_bit))==0?0:1);
		case PIOH_INDEX:
			return ((rGPHDAT & (1<<gpio_bit))==0?0:1);
		case PIOJ_INDEX:
			return ((rGPJDAT & (1<<gpio_bit))==0?0:1);
		default:break;
	}
	
}
void PollUpGPIO(GPIO gpio,BYTE up)
{
	BYTE gpio_bit;
	PIO_INDEX pio_index;

	gpio_bit = GPIO_LUT[gpio].uiGPIOBit;
	pio_index = GPIO_LUT[gpio].bIndex;
	
	switch(pio_index)
	{
		case PIOB_INDEX:
			if(up)
				rGPBUP &= ~(1<<gpio_bit); 
			else
				rGPBUP |= 1<<gpio_bit;
			break;
		case PIOC_INDEX:
			if(up)
				rGPCUP &= ~(1<<gpio_bit); 
			else
				rGPCUP |= 1<<gpio_bit;
			break;
		case PIOD_INDEX:
			if(up)
				rGPDUP &= ~(1<<gpio_bit); 
			else
				rGPDUP |= 1<<gpio_bit;
			break;
		case PIOE_INDEX:
			if(up)
				rGPEUP &= ~(1<<gpio_bit); 
			else
				rGPEUP |= 1<<gpio_bit;
			break;
		case PIOF_INDEX:
			if(up)
				rGPFUP &= ~(1<<gpio_bit); 
			else
				rGPFUP |= 1<<gpio_bit;
			break;
		case PIOG_INDEX:
			if(up)
				rGPGUP &= ~(1<<gpio_bit); 
			else
				rGPGUP |= 1<<gpio_bit;
			break;
		case PIOH_INDEX:
			if(up)
				rGPHUP &= ~(1<<gpio_bit); 
			else
				rGPHUP |= 1<<gpio_bit;
			break;
		case PIOJ_INDEX:
			if(up)
				rGPJUP &= ~(1<<gpio_bit); 
			else
				rGPJUP |= 1<<gpio_bit;
			break;
		default:break;
	}	
}