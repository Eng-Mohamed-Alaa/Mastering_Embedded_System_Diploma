#ifndef I2C_H_
#define I2C_H_

//includes
#include "memory_map.h"
#include "stdint.h"

//configuration macros
#define I2C_SCL_Prescaler	1	//	can be a value of (1,4,16,64)


//I2C_master APIs prototypes
void I2C_Init(uint32_t I2C_SCL_Speed);
void I2C_Start(void);
void I2C_Master_TX(uint8_t Data);
void I2C_Stop(void);
uint8_t I2C_Master_RX(uint8_t ACK);



//I2C_slave APIs prototypes
void I2C_Set_Address(uint8_t Address);
uint8_t I2C_Slave_RX(uint8_t ACK);
void I2C_Slave_TX(uint8_t Data);



#endif /* I2C_H_ */