/*
 * Keypad_Private.h
 *
 * Created: 10/25/2023 11:23:52 PM
 *  Author: computer store
 */ 

#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_

//========================================================
//Includes: I include only this file in Keypad.c
//========================================================
#include <HAL/Keypad/Keypad_Includes/Keypad.h>
#include <HAL/Keypad/Keypad_Includes/Keypad_CFG.h>
#include <MCAL/PORT/PORT_Includes/Port.h>
#include <MCAL/DIO/DIO_Includes/DIO.h>
#include <Services/Std_types.h>
#include <Services/Std_types.h>

//========================================================
//Keypad Pins Indexes
//========================================================
#define Keypad_R1_Index		0
#define Keypad_R2_Index		1
#define Keypad_R3_Index		2
#define Keypad_R4_Index		3
#define Keypad_C1_Index		4
#define Keypad_C2_Index		5
#define Keypad_C3_Index		6
#define Keypad_C4_Index		7

#define Keypad_Col_NULL		0xFF


//========================================================
//static functions prototypes
//========================================================
static uint8 Keypad_Get_Active_Column();
static uint8 Keypad_GRead_Mode = Keypad_Read_Single_Press;


#endif /* KEYPAD_PRIVATE_H_ */