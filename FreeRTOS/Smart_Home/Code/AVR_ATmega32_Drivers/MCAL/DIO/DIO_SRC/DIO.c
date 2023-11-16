/*
 * DIO.c
 *
 * Created: 10/20/2023 3:02:46 PM
 *  Author: computer store
 */ 
#include <MCAL/PORT/PORT_Includes/Port.h>
#include <MCAL/DIO/DIO_Includes/DIO.h>
#include <MCAL/DIO/DIO_Includes/DIO_Private.h>
#include <MCAL/DIO/DIO_Includes/DIO_CFG.h>
#include <Services/Bit_utils.h>

 
 DIO_Error_State DIO_Read_Channel_Direction(volatile Puint8 PORT_Address , uint8 PIN_Number, Puint8 PIN_Mode)
{
	*PIN_Mode = PIN_Input;
	DIO_Error_State Error_state = DIO_No_Error;
	
	if(PORT_Address != PORTA_ADD && PORT_Address != PORTB_ADD && PORT_Address != PORTC_ADD && PORT_Address != PORTD_ADD)
	{
		Error_state = DIO_Error_Invalid_PORT_Address;
	}
	else if(PIN_Number > PORT_PIN7)
	{
		Error_state = DIO_Error_Invalid_PIN_Number;
	}
	
	else
	{
		volatile Puint8 DDRX_ADD= (Puint8)0;
		switch((uint16)PORT_Address)
		{
			case (uint16)PORTA_ADD:
			DDRX_ADD = DDRA_ADD;
			break;
			
			case (uint16)PORTB_ADD:
			DDRX_ADD = DDRB_ADD;
			break;

			case (uint16)PORTC_ADD:
			DDRX_ADD = DDRC_ADD;
			break;

			case (uint16)PORTD_ADD:
			DDRX_ADD = DDRD_ADD;
			break;
		}
		
		uint8 PIN_Value = GET_BIT(*DDRX_ADD, PIN_Number);
		if(PIN_Value)
			*PIN_Mode = PIN_Output;
	}
	
	return Error_state;
}


DIO_Error_State DIO_Write_Channel(volatile Puint8 PORT_Address, uint8 PIN_Number, uint8 PIN_Value)
{
	uint8 PIN_Mode;
	DIO_Error_State Error_state = DIO_Read_Channel_Direction(PORT_Address, PIN_Number, &PIN_Mode);
	
	if(Error_state == DIO_No_Error && PIN_Mode == PIN_Input)
	{
		Error_state = DIO_Error_Write_to_Input_PIN;
	}
	else if(Error_state == DIO_No_Error && PIN_Mode == PIN_Output)
	{
		if(PIN_Value == PIN_High)
			SET_BIT(*PORT_Address, PIN_Number);
		else if(PIN_Value == PIN_Low)
			CLR_BIT(*PORT_Address, PIN_Number);
		else
			Error_state = DIO_Error_Invalid_PIN_Value;
	}
	
	return Error_state;
}


//can read pin value whether the pin is input or output
DIO_Error_State DIO_Read_Channel(volatile Puint8 PORT_Address, uint8 PIN_Number, Puint8 PIN_Value)
{
	DIO_Error_State Error_state = DIO_No_Error;
	if(PORT_Address != PORTA_ADD && PORT_Address != PORTB_ADD && PORT_Address != PORTC_ADD && PORT_Address != PORTD_ADD)
	{
		Error_state = DIO_Error_Invalid_PORT_Address;
	}
	else if(PIN_Number > PORT_PIN7)
	{
		Error_state = DIO_Error_Invalid_PIN_Number;
	}
	else
	{
		volatile Puint8 PINX_ADD= (Puint8)0;
		switch((uint16)PORT_Address)
		{
			case (uint16)PORTA_ADD:
			PINX_ADD = PINA_ADD;
			break;
			
			case (uint16)PORTB_ADD:
			PINX_ADD = PINB_ADD;
			break;

			case (uint16)PORTC_ADD:
			PINX_ADD = PINC_ADD;
			break;

			case (uint16)PORTD_ADD:
			PINX_ADD = PIND_ADD;
			break;
		}
		
		*PIN_Value = GET_BIT(*PINX_ADD, PIN_Number);
	}
	return Error_state;
}

 DIO_Error_State DIO_Flip_Channel(volatile Puint8 PORT_Address, uint8 PIN_Number)
{
	uint8 PIN_Mode;
	DIO_Error_State Error_state = DIO_Read_Channel_Direction(PORT_Address, PIN_Number, &PIN_Mode);
	 
	if(Error_state == DIO_No_Error && PIN_Mode == PIN_Input)
	{
		Error_state = DIO_Error_Write_to_Input_PIN;
	}
	else if(Error_state == DIO_No_Error && PIN_Mode == PIN_Output)
	{
		TGL_BIT(*PORT_Address,PIN_Number);
	}
	 
	return Error_state;
	 
 }
 
 DIO_Error_State DIO_Write_PORT(volatile Puint8 PORT_Address, uint8 PORT_Value)
{
	uint8 PIN_Mode;
	DIO_Error_State Error_state = DIO_No_Error;
	
	if(PORT_Address != PORTA_ADD && PORT_Address != PORTB_ADD && PORT_Address != PORTC_ADD && PORT_Address != PORTD_ADD)
	{
		Error_state = DIO_Error_Invalid_PORT_Address;
	}
	else
	{
		for(uint8 PIN_Index = PORT_PIN0; PIN_Index <= PORT_PIN7; ++PIN_Index)
		{
			Error_state = DIO_Read_Channel_Direction(PORT_Address, PIN_Index, &PIN_Mode);
			if(PIN_Mode == PIN_Input)
			{	
				Error_state = DIO_Error_Write_to_Input_PIN;
				break;
			}
		}
	
		if(Error_state == DIO_No_Error)
		{
			*PORT_Address = PORT_Value;
		}
	}
	return Error_state;
}
 
 DIO_Error_State DIO_Read_PORT(volatile Puint8 PORT_Address, Puint8 PORT_Value)
{
	DIO_Error_State Error_state = DIO_No_Error;
	if(PORT_Address != PORTA_ADD && PORT_Address != PORTB_ADD && PORT_Address != PORTC_ADD && PORT_Address != PORTD_ADD)
	{
		Error_state = DIO_Error_Invalid_PORT_Address;
	}
	else
	{
		volatile Puint8 PINX_ADD= (Puint8)0;
		switch((uint16)PORT_Address)
		{
			case (uint16)PORTA_ADD:
			PINX_ADD = PINA_ADD;
			break;
			
			case (uint16)PORTB_ADD:
			PINX_ADD = PINB_ADD;
			break;

			case (uint16)PORTC_ADD:
			PINX_ADD = PINC_ADD;
			break;

			case (uint16)PORTD_ADD:
			PINX_ADD = PIND_ADD;
			break;
		}
		
		*PORT_Value = *PINX_ADD ;
	}
	return Error_state;	  
}