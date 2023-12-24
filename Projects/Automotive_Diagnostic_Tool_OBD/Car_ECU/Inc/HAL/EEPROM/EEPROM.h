/**
 ******************************************************************************
 * @file           : EEPROM.h
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 28, 2023
 ******************************************************************************
 */

#ifndef HAL_EEPROM_EEPROM_H_
#define HAL_EEPROM_EEPROM_H_



/************************************* include section ****************************************/
#include"../../../INC/MCAL/I2C/I2C.h"
/************************************* include section end ************************************/

/***************************************** macros section *************************************/


/*********************************** macros section end ***************************************/


/*********************************** user defined data types section **************************/


/*********************************** user defined data types section end **************************/



/****************************** function prototypes section****************************************/
void EEPROM_INIT(void);
void EEPROM_Write_byte(uint8 add_in_eeprom,uint8 data);
void EEPROM_Read_byte(uint8 add_in_eeprom,uint8 *data);
/****************************** function prototypes section end************************************/

#endif /* HAL_EEPROM_EEPROM_H_ */
