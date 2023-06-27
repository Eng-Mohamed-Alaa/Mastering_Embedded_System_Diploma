/*
 * STM32F103C6_GPIO_Driver.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Mohamed Alaa
 */

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_

//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103x6.h"

//----------------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------------

//GPIO_Pin_Number specifies the pin number to be configured and is set according to @ ref pin number
//GPIO_Pin_Mode specifies the pin mode to be configured and is set according to @ ref pin mode
//GPIO_Pin_Speed specifies the pin speed to be configured and is set according to @ ref pin output speed
typedef struct{
	uint16_t GPIO_Pin_Number;
	uint8_t GPIO_Pin_Mode;
	uint8_t GPIO_Pin_Output_Speed;
}GPIO_Pin_Configuration_t;

//----------------------------------------------------------------
//Configurations macros
//----------------------------------------------------------------

//@ ref pin number
#define GPIO_Pin0		((uint16_t)0x0001) //1<<0
#define GPIO_Pin1		((uint16_t)0x0002) //1<<1
#define GPIO_Pin2		((uint16_t)0x0004) //1<<2
#define GPIO_Pin3		((uint16_t)0x0008) //1<<3
#define GPIO_Pin4		((uint16_t)0x0010) //1<<4
#define GPIO_Pin5		((uint16_t)0x0020) //1<<5
#define GPIO_Pin6		((uint16_t)0x0040) //1<<6
#define GPIO_Pin7		((uint16_t)0x0080) //1<<7
#define GPIO_Pin8		((uint16_t)0x0100) //1<<8
#define GPIO_Pin9		((uint16_t)0x0200) //1<<9
#define GPIO_Pin10		((uint16_t)0x0400) //1<<10
#define GPIO_Pin11		((uint16_t)0x0800) //1<<11
#define GPIO_Pin12		((uint16_t)0x1000) //1<<12
#define GPIO_Pin13		((uint16_t)0x2000) //1<<13
#define GPIO_Pin14		((uint16_t)0x4000) //1<<14
#define GPIO_Pin15		((uint16_t)0x8000) //1<<15
#define GPIO_All_Pins	((uint16_t)0xFFFF)


//@ ref pin mode
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input Open-drain

#define GPIO_Mode_Input_Analog	((uint8_t)0x00)
#define GPIO_Mode_Input_FLO		((uint8_t)0x01)
#define GPIO_Mode_Input_PU		((uint8_t)0x02)
#define GPIO_Mode_Input_PD		((uint8_t)0x03)
#define GPIO_Mode_Output_PP		((uint8_t)0x04)
#define GPIO_Mode_Output_OD		((uint8_t)0x05)
#define GPIO_Mode_AF_PP			((uint8_t)0x06)
#define GPIO_Mode_AF_OD			((uint8_t)0x07)
#define GPIO_Mode_AF_Input		((uint8_t)0x08) //in the driver this option is considered as input floating but in the TRM any input can be alternative function input(Analog, floating, ...)

//@ ref pin output speed
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz

#define GPIO_Output_Speed_10M 	 ((uint8_t)0x01)
#define GPIO_Output_Speed_2M 	 ((uint8_t)0x02)
#define GPIO_Output_Speed_50M 	 ((uint8_t)0x03)

//@ref  Pin Value
#define GPIO_Pin_Set 	1
#define GPIO_Pin_Reset 	0

//@ref Pin configuration lock status
#define GPIO_Pin_Config_Lock_Enabled 	1
#define GPIO_Pin_Config_Lock_Error 		0


//----------------------------------------------------------------
//APIs supported by "MCAL GPIO driver"
//----------------------------------------------------------------

//Init/Deinit API
void MCAL_GPIO_Init(volatile GPIO_typedef *GPIOX, GPIO_Pin_Configuration_t *Pin_Configuration);
void MCAL_GPIO_Deinit(volatile GPIO_typedef *GPIOX);

//Pin API
uint8_t MCAL_GPIO_Read_Pin( volatile GPIO_typedef *GPIOX, uint16_t Pin_Number);
void MCAL_GPIO_Write_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number, uint8_t Pin_Value); //Pin_Value is set according to @ref  Pin Value
void MCAL_GPIO_Toggle_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number);
uint8_t MCAL_GPIO_Lock_Pin(volatile GPIO_typedef *GPIOX, uint16_t Pin_Number);

//Port API
uint16_t MCAL_GPIO_Read_Port(volatile GPIO_typedef *GPIOX);
void MCAL_GPIO_Write_Port(volatile GPIO_typedef *GPIOX, uint16_t Value);



#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
