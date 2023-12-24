/*
 * LED.c
 *
 *  Created on: Dec 6, 2023
 *      Author: computer store
 */

#include "MCAL/GPIO/GPIO.h"
#include "HAL/LED/LED.h"
#include "HAL/LED/LED_CFG.h"

void LED_Init(void)
{
	GPIO_Port_Enable_clock(LED_PORT);
	GPIO_PIN_INIT(LED_PIN, LED_PORT, LED_Mode, LED_Max_Speed, FLOATING);
}

void LED_DeInit(void)
{
	GPIO_PIN_INIT(LED_PIN, LED_PORT, InputFloating, LED_Max_Speed, FLOATING);
}

void LED_On(void)
{
	GPIO_set_PIN_value(LED_PIN,LED_PORT,GPIO_LOGIC_LOW);
}

void LED_OFF(void)
{
	GPIO_set_PIN_value(LED_PIN,LED_PORT,GPIO_LOGIC_HIGH);
}
