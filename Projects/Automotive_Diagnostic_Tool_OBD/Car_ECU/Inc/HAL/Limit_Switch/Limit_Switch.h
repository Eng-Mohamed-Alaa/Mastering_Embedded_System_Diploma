/*
 * Limit_Switch.h
 *
 *  Created on: Nov 27, 2023
 *      Author: computer store
 */

#ifndef HAL_LIMIT_SWITCH_LIMIT_SWITCH_H_
#define HAL_LIMIT_SWITCH_LIMIT_SWITCH_H_

typedef enum{
	Limit_SW_ST_Not_Pressed = 0,
	Limit_SW_ST_Pressed ,
	Limit_SW_ST_Error
}Limit_SW_State_t;

void Limit_SW_Init(void);
Limit_SW_State_t Limit_SW_Get_State(void);

#endif /* HAL_LIMIT_SWITCH_LIMIT_SWITCH_H_ */
