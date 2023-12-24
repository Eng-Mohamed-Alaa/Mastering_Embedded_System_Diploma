/*
 * CAR_DC_MOTORS.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef HAL_CAR_DC_MOTORS_CAR_DC_MOTORS_H_
#define HAL_CAR_DC_MOTORS_CAR_DC_MOTORS_H_



#endif /* HAL_CAR_DC_MOTORS_CAR_DC_MOTORS_H_ */


void CAR_DC_MOTORS_vidInit(void);

void CAR_vidMove_Forward(void);
void CAR_vidMove_Backward(void);
void CAR_vidTurn_Right(void);
void CAR_vidTurn_Left(void);
void CAR_vid_Stop(void);

/*APIs for PhotoSession */
void CAR_vid_Stop_with_Steering_turned_left(void);
void CAR_vid_Stop_with_Steering_turned_right(void);
