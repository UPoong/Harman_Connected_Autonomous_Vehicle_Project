/*
 * bluetooth.c
 *
 *  Created on: Oct 11, 2024
 *      Author: jsmok
 */


#include "bluetooth.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

uint8_t rxData1;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart )
{
	HAL_UART_Receive_IT(&huart6, &rxData1, sizeof(rxData1));
}

//void UART6INIT(void)
//{
//	HAL_UART_Receive_IT(&huart6, &rxData1, sizeof(rxData1));
//}


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart )
//{
//	if(huart->Instance == USART2)
//	{
//		//HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
//		HAL_UART_Transmit_IT(&huart6, &rxData, sizeof(rxData));
//	}
//
//	if(huart->Instance == USART6)
//	{
//		HAL_UART_Receive_IT(&huart6, &rxData1, sizeof(rxData1));
//		//FORWARD
//		if(rxData1 == 'F')
//		{
//			HAL_UART_Transmit_IT(&huart2, Forward_arr, sizeof(Forward_arr));
//			Motor_Forward();
//			move_cursor(1, 4);
//			lcd_string("FORWARD ");
//		}
//
//		//RIGHT
//		else if(rxData1 == 'R')
//		{
//			HAL_UART_Transmit_IT(&huart2, Right_arr, sizeof(Right_arr));
//			Motor_Right();
//			move_cursor(1, 4);
//			lcd_string("RIGHT    ");
//		}
//
//		//LEFT
//		else if(rxData1 == 'L')
//		{
//			HAL_UART_Transmit_IT(&huart2, Left_arr, sizeof(Left_arr));
//			Motor_Left();
//			move_cursor(1, 4);
//			lcd_string("LEFT    ");
//		}
//
//		//BACKWARD
//		else if(rxData1 == 'B')
//		{
//			HAL_UART_Transmit_IT(&huart2, Backward_arr, sizeof(Backward_arr));
//			Motor_Backward();
//			move_cursor(1, 4);
//			lcd_string("BACKWARD");
//		}
//
//		//reset
//		else if(rxData1 == 'X')
//		{
//			NVIC_SystemReset();
//		}
//
//		//PAUSE
//		else //if(rxData1 == '')
//		{
//			HAL_UART_Transmit_IT(&huart2, Pause_arr, sizeof(Pause_arr));
//			Motor_Stop();
//			move_cursor(1, 4);
//			lcd_string("STOP    ");
//		}
//	}
//}


