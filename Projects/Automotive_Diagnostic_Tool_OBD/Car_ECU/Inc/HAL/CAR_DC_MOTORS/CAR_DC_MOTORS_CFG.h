/*
 * CAR_DC_MOTORS_CFG.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef HAL_CAR_DC_MOTORS_CAR_DC_MOTORS_CFG_H_
#define HAL_CAR_DC_MOTORS_CAR_DC_MOTORS_CFG_H_


#define Steering_Robot		Used_Robot

#ifdef Steering_Robot


/*** DC MOTOR Responsible for CAR motion ***/
#define Motion_DC_Motor_DIRA		GPIO_PIN_12
#define Motion_DC_Motor_DIRB		GPIO_PIN_13
#define Motion_DC_Motor_EN			GPIO_PIN_14

#define Motion_DC_Motor_PORT		GPIO_PORT_B

/*** DC MOTOR Responsible for Steering ***/
#define Steering_DC_Motor_DIRA		GPIO_PIN_4
#define Steering_DC_Motor_DIRB		GPIO_PIN_6
#define Steering_DC_Motor_EN		GPIO_PIN_5

#define Steering_DC_Motor_PORT		GPIO_PORT_A


#endif

#ifdef Differential_Robot

#endif

#endif /* HAL_CAR_DC_MOTORS_CAR_DC_MOTORS_CFG_H_ */
