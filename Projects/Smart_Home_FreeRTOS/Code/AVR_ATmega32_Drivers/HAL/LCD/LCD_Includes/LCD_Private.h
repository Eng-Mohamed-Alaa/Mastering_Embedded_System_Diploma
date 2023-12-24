/*
 * LCD_Private.h
 *
 * Created: 10/21/2023 12:30:45 PM
 *  Author: computer store
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define LCD_DDRAM			0x80
#define LCD_CGRAM			0x40


static void LCD_Helper_Send_Data_Bus(uint8 Data);

#endif /* LCD_PRIVATE_H_ */