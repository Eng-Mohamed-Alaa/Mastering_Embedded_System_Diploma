
#ifndef STM32F103C6_SPI_DRIVER_H_
#define STM32F103C6_SPI_DRIVER_H_

//----------------------------------------------------------------
//includes
//----------------------------------------------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_RCC_Driver.h"
#include "stdint.h"


//----------------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------------

struct S_IRQ_SRC
{
	uint8_t TXE:1;	//TX buffer empty interrupt
	uint8_t RXNE:1;	//RX buffer not empty interrupt
	uint8_t ERRI:1;	//Error interrupt
	uint8_t Reserved:5;
};

//Configuration structure
typedef struct{

	uint16_t	Device_Mode;								//specifies the SPi operating mode
															//@ref SPI_Device_Mode

	uint16_t	Communication_Mode;							//specifies the SPI is (Full/Half)-duplex / simplex
															//@ref SPI_Communication_Mode

	uint16_t	Frame_Format;								//specifies the MSB/LSB is sent first
															//@ref SPI_Frame_Format

	uint16_t	Data_Size;									//specifies the number of bits to be sent 8/16 bits
															//@ref SPI_Data_Size

	uint16_t	CLK_Polarity;								//specifies the idle state of the clock High/Low
															//@ref SPI_CLK_Polarity

	uint16_t	CLK_Phase;									//specifies at which edge of the clock the sampling occurs
															//@ref SPI_CLK_Phase

	uint16_t	NSS; 										//specifies wether the NSS signal is managed by Hardware(NSS pin)/Software(SSI Bit enable)
															//@ref SPI_NSS

	uint16_t	SPI_BAUDRATE_Prescaler;						//specifies the baud rate prescaler value which is used to configure SCK of the SPI(master)
															//to define the rate the data is transmitted/received with
															//no need to set slave clock because it's driven by the master
															//you should configure the RCC module to provide the right clock for ABPx >>> to SPIx (x = [1:0])
															//@ref SPI_BAUDRATE_Prescaler

	uint16_t	IRQ_Enable;									//specifies the interrupt request is enabled or disabled for the configured SPI
															//@ref SPI_IRQ_Enable

	void(*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);		//holds the address of the function to be called once the interrupt occurs


}SPI_Config_t;


enum SPI_Polling_Mechanism{
	Polling_Enable,
	Polling_Disable
};



//----------------------------------------------------------------
//Reference macros
//----------------------------------------------------------------

//****************************************************************
//@ref SPI_Device_Mode
#define SPI_Device_Mode_Slave						(uint16_t)(0)
#define SPI_Device_Mode_Master						(uint16_t)(1<<2) //CR1. Bit 2 MSTR: Master selection


//****************************************************************
//@ref SPI_Communication_Mode
#define SPI_Direction_2Lines						(uint16_t)(0)
#define SPI_Direction_2Lines_Receive_Only			(uint16_t)(1<<10) //CR1.Bit 10 RXONLY: Receive only
#define SPI_Direction_1Lines_Receive_Only			(uint16_t)(1<<15) //CR1.Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_Direction_1Lines_Transmit_Only			(uint16_t)(1<<14 | 1<<15) //CR1.Bit 14 BIDIOE: Output enable in bidirectional mode & BIDIMODE: Bidirectional data mode enable


//****************************************************************
//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_Transmitted_First		(uint16_t)(0)
#define SPI_Frame_Format_LSB_Received_First			(uint16_t)(1<<7) //CR1.Bit 7 LSBFIRST: Frame format


//****************************************************************
//@ref SPI_Data_Size
#define SPI_Data_Size_8Bits							(uint16_t)(0)
#define SPI_Data_Size_16Bits						(uint16_t)(1<<11) //CR1.Bit 11 DFF: Data frame format


//****************************************************************
//@ref SPI_CLK_Polarity
#define SPI_CLK_Polarity_Idle_Low					(uint16_t)(0)
#define SPI_CLK_Polarity_Idle_High					(uint16_t)(1<<1) //CR1.Bit 1 CPOL: Clock polarity


//****************************************************************
//@ref SPI_CLK_Phase
#define SPI_CLK_Phase_Data_Capture_at_1st_Edge		(uint16_t)(0)
#define SPI_CLK_Phase_Data_Capture_at_2nd_Edge		(uint16_t)(1<<0) //CR1.Bit 0 CPHA: Clock phase


//****************************************************************
//@ref SPI_NSS

//Hardware
#define SPI_NSS_Hardware_Slave						(uint16_t)(0) //CR1.Bit 9 SSM: Software slave management
#define SPI_NSS_Hardware_Master_SS_Output_Enable	(uint16_t)(1<<2) //CR2.Bit 2 SSOE: SS output enable
#define SPI_NSS_Hardware_Master_SS_Output_Disable	~(uint16_t)(1<<2)//CR2.Bit 2 SSOE: SS output enable

//NSS is Driven by Software (Master/Slave)
#define SPI_NSS_Software_Reset						(uint16_t)(1<<9) //CR1.Bit 9 SSM: Software slave management
#define SPI_NSS_Software_set						(uint16_t)(1<<8 | 1<<9) //CR1.Bit 9 SSM: Software slave management & CR1.Bit 8 SSI: Internal slave select


//****************************************************************
//@ref SPI_BAUDRATE_Prescaler
#define SPI_BAUDRATE_Prescaler_2					(uint16_t)(0) 			//CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_4					(uint16_t)(0b001 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_8					(uint16_t)(0b010 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_16					(uint16_t)(0b011 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_32					(uint16_t)(0b100 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_64					(uint16_t)(0b101 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_128					(uint16_t)(0b110 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BAUDRATE_Prescaler_256					(uint16_t)(0b111 << 3) //CR1.Bits 5:3 BR[2:0]: Baud rate control


//****************************************************************
//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_None							(uint16_t)(0)
#define SPI_IRQ_Enable_TXEIE						(uint16_t)(1<<7) //CR2.Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RENEIE						(uint16_t)(1<<6) //CR2.Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE						(uint16_t)(1<<5) //CR2.Bit 5 ERRIE: Error interrupt enable


//----------------------------------------------------------------
//APIs supported by "MCAL SPI driver"
//----------------------------------------------------------------

void MCAL_SPI_Init(volatile SPI_typedef* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_Dinit(volatile SPI_typedef* SPIx);
void MCAL_SPI_GPIO_Set_Pins(volatile SPI_typedef* SPIx);
void MCAL_SPI_Send_Data(volatile SPI_typedef* SPIx, uint16_t* P_TX_Buffer, enum SPI_Polling_Mechanism Polling_En);
void MCAL_SPI_Receive_Data(volatile SPI_typedef* SPIx, uint16_t* P_TX_Buffer, enum SPI_Polling_Mechanism Polling_En);
void MCAL_SPI_TX_RX_Data(volatile SPI_typedef* SPIx, uint16_t* P_TX_Buffer, enum SPI_Polling_Mechanism Polling_En);


#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
