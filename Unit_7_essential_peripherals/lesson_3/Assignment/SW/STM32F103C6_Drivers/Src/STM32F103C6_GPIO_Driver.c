/*
 * STM32F103C6_GPIO_Driver.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Mohamed Alaa
 */

//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103C6_GPIO_Driver.h"

//----------------------------------------------------------------
//GPIO driver static functions
//----------------------------------------------------------------

static uint8_t GPIO_Get_Config_Position(uint16_t Pin_Number);

static uint8_t GPIO_Get_Config_Position(uint16_t Pin_Number)
{
	switch(Pin_Number)
	{
	case (GPIO_Pin0):
	case (GPIO_Pin8):
		return 0;
	case (GPIO_Pin1):
	case (GPIO_Pin9):
		return 4;
	case (GPIO_Pin2):
	case (GPIO_Pin10):
		return 8;
	case (GPIO_Pin3):
	case (GPIO_Pin11):
		return 12;
	case (GPIO_Pin4):
	case (GPIO_Pin12):
		return 16;
	case (GPIO_Pin5):
	case (GPIO_Pin13):
		return 20;
	case (GPIO_Pin6):
	case (GPIO_Pin14):
		return 24;
	case (GPIO_Pin7):
	case (GPIO_Pin15):
		return 28;
	}

}

//----------------------------------------------------------------
//APIs Implementation by "MCAL GPIO driver"
//----------------------------------------------------------------


//Init/Deinit API

void MCAL_GPIO_Init(volatile GPIO_typedef *GPIOX, GPIO_Pin_Configuration_t *Pin_Configuration)
{
	uint32_t *Config_Register = NULL;

	// specify which register from CRL and CRH is responsible to configure the pin according to pin number
	Config_Register= (Pin_Configuration->GPIO_Pin_Number < GPIO_Pin8) ? (&(GPIOX->CRL)) : (&(GPIOX->CRH)) ;

	//get the pin configuration position in the Config_Register
	uint8_t Config_Position = GPIO_Get_Config_Position(Pin_Configuration->GPIO_Pin_Number);

	//clear the pin configuration position in the config_register (Pin is temporary Input Analog)
	*Config_Register &= ~(0xF << Config_Position);

	uint8_t config_value; //value that will be written to the pin configuration position in the config_register


	switch(Pin_Configuration->GPIO_Pin_Mode)
	{
	// pin is input floating or Analog or with pull up resistance (same for AF input floating or analog or pull up resistance according to the TRM)
	case (GPIO_Mode_Input_FLO):
	case (GPIO_Mode_Input_Analog):
		config_value = (Pin_Configuration->GPIO_Pin_Mode <<2);
		break;

	// pin is input with pull up or pull down resistance (same for AF input with pull up resistance according to the TRM)
	//same config_value of input with pull down resistance the difference is the GPIOX_ODR bit value to choose between pull up/down resistance
	case (GPIO_Mode_Input_PU):
		config_value = (GPIO_Mode_Input_PU <<2);
		GPIOX->ODR |= (Pin_Configuration->GPIO_Pin_Number); //set PXODR to 1 to activate select pull up resistance
		break;

	// pin is input with pull down resistance (same for AF input with pull down resistance according to the TRM)
	//same config_value of input with pull up resistance the difference is the GPIOX_ODR bit value to choose between pull up/down resistance
	case (GPIO_Mode_Input_PD):
		config_value = (GPIO_Mode_Input_PU <<2);
		GPIOX->ODR &= ~(Pin_Configuration->GPIO_Pin_Number); //set PXODR to 0 to select pull down resistance
		break;

	//pin is Alternative function input this option is considered as input floating in this driver
	case (GPIO_Mode_AF_Input):
		config_value = (GPIO_Mode_Input_FLO <<2);
		break;

	//pin is (output/Alternative function output) open drain or push pull
	case (GPIO_Mode_Output_OD):
	case (GPIO_Mode_Output_PP):
	case (GPIO_Mode_AF_OD):
	case (GPIO_Mode_AF_PP):
		config_value = ((Pin_Configuration->GPIO_Pin_Output_Speed) | ((Pin_Configuration->GPIO_Pin_Mode-4) <<2));
		break;
	}

	*Config_Register |= (config_value << Config_Position);
}

void MCAL_GPIO_Deinit(volatile GPIO_typedef *GPIOX)
{
	//method 1 setting each writable register manually to the reset value
//	GPIOX->BRR = 0x00000000;
//	GPIOX->BSRR = 0x00000000;
//	GPIOX->ODR = 0x00000000;
//	GPIOX->IDR; read only
//	GPIOX->CRL = 0x44444444;
//	GPIOX->CRH = 0x44444444;
//	GPIOX->LCKR = (0x00000000);

	//method 2 using RCC_APB2RSTR register

	switch((uint32_t)GPIOX)
	{
	case ((uint32_t)GPIOA):
		RCC->APB2RSTR |= 1<<2;
		RCC->APB2RSTR &= ~(1<<2);
		break;
	case ((uint32_t)GPIOB):
		RCC->APB2RSTR |= 1<<3;
		RCC->APB2RSTR &= ~(1<<3);
		break;
	case ((uint32_t)GPIOC):
		RCC->APB2RSTR |= 1<<4;
		RCC->APB2RSTR &= ~(1<<4);
		break;
	case ((uint32_t)GPIOD):
		RCC->APB2RSTR |= 1<<5;
		RCC->APB2RSTR &= ~(1<<5);
		break;
	case ((uint32_t)GPIOE):
		RCC->APB2RSTR |= 1<<6;
		RCC->APB2RSTR &= ~(1<<6);
	}

}

//****************************************************************
//Pin API

uint8_t MCAL_GPIO_Read_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number)
{
	uint8_t pin_status = GPIO_Pin_Reset;
	if((GPIOX->IDR) & Pin_Number)
		{
			pin_status = GPIO_Pin_Set; //the bit is not zero
		}
	return pin_status;
}

void MCAL_GPIO_Write_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number, uint8_t Pin_Value)
{
	switch(Pin_Value)
	{
	case (GPIO_Pin_Set):
		GPIOX->ODR |= Pin_Number;
		break;
	case (GPIO_Pin_Reset):
		GPIOX->ODR &= ~(Pin_Number);
		break;
	}
}

void MCAL_GPIO_Toggle_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number)
{
	GPIOX->ODR ^= Pin_Number;
}

uint8_t MCAL_GPIO_Lock_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number)
{
//GPIOx_LCKR
//	Bit 16 LCKK[16]: Lock key
//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	LOCK key writing sequence:
//	Write 1
//	Write 0
//	Write 1
//	Read 0
//	Read 1 (this read is optional but confirms that the lock is active)
//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	Any error in the lock sequence will abort the lock.
//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	These bits are read write but can only be written when the LCKK bit is 0.
//	0: Port configuration not locked
//	1: Port configuration locked.

	uint32_t temp = (1<<16 | Pin_Number); //temp holds 1 to bit 16 corresponding to LCKK and 1 to the bit corresponding to pin we want to lock its configuration

	GPIOX->LCKR = temp; //LCKK = 1, LCK_desired_bit = 1 at same time (no problem)
	GPIOX->LCKR = Pin_Number; //LCKK = 0, LCKdesired still 1
	GPIOX->LCKR = temp; // LCKK = 1, LCK_desired_bit still 1
	if( (( GPIOX->LCKR >>16 ) & 1) == 0) //read LCKK should be 0
	{
		if( (( GPIOX->LCKR >>16 ) & 1) == 1) //read LCKK should be 1
			{return GPIO_Pin_Config_Lock_Enabled;}
	}
	return GPIO_Pin_Config_Lock_Error;
}

//****************************************************************
//Port API
uint16_t MCAL_GPIO_Read_Port(volatile GPIO_typedef *GPIOX)
{
	return (uint16_t)GPIOX->IDR;
}

void MCAL_GPIO_Write_Port(volatile GPIO_typedef *GPIOX, uint16_t Value)
{
	GPIOX->ODR = (uint32_t) Value;
}



