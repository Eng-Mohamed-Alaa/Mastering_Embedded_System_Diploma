/*
 * Servo_Motor_CFG.h
 *
 *  Created on: Nov 26, 2023
 *      Author: computer store
 */

#ifndef HAL_SERVO_MOTOR_SERVO_MOTOR_CFG_H_
#define HAL_SERVO_MOTOR_SERVO_MOTOR_CFG_H_

#include "MCAL/Timer/Timer.h"
#include "MCAL/GPIO/GPIO.h"

//=======================================================
//Servo motor connections
//=======================================================
#define Servo_Signal_Port						GPIO_PORT_A
#define Servo_Signal_PIN						GPIO_PIN_1
#define Servo_Timer								TIM2
#define Servo_Signal_Timer_Channel				Channel2

//=======================================================
//Servo motor specifications
//=======================================================
#define Servo_Siganl_Refresh_Rate_us			20000
#define Servo_Pulse_Max_Width_us				2300
#define Servo_Pulse_Min_Width_us				800
#define Servo_Rotation_Range					180 //degrees

#endif /* HAL_SERVO_MOTOR_SERVO_MOTOR_CFG_H_ */
