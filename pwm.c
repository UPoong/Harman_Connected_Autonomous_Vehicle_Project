/*
 * pwm.c
 *
 *  Created on: Jul 31, 2024
 *      Author: jsmok
 */


#include "pwm.h"
#include "I2C_lcd.h"
#include "bluetooth.h"
#include "tim.h"
#include "stdlib.h"
#include "stm32f4xx_hal.h"

uint8_t mode;
uint8_t rxData;
extern uint8_t rxData1;

//uint8_t Forward_arr[] = "FOWARD\n";
//uint8_t Backward_arr[] = "BACKWARD\n";
//uint8_t Right_arr[] = "RIGHT\n";
//uint8_t Left_arr[] = "LEFT\n";
//uint8_t Pause_arr[] = "PAUSE\n";

uint16_t distance1 = 0;
uint16_t distance2 = 0;
uint16_t distance3 = 0;

//#define THRESHOLD_DISTANCE_SIDE		15
//#define THRESHOLD_DISTANCE_FRONT	45

void pwmInit(void)
{
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
}

void PWM_SetDutyCycle(uint32_t channel, uint16_t dutyCycle)
{
	__HAL_TIM_SET_COMPARE(&htim3, channel, dutyCycle);
}

/////// bluetooth drive
void Motor_Forward(void)
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 1000);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 300);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

void Motor_Backward(void)
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 700);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 700);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}

void Motor_Right(void)
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 500);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 500);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}


void Motor_Left(void)
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 400);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 400);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

void Motor_Stop(void)
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 700);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 700);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}


//// Auto drive
void Motor_Forward_slow(void)
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 300);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 500);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

void Motor_Right_slow(void)		// 숫자가 작을수록 빠름
{
	// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 300);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 300);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

void Motor_Left_slow(void)		// 숫자가 높을수록 빠름
{
// 앞쪽, 뒤쪽 우측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 900);  // PWM 채널 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

	// 앞쪽, 뒤쪽 좌측 모터
	PWM_SetDutyCycle(TIM_CHANNEL_2, 900);  // PWM 채널 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);  // 방향 제어 핀
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}



void BT_Drive(void)
{
	if(mode == 1)
	{
		//FORWARD
		if(rxData1 == 'F')
		{
			Motor_Forward();
//			move_cursor(1, 4);
//			lcd_string("FORWARD ");
		}

		//Right
		else if(rxData1 == 'R')
		{
			Motor_Right();
//			move_cursor(1, 4);
//			lcd_string("RIGHT    ");
		}

		//LEFT
		else if(rxData1 == 'L')
		{
			Motor_Left();
//			move_cursor(1, 4);
//			lcd_string("LEFT    ");
		}

		//BACKWARD
		else if(rxData1 == 'S')
		{
			Motor_Backward();
//			move_cursor(1, 4);
//			lcd_string("BACKWARD");
		}

		//PAUSE
		else //if(rxData1 == '0')
		{
			Motor_Stop();
//			move_cursor(1, 4);
//			lcd_string("STOP    ");
		}
	}
}


void Auto_Drive(void)
{
	if(mode == 2)
	{
		if(distance2 >= 40)		// 전방에 장애물이 없다면
		{
			if((distance1 >= 15) && (distance3 >= 15))
			{
				Motor_Forward();
			}

			else if(distance1 < 25)
			{
				Motor_Right_slow();
			}

			else if(distance3 < 75)		// distance3 < 20
			{
				Motor_Left_slow();
			}
		}

		else if((25 <= distance2) && (distance2 < 40))
		{
			if((distance1 >= 15) && (distance3 >= 15))
			{
				Motor_Forward_slow();
			}

			else if(distance1 < 25)
			{
				Motor_Right_slow();
			}

			else if(distance3 < 75)
			{
				Motor_Left_slow();
			}
		}


		else if(distance2 < 25)		// 전방에 장애물이 있다면
		{
			if((distance1 < distance3) || (distance1 < 25))
			{
				Motor_Right_slow();
			}
			else if((distance1 > distance3) || (distance3 < 75))
			{
				Motor_Left_slow();
			}
		}

//		else if(distance2 < 10)		// 전방에 장애물이 너무 가까이 있다면 후진 후 멈춤
//		{
//			Motor_Backward();
//
//			if(distance2 > 10)
//			{
//				Motor_Stop();
//			}
//		}
	}
}






