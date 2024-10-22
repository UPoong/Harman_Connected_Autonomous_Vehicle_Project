/*
 * ultrasonic.c
 *
 *  Created on: Aug 1, 2024
 *      Author: jsmok
 */

#include "ultrasonic.h"
#include "tim.h"
#include "stm32f4xx_hal.h"

uint16_t echoTime1 = 0;
uint16_t echoTime2 = 0;
uint16_t echoTime3 = 0;

uint8_t captureFlag1 = 0;
uint8_t captureFlag2 = 0;
uint8_t captureFlag3 = 0;

uint32_t INC_Value_1_Ultrasonic1 = 0;
uint32_t INC_Value2_Ultrasonic1 = 0;

uint32_t INC_Value_1_Ultrasonic2 = 0;
uint32_t INC_Value2_Ultrasonic2 = 0;

uint32_t INC_Value_1_Ultrasonic3 = 0;
uint32_t INC_Value2_Ultrasonic3 = 0;


void UltrasonicInit(void)
{
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);		// ultrasonic_1
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);		// ultrasonic_2
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);		// ultrasonic_3
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	/////////////////////////////////////////////////////// ultrasonic_1
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (captureFlag1 == 0)
		{
			INC_Value_1_Ultrasonic1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
			captureFlag1 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (captureFlag1 == 1)
		{
			INC_Value2_Ultrasonic1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(&htim2, 0);

			if (INC_Value2_Ultrasonic1 > INC_Value_1_Ultrasonic1)
			{
				echoTime1 = INC_Value2_Ultrasonic1 - INC_Value_1_Ultrasonic1;
			}
			else if (INC_Value2_Ultrasonic1 < INC_Value_1_Ultrasonic1)
			{
				echoTime1 = (0xffff - INC_Value_1_Ultrasonic1) + INC_Value2_Ultrasonic1;
			}

			distance1 = echoTime1 / 58;
			//			//////////////
			//			if(distance > 200)
			//			{
			//				distance = 200;
			//			}

			captureFlag1 = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC1);
		}
	}


	////////////////////////////////////////////////// ultrasonic_2
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		if (captureFlag2 == 0)
		{
			INC_Value_1_Ultrasonic2 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
			captureFlag2 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (captureFlag2 == 1)
		{
			INC_Value2_Ultrasonic2 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
			__HAL_TIM_SET_COUNTER(&htim2, 0);

			if (INC_Value2_Ultrasonic2 > INC_Value_1_Ultrasonic2)
			{
				echoTime2 = INC_Value2_Ultrasonic2 - INC_Value_1_Ultrasonic2;
			}
			else if (INC_Value2_Ultrasonic2 < INC_Value_1_Ultrasonic2)
			{
				echoTime2 = (0xffff - INC_Value_1_Ultrasonic2) + INC_Value2_Ultrasonic2;
			}

			distance2 = echoTime2 / 58;
			//			//////////////
			//			if(distance > 200)
			//			{
			//				distance = 200;
			//			}

			captureFlag2 = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC2);
		}
	}

	////////////////////////////////////////////////////// ultrasonic_3
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	{
		if (captureFlag3 == 0)
		{
			INC_Value_1_Ultrasonic3 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_3);
			captureFlag3 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (captureFlag3 == 1)
		{
			INC_Value2_Ultrasonic3 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_3);
			__HAL_TIM_SET_COUNTER(&htim2, 0);

			if (INC_Value2_Ultrasonic3 > INC_Value_1_Ultrasonic3)
			{
				echoTime3 = INC_Value2_Ultrasonic3 - INC_Value_1_Ultrasonic3;
			}
			else if (INC_Value2_Ultrasonic3 < INC_Value_1_Ultrasonic3)
			{
				echoTime3 = (0xffff - INC_Value_1_Ultrasonic3) + INC_Value2_Ultrasonic3;
			}

			distance3 = echoTime3 / 58;
			//			//////////////
			//			if(distance > 200)
			//			{
			//				distance = 200;
			//			}

			captureFlag3 = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC3);
		}
	}
}


void HCSR04_read1(void)
{
	HAL_GPIO_WritePin(TRIG_PORT1, TRIG_PIN1, 1);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_PORT1, TRIG_PIN1, 0);

	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC1); // 초음파 센서용 타이머 채널
}


void HCSR04_read2(void)
{
	HAL_GPIO_WritePin(TRIG_PORT2, TRIG_PIN2, 1);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_PORT2, TRIG_PIN2, 0);

	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC2); // 초음파 센서용 타이머 채널
}

void HCSR04_read3(void)
{
	HAL_GPIO_WritePin(TRIG_PORT3, TRIG_PIN3, 1);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_PORT3, TRIG_PIN3, 0);

	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC3); // 초음파 센서용 타이머 채널
}
