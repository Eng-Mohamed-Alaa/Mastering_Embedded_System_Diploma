/*
 * Timer.c
 *
 *  Created on: Nov 23, 2023
 *      Author: computer store
 */

#include "../SERVICES/Standard_Data_Types.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/Timer/Timer_PRIV.h"
#include "MCAL/Timer/Timer.h"

void Timer_Init(volatile TIMx_t* TIMx, TIMx_Init_CFG_t* CFG)
{
	//enable the clock for the targeted timer: TIMx [TIM5:TIM2]
	switch((uint32)TIMx)
	{
	case (uint32)TIM2:
		Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_TIM2,RCC_Periph_ENABLE);
	break;

	case (uint32)TIM3:
		Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_TIM3,RCC_Periph_ENABLE);
	break;

	case (uint32)TIM4:
		Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_TIM4,RCC_Periph_ENABLE);
	break;

	case (uint32)TIM5:
		Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_TIM5,RCC_Periph_ENABLE);
	break;
	}

	//clear the Control register of the targeted TIMx [TIM5:TIM2]
	TIMx->CR1 = 0;

	//assign the user configurations in the Control register 1 of the targeted TIMx [TIM5:TIM2]
	//for our application no need to configure more features in the driver so TIMx->CR2 and unconfigured fields in TIMx->CR1 will be 0 to meet our apllication needs
	TIMx->CR1 |= ( (CFG->Auto_Reload_Preload) | (CFG->Direction_Mode) | (CFG->One_Pulse_Mode) |
			(CFG->Update_Request_Source) | (CFG->Update_State) );

	//assign the prescaler value in TIMx [TIM5:TIM2], The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1)
	TIMx->PSC = CFG->Prescaler;
}

void Timer_PWM_CFG(volatile TIMx_t* TIMx, TIMx_PWM_CFG_t* CFG)
{
	//enable the clock of the channel Port of the PWM in TIMx [TIM5:TIM2]
	GPIO_Port_Enable_clock(CFG->Chacnnel_Port);

	//configure the Channel PIN of the PWM in TIMx [TIM5:TIM2]
	GPIO_PIN_INIT(CFG->Chacnnel_Locpin, CFG->Chacnnel_Port, AF_output_Push_pull, GPIO_max_speed_10_MHz, FLOATING);

	//Channelx, x [4:1] can be active or not active
	//active means connected to the port's pin, and not active means the wire is inside the Timerx no physical connection to the port's pin
	switch(CFG->Channelx_Index)
	{
	case Channel1:
		TIMx->CCMR1 &= 0xFF00; 									//clear the first byte in CCMR1 which is related to Channel1 to be configured
		TIMx->CCMR1 |= (1 << TIMx_CCMR1_OC1PE) | (0b110 << TIMx_CCMR1_OC1M); //enable Output compare 2 preload and PWM mode1 for Channel1

		TIMx->CCER &= 0xFFF0;									 //clear the first nipple which is related to Channel1 to be configured
		TIMx->CCER |= 1<<TIMx_CCER_CC1E; 						 //enable Channel1 to be Active
		TIMx->CCER |= CFG->Active_Value << TIMx_CCER_CC1P; 		 //assign the active value (output polarity) of Channel1
	break;

	case Channel2:
		TIMx->CCMR1 &= 0x00FF; 									//clear the last byte in CCMR1 which is related to Channel2 to be configured
		TIMx->CCMR1 |= (1 << TIMx_CCMR1_OC2PE) | (0b110 << TIMx_CCMR1_OC2M) ; //enable Output compare 2 preload and PWM mode1 for Channel2

		TIMx->CCER &= 0xFF0F;									 //clear the first nibble which is related to Channel2 to be configured
		TIMx->CCER |= 1<<TIMx_CCER_CC2E;						 //enable Channel2 to be Active
		TIMx->CCER |= CFG->Active_Value << TIMx_CCER_CC2P; 		 //assign the active value (output polarity) of Channel2
	break;

	case Channel3:
		TIMx->CCMR2 &= 0xFF00; 									//clear the first byte in CCMR2 which is related to Channel3 to be configured
		TIMx->CCMR2 |= (1 << TIMx_CCMR2_OC3PE) | (0b110 << TIMx_CCMR2_OC3M) ; //enable Output compare 3 preload and PWM mode1 for Channel3

		TIMx->CCER &= 0xF0FF;									 //clear the third nibble which is related to Channel3 to be configured
		TIMx->CCER |= 1<<TIMx_CCER_CC3E;						 //enable Channel3 to be Active
		TIMx->CCER |= CFG->Active_Value << TIMx_CCER_CC3P; 		 //assign the active value (output polarity) of Channel3
	break;

	case Channel4:
		TIMx->CCMR2 &= 0x00FF; 									//clear the last byte in CCMR2 which is related to Channel4 to be configured
		TIMx->CCMR2 |= (1 << TIMx_CCMR2_OC4PE) | (0b110 << TIMx_CCMR2_OC4M) ; //enable Output compare 4 preload and PWM mode1 for Channel4

		TIMx->CCER &= 0xF0FF;									 //clear the last nibble which is related to Channel4 to be configured
		TIMx->CCER |= 1<<TIMx_CCER_CC3E;						 //enable Channel4 to be Active
		TIMx->CCER |= CFG->Active_Value << TIMx_CCER_CC3P; 		 //assign the active value (output polarity) of Channel4
	break;
	}
}

void Timer_PWM_Start(volatile TIMx_t* TIMx, TIMx_PWM_Timing_t* CFG)
{

	TIMx->CCRx[CFG->Channelx_Index] = CFG->Pulse_Time_us;			//assign the capture/compare register value for targeted channel

	//assign the ARR value in TIMx [TIM5:TIM2]
	//ARR is the value to be loaded in the actual auto-reload register
	//this value will control the refresh time for the servo motors form 0 to 0xFFFF us
	TIMx->ARR = CFG->Periodic_Time_us;

	if( ((TIMx->CR1 >> TIMx_CR1_CEN) & 1) == 0)
	{
		//enable timer module
		TIMx->CR1 |= 1<<TIMx_CR1_CEN;
	}
}

void Timer_Stop(volatile TIMx_t* TIMx)
{
	//disable the timer module
	TIMx->CR1 &= ~(1<<TIMx_CR1_CEN);

	//clear the counter of the timer
	TIMx->CNT &= ~(0xFFFF);
}


