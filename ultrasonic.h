/*
 * ultrasonic.h
 *
 *  Created on: Aug 1, 2024
 *      Author: jsmok
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "top.h"
#include "delay.h"
extern TIM_HandleTypeDef htim2;

#define TRIG_PORT1		GPIOC
#define TRIG_PIN1			GPIO_PIN_0

#define TRIG_PORT2		GPIOC
#define TRIG_PIN2			GPIO_PIN_1

#define TRIG_PORT3		GPIOA
#define TRIG_PIN3			GPIO_PIN_8

//extern uint32_t INC_Value_1_Ultrasonic1 = 0;
//extern uint32_t INC_Value2_Ultrasonic1 = 0;
//
//extern uint32_t INC_Value_1_Ultrasonic2 = 0;
//extern uint32_t INC_Value2_Ultrasonic2 = 0;
//
//extern uint32_t INC_Value_1_Ultrasonic3 = 0;
//extern uint32_t INC_Value2_Ultrasonic3 = 0;

extern uint16_t echoTime1;
extern uint16_t echoTime2;
extern uint16_t echoTime3;

extern uint8_t captureFlag1;
extern uint8_t captureFlag2;
extern uint8_t captureFlag3;

extern uint16_t distance1;
extern uint16_t distance2;
extern uint16_t distance3;

void UltrasonicInit(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HCSR04_read1(void);
void HCSR04_read2(void);
void HCSR04_read3(void);

#endif /* ULTRASONIC_H */
