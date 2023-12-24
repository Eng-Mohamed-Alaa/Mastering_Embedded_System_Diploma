/*
 * LCD.c
 *
 * Created: 10/21/2023 12:30:01 PM
 *  Author: computer store
 */ 


#include <HAL/LCD/LCD_Includes/LCD.h>
#include <HAL/LCD/LCD_Includes/LCD_Private.h>
#include <HAL/LCD/LCD_Includes/LCD_CFG.h>
#include <MCAL/PORT/PORT_Includes/Port.h>
#include <MCAL/DIO/DIO_Includes/DIO.h>
#include <Services/Bit_utils.h>

void LCD_Display_Character(uint8 Data)
{
	DIO_Write_Channel(LCD_RS_PORT, LCD_RS_PIN, PIN_High);
	//DIO_Write_Channel(LCD_RW_PORT, LCD_RW_PIN, PIN_Low);			//always ground in Eta32
	LCD_Helper_Send_Data_Bus(Data);
}

void LCD_Send_Command(uint8 Data)
{
	DIO_Write_Channel(LCD_RS_PORT, LCD_RS_PIN, PIN_Low);
	
	//DIO_Write_Channel(LCD_RW_PORT, LCD_RW_PIN, PIN_Low);			//always ground in Eta32
	
	LCD_Helper_Send_Data_Bus(Data);
}

void LCD_GoTO_XY(uint8 Line, uint8 Column)
{
	LCD_Send_Command(LCD_DDRAM + Line + Column);
}

void LCD_Clear(void)
{
	LCD_Send_Command(LCD_Display_Clear);
}

static void LCD_Helper_Send_Data_Bus(uint8 Data)
{
	
	uint8 Bit_Value = 0;
	
#ifdef	LCD_8Bit_Mode

	Bit_Value = GET_BIT(Data, 0);
	DIO_Write_Channel(LCD_D0_PORT, LCD_D0_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 1);
	DIO_Write_Channel(LCD_D1_PORT, LCD_D1_PIN, Bit_Value);		
	Bit_Value = GET_BIT(Data, 2);
	DIO_Write_Channel(LCD_D2_PORT, LCD_D2_PIN, Bit_Value);		
	Bit_Value = GET_BIT(Data, 3);
	DIO_Write_Channel(LCD_D3_PORT, LCD_D3_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 4);
	DIO_Write_Channel(LCD_D4_PORT, LCD_D4_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 5);
	DIO_Write_Channel(LCD_D5_PORT, LCD_D5_PIN, Bit_Value);	
	Bit_Value = GET_BIT(Data, 6);
	DIO_Write_Channel(LCD_D6_PORT, LCD_D6_PIN, Bit_Value);	
	Bit_Value = GET_BIT(Data, 7);
	DIO_Write_Channel(LCD_D7_PORT, LCD_D7_PIN, Bit_Value);	
#endif


#ifdef	LCD_4Bit_Mode
	
	//send higher nibble
	Bit_Value = GET_BIT(Data, 4);
	DIO_Write_Channel(LCD_D4_PORT, LCD_D4_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 5);
	DIO_Write_Channel(LCD_D5_PORT, LCD_D5_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 6);
	DIO_Write_Channel(LCD_D6_PORT, LCD_D6_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 7);
	DIO_Write_Channel(LCD_D7_PORT, LCD_D7_PIN, Bit_Value);

	//send Lower nibble
	Bit_Value = GET_BIT(Data, 0);
	DIO_Write_Channel(LCD_D4_PORT, LCD_D4_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 1);
	DIO_Write_Channel(LCD_D5_PORT, LCD_D5_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 2);
	DIO_Write_Channel(LCD_D6_PORT, LCD_D6_PIN, Bit_Value);
	Bit_Value = GET_BIT(Data, 3);
	DIO_Write_Channel(LCD_D7_PORT, LCD_D7_PIN, Bit_Value);
#endif	
}

void LCD_Kick1(void)
{
	DIO_Write_Channel(LCD_EN_PORT, LCD_EN_PIN, PIN_High);
}

void LCD_Kick2(void)
{
	DIO_Write_Channel(LCD_EN_PORT, LCD_EN_PIN, PIN_Low);
}
