/*
 * Port_CFG.h
 *
 * Created: 10/20/2023 12:11:31 PM
 *  Author: computer store
 */ 

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#include <MCAL/PORT/PORT_Includes/Port.h>
/*those values are defined in Port.h file and are used to initialize the configuration of the pins in this file
	1- PIN_Input_Floating
	2- PIN_Input_pullup
	3- PIN_Output_High 
	3- PIN_Output_Low
*/


// PortA
#define	PORTA_PIN0_Mode			PIN_Input_Floating
#define	PORTA_PIN1_Mode			PIN_Output_Low
#define	PORTA_PIN2_Mode			PIN_Output_Low
#define	PORTA_PIN3_Mode			PIN_Output_Low	
#define	PORTA_PIN4_Mode			PIN_Output_Low
#define	PORTA_PIN5_Mode			PIN_Output_Low
#define	PORTA_PIN6_Mode			PIN_Output_Low
#define	PORTA_PIN7_Mode			PIN_Output_Low

// PortB
#define	PORTB_PIN0_Mode			PIN_Output_Low
#define	PORTB_PIN1_Mode			PIN_Output_Low
#define	PORTB_PIN2_Mode			PIN_Output_Low
#define	PORTB_PIN3_Mode			PIN_Output_Low
#define	PORTB_PIN4_Mode			PIN_Output_Low
#define	PORTB_PIN5_Mode			PIN_Output_Low
#define	PORTB_PIN6_Mode			PIN_Output_Low
#define	PORTB_PIN7_Mode			PIN_Output_Low

// PortC
#define	PORTC_PIN0_Mode			PIN_Output_Low
#define	PORTC_PIN1_Mode			PIN_Output_Low
#define	PORTC_PIN2_Mode			PIN_Output_Low
#define	PORTC_PIN3_Mode			PIN_Output_Low
#define	PORTC_PIN4_Mode			PIN_Output_Low
#define	PORTC_PIN5_Mode			PIN_Output_Low
#define	PORTC_PIN6_Mode			PIN_Output_Low
#define	PORTC_PIN7_Mode			PIN_Output_Low

// PortD
#define	PORTD_PIN0_Mode			PIN_Output_Low
#define	PORTD_PIN1_Mode			PIN_Output_Low
#define	PORTD_PIN2_Mode			PIN_Output_Low
#define	PORTD_PIN3_Mode			PIN_Output_Low
#define	PORTD_PIN4_Mode			PIN_Output_Low
#define	PORTD_PIN5_Mode			PIN_Output_Low
#define	PORTD_PIN6_Mode			PIN_Output_Low
#define	PORTD_PIN7_Mode			PIN_Output_Low


#endif /* PORT_CFG_H_ */