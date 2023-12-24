/*
 * Car_Mirror.h
 *
 *  Created on: Nov 29, 2023
 *      Author: computer store
 */
#ifndef HAL_MIRROR_MIRROR_H_
#define HAL_MIRROR_MIRROR_H_

typedef enum{
	Mirror_ST_Open = 0,
	Mirror_ST_Closed,
	Mirror_ST_Error
}Mirror_State_t;

void Mirror_Init();
void Mirror_Open();
void Mirror_Close();
Mirror_State_t Mirror_Get_State();

#endif /* HAL_MIRROR_MIRROR_H_ */
