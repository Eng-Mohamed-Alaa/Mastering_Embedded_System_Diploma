/*
 * CAR_DC_MOTORS.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Tariq
 */
/*================ Services Includes =======================*/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/MAGIC_NUMBERS.h"
#include "../SERVICES/Bit_Wise_Operations.h"
/*================ MCAL Includes ===========================*/
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/Timer/Timer.h"
/*==================HAL Includes ===========================*/
#include"../../../INC/HAL/CAR_DC_MOTORS/CAR_DC_MOTORS.h"
#include"../../../INC/HAL/CAR_DC_MOTORS/CAR_DC_MOTORS_CFG.h"



void CAR_DC_MOTORS_vidInit(void)
{
#if(Motion_DC_Motor_PORT == Steering_DC_Motor_PORT)
	 	 GPIO_Port_Enable_clock(Motion_DC_Motor_PORT);
#elif
	 	 GPIO_Port_Enable_clock(Motion_DC_Motor_PORT);
	     GPIO_Port_Enable_clock(Steering_DC_Motor_PORT);
#endif

	     GPIO_PIN_INIT(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	     GPIO_PIN_INIT(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	     GPIO_PIN_INIT(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	     GPIO_PIN_INIT(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	     GPIO_PIN_INIT(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	     GPIO_PIN_INIT(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
}

void CAR_vidMove_Forward(void)
{
	 	 	 	 GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENA
   		         GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW); //ENB

   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH);  //M1A
   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);   //M1B

   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2A
   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2B
}
void CAR_vidMove_Backward(void)
{
	 	 	 	 	 GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENA
	   		         GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW); //ENB

	   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);  //M1A
	   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH);   //M1B

	   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2A
	   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2B
}
void CAR_vidTurn_Right(void)
{
	 	 	 	 	 GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENA
	   		         GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENB

	   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH);  //M1A
	   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);   //M1B

	   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH);	//M2A
	   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2B
}
void CAR_vidTurn_Left(void)
{
	 	 	 	 	 GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENA
	   		         GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENB

	   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_HIGH);  //M1A
	   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);   //M1B

	   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2A
	   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH);	//M2B
}
void CAR_vid_Stop(void)
{
		 	 	 	 	 GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW); //ENA
		   		         GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW); //ENB

		   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);  //M1A
		   		         GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);   //M1B

		   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2A
		   		         GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2B
}
void CAR_vid_Stop_with_Steering_turned_left(void)
{
	   GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW); //ENA
       GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENB

       GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);  //M1A
       GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);   //M1B

       GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2A
       GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH);	//M2B

}
void CAR_vid_Stop_with_Steering_turned_right(void)
{
	   GPIO_set_PIN_value(Motion_DC_Motor_EN,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW); //ENA
       GPIO_set_PIN_value(Steering_DC_Motor_EN,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH); //ENB

       GPIO_set_PIN_value(Motion_DC_Motor_DIRA,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);  //M1A
       GPIO_set_PIN_value(Motion_DC_Motor_DIRB,Motion_DC_Motor_PORT,GPIO_LOGIC_LOW);   //M1B

       GPIO_set_PIN_value(Steering_DC_Motor_DIRA,Steering_DC_Motor_PORT,GPIO_LOGIC_HIGH);	//M2A
       GPIO_set_PIN_value(Steering_DC_Motor_DIRB,Steering_DC_Motor_PORT,GPIO_LOGIC_LOW);	//M2B
}
