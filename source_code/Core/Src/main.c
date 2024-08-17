/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "log.h"
#include "EPD_GUI.h"
#include "Pic.h"
#include "i2c_slave.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t ImageBW[2888];

struct I2c_Slave_Pack i2c_slave_pack;
struct Lcd_Data_Pack lcd_data_pack;

uint32_t last_key_cnt = 0;
extern uint32_t key_cnt;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  Log_Init();
  Log_Printf("xiaomi temp humi start\n");
  Paint_NewImage(ImageBW,EPD_W,EPD_H,0,WHITE);
  Paint_Clear(WHITE);
  Log_Printf("lcd init ok\n");
  EPD_FastMode1Init();
  EPD_Display_Clear();
  EPD_FastUpdate();
  EPD_Clear_R26H();

  Log_Printf("lcd display pic ok\n");
  uint32_t input_data = 0;
  float float_time=12.11;
  float float_num=28.9;
  uint8_t dat = 0;
  uint32_t time;
  uint32_t number = 79;

  NVIC_EnableIRQ(EXTI4_15_IRQn);
  NVIC_SetPriority(EXTI4_15_IRQn, 1);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    LL_mDelay(1000);
    Log_Printf("loop test %d\n", key_cnt);
    if(i2c_slave_pack.raw_data_len) {
	    Log_Printf("lcd data update\n");
        //    for(uint8_t i = 0;i < i2c_slave_pack.raw_data_len; i++)
        //	    Log_Printf("0x%x\n", i2c_slave_pack.raw_data[i]);
            i2c_slave_pack.raw_data_len = 0;
            Update_Lcd_Data(&i2c_slave_pack, &lcd_data_pack);
            Log_Printf("temp:%d\n", (uint16_t)(lcd_data_pack.temp*10));
            Log_Printf("humi:%d\n", lcd_data_pack.humi);
            Log_Printf("smile:%d\n", lcd_data_pack.smile);
            Log_Printf("ble:%d\n", lcd_data_pack.ble);
            Log_Printf("format:%d\n", lcd_data_pack.temp_format);
            Log_Printf("battery:%d\n", lcd_data_pack.battery);
	    EPD_ShowNum(32, 0, lcd_data_pack.smile, 1, 24, BLACK);
	    if(lcd_data_pack.ble)
		    EPD_ShowPicture(100, 0, 24, 24, gImage_bt_icon, BLACK);
    }
    if(last_key_cnt != key_cnt%3) {
	Paint_Clear(WHITE);
    	if(key_cnt%3 == 0) {
    		float_time = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC)) + __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC)) * 0.01;
    		EPD_ShowWatch(8,56,float_time, 4, 2, 48,BLACK);
    		float_num = lcd_data_pack.temp;
    		EPD_ShowFloatNum1(8,106, float_num, 3, 1, 24,BLACK);
    		number = lcd_data_pack.humi;
    		EPD_ShowNum(96,106, number, 2, 24,BLACK);
    	} else if(key_cnt%3 == 1) {
    		float_time = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC)) + __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC)) * 0.01;
    		EPD_ShowWatch(8,106,float_time, 4, 2, 24,BLACK);
    		float_num = lcd_data_pack.temp;
    		EPD_ShowFloatNum1(8,56, float_num, 3, 1, 48,BLACK);
    		number = lcd_data_pack.humi;
    		EPD_ShowNum(96,106, number, 2, 24,BLACK);
    	} else {
    		float_time = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC)) + __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC)) * 0.01;
    		EPD_ShowWatch(8,56,float_time, 4, 2, 24,BLACK);
    		float_num = lcd_data_pack.temp;
    		EPD_ShowFloatNum1(96,106, float_num, 3, 1, 24,BLACK);
    		number = lcd_data_pack.humi;
    		EPD_ShowNum(8,56, number, 2, 48,BLACK);
    	}
    	EPD_Init();
    	EPD_FastMode1Init();
    	EPD_Display_Clear();
    	EPD_FastUpdate();
    	EPD_Clear_R26H();
	last_key_cnt = key_cnt%3;
    }
    EPD_Display(ImageBW);
    EPD_PartUpdate();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_PWR_EnableBkUpAccess();
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
  LL_RCC_LSE_Enable();

   /* Wait till LSE is ready */
  while(LL_RCC_LSE_IsReady() != 1)
  {

  }
  if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
  }
  LL_RCC_EnableRTC();
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_3, LL_RCC_PLL_DIV_2);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }

  LL_Init1msTick(24000000);

  LL_SetSystemCoreClock(24000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
