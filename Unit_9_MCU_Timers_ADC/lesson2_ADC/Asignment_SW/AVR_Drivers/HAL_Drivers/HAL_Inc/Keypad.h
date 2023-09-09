
#ifndef KEYPAD_H_
#define KEYPAD_H_

//--------------------------------------------------------
//includes
//--------------------------------------------------------
#include "memory_map.h"
#include "avr/io.h"
#include "util/delay.h"

//--------------------------------------------------------
//port mapping
//--------------------------------------------------------

#define Keypad_Row_Port_Output		PORTC
#define Keypad_Row_Port_Input		PINC
#define Keypad_Row_DATADIR			DDRC
#define Keypad_Col_Port_Output		PORTC
#define Keypad_Col_Port_Input		PINC
#define Keypad_Col_DATADIR			DDRC

//--------------------------------------------------------
//configuration macros
//--------------------------------------------------------

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

//--------------------------------------------------------
//Keypad APIs
//--------------------------------------------------------

void Keypad_Init(void);
uint8_t Keypad_Get_Button(void);

#endif /* AMIT_KEYPAD_H_ */


