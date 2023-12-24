/*
 * Timrer.h
 *
 *  Created on: Nov 23, 2023
 *      Author: computer store
 */

#ifndef MCAL_TIMER_TIMRER_H_
#define MCAL_TIMER_TIMRER_H_

#include "../SERVICES/Standard_Data_Types.h"
#include "MCAL/GPIO/GPIO.h"


//=======================================================
//supported Timers Base Addresses section
//=======================================================
#define TIM2_Base_Address 		0x40000000
#define TIM3_Base_Address 		0x40000400
#define TIM4_Base_Address 		0x40000800
#define TIM5_Base_Address 		0x40000C00


//=======================================================
//user defined data types section
//=======================================================


//*************************************************
//timer module registers
//*************************************************
typedef struct
{
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SMCR;
	volatile uint32 DIER;
	volatile uint32 SR;
	volatile uint32 EGR;
	volatile uint32 CCMR1;
	volatile uint32 CCMR2;
	volatile uint32 CCER;
	volatile uint32 CNT;
	volatile uint32 PSC;
	volatile uint32 ARR;
	volatile uint32 Reserved1;
	volatile uint32 CCRx[4];
	volatile uint32 Reserved2;
	volatile uint32 DCR;
	volatile uint32 DMAR;
}TIMx_t;


//*************************************************
//timer initialization configuration structure
//*************************************************
typedef struct
{
	uint16 Update_State;							//set according to @ref Update_State
	uint16 Update_Request_Source;					//set according to @ref Update_Request_Source
	uint16 One_Pulse_Mode;							//set according to @ref One_Pulse_Mode
	uint16 Direction_Mode; 							//set according to @ref Direction_Mode
	uint16 Auto_Reload_Preload;						//set according to @ref Auto_Reload_Preload
	uint16 Prescaler;								//value from 0x0000 to 0xFFFF
													//set Prescaler value to get 1 MHz input clock for the timer counter
}TIMx_Init_CFG_t;


//*************************************************
//PWM mode configuration structure
//*************************************************
typedef struct
{
	uint8 Channelx_Index;							//set according to @ref Channelx_Index
	uint8 Active_Value; 							//set according to @ref Active_Value
	GPIO_enuPIN_NO_t Chacnnel_Locpin;				//set according to GPIO_enuPIN_NO_t values in GPIO.h
	GPIO_enuPORT_NO_t Chacnnel_Port;				//set according to GPIO_enuPORT_NO_t values in GPIO.h
}TIMx_PWM_CFG_t;


//*************************************************
//PWM timing configuration structure
//*************************************************
typedef struct
{
	uint8 Channelx_Index;							//set according to @ref Channelx_Index
	uint16 Periodic_Time_us; 						//from 0 to 0xFFFF
	uint16 Pulse_Time_us;							//from 0 to 0xFFFF
}TIMx_PWM_Timing_t;

//=======================================================
// Configuration macros for the APIs parameters
//=======================================================

//@ref Timer Instances
#define TIM2			((volatile TIMx_t*)(TIM2_Base_Address))
#define TIM3			((volatile TIMx_t*)(TIM3_Base_Address))
#define TIM4			((volatile TIMx_t*)(TIM4_Base_Address))
#define TIM5			((volatile TIMx_t*)(TIM5_Base_Address))

//@ref Update_State
#define Update_State_Disable							(0x00000002)
#define Update_State_Enable								(0)  				//for our project use this for configurations

//@ref Update_Request_Source
#define Update_Request_Source_Any						(0)
#define Update_Request_Source_OVF_UDF					(0x00000004)		//for our project use this for configurations

//@ref One_Pulse_Mode
#define One_Pulse_Mode_Disable							(0)					//for our project use this for configurations
#define One_Pulse_Mode_Enable							(0x00000008)

//@ref Direction_Mode
#define Direction_Mode_Edge_Aligned_UP					(0)					//for our project use this for configurations
#define Direction_Mode_Edge_Aligned_Down				(0x00000010)
#define Direction_Mode_Center_Aligned_M1				(0x00000020)
#define Direction_Mode_Center_Aligned_M2				(0x00000040)
#define Direction_Mode_Center_Aligned_M3				(0x00000060)

//@ref Auto_Reload_Preload
#define Auto_Reload_Preload_Enable						(0x00000080)		 //for our project use this for configurations
#define Auto_Reload_Preload_Disable						(0)

//@ref Active_Value
#define Active_High										(0)					 //for our project use this for configurations
#define Active_Low										(1)


//@ref Channelx_Index
#define Channel1										(0)
#define Channel2										(1)
#define Channel3										(2)
#define Channel4										(3)


//=======================================================
//Timer APIs
//=======================================================

//****************************************************************************************************************
/*
 * API name: Timer_Init
 * API Parameters:
 * 					Par1 name: TIMx / Par1 type: pointer to TIMx_t / Par1 reference: go to (@ref Timer Instances)
 * 					Par2 name: CFG / Par2 type: pointer to TIMx_Init_CFG_t / Par2 references: go to (timer initialization configuration structure)
 * API Return: void
 * API Functionality: initialize the general HW of the targeted (TIMx) according to user configurations (CFG)
 */
void Timer_Init(volatile TIMx_t* TIMx, TIMx_Init_CFG_t* CFG);
//****************************************************************************************************************


//****************************************************************************************************************
/*
 * API name: Timer_PWM_CFG
 * API Parameters:
 * 					Par1 name: TIMx / Par1 type: pointer to TIMx_t / Par1 reference: go to (@ref Timer Instances)
 * 					Par2 name: CFG / Par2 type: pointer to TIMx_PWM_CFG_t / Par2 references: go to (PWM mode configuration structure)
 * API Return: void
 * API Functionality: configure and enable the PWM mode of the targeted (TIMx) according to user configurations (CFG) for the targeted channel
 */
void Timer_PWM_CFG(volatile TIMx_t* TIMx, TIMx_PWM_CFG_t* CFG);
//****************************************************************************************************************


//****************************************************************************************************************
/*
 * API name: Timer_Start
 * API Parameters:
 * 					Par1 name: TIMx / Par1 type: pointer to TIMx_t / Par1 reference: go to (@ref Timer Instances)
 * 					Par2 name: CFG / Par2 type: pointer to TIMx_PWM_Timing_t / Par2 references: go to (PWM timing configuration structure)
 * API Return: void
 * API Functionality: enable the counter of the targeted TIMx
 */
void Timer_PWM_Start(volatile TIMx_t* TIMx, TIMx_PWM_Timing_t* CFG);
//****************************************************************************************************************


//****************************************************************************************************************
/*
 * API name: Timer_Stop
 * API Parameters:
 * 					Par1 name: TIMx / Par1 type: TIMx_t / Par1 reference: go to (@ref Timer Instances)
 * API Return: void
 * API Functionality: stop and clear the counter of the targeted TIMx
 */
void Timer_Stop(volatile TIMx_t* TIMx);
//****************************************************************************************************************


#endif /* MCAL_TIMER_TIMRER_H_ */
