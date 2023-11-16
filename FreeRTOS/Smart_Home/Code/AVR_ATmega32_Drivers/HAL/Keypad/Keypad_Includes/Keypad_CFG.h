/*
 * Keypad_SRC.h
 *
 * Created: 10/25/2023 11:24:13 PM
 *  Author: computer store
 */ 

#ifndef KEYPAD_SRC_H_
#define KEYPAD_SRC_H_

//========================================================
//Includes
//========================================================
#include <Services/Std_types.h>
#include <MCAL/PORT/PORT_Includes/Port.h>

//========================================================
//ROW1 mode selection macro (define only one macro of the following and comment the other) 
//in Eta32 ROW1 has two modes of hardware connection short circuited and connected to PC5 
//========================================================
//#define Kepad_R1_Connect_GND			//in Eta32 ROW1 in the keypad is directly connected to the ground and PC5 is free to be used in another application
#define Kepad_R1_Connect_PIN			// ROW1 in the keypad is directly connected to PC5

//========================================================
//Keypad Configuration array
//========================================================
typedef struct
{
	volatile Puint8 Keypad_Rx_or_Cx_PORT;
	uint8 Keypad_Rx_or_Cx_PIN;
	uint8 Keypad_Rx_or_Cx_Mode;
}Keypad_CFG_t;

Keypad_CFG_t Keypad_CFG[8] = {
								{ PORTC_ADD, PORT_PIN0, PIN_Output_High},		//R1, this configuration for R1 has no effect if Kepad_R1_Connect_GND is selected
								{ PORTC_ADD, PORT_PIN1, PIN_Output_High},		//R2
								{ PORTC_ADD, PORT_PIN2, PIN_Output_High},		//R3
								{ PORTC_ADD, PORT_PIN3, PIN_Output_High},		//R4
								//columns are pulled up with external resistance and VCC in Eta32 so the best configuration is PIN_Input_Floating
								{ PORTC_ADD, PORT_PIN4, PIN_Input_Floating},	//C1
								{ PORTC_ADD, PORT_PIN5, PIN_Input_Floating},	//C2
								{ PORTC_ADD, PORT_PIN6, PIN_Input_Floating},	//C3
								{ PORTC_ADD, PORT_PIN7, PIN_Input_Floating}		//C4
							 };
//========================================================
//Keypad Switches values
//========================================================
#define Keypad_SW_NULL		'N'				//this value will be used to represent that no button is pressed so must be unique

uint8 Keypad_SW_Values[4][4] = {  
								{ '7', '8', '9', '/'}, //R1, {C1,C2,C3,C4}	note: if you choose Kepad_R1_Connect_GND in ROW1 mode selection macro this value has no effect
								{ '4', '5', '6', '*'}, //R2, {C1,C2,C3,C4}	
								{ '1', '2', '3', '-'}, //R3, {C1,C2,C3,C4}	
								{ 'c', '0', '=', '+'}  //R4, {C1,C2,C3,C4}	
							   };


#endif /* KEYPAD_SRC_H_ */