/*
 * Servo_Motor.h
 *
 *  Created on: Nov 26, 2023
 *      Author: computer store
 */

#ifndef HAL_SERVO_MOTOR_SERVO_MOTOR_H_
#define HAL_SERVO_MOTOR_SERVO_MOTOR_H_

#include "../SERVICES/Standard_Data_Types.h"

void Servo_Init(void);
void Servo_Rotate(uint16 Rotation_Angle);
void Servo_Stop(void);


#endif /* HAL_SERVO_MOTOR_SERVO_MOTOR_H_ */
