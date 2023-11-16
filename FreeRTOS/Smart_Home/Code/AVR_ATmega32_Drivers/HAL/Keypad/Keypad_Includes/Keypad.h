/*
 * Keypad.h
 *
 * Created: 10/25/2023 11:25:05 PM
 *  Author: computer store
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

//========================================================
//Includes
//========================================================
#include <Services/Std_types.h>

//========================================================
//Configuration macros
//========================================================
#define Keypad_Read_Single_Press	0
#define Keypad_Read_MultiPress		1

//========================================================
//Keypad APIs prototypes
//========================================================
void Keypad_Init(void);
uint8 Keypad_Read_Character(uint8 Keypad_Read_Mode);

#endif /* KEYPAD_H_ */