/*
 * DIO.h
 *
 * Created: 10/20/2023 3:03:01 PM
 *  Author: computer store
 */ 

#ifndef DIO_H_
#define DIO_H_

#include <Services/Std_types.h>
#include <MCAL/DIO/DIO_Includes/DIO_Private.h>

//============================================================================
//user defined data types
//============================================================================
typedef enum{
	DIO_No_Error,
	DIO_Error_Invalid_PORT_Address,
	DIO_Error_Invalid_PIN_Number,
	DIO_Error_Invalid_PIN_Value,
	DIO_Error_Write_to_Input_PIN,
}DIO_Error_State;



#define PIN_Low		0
#define PIN_High	1


//APIs Prototypes
 DIO_Error_State DIO_Read_Channel_Direction(volatile Puint8 PORT_Address , uint8 PIN_Number, Puint8 PIN_Mode);
DIO_Error_State DIO_Write_Channel(volatile Puint8 PORT_Address, uint8 PIN_Number, uint8 PIN_Value);
DIO_Error_State DIO_Read_Channel(volatile Puint8 PORT_Address, uint8 PIN_Number, Puint8 PIN_Value);
DIO_Error_State DIO_Flip_Channel(volatile Puint8 PORT_Address, uint8 PIN_Number);
DIO_Error_State DIO_Write_PORT(volatile Puint8 PORT_Address, uint8 PORT_Value);
DIO_Error_State DIO_Read_PORT(volatile Puint8 PORT_Address, Puint8 PORT_Value);
#endif /* DIO_H_ */