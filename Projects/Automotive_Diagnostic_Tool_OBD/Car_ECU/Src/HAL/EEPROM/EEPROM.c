/**
 ******************************************************************************
 * @file           : EEPROM.c
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 28, 2023
 ******************************************************************************
 */

#include"../../../INC/MCAL/I2C/I2C.h"
#include"../../../Inc/HAL/EEPROM/EEPROM.h"
#include "../../../Inc/HAL/EEPROM/EEPROM_CFG.h"

void EEPROM_INIT(void)
{
  I2C_INIT(&EEPROM_i2c);
}


void EEPROM_Write_byte(uint8 add_in_eeprom,uint8 data)
{
  I2C_send_start_cond();
  I2C_SEND_ADRESS_WRITE(EEPROM_I2C_SLAVE_ADD);
  I2C_WRITE_Byte(add_in_eeprom);
  I2C_WRITE_Byte(data);
  I2C_send_stop();
}

void EEPROM_Read_byte(uint8 add_in_eeprom,uint8 *data)
{
  I2C_send_start_cond();
  I2C_SEND_ADRESS_WRITE(EEPROM_I2C_SLAVE_ADD);
  I2C_WRITE_Byte(add_in_eeprom);
  I2C_START_Generate;
  //wait until  SB
  while( ! I2C_GET_START_STATUS );
  I2C_ACK_Disable;
  I2C_SEND_ADRESS_READ_WITH_ACK(EEPROM_I2C_SLAVE_ADD);
  I2C_READ_Byte(data);
  I2C_STOP_Generate;
}
