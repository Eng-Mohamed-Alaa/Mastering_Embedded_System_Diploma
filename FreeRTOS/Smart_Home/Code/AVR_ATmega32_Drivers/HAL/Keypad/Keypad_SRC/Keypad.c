/*
 * Keypad.c
 *
 * Created: 10/25/2023 11:25:18 PM
 *  Author: computer store
 */ 

//========================================================
//Includes: all header files needed are included inside <Keypad_Private.h>
//========================================================
#include <HAL/Keypad/Keypad_Includes/Keypad_Private.h>


void Keypad_Init(void)
{
	//in Eta 32 R1 Pin can be connected to ground directly or to certain PIN PC
	#ifdef Kepad_R1_Connect_PIN		
	Port_Set_Pin_Mode(Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_PIN, Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_Mode);
	#endif	
	
	for(uint8 PIN_Index = Keypad_R2_Index; PIN_Index <= Keypad_C4_Index; ++PIN_Index)
	{
		Port_Set_Pin_Mode(Keypad_CFG[PIN_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[PIN_Index].Keypad_Rx_or_Cx_PIN, Keypad_CFG[PIN_Index].Keypad_Rx_or_Cx_Mode);
	}
}

uint8 Keypad_Read_Character(uint8 Keypad_Read_Mode)
{
	// copy read mode from local variable to global variable
	Keypad_GRead_Mode = Keypad_Read_Mode;
	uint8 Keypad_Active_Col = Keypad_Col_NULL;
	uint8 Keypad_Active_Row = Keypad_R2_Index;
	uint8 SW_Value = Keypad_SW_NULL;
	
	#ifdef Kepad_R1_Connect_PIN
	DIO_Write_Channel(Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_PIN, PIN_Low);
	Keypad_Active_Col = Keypad_Get_Active_Column();
		DIO_Write_Channel(Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Keypad_R1_Index].Keypad_Rx_or_Cx_PIN, PIN_High);
	Keypad_Active_Row = Keypad_R1_Index;
	#endif
	
	if(Keypad_Active_Col == Keypad_Col_NULL)
	{
		for(uint8 Keypad_Row_Index = Keypad_R2_Index ; Keypad_Row_Index <= Keypad_R4_Index; ++Keypad_Row_Index)
		{
			DIO_Write_Channel(Keypad_CFG[Keypad_Row_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Keypad_Row_Index].Keypad_Rx_or_Cx_PIN, PIN_Low);
			Keypad_Active_Col = Keypad_Get_Active_Column();
			DIO_Write_Channel(Keypad_CFG[Keypad_Row_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Keypad_Row_Index].Keypad_Rx_or_Cx_PIN, PIN_High);
			if(Keypad_Active_Col != Keypad_Col_NULL)
			{
				Keypad_Active_Row = Keypad_Row_Index;
				break;
			}
		}
	}
	if (Keypad_Active_Col != Keypad_Col_NULL)
	{
		SW_Value = Keypad_SW_Values[Keypad_Active_Row][Keypad_Active_Col-4];
	}
	
	return SW_Value;	// if no Switch is pressed SW_Value is Keypad_SW_NULL defined in Keypad_CFg.h
}

static uint8 Keypad_Get_Active_Column()
{
	uint8 SW_Not_Pressed = 1;
	uint8 Keypad_Active_Col = Keypad_Col_NULL;
	
	for(uint8 Col_Index = Keypad_C1_Index;  Col_Index <= Keypad_C4_Index ; ++Col_Index)
	{
		// Keypad_Read_MultiPress mode returns the value of the button if it's pressed before the user release the button so if Keypad_Read is used in a loop it will read the same press several times
		if(Keypad_GRead_Mode == Keypad_Read_MultiPress)	
		{
			DIO_Read_Channel(Keypad_CFG[Col_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Col_Index].Keypad_Rx_or_Cx_PIN, &SW_Not_Pressed);
			if(!SW_Not_Pressed)
			{
				Keypad_Active_Col = Col_Index;
				break;	
			}
		}
		
		// Keypad_Read_Single_Press mode returns the value of the button if it's pressed after the user release the button so if Keypad_Read is used in a loop it will read the same press one time
		else if(Keypad_GRead_Mode == Keypad_Read_Single_Press)
		{				
			DIO_Read_Channel(Keypad_CFG[Col_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Col_Index].Keypad_Rx_or_Cx_PIN, &SW_Not_Pressed);
			
			if(!SW_Not_Pressed)
			{	Keypad_Active_Col = Col_Index;	}
				
			while(!SW_Not_Pressed)	//loop as long as the the button is still pressed until it's released and SW_Not_Pressed read one 
			{	DIO_Read_Channel(Keypad_CFG[Col_Index].Keypad_Rx_or_Cx_PORT, Keypad_CFG[Col_Index].Keypad_Rx_or_Cx_PIN, &SW_Not_Pressed);	}
			
			if (Keypad_Active_Col == Col_Index)
			{	break;	}
		}	
	}
	return	Keypad_Active_Col;
}


