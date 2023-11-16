/*
 * Port.c
 *
 * Created: 10/20/2023 12:10:07 PM
 *  Author: computer store
 */ 
#include <MCAL/PORT/PORT_Includes/Port.h>
#include <MCAL/PORT/PORT_Includes/Port_CFG.h>
#include <MCAL/PORT/PORT_Includes/Port_Private.h>
#include <Services/Bit_utils.h>
#include <Services/Std_types.h>


void PORT_Init(void)
{
	
#undef PIN_Input_pullup	
#undef PIN_Output_High		
#undef PIN_Output_Low

#define PIN_Input_pullup	0
#define PIN_Output_High		1
#define PIN_Output_Low		1

	DDRA_REG = CONC(PORTA_PIN7_Mode,PORTA_PIN6_Mode,PORTA_PIN5_Mode,PORTA_PIN4_Mode,PORTA_PIN3_Mode,PORTA_PIN2_Mode,PORTA_PIN1_Mode,PORTA_PIN0_Mode);
	DDRB_REG = CONC(PORTB_PIN7_Mode,PORTB_PIN6_Mode,PORTB_PIN5_Mode,PORTB_PIN4_Mode,PORTB_PIN3_Mode,PORTB_PIN2_Mode,PORTB_PIN1_Mode,PORTB_PIN0_Mode);
	DDRC_REG = CONC(PORTC_PIN7_Mode,PORTC_PIN6_Mode,PORTC_PIN5_Mode,PORTC_PIN4_Mode,PORTC_PIN3_Mode,PORTC_PIN2_Mode,PORTC_PIN1_Mode,PORTC_PIN0_Mode);
	DDRD_REG = CONC(PORTD_PIN7_Mode,PORTD_PIN6_Mode,PORTD_PIN5_Mode,PORTD_PIN4_Mode,PORTD_PIN3_Mode,PORTD_PIN2_Mode,PORTD_PIN1_Mode,PORTD_PIN0_Mode);

#undef PIN_Input_pullup
#undef PIN_Output_High
#undef PIN_Output_Low

#define PIN_Input_pullup	1
#define PIN_Output_High		1
#define PIN_Output_Low		0

	PORTA_REG = CONC(PORTA_PIN7_Mode,PORTA_PIN6_Mode,PORTA_PIN5_Mode,PORTA_PIN4_Mode,PORTA_PIN3_Mode,PORTA_PIN2_Mode,PORTA_PIN1_Mode,PORTA_PIN0_Mode);
	PORTB_REG = CONC(PORTB_PIN7_Mode,PORTB_PIN6_Mode,PORTB_PIN5_Mode,PORTB_PIN4_Mode,PORTB_PIN3_Mode,PORTB_PIN2_Mode,PORTB_PIN1_Mode,PORTB_PIN0_Mode);
	PORTC_REG = CONC(PORTC_PIN7_Mode,PORTC_PIN6_Mode,PORTC_PIN5_Mode,PORTC_PIN4_Mode,PORTC_PIN3_Mode,PORTC_PIN2_Mode,PORTC_PIN1_Mode,PORTC_PIN0_Mode);
	PORTD_REG = CONC(PORTD_PIN7_Mode,PORTD_PIN6_Mode,PORTD_PIN5_Mode,PORTD_PIN4_Mode,PORTD_PIN3_Mode,PORTD_PIN2_Mode,PORTD_PIN1_Mode,PORTD_PIN0_Mode);

#undef PIN_Input_pullup
#undef PIN_Output_High
#undef PIN_Output_Low

#define PIN_Input_pullup	1
#define PIN_Output_High		2
#define PIN_Output_Low		3
}


PORT_Error_State Port_Set_Pin_Direction(volatile Puint8 PORT_Address, uint8 PIN_Number, uint8 PIN_Mode)
{
	PORT_Error_State Error_state = PORT_No_Error;

	if(PORT_Address != PORTA_ADD && PORT_Address != PORTB_ADD && PORT_Address != PORTC_ADD && PORT_Address != PORTD_ADD)
	{
		Error_state = PORT_Error_Invalid_PORT_Address;
	}
	else if(PIN_Number > PORT_PIN7)
	{
		Error_state = PORT_Error_Invalid_PIN_Number;
	}
	else if(PIN_Mode > PIN_Output)
	{
		Error_state = PORT_Error_Invalid_PIN_Direction;
	}
	
	else
	{
		volatile Puint8 DDRX_ADD= (volatile Puint8)0;
		switch((uint8)PORT_Address)
		{
			case (uint8)PORTA_ADD:
				DDRX_ADD = DDRA_ADD;
				break;
		
			case (uint8)PORTB_ADD:
				DDRX_ADD = DDRB_ADD;
				break;

			case (uint8)PORTC_ADD:
				DDRX_ADD = DDRC_ADD;
				break;

			case (uint8)PORTD_ADD:
				DDRX_ADD = DDRD_ADD;
				break;
		}
		
		switch(PIN_Mode)
		{
			case PIN_Input:		
				CLR_BIT(*DDRX_ADD,PIN_Number);
				break;
		
			case PIN_Output:
				SET_BIT(*DDRX_ADD,PIN_Number);
		}
	}
	
	return Error_state;
}

PORT_Error_State Port_Set_Pin_Mode(volatile Puint8 PORT_Address, uint8 PIN_Number, uint8 PIN_Mode)
{
	PORT_Error_State Error_state = PORT_No_Error;
	switch(PIN_Mode)
	{
		case PIN_Input_Floating:
		case PIN_Input_pullup:
		Error_state = Port_Set_Pin_Direction(PORT_Address, PIN_Number, PIN_Input);
		break;
		
		case PIN_Output_High:
		case PIN_Output_Low:
		Error_state = Port_Set_Pin_Direction(PORT_Address, PIN_Number, PIN_Output);
		break;
	}
	
	if(Error_state == PORT_No_Error)
	{	
		switch(PIN_Mode)
		{
			case PIN_Input_Floating:
			case PIN_Output_Low:
				CLR_BIT(*PORT_Address,PIN_Number);
				break;
				
			case PIN_Input_pullup:
			case PIN_Output_High:
				SET_BIT(*PORT_Address,PIN_Number);
				break;
		}
	}	
	return Error_state;
}
