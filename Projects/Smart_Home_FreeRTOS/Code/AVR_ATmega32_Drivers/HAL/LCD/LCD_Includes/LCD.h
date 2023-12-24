/*
 * LCD.h
 *
 * Created: 10/21/2023 12:30:29 PM
 *  Author: computer store
 */ 

#ifndef LCD_H_
#define LCD_H_
#include <Services/Std_types.h>

//LCD Commands
#define LCD_Display_Clear						0x01
#define LCD_Display_On							0x0C	
#define LCD_Display_Off							0x08
#define LCD_Shift_Cursor_Disp_fix				0x06	
#define LCD_Shift_Disp_Cursor_fix				0x05
#define LCD_8Bit								0x38
#define LCD_4Bit								0x28
#define LCD_Return_Home							0x02


#define LCD_Line1								0x00	
#define LCD_Line2								0x40
#define LCD_Line3								0x14
#define LCD_Line4								0x54

#define LCD_Col1								0
#define LCD_Col2								1
#define LCD_Col3								2
#define LCD_Col4								3
#define LCD_Col5								4
#define LCD_Col6								5
#define LCD_Col7								6
#define LCD_Col8								7
#define LCD_Col9								8
#define LCD_Col10								9
#define LCD_Col11								10
#define LCD_Col12								11
#define LCD_Col13								12
#define LCD_Col14								13
#define LCD_Col15								14
#define LCD_Col16								15
#define LCD_Col17								16
#define LCD_Col18								17
#define LCD_Col19								18
#define LCD_Col20								19


void LCD_Init(void);
void LCD_Display_Character(uint8 Data);
void LCD_Display_String(const Puint8 Data);
void LCD_Display_Number(unsigned long long Data);
void LCD_Send_Command(uint8 Data);
void LCD_GoTO_XY(uint8 Line, uint8 Column);
void LCD_Create_Custom_Character(Puint8 Custome_Character, uint8 Postion_Index);
void LCD_Clear(void);
void LCD_Kick1(void);
void LCD_Kick2(void);

#endif /* LCD_H_ */