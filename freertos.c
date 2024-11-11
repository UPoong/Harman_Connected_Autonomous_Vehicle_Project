/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pwm.h"
#include "delay.h"
#include "ultrasonic.h"
#include "I2C_lcd.h"
#include "top.h"
#include "bluetooth.h"

#include "usart.h"
#include "gpio.h"

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
/* USER CODE BEGIN Variables */
extern uint8_t mode;
extern uint8_t rxData;
extern uint8_t rxData1;

//extern uint16_t distance1 = 0;
//extern uint16_t distance2 = 0;
//extern uint16_t distance3 = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */


/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	// PWM motor
//	  HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
	  HAL_UART_Receive_IT(&huart6, &rxData1, sizeof(rxData1));

	  pwmInit();

	  //ULTRASONIC
	  UltrasonicInit();

	  HAL_TIM_Base_Start(&htim10);	// for delay func
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);		// for ultrasonic
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);		// for ultrasonic
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);		// for ultrasonic

	  // LCD
//	  i2c_lcd_init();
//
//	  move_cursor(0, 4);
//	  lcd_string("WELCOME");
//
//	  move_cursor(1, 2);
//	  lcd_string("CHOOSE MODE");

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

  	osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
  	// bluetooth mode
  	if(rxData1 == 'B')
  	{
//  		move_cursor(0, 1);
//  		lcd_string("BLUETOOTH MODE");
//  		HAL_Delay(10);
//  		move_cursor(1, 1);
//  		lcd_string("                    ");
  		mode = 1;
  	}
  	// Auto mode
  	else if(rxData1 == 'A')
  	{
//  		move_cursor(0, 3);
//  		//lcd_command(CLEAR_DISPLAY);
//  		HAL_Delay(10);
//  		lcd_string("AUTO MODE  ");
//  		HAL_Delay(10);
//  		move_cursor(1, 1);
//  		lcd_string("                ");
  		mode = 2;
  	}

  	//reset
  	else if(rxData1 == 'P')
  	{
//  		move_cursor(1, 4);
//  		lcd_string("RESETTING");
  		HAL_Delay(1000);

  		// board reset
  		NVIC_SystemReset();
  	}
  	Auto_Drive();
  	BT_Drive();
  	osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
  	HCSR04_read1();
//  	  	if(distance1 <= 15)
//  	  	{
//  	  		Motor_Stop();
//  	  		move_cursor(1, 4);
//  	  		lcd_string("!!STOP!!");
//  	  	}
  	HAL_Delay(10);

  	HCSR04_read2();
//  	  	if(distance2 <= 15)
//  	  	{
//  	  		Motor_Stop();
//  	  		move_cursor(1, 4);
//  	  		lcd_string("!!STOP!!");
//  	  	}
  	HAL_Delay(10);

  	HCSR04_read3();
//  	  	if(distance3 <= 15)
//  	  	{
//  	  		Motor_Stop();
//  	  		move_cursor(1, 4);
//  	  		lcd_string("!!STOP!!");
//  	  	}
  	HAL_Delay(10);

  	osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

