

#ifndef KEYPAD_H
#define KEYPAD_H

#define KEY_NOT_PRESSED		0x9F

typedef enum{
	KEYPAD_ERROR_FREE,
	NO_KEY_PRESSED
}ERROR_KEYPAD_STATUS;

void KEYPAD_voidInit(void);
ERROR_KEYPAD_STATUS KEYPAD_FindKey(uint8 *Loc_keyPress);
void KEYPAD_ReadPins(uint8 *value);
void KEYPAD_WritrPin(uint8 value);



#endif 
