
#ifndef LCD_H_
#define LCD_H_
//#define F_CPU 1000000UL

//--------------------------------------------------------
//includes
//--------------------------------------------------------

#include<avr/io.h>
#include<util/delay.h>

//--------------------------------------------------------
//LCD port mapping
//--------------------------------------------------------

#define LCD_PORT				PORTA			
#define LCD_DataDir_PORT		DDRA
#define LCD_CTRL				PORTB
#define LCD_DataDir_CTRL		DDRB
#define LCD_Port_Input			PINA


//--------------------------------------------------------
//LCD configuration macros
//--------------------------------------------------------

//#define LCD_EIGHT_BIT_MODE
#define LCD_FOUR_BIT_MODE

#define LCD_DATA_shift		4 // in 8 bit mode 0 and in 4 bit mode 4

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

// ********************************************************
//command section >>> used as input in LCD_WRITE_COMMAND function

#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_ENTRY_MODE								(0x06)


//--------------------------------------------------------
//LCD APIs
//--------------------------------------------------------
void LCD_INIT();
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char character);
void LCD_WRITE_STRING(char* string);
void LCD_Clear_Screen(void);
void LCD_GOTO_XY(unsigned char line, unsigned char position);


#endif /* LCD_H_ LCD_DataDir_CTRL*/



