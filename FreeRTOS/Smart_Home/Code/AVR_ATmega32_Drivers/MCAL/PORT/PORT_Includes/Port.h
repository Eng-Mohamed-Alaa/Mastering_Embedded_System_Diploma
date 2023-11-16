/*
 * port.h
 *
 * Created: 10/20/2023 12:10:23 PM
 *  Author: computer store
 */ 
#ifndef PORT_H_
#define PORT_H_

#include <Services/Std_types.h>

//============================================================================
//user defined data types
//============================================================================
typedef enum{
	PORT_No_Error,
	PORT_Error_Invalid_PORT_Address,
	PORT_Error_Invalid_PIN_Number,
	PORT_Error_Invalid_PIN_Direction,
	PORT_Error_Invalid_PIN_Mode,
}PORT_Error_State;

//============================================================================
//
//============================================================================



#define	PORTA_ADD			((volatile Puint8) 0x3B)
#define	PORTB_ADD			((volatile Puint8) 0x38)
#define	PORTC_ADD			((volatile Puint8) 0x35)
#define	PORTD_ADD			((volatile Puint8) 0x32)

#define	DDRA_ADD			((volatile Puint8) 0x3A)
#define	DDRB_ADD			((volatile Puint8) 0x37)
#define	DDRC_ADD			((volatile Puint8) 0x34)
#define	DDRD_ADD			((volatile Puint8) 0x31)

#define	PINA_ADD			((volatile Puint8) 0x39)
#define	PINB_ADD			((volatile Puint8) 0x36)
#define	PINC_ADD			((volatile Puint8) 0x33)
#define	PIND_ADD			((volatile Puint8) 0x30)

#define	PORTA_REG			(*PORTA_ADD)
#define	PORTB_REG			(*PORTB_ADD)
#define	PORTC_REG			(*PORTC_ADD)
#define	PORTD_REG			(*PORTD_ADD)

#define	DDRA_REG			(*DDRA_ADD)
#define	DDRB_REG			(*DDRB_ADD)
#define	DDRC_REG			(*DDRC_ADD)
#define	DDRD_REG			(*DDRD_ADD)

#define	PINA_REG			(*PINA_ADD)
#define	PINB_REG			(*PINB_ADD)
#define	PINC_REG			(*PINC_ADD)
#define	PIND_REG			(*PIND_ADD)

/*	1- PIN_Input_Floating
	2- PIN_Input_pullup
	3- PIN_Output_High 
	4- PIN_Output_Low
	5- PIN_Input
	6- PIN_Output
*/
#define	PIN_Input_Floating			0
#define PIN_Input_pullup			1
#define PIN_Output_High				2
#define PIN_Output_Low				3
#define PIN_Input					5
#define PIN_Output					6


//============================================================================
//Port_Pin_Numbers is used to set Pin_Number in API Port_Set_Pin_Direction and Port_Set_Pin_Mode
//============================================================================
#define PORT_PIN0		0
#define PORT_PIN1		1
#define PORT_PIN2		2
#define PORT_PIN3		3
#define PORT_PIN4		4
#define PORT_PIN5		5
#define PORT_PIN6		6
#define PORT_PIN7		7

//APIs Prototypes
void PORT_Init(void);
PORT_Error_State Port_Set_Pin_Direction(volatile Puint8 PORT_Address, uint8 PIN_Number, uint8 PIN_Mode);
PORT_Error_State Port_Set_Pin_Mode(volatile Puint8 PORT_Address, uint8 PIN_Number, uint8 PIN_Mode);


#endif /* PORT_H_ */