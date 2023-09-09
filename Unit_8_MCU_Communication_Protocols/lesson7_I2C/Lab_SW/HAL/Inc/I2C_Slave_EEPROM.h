#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_

//--------------------------------------------------------
//includes
//--------------------------------------------------------

#include <stdint.h>
#include <STM32F103C6_I2C_Driver.h>

//--------------------------------------------------------
//configuration macros
//--------------------------------------------------------

#define EEPROM_Slave_Address	0x2A

//--------------------------------------------------------
//EEPROM APIs
//--------------------------------------------------------

void EEPROM_Init(void);
uint8_t	EEPROM_Write_Nbytes(uint16_t Memory_Address, uint8_t* Data, uint8_t Data_Length);
uint8_t	EEPROM_Read_Nbytes(uint16_t Memory_Address, uint8_t* Data, uint8_t Data_Length);


#endif /* INC_I2C_SLAVE_EEPROM_H_ */
