/*
 * ADC.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Tariq
 */

/*================ Services Includes =====================*/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/MAGIC_NUMBERS.h"
#include "../SERVICES/Bit_Wise_Operations.h"
/*================ MCAL Includes =========================*/
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/ADC/ADC_Private.h"
#include "MCAL/ADC/ADC_Config.h"
#include "MCAL/ADC/ADC.h"


/*
 * @Brief: Init ADC Peripheral with static configuration
 * @Input param: void
 * @return type: void
 */
void ADC_vidInit(void)
{
	/*Enable Clock for wanted GPIO Port */
     GPIO_Port_Enable_clock(GPIO_PORT_A);


	/*Select GPIO Analog Mode for wanted Channels*/
	//Not done yet

	/*Select GPIO PinMode Input Floating (not pull up nor pull down)*/
     GPIO_PIN_INIT(ADC_Regular_Priority_1, GPIO_PORT_A, Input_Analog,GPIO_INPUT,FLOATING);



	/*Enable ADC1 Peripheral Clock*/
     Rcc_enuControl_APB2_Peripheral( RCC_APB2_Periph_ADC1,RCC_Periph_ENABLE);


	/*Setting Analog Watchdog mode*/
	ADC_REGS->ADC_CR1 &= RESET_Analog_Watchdog_Mode_Selection_Bits;
	ADC_REGS->ADC_CR1 |= Analog_Watchdog_Mode;

	/*Setting ADC Dual Mode*/
	ADC_REGS->ADC_CR1 &= RESET_DUAL_MODE_SELECTION_BITS;
	ADC_REGS->ADC_CR1 |= ADC_DUAL_MODE ;

	/*SETTING DISCNUM Mode*/
	ADC_REGS->ADC_CR1 &= RESET_DISCNUM_BITS;
	ADC_REGS->ADC_CR1 |= DISCNUM_MODE ;

	/*SETTING AWDCH*/
	ADC_REGS->ADC_CR1 &= RESET_AWDCH_BITS;
	ADC_REGS->ADC_CR1 |= AWDCH_Mask;

	/*SETTING REST OF REGISTER BITS TO ZERO*/
	ADC_REGS->ADC_CR1 &= ADC_CR1_TEAM_A_MASK;

	/*SETTING INTERNAL TEMP SENSOR MODE*/
//#if  (Disable_Internal_Temp_Sensor == ADC_Internal_Temp_Sensor)
	//CLR_BIT(ADC_REGS->ADC_CR2,ADC_CR2_TSVREFE);

//#elif (Enable_Internal_Temp_Sensor == ADC_Internal_Temp_Sensor)
	SET_BIT(ADC_REGS->ADC_CR2,ADC_CR2_TSVREFE);
//#endif

	/*SETTING COLLECTION OF BITS WITH ZERO*/
	ADC_REGS->ADC_CR2 &= ADC_CR2_TEAM_A_MASK;

	/*SETTING DATA ADJUST MODE*/
	ADC_REGS->ADC_CR2 |= DATA_ALIGNMENT_MODE;

	/*SETTING Conversion Mode*/
	CLR_BIT(ADC_REGS->ADC_CR2,ADC_CR2_CONT);
	ADC_REGS->ADC_CR2 |= ADC_Conversion_Mode;

	/*Powering On ADC Peripherl*/
	SET_BIT(ADC_REGS->ADC_CR2,ADC_CR2_ADON);

	/*Setting all channels with sample time of 1.5 cycles*/
	ADC_REGS->ADC_SMPR2 = Sample_time_1_5_for_all_channels;
	ADC_REGS->ADC_SMPR1 = Sample_time_1_5_for_all_channels;

	/*Setting Channel with highest regular priority*/
	ADC_REGS->ADC_SQR3  |= ADC_Regular_Priority_1;
	/*Setting Channel with regular Priority 2*/
	ADC_REGS->ADC_SQR3  |= (ADC_Regular_Priority_2 <<5);
	/*Setting Channel with regular Priority 3*/
	ADC_REGS->ADC_SQR3  |= (ADC_Regular_Priority_3 <<10);
	/*Setting Channel with regular Priority 4*/
	ADC_REGS->ADC_SQR3  |= (ADC_Regular_Priority_4 <<15);
	/*Setting Channel with regular Priority 5*/
	ADC_REGS->ADC_SQR3  |= (ADC_Regular_Priority_5 <<20);
	/*Setting Channel with regular Priority 6*/
	ADC_REGS->ADC_SQR3   |= (ADC_Regular_Priority_6 <<25);
	/*Leaving other Not used Register on the reset value*/
	ADC_REGS->ADC_SQR2  = ADC_SQR2_RESET_VALUE ;
	ADC_REGS->ADC_SQR1  = ADC_SQR1_RESET_VALUE ;
	ADC_REGS->ADC_LTR   = ADC_LTR_RESET_VALUE  ;
	ADC_REGS->ADC_HTR   = ADC_HTR_RESET_VALUE  ;
	ADC_REGS->ADC_JOFR1 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JOFR2 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JOFR3 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JOFR4 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JSQR  = ADC_JSQR_RESET_VALUE ;

	/*Powering On ADC Peripherl*/
	SET_BIT(ADC_REGS->ADC_CR2,ADC_CR2_ADON);
}


/*
 * @Brief: DeInit ADC Peripheral
 * @Input param: void
 * @return type: void
 */
void ADC_vidDeInit(void)
{
	ADC_REGS->ADC_CR2   = ADC_CR2_RESET_VALUE  ;
	ADC_REGS->ADC_CR1   = ADC_CR1_RESET_VALUE  ;
	ADC_REGS->ADC_SMPR1 = ADC_SMPR1_RESET_VALUE;
	ADC_REGS->ADC_SMPR2 = ADC_SMPR2_RESET_VALUE;
	ADC_REGS->ADC_SQR3  = ADC_SQR3_RESET_VALUE ;
	ADC_REGS->ADC_SQR2  = ADC_SQR2_RESET_VALUE ;
	ADC_REGS->ADC_SQR1  = ADC_SQR1_RESET_VALUE ;
	ADC_REGS->ADC_LTR   = ADC_LTR_RESET_VALUE  ;
	ADC_REGS->ADC_HTR   = ADC_HTR_RESET_VALUE  ;
	ADC_REGS->ADC_JOFR1 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JOFR2 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JOFR3 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JOFR4 = ADC_JOFRx_RESET_VALUE;
	ADC_REGS->ADC_JSQR  = ADC_JSQR_RESET_VALUE ;
}


enu_ADC_Error_Status ADC_enu_Read_Regular_Channel(Puint16 add_pu16Value)
{
	enu_ADC_Error_Status Return_val = ADC_STATUS_FAILED;
	if(add_pu16Value == NULL) Return_val = ADC_NULL_PTR_ERROR;
	else
	{
		uint8 loc_u8Time_out_counter = 0;
		SET_BIT(ADC_REGS->ADC_CR2,ADC_CR2_SWSTART);
		while( (GET_BIT(ADC_REGS->ADC_SR,ADC_SR_EOC) != 1) && loc_u8Time_out_counter <200)
		{
			loc_u8Time_out_counter++;
			if(loc_u8Time_out_counter == 200) Return_val = ADC_TIME_OUT_ERROR;

		}
		if(loc_u8Time_out_counter < 200)
		{	if(RIGHT_ALIGNMENT == DATA_ALIGNMENT_MODE)
			*add_pu16Value = ADC_REGS->ADC_DR;
		}
		else
		{
			//Time out occured
		}
	}
	return Return_val;
}
