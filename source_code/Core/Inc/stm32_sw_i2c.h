/*
  stm32_sw_i2c.h - Library for implementing I2C in SW on any GPIO on STM32 MCU.
  Created by Mawaba Pascal Dao, Dec 2, 2020.
  Released into the public domain.
*/
#ifndef __STM32_SW_I2C_H
#define __STM32_SW_I2C_H

#include "main.h"

#define SW_I2C_SDA_GPIO_Port GPIOA
#define SW_I2C_SDA_Pin       LL_GPIO_PIN_13
#define SW_I2C_SCL_GPIO_Port GPIOA
#define SW_I2C_SCL_Pin       LL_GPIO_PIN_14
#define DWT_Delay_us         LL_mDelay

#define I2C_CLEAR_SDA LL_GPIO_ResetOutputPin(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin);
#define I2C_SET_SDA   LL_GPIO_SetOutputPin(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin);
#define I2C_READ_SDA LL_GPIO_IsInputPinSet(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin)
#define I2C_CLEAR_SCL LL_GPIO_ResetOutputPin(SW_I2C_SCL_GPIO_Port, SW_I2C_SCL_Pin);
#define I2C_SET_SCL   LL_GPIO_SetOutputPin(SW_I2C_SCL_GPIO_Port, SW_I2C_SCL_Pin);
#define I2C_DELAY DWT_Delay_us(1); // 1 microsecond delay

void I2C_init(void);

void I2C_start_cond(void);

void I2C_stop_cond(void);

void I2C_write_bit(uint8_t b);

uint8_t I2C_read_SDA(void);

// Reading a bit in I2C:
uint8_t I2C_read_bit(void);

_Bool I2C_write_byte(uint8_t B, _Bool start, _Bool stop);

uint8_t I2C_read_byte(_Bool ack, _Bool stop);

_Bool I2C_send_byte(uint8_t address, uint8_t data);

uint8_t I2C_receive_byte(uint8_t address);

_Bool I2C_send_byte_data(uint8_t address, uint8_t reg, uint8_t data);

uint8_t I2C_receive_byte_data(uint8_t address, uint8_t reg);

_Bool I2C_transmit(uint8_t address, uint8_t data[], uint8_t size);

_Bool I2C_receive(uint8_t address, uint8_t reg[], uint8_t *data, uint8_t reg_size, uint8_t size);

#endif /*__STM32_SW_I2C_H */
