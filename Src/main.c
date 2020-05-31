/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "functions.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void showLED(uint8_t *pos);
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

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
	LED_debug_init();
	MX_DMA_Init();
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();
//  MX_TIM3_Init();
//  MX_TIM8_Init();
//  MX_I2C2_Init();
//  MX_USART1_UART_Init();
//  MX_USART3_UART_Init();
//  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
	// update 100 LED take ~0.00321s <=> 3.21ms
	// update 50  LED take ~0.00168s <=> 1.68ms
	LED_data temp;
	temp.blue = 50;
	temp.red = 50;
	temp.green = 50;
	led_set_color_all(temp);
  led_update(1);
	for (uint32_t i=0; i < 20000000; i++);
	temp.blue = 0;
	temp.red = 0;
	temp.green = 0;
	led_set_color_all(temp);
  led_update(1);
	temp.blue = 15;
	temp.red = 15;
	temp.green = 0;
  /* USER CODE END 2 */
	
	testFunction();
	uint8_t possition = 0;
	uint8_t *pos = &possition;
  /* Infinite loop */
	
  /* USER CODE BEGIN WHILE */
  while(1)
  {
		// USER CODE END WHILE
    /*
		for (int i=0; i<LED_CNT; i++)
		{
			led_set_color(i, COLOR_RED);
		}
		led_update(1);
		delay(30);
		*/
    // USER CODE BEGIN 3
		showLED(pos);
  }
  /* USER CODE END 3 */
}

void showLED(uint8_t *pos)
{
	if (StartPos(*pos))	{
		loadDataToLED(*pos);
		led_update(1);
		(*pos)++;
		if (*pos == 119)
			*pos = 0;
	}
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
