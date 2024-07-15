#ifndef _SPI_INIT_H_
#define _SPI_INIT_H_

#include "stm32l0xx_ll_gpio.h"

#define EPD_SCL_GPIO_PORT		GPIOA
#define EPD_SCL_GPIO_PIN		LL_GPIO_PIN_0

#define EPD_SDA_GPIO_PORT		GPIOA
#define EPD_SDA_GPIO_PIN		LL_GPIO_PIN_1	

#define EPD_RES_GPIO_PORT		GPIOA
#define EPD_RES_GPIO_PIN		LL_GPIO_PIN_4	

#define EPD_DC_GPIO_PORT		GPIOA
#define EPD_DC_GPIO_PIN			LL_GPIO_PIN_5	

#define EPD_CS_GPIO_PORT		GPIOA
#define EPD_CS_GPIO_PIN			LL_GPIO_PIN_6	

#define EPD_BUSY_GPIO_PORT		GPIOA
#define EPD_BUSY_GPIO_PIN		LL_GPIO_PIN_7	

#define EPD_SCL_Clr() LL_GPIO_ResetOutputPin(EPD_SCL_GPIO_PORT,EPD_SCL_GPIO_PIN)
#define EPD_SCL_Set() LL_GPIO_SetOutputPin(EPD_SCL_GPIO_PORT,EPD_SCL_GPIO_PIN)

#define EPD_SDA_Clr() LL_GPIO_ResetOutputPin(EPD_SDA_GPIO_PORT,EPD_SDA_GPIO_PIN)
#define EPD_SDA_Set() LL_GPIO_SetOutputPin(EPD_SDA_GPIO_PORT,EPD_SDA_GPIO_PIN)

#define EPD_RES_Clr() LL_GPIO_ResetOutputPin(EPD_RES_GPIO_PORT,EPD_RES_GPIO_PIN)
#define EPD_RES_Set() LL_GPIO_SetOutputPin(EPD_RES_GPIO_PORT,EPD_RES_GPIO_PIN)

#define EPD_DC_Clr() LL_GPIO_ResetOutputPin(EPD_DC_GPIO_PORT,EPD_DC_GPIO_PIN)
#define EPD_DC_Set() LL_GPIO_SetOutputPin(EPD_DC_GPIO_PORT,EPD_DC_GPIO_PIN)

#define EPD_CS_Clr() LL_GPIO_ResetOutputPin(EPD_CS_GPIO_PORT,EPD_CS_GPIO_PIN)
#define EPD_CS_Set() LL_GPIO_SetOutputPin(EPD_CS_GPIO_PORT,EPD_CS_GPIO_PIN)

#define EPD_ReadBusy LL_GPIO_IsInputPinSet(EPD_BUSY_GPIO_PORT,EPD_BUSY_GPIO_PIN)


void EPD_GPIOInit(void);	//init the gpio for lcd
void EPD_WR_Bus(uint8_t dat);	//write byte
void EPD_WR_REG(uint8_t reg);	//write command
void EPD_WR_DATA8(uint8_t dat);	//write data

#endif



