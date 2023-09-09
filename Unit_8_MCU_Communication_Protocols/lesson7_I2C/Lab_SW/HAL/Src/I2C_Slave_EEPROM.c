
//--------------------------------------------------------
//includes
//--------------------------------------------------------

#include <I2C_Slave_EEPROM.h>

void EEPROM_Init(void)
{
	I2C_Init_Typedef I2C1_CFG;

	//set I2C1 configurations to act as a master
	I2C1_CFG.General_Call_Address_Detection = I2C_ENGC_Enable;
	I2C1_CFG.I2C_ACK_Control = I2C_ACK_Enable ;
	I2C1_CFG.I2C_Mode = I2C_Mode_I2C;
	I2C1_CFG.I2C_SCLK_Speed = I2C_SCLK_Speed_SM_100K;
	I2C1_CFG.I2C_Stretch_Mode = I2C_Stretch_Mode_Enable;
	I2C1_CFG.P_Slave_Event_CallBack = NULL;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C1_CFG);
}

uint8_t	EEPROM_Write_Nbytes(uint16_t Memory_Address, uint8_t* Data, uint8_t Data_Length)
{
	uint8_t i, buffer[257];
	buffer[0] = (uint8_t)(Memory_Address >> 8); //the upper byte of the memory address
	buffer[1] = (uint8_t)Memory_Address ; //the upper byte of the memory address

	for(i=2; i < Data_Length+2; ++i)
	{	buffer[i] = Data[i-2];	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, (Data_Length+2), with_stop, start);
	return 0;
}

uint8_t	EEPROM_Read_Nbytes(uint16_t Memory_Address, uint8_t* Data, uint8_t Data_Length)
{
	uint8_t buffer[257];
	buffer[0] = (uint8_t)(Memory_Address >> 8); //the upper byte of the memory address
	buffer[1] = (uint8_t)Memory_Address ; //the upper byte of the memory address

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, 2, without_stop, start);
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, Data, Data_Length, with_stop, repeated_start);
	return 0;

}
