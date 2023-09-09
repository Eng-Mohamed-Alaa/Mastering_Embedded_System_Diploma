
//includes
#include "I2C.h"

//I2C_master APIs implementation
void I2C_Init(uint32_t I2C_SCL_Speed)
{
	TWBR = (uint8_t)( ((F_CPU/I2C_SCL_Speed)- 16)/(2*I2C_SCL_Prescaler)); 
	switch (I2C_SCL_Prescaler)
	{
		case 1:
		TWSR = 0;
		break;
		case 4:
		TWSR = 1;		
		break;
		case 16:
		TWSR = 2;	
		break;
		case 64:
		TWSR = 3;
		break;
	}
	
	
}
void I2C_Start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ((!Read_Bit(TWCR, TWINT)) & (TWCR != 0x08));
}
void I2C_Master_TX(uint8_t Data)
{
	TWDR = Data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!Read_Bit(TWCR, TWINT));
}
void I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

uint8_t I2C_Master_RX(uint8_t ACK)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!Read_Bit(TWCR, TWINT));	
	return TWDR;
}


//I2C_slave APIs implementation
void I2C_Set_Address(uint8_t Address)
{
	TWAR = Address;
}
uint8_t I2C_Slave_RX(uint8_t ACK)
{
	uint8_t x=0;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!Read_Bit(TWCR, TWINT));
	while (TWSR != 0x80) 
		x=TWSR;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!Read_Bit(TWCR, TWINT));
	while (TWSR != 0x80)
		x=TWSR;
	return TWDR;
}
void I2C_Slave_TX(uint8_t Data)
{
	TWDR = Data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!Read_Bit(TWCR, TWINT));
}