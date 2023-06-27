
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

static uint16_t Keypad_Row_Pin[] = {R0, R1, R2, R3};
static uint16_t Keypad_Col_Pin[] = {C0, C1, C2, C3};

//--------------------------------------------------------
//static functions prototype
//--------------------------------------------------------
static uint8_t Keypad_Get_Value(uint8_t Row_index, uint8_t Col_index);

//--------------------------------------------------------
//API implementation
//--------------------------------------------------------

void Keypad_Init(void)
{
	GPIO_Pin_Configuration_t Keypad_Pin_Config;

	//Keypad rows and columns are set as output push-pull
	Keypad_Pin_Config.GPIO_Pin_Mode = GPIO_Mode_Output_PP;
	Keypad_Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;

	Keypad_Pin_Config.GPIO_Pin_Number = R0;
	MCAL_GPIO_Init(Keypad_Row_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = R1;
	MCAL_GPIO_Init(Keypad_Row_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = R2;
	MCAL_GPIO_Init(Keypad_Row_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = R3;
	MCAL_GPIO_Init(Keypad_Row_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = C0;
	MCAL_GPIO_Init(Keypad_Col_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = C1;
	MCAL_GPIO_Init(Keypad_Col_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = C2;
	MCAL_GPIO_Init(Keypad_Col_Port, &Keypad_Pin_Config);
	Keypad_Pin_Config.GPIO_Pin_Number = C3;
	MCAL_GPIO_Init(Keypad_Col_Port, &Keypad_Pin_Config);

	//Keypad columns are set to 1
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, R0, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, R1, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, R2, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, R3, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, C0, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, C1, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, C2, Keypad_Pin_Set);
	MCAL_GPIO_Write_Pin(Keypad_Col_Port, C3, Keypad_Pin_Set);
}

uint8_t Keypad_Get_Key(void)
{
	uint8_t C,R;
	for(C=0; C < Columns_NO; C++)
	{
		//Reset column to zero to check if a row value is changed by a key press , (key press + column =0) >>> Row = 0
		MCAL_GPIO_Write_Pin(Keypad_Col_Port, Keypad_Col_Pin[C], Keypad_Pin_Reset);
		for(R=0; R < Rows_NO; R++)
		{
			if( MCAL_GPIO_Read_Pin(Keypad_Row_Port, Keypad_Row_Pin[R]) == 0)
			{
				while( (MCAL_GPIO_Read_Pin(Keypad_Row_Port, Keypad_Row_Pin[R]) & 1) == 0);  //single press
				MCAL_GPIO_Write_Pin(Keypad_Col_Port, Keypad_Col_Pin[C], Keypad_Pin_Set);
				return Keypad_Get_Value(R,C);
			}
		}
		MCAL_GPIO_Write_Pin(Keypad_Col_Port, Keypad_Col_Pin[C], Keypad_Pin_Set);
	}
	return 0; //no press
}

//--------------------------------------------------------
//static functions implementation
//--------------------------------------------------------

static uint8_t Keypad_Get_Value(uint8_t Row_index, uint8_t Col_index)
{
	if(Row_index == 0){
		switch (Col_index)
		{
		case 0: return '7';
		case 1: return '8';
		case 2: return '9';
		case 3: return '/';
		}
	}
	else if(Row_index == 1){
		switch (Col_index)
		{
		case 0: return '4';
		case 1: return '5';
		case 2:	return '6';
		case 3: return '*';
		}
	}
	else if(Row_index == 2){
		switch (Col_index)
		{
		case 0: return '1';
		case 1: return '2';
		case 2: return '3';
		case 3: return '-';
		}
	}

	else if(Row_index == 3){
		switch (Col_index)
		{
		case 0: return 'c'; //clear
		case 1: return '0';
		case 2: return '=';
		case 3:	return '+';
		}
	}
	return 0;
}
