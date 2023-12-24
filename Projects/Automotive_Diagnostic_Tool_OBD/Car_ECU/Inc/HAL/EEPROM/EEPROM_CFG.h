/*
 * EEPROM_CFG.h
 *
 *  Created on: Dec 6, 2023
 *      Author: ahmed radwan
 */

#ifndef HAL_EEPROM_EEPROM_CFG_H_
#define HAL_EEPROM_EEPROM_CFG_H_

#define EEPROM_I2C_SLAVE_ADD 0x50



I2C_Init_t EEPROM_i2c={
	.ClockSpeed=100000,
    .AddressingMode=I2C_ADDRESSINGMODE_7BIT,
	.DutyCycle=I2C_DUTYCYCLE_2,
	.Error_interrupt=I2C_enuINTERRUPT_DISABLE,
	.Event_interrupt=I2C_enuINTERRUPT_DISABLE,
	.GeneralCallMode=I2C_GENERALCALL_DISABLE,
	.StretchMode=I2C_CLOCK_STRETCH_DISABLE,
	.OwnAddress1=0x99,
	.AHB_BUS_SPEED=8
		};

#endif /* HAL_EEPROM_EEPROM_CFG_H_ */
