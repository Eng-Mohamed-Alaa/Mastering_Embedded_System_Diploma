/*
 * LED_CFG.h
 *
 *  Created on: Dec 6, 2023
 *      Author: computer store
 */

#ifndef HAL_LED_LED_CFG_H_
#define HAL_LED_LED_CFG_H_

#include "MCAL/GPIO/GPIO.h"

#define LED_PORT				GPIO_PORT_C
#define LED_PIN					GPIO_PIN_13
#define LED_Mode				output_Open_drain
#define LED_Max_Speed			GPIO_max_speed_2_MHz


#endif /* HAL_LED_LED_CFG_H_ */
