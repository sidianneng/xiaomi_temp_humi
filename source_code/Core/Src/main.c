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

extern uint8_t uart_data[], uart_data_ready;

static LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
static LL_RTC_DateTypeDef RTC_DateStruct = {0};
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
  LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_HSI);
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
 
  //main page one
  //EPD_ShowPicture(10, 14, 24, 24, gImage_2424_bat, BLACK);
  //EPD_ShowPicture(44, 10, 64, 32, gImage_6432_smile_happy, BLACK);
  //EPD_ShowPicture(120, 14, 24, 24, gImage_2424_bt, BLACK);
  //EPD_ShowString(0,44,"12",64,BLACK);
  //EPD_ShowPicture(64, 44, 24, 64, gImage_2464_colon, BLACK);
  //EPD_ShowString(88 ,44,"33",64,BLACK);
  //EPD_ShowString(20 ,114,"28.9",24,BLACK);
  //EPD_ShowPicture(68, 114, 12, 24, gImage_1224_c, BLACK);
  //EPD_ShowString(100 ,114,"78%",24,BLACK);

  //main page two
  //EPD_ShowPicture(10, 14, 24, 24, gImage_2424_bat, BLACK);
  //EPD_ShowPicture(44, 10, 64, 32, gImage_6432_smile_happy, BLACK);
  //EPD_ShowPicture(120, 14, 24, 24, gImage_2424_bt, BLACK);
  //EPD_ShowString(0 ,44,"28.9", 64,BLACK);
  //EPD_ShowPicture(128, 44, 12, 24, gImage_1224_c, BLACK);
  //EPD_ShowString(10,114,"12:33",24,BLACK);
  //EPD_ShowString(100 ,114,"78%",24,BLACK);

  //main page three
  //EPD_ShowPicture(10, 14, 24, 24, gImage_2424_bat, BLACK);
  //EPD_ShowPicture(44, 10, 64, 32, gImage_6432_smile_happy, BLACK);
  //EPD_ShowPicture(120, 14, 24, 24, gImage_2424_bt, BLACK);
  //EPD_ShowString(32 ,44,"78%",64,BLACK);
  //EPD_ShowString(10,114,"12:33",24,BLACK);
  //EPD_ShowString(88 ,114,"28.9",24,BLACK);
  //EPD_ShowPicture(140, 114, 12, 24, gImage_1224_c, BLACK);

  uint8_t time_hour, time_min;
  uint8_t last_time_hour, last_time_min;
  float temp;
  float last_temp;
  int8_t humi;
  int8_t last_humi;
  uint32_t rev_id = 0;
  //bit0:i2c receive data
  //bit1:rtc time change 
  //bit2:key input
  uint8_t lcd_update_flag = 0x80;

  //LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
  //LL_mDelay(50);
  //LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
  /* USER CODE BEGIN 2 */
  Log_Printf("rev:0x%x\n", LL_DBGMCU_GetRevisionID());
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //LL_mDelay(1000);
    Log_Printf("loop test %d\n", key_cnt);
    //Log_Printf("enter sleep\n");
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_14);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_9);
    PrepareUSARTToStopMode();
    EnterSleepMode();
    //Log_Printf("wakeup from sleep\n");
    if(i2c_slave_pack.raw_data_len) {
            i2c_slave_pack.raw_data_len = 0;
            Update_Lcd_Data(&i2c_slave_pack, &lcd_data_pack);
            Log_Printf("temp:%d\n", (uint16_t)(lcd_data_pack.temp*10));
            Log_Printf("humi:%d\n", lcd_data_pack.humi);
            Log_Printf("smile:%d\n", lcd_data_pack.smile);
            Log_Printf("ble:%d\n", lcd_data_pack.ble);
            Log_Printf("format:%d\n", lcd_data_pack.temp_format);
            Log_Printf("battery:%d\n", lcd_data_pack.battery);
            if(lcd_data_pack.ble)
                EPD_ShowPicture(120, 14, 24, 24, gImage_2424_bt, BLACK);
            if(lcd_data_pack.smile == 1)
        	EPD_ShowPicture(44, 10, 64, 32, gImage_6432_smile_happy, BLACK);
            else if(lcd_data_pack.smile == 2)
        	EPD_ShowPicture(44, 10, 64, 32, gImage_6432_smile_sad, BLACK);
            temp = lcd_data_pack.temp;
            humi = lcd_data_pack.humi;
	    lcd_update_flag |= (0x01 << 0);
    }

    time_hour = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC));
    time_min  = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC));
    if(time_hour != last_time_hour || time_min != last_time_min)
	    lcd_update_flag |= (0x01 << 1);
    last_time_hour = time_hour;
    last_time_min  = time_min;

    if(last_key_cnt != key_cnt%3 || (lcd_update_flag & 0x01)) {
    	if(key_cnt%3 == 0) {
                EPD_ShowNum(0, 44, time_hour, 2, 64, BLACK);
                EPD_ShowPicture(64, 44, 24, 64, gImage_2464_colon, BLACK);
                EPD_ShowNum(88, 44, time_min, 2, 64, BLACK);
                EPD_ShowFloatNum1(20, 114, temp, 3, 1, 24, BLACK);
                EPD_ShowPicture(68, 114, 12, 24, gImage_1224_c, BLACK);
                EPD_ShowNum(100 ,114, humi, 2, 24, BLACK);
        	EPD_ShowChar(124, 114, '%', 24, BLACK);
    	} else if(key_cnt%3 == 1) {
                EPD_ShowFloatNum1(0 ,44, temp, 3, 1, 64, BLACK);
                EPD_ShowPicture(128, 44, 12, 24, gImage_1224_c, BLACK);
                EPD_ShowNum(10, 114, time_hour, 2, 24, BLACK);
        	EPD_ShowChar(34, 114, ':', 24, BLACK);
                EPD_ShowNum(46, 114, time_min, 2, 24, BLACK);
                EPD_ShowNum(100, 114, humi, 2, 24, BLACK);
        	EPD_ShowChar(124, 114, '%', 24, BLACK);
    	} else {
                EPD_ShowNum(32, 44, humi, 2, 64, BLACK);
        	EPD_ShowChar(96, 44, '%', 64, BLACK);
                EPD_ShowNum(10, 114, time_hour, 2, 24, BLACK);
        	EPD_ShowChar(34, 114, ':', 24, BLACK);
                EPD_ShowNum(46, 114, time_min, 2, 24, BLACK);
                EPD_ShowFloatNum1(88, 114, temp, 3, 1, 24, BLACK);
                EPD_ShowPicture(140, 114, 12, 24, gImage_1224_c, BLACK);
    	}
	lcd_update_flag |= (0x01 << 2);
    }
    last_key_cnt = key_cnt%3;

    if(uart_data_ready) {
            Log_Printf("u:%s\n", uart_data);
            RTC_TimeStruct.Hours =   (uart_data[8] - 0x30) * 0x10 + (uart_data[9] - 0x30);
            RTC_TimeStruct.Minutes = (uart_data[10] - 0x30) * 0x10 + (uart_data[11] - 0x30);
            RTC_TimeStruct.Seconds = (uart_data[12] - 0x30) * 0x10 + (uart_data[13] - 0x30);
            LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
            RTC_DateStruct.Month = (uart_data[4] - 0x30) * 0x10 + (uart_data[5] - 0x30);
            RTC_DateStruct.Day = (uart_data[6] - 0x30) * 0x10 + (uart_data[7] - 0x30);
            RTC_DateStruct.Year =(uart_data[2] - 0x30) * 0x10 + (uart_data[3] - 0x30) ;
            LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
            uart_data_ready = 0;
    }

    if(lcd_update_flag) {
        EPD_Display(ImageBW);
        EPD_PartUpdate();
    }

    lcd_update_flag = 0x00;

    //Log_Printf("rtc year:%d\n", __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetYear(RTC)));
    //Log_Printf("rtc month:%d\n", __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetMonth(RTC)));
    //Log_Printf("rtc weekday:%d\n", __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetWeekDay(RTC)));
    //Log_Printf("rtc hour:%d\n", __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC)));
    //Log_Printf("rtc min:%d\n", __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC)));
    //Log_Printf("rtc sec:%d\n", __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetSecond(RTC)));
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
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
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }

  LL_Init1msTick(16000000);

  LL_SetSystemCoreClock(16000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_HSI);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
}

/* USER CODE BEGIN 4 */
void EnterSleepMode(void)
{
  LL_PWR_ClearFlag_WU();
  LL_PWR_SetRegulModeLP(LL_PWR_REGU_LPMODES_LOW_POWER);
  /* Set Stop 0 mode when CPU enters deepsleep */
  LL_PWR_SetPowerMode(LL_PWR_MODE_STOP);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For Interrupt */
  __WFI();
}
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
