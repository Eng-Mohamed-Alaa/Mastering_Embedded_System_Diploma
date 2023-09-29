
#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 8000000UL

//--------------------------------------------------------
//includes
//--------------------------------------------------------

#include <stdint.h>
#include <STM32F103C6_GPIO_Driver.h>
//--------------------------------------------------------
//port mapping
//--------------------------------------------------------

#define Keypad_Row_Port				GPIOB
#define Keypad_Col_Port				GPIOB

//--------------------------------------------------------
//configuration macros
//--------------------------------------------------------

#define R0 	GPIO_Pin0
#define R1 	GPIO_Pin1
#define R2 	GPIO_Pin3
#define R3  GPIO_Pin4
#define C0  GPIO_Pin5
#define C1 	GPIO_Pin6
#define C2 	GPIO_Pin7
#define C3 	GPIO_Pin8

#define Keypad_Pin_Set 		GPIO_Pin_Set
#define Keypad_Pin_Reset 	GPIO_Pin_Reset

//--------------------------------------------------------
//Keypad APIs
//--------------------------------------------------------

void Keypad_Init(void);
uint8_t Keypad_Get_Key(void);

#endif /* AMIT_KEYPAD_H_ */


