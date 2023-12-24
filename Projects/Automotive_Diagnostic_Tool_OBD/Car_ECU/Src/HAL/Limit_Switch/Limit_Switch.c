/*
 * Limit_Switch.c
 *
 *  Created on: Nov 27, 2023
 *      Author: computer store
 */

#include "MCAL/GPIO/GPIO.h"
#include "HAL/Limit_Switch/Limit_Switch.h"
#include "HAL/Limit_Switch/Limit_Switch_CFG.h"



void Limit_SW_Init(void)
{
	GPIO_Port_Enable_clock(Limit_SW_PORT);
	GPIO_PIN_INIT(Limit_SW_PIN, Limit_SW_PORT, Input_pull_up_down, GPIO_max_speed_10_MHz, pull_Down);
}

Limit_SW_State_t Limit_SW_Get_State(void)
{
	uint8 SW_PIN_Value;
	GPIO_get_PIN_value( Limit_SW_PIN, Limit_SW_PORT, &SW_PIN_Value);
	Limit_SW_State_t Limit_SW_State;
	switch(SW_PIN_Value)
	{
	case 0:
		Limit_SW_State = Limit_SW_ST_Not_Pressed;
	break;

	case 1:
		Limit_SW_State = Limit_SW_ST_Pressed;
	break;

	default:
		Limit_SW_State = Limit_SW_ST_Error;
	break;
	}

	return Limit_SW_State;
}
