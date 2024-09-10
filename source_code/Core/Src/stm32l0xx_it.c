/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"
#include "log.h"
#include "i2c_slave.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable Interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles I2C1 event global interrupt / I2C1 wake-up interrupt through EXTI line 23.
  */
volatile uint8_t i2c_data_index = 0;
extern struct I2c_Slave_Pack i2c_slave_pack;
extern struct Lcd_Data_Pack lcd_data_pack; 
void I2C1_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_IRQn 0 */
  if(LL_I2C_IsActiveFlag_RXNE(I2C1)){
	  i2c_slave_pack.raw_data_len = 0;
	  if(i2c_data_index < sizeof(i2c_slave_pack.raw_data)) {
		  i2c_slave_pack.raw_data[i2c_data_index++] = LL_I2C_ReceiveData8(I2C1);
	  }
  }

  if(LL_I2C_IsActiveFlag_STOP(I2C1)) {
	  LL_I2C_ClearFlag_STOP(I2C1);
	  i2c_slave_pack.raw_data_len = i2c_data_index;
	  i2c_data_index = 0;
  }

  if(LL_I2C_IsActiveFlag_ADDR(I2C1)) {
          LL_I2C_ClearFlag_ADDR(I2C1);
          LL_I2C_EnableIT_TX(I2C1);
  }

  //transmit a byte to master if they send a read command
  if(LL_I2C_IsActiveFlag_TXIS(I2C1))
        LL_I2C_TransmitData8(I2C1, 0x00);

  /* USER CODE END I2C1_IRQn 0 */

  /* USER CODE BEGIN I2C1_IRQn 1 */

  /* USER CODE END I2C1_IRQn 1 */
}

/* USER CODE BEGIN 1 */
uint32_t key_cnt = 0;
void EXTI4_15_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14) != RESET)
    {
	key_cnt++;
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
    }

    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_9) != RESET)
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_9);
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
#include "log.h"
uint8_t uart_data[20];
uint8_t uart_index = 0;
uint8_t uart_data_ready = 0;
uint8_t temp;
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  if(LL_USART_IsActiveFlag_RXNE(USART2)) {
          temp = LL_USART_ReceiveData8(USART2);
          uart_data[uart_index++] = temp;
          if(temp == 0x0d) {
        	  uart_data_ready = 1;
        	  uart_index = 0;
          }
  }
  if(LL_USART_IsActiveFlag_WKUP(USART2) && LL_USART_IsEnabledIT_WKUP(USART2)) {
	  /* Disable the UART Wake UP from stop mode Interrupt */
          LL_USART_DisableIT_WKUP(USART2);

	  /* WUF flag clearing */
          LL_USART_ClearFlag_WKUP(USART2);
  }
  /* USER CODE END USART2_IRQn 0 */
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
