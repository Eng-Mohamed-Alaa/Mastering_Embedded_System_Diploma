#ifndef INC_STM32F103C6_I2C_DRIVER_H_
#define INC_STM32F103C6_I2C_DRIVER_H_

//----------------------------------------------------------------
//includes
//----------------------------------------------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_RCC_Driver.h"
#include "stdint.h"

//----------------------------------------------------------------
//User type definitions
//----------------------------------------------------------------

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,	//the app layer should send the data (I2C_SlaveSendData) in this state
	I2C_EV_DATA_RCV	//the app layer should read the data (I2C_SlaveSendData) in this state

}Slave_State;

struct S_I2C_Slave_Device_Address
{

	uint16_t					Enable_Dual_ADD; //1-Enable	0-Disable
	uint16_t					Primary_Slave_Address;
	uint16_t					Secondary_Slave_Address;
	uint32_t					I2C_Addressing_Slave_Mode; //@ref I2C_Addressing_Slave_Mode

};

typedef struct
{

	uint32_t								I2C_SCLK_Speed;		//@ref I2C_SCLK_Speed
	uint32_t								I2C_Stretch_Mode;	//@ref I2C_Stretch_Mode
	uint32_t								I2C_Mode;			//@ref I2C_Mode
	struct S_I2C_Slave_Device_Address		I2C_Slave_Address;
	uint32_t								I2C_ACK_Control;	//@ref I2C_ACK_Control
	uint32_t								General_Call_Address_Detection; //@ref I2C_ENGC
	void(* P_Slave_Event_CallBack)(Slave_State state);

}I2C_Init_Typedef;

typedef enum { with_stop= 0, without_stop} Stop_Condition;
typedef enum {start = 0, repeated_start} Repeated_Start;
typedef enum {Disable_state = 0, Enable_state} Functional_State;
typedef enum {Reset = 0, Set} Flag_Status;
typedef enum {I2C_Direction_TX = 0, I2C_Direction_RX} I2C_Direction;

typedef enum {
	I2C_Flag_Busy,
	EV5,	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6,	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7,	//EV7: RXNE=1, cleared by reading DR register
	EV8,	//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1,	//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	Master_Byte_Transmitting = (uint32_t)(0x00070080) //covered flags: TRA, Busy, MSL, TXE
}Status;


//----------------------------------------------------------------
//Reference macros
//----------------------------------------------------------------

//****************************************************************
//@ref I2C_SCLK_Speed
//standard speed up to 100KHz
//fast speed up to 400KHz

//The following is the required sequence in master mode
//The peripheral input clock must be programmed in the I2C_CR2 register Bits 5:0 FREQ[5:0]: Peripheral clock frequency in order to generate correct timings
// Configure the clock control registers
// Configure the rise time register
// Program the I2C_CR1 register to enable the peripheral

//slave mode
//The peripheral input clock must be programmed in the I2C_CR2 register Bits 5:0 FREQ[5:0]: Peripheral clock frequency in order to generate correct timings.

#define I2C_SCLK_Speed_SM_50K					(50000U)
#define I2C_SCLK_Speed_SM_100K					(100000U)
#define I2C_SCLK_Speed_FM_200K					(200000U)	//fast mode is not supported yet
#define I2C_SCLK_Speed_FM_400K					(400000U)	//fast mode is not supported yet


//****************************************************************
//@ref I2C_Stretch_Mode
#define I2C_Stretch_Mode_Enable					(0U)
#define I2C_Stretch_Mode_Disable				I2C_CR1_NOSTRETCH


//****************************************************************
//@ref I2C_Mode
#define I2C_Mode_I2C							(0U)
#define I2C_Mode_SMBus							I2C_CR1_SMBUS


//****************************************************************
//@ref I2C_Addressing_Slave_Mode
#define I2C_Addressing_Slave_Mode_7Bits							(0U)
#define I2C_Addressing_Slave_Mode_10Bits						((uint16_t)(1<<15))


//****************************************************************
//@ref I2C_ACK_Control
#define I2C_ACK_Enable							(I2C_CR1_ACK)
#define I2C_ACK_Disable							((uint16_t)0)


//****************************************************************
//@ref I2C_ENGC
#define I2C_ENGC_Enable							(I2C_CR1_ENGC)
#define I2C_ENGC_Disable						(0U)

//----------------------------------------------------------------
//APIs supported by "MCAL I2C driver"
//----------------------------------------------------------------

void MCAL_I2C_Init(volatile I2C_typedef* I2Cx, I2C_Init_Typedef* I2C_Init_Struct);
void MCAL_I2C_Dinit(volatile I2C_typedef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(volatile I2C_typedef* I2Cx);
void MCAL_I2C_Master_TX(volatile I2C_typedef* I2Cx, uint16_t Device_Add, uint8_t *Data, uint32_t Data_Length, Stop_Condition Stop, Repeated_Start Start);
void MCAL_I2C_Master_RX(volatile I2C_typedef* I2Cx, uint16_t Device_Add, uint8_t *Data, uint32_t Data_Length, Stop_Condition Stop, Repeated_Start Start);
void MCAL_I2C_Slave_TX(volatile I2C_typedef* I2Cx, uint8_t Data);
uint8_t MCAL_I2C_Slave_RX(volatile I2C_typedef* I2Cx);


//----------------------------------------------------------------
//Generic APIs
//----------------------------------------------------------------
void I2C_Generate_Start(volatile I2C_typedef* I2Cx, Functional_State New_State,  Repeated_Start Start);
Flag_Status I2C_Get_Status(volatile I2C_typedef* I2Cx, Status Flag);
void I2C_Send_Address(volatile I2C_typedef* I2Cx, uint16_t Address, I2C_Direction Direction );
void I2C_Generate_Stop(volatile I2C_typedef* I2Cx, Functional_State New_State);
void I2C_Acknowledge_Config(volatile I2C_typedef* I2Cx, Functional_State New_State);



#endif /* INC_STM32F103C6_I2C_DRIVER_H_ */
