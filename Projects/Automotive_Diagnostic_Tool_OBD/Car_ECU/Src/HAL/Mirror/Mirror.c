/*
 * Car_Mirror.c
 *
 *  Created on: Nov 29, 2023
 *      Author: computer store
 */

#include <HAL/Mirror/Mirror.h>
#include <HAL/Mirror/Mirror_CFG.h>
#include "HAL/Servo_Motor/Servo_Motor.h"
#include "HAL/Limit_Switch/Limit_Switch.h"

void Mirror_Init()
{
	Servo_Init();
	Limit_SW_Init();
}

void Mirror_Open()
{
	Servo_Rotate(Car_Mirror_Open_Angle);
}

void Mirror_Close()
{
	Servo_Rotate(Car_Mirror_Close_Angle);
}

void Mirror_Stop()
{
	Servo_Stop();
}

Mirror_State_t Mirror_Get_State()
{
	Mirror_State_t Mirror_State;
	Limit_SW_State_t Car_Mirror_Limit_SW_State = Limit_SW_Get_State();

	switch(Car_Mirror_Limit_SW_State)
	{
	case Limit_SW_ST_Not_Pressed:
		Mirror_State = Mirror_ST_Closed;
	break;

	case Limit_SW_ST_Pressed:
		Mirror_State = Mirror_ST_Open;
	break;

	default:
		Mirror_State = Mirror_ST_Error;
	}
	return Mirror_State;
}

