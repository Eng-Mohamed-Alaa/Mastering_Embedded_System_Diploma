/*
 * Servo.c
 *
 *  Created on: Nov 26, 2023
 *      Author: computer store
 */

#include "../SERVICES/Standard_Data_Types.h"
#include "HAL/Servo_Motor/Servo_Motor.h"
#include "HAL/Servo_Motor/Servo_Motor_CFG.h"

#define Servo_Pulse_Width_Per_Degree_us			((float32)(Servo_Pulse_Max_Width_us - Servo_Pulse_Min_Width_us)/Servo_Rotation_Range)

void Servo_Init(void)
{
	TIMx_Init_CFG_t Servo_Timer_CFG = {Update_State_Enable, Update_Request_Source_OVF_UDF, One_Pulse_Mode_Disable, Direction_Mode_Edge_Aligned_UP
										, Auto_Reload_Preload_Enable, 7};
	Timer_Init(Servo_Timer, &Servo_Timer_CFG);

	TIMx_PWM_CFG_t Servo_PWM_CFG = {Servo_Signal_Timer_Channel, Active_High, Servo_Signal_PIN, Servo_Signal_Port};
	Timer_PWM_CFG(Servo_Timer, &Servo_PWM_CFG);
}

void Servo_Rotate(uint16 Rotation_Angle)
{
	uint16 PWM_T_High_us = Servo_Pulse_Min_Width_us + Rotation_Angle*Servo_Pulse_Width_Per_Degree_us;
	TIMx_PWM_Timing_t TIMx_PWM_Timing = {Servo_Signal_Timer_Channel, Servo_Siganl_Refresh_Rate_us, PWM_T_High_us};
	Timer_PWM_Start(Servo_Timer, &TIMx_PWM_Timing);
}

void Servo_Stop()
{
	Timer_Stop(Servo_Timer);
}
