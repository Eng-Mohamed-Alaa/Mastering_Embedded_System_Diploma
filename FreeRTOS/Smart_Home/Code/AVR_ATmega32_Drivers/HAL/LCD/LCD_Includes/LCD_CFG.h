/*
 * LCD_CFG.h
 *
 * Created: 10/21/2023 12:31:02 PM
 *  Author: computer store
 */ 

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include <MCAL/PORT/PORT_Includes/Port.h>

//only one mode can be defined at a time
#define LCD_8Bit_Mode
//#define LCD_4Bit_Mode

#define LCD_RS_PIN			PORT_PIN1
#define LCD_EN_PIN			PORT_PIN2
//#define LCD_RW_PIN		PORT_PINx		//always ground in Eta32

#define LCD_RS_PORT			PORTA_ADD
#define LCD_EN_PORT			PORTA_ADD
//#define LCD_RW_PORT			PORTx_ADD	//always ground in Eta32


#define LCD_D0_PIN			PORT_PIN0	//not used in Eta32
#define LCD_D1_PIN			PORT_PIN1	//not used in Eta32
#define LCD_D2_PIN			PORT_PIN2	//not used in Eta32
#define LCD_D3_PIN			PORT_PIN3	//not used in Eta32
#define LCD_D4_PIN			PORT_PIN4
#define LCD_D5_PIN			PORT_PIN5
#define LCD_D6_PIN			PORT_PIN6
#define LCD_D7_PIN			PORT_PIN7


#define LCD_D0_PORT			PORTB_ADD	//not used in Eta32
#define LCD_D1_PORT			PORTB_ADD	//not used in Eta32
#define LCD_D2_PORT			PORTB_ADD	//not used in Eta32
#define LCD_D3_PORT			PORTB_ADD	//not used in Eta32
#define LCD_D4_PORT			PORTB_ADD
#define LCD_D5_PORT			PORTB_ADD
#define LCD_D6_PORT			PORTB_ADD
#define LCD_D7_PORT			PORTB_ADD


#endif /* LCD_CFG_H_ */