#include "SPI_Init.h"

void EPD_GPIOInit(void)
{
}


void EPD_WR_Bus(uint8_t dat)
{
	uint8_t i;
	EPD_CS_Clr();
	for(i=0;i<8;i++)
	{
		EPD_SCL_Clr();
		if(dat&0x80)
		{
			EPD_SDA_Set();
		}
		else
		{
			EPD_SDA_Clr();
		}
		EPD_SCL_Set();
		dat<<=1;
	}
	EPD_CS_Set();	
}

void EPD_WR_REG(uint8_t reg)
{
	EPD_DC_Clr();
	EPD_WR_Bus(reg);
	EPD_DC_Set();
}
void EPD_WR_DATA8(uint8_t dat)
{
	EPD_DC_Set();
	EPD_WR_Bus(dat);
	EPD_DC_Set();
}





