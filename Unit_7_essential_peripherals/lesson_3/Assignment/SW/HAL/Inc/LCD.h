
#ifndef LCD_H_
#define LCD_H_
//#define F_CPU 1000000UL

//--------------------------------------------------------
//includes
//--------------------------------------------------------

#include<STM32F103C6_GPIO_Driver.h>
#include<stdint.h>

//--------------------------------------------------------
//LCD port mapping
//--------------------------------------------------------

#define LCD_PORT				GPIOA
#define LCD_CTRL				GPIOA

//--------------------------------------------------------
//LCD configuration macros
//--------------------------------------------------------

#define LCD_EIGHT_BIT_MODE
//#define LCD_FOUR_BIT_MODE

#define LCD_DATA_shift		0 // in 8 bit mode 0 and in 4 bit mode 4


#define LCD_D0			GPIO_Pin0
#define LCD_D1			GPIO_Pin1
#define LCD_D2			GPIO_Pin2
#define LCD_D3			GPIO_Pin3
#define LCD_D4			GPIO_Pin4
#define LCD_D5			GPIO_Pin5
#define LCD_D6			GPIO_Pin6
#define LCD_D7			GPIO_Pin7

#define LCD_RS 			GPIO_Pin8
#define LCD_RW 			GPIO_Pin9
#define LCD_EN 			GPIO_Pin10

#define	LCD_Pin_Set 	GPIO_Pin_Set
#define	LCD_Pin_Reset 	GPIO_Pin_Reset


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
void LCD_WRITE_COMMAND(uint8_t command);
void LCD_WRITE_CHAR(uint8_t character);
void LCD_WRITE_STRING(char* string);
void LCD_Clear_Screen(void);
void LCD_GOTO_XY(uint8_t line, uint8_t position);


#endif /* LCD_H_ LCD_DataDir_CTRL*/



