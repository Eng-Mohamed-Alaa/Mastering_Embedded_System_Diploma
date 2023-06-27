
//--------------------------------------------------------
//includes
//--------------------------------------------------------

#include "Keypad.h"

//--------------------------------------------------------
//Macros
//--------------------------------------------------------
#define Columns_NO	4
#define Rows_NO		4

//--------------------------------------------------------
//Global variables
//--------------------------------------------------------

static uint8_t Keypad_Row_Pin[] = {R0, R1, R2, R3}; 
static uint8_t Keypad_Col_Pin[] = {C0, C1, C2, C3};

//--------------------------------------------------------
//static functions prototype
//--------------------------------------------------------
static uint8_t Keypad_Get_Value(uint8_t Row_index, uint8_t Col_index);

//--------------------------------------------------------
//API implementation
//--------------------------------------------------------

void Keypad_Init(void)
{
	//Keypad ROWs are set as input 
	Keypad_Row_DATADIR &= ~(1 << R0 | 1 << R1 | 1 << R2 | 1 << R3);
	
	//pull-up resistance are activated for Keypad ROWs (1)
	Keypad_Row_Port_Output |= (1 << R0 | 1 << R1 | 1 << R2 | 1 << R3);
	 
	//Keypad columns are set as output
	Keypad_Col_DATADIR |= (1 << C0 | 1 << C1 | 1 << C2 | 1 << C3);
	
	//Keypad columns are set to 1
	Keypad_Col_Port_Output |= (1 << C0 | 1 << C1 | 1 << C2 | 1 << C3);
}

uint8_t Keypad_Get_Button(void)
{
	uint8_t C,R;
	for(C=0; C < Columns_NO; C++)
	{
		//Reset column to zero to check if a row value is changed by a button press , (button press + column =0) >>> Row = 0  
		Keypad_Col_Port_Output &= ~(1 << Keypad_Col_Pin[C]);
		for(R=0; R < Rows_NO; R++)
		{
			if( ( (Keypad_Row_Port_Input >> Keypad_Row_Pin[R]) & 1) == 0)
			{
				while(( (Keypad_Row_Port_Input >> Keypad_Row_Pin[R]) & 1) == 0);  //single press
				Keypad_Col_Port_Output |= (1 << Keypad_Col_Pin[C]);
				return Keypad_Get_Value(R,C);
			}
		}
		Keypad_Col_Port_Output |= (1 << Keypad_Col_Pin[C]);
	}
	return 0; //no press
}

//--------------------------------------------------------
//static functions implementation
//--------------------------------------------------------

static uint8_t Keypad_Get_Value(uint8_t Row_index, uint8_t Col_index)
{
	if(Row_index == 0)
	{
		switch (Col_index)
		{
		case 0: return '7';
		case 1: return '8';
		case 2: return '9';
		case 3: return '/';
		}
	}
	else if(Row_index == 1)
	{
		switch (Col_index)
		{
		case 0: return '4';
		case 1: return '5';
		case 2:	return '6';
		case 3: return '*';
		}
	}
	else if(Row_index == 2)
	{
		switch (Col_index)
		{
		case 0: return '1';
		case 1: return '2';
		case 2: return '3';
		case 3: return '-';
		}
	}
	
	else if(Row_index == 3)
	{
		switch (Col_index)
		{
		case 0: return 'c'; //clear
		case 1: return '0';
		case 2: return '=';
		case 3:	return '+';
		}
	}
}