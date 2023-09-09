
#ifndef STM32F103C6_USART_DRIVER_H_
#define STM32F103C6_USART_DRIVER_H_

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

typedef struct{
	uint8_t		UART_Mode;			//specifies TX/RX/Both enabled or disabled
									//this parameter must be set based on @ref UART_Mode_Define

	uint32_t 	BaudRate;			//specifies the UART communication baud rate
									//this parameter must be set based on @ref UART_BaudRate_Define

	uint16_t 	Payload_Length;		//specifies Number of the data bits transmitted or received in a frame
									//this parameter must be set based on @ref UART_Payload_Length_Define

	uint16_t	Parity;				//specifies the parity is odd/even/none
									//this parameter must be set based on @ref UART_Parity_Define

	uint16_t	StopBits;			//specifies Number of the stop bits transmitted or received in a frame
									//this parameter must be set based on @ref UART_StopBits_Define

	uint16_t	HW_Flow_CTRL;		//specifies CTS/RTS/Both enabled or disabled
									//this parameter must be set based on @ref UART_HW_Flow_CTRL_Define

	uint16_t	IRQ_Enable;			//specifies Which
									//this parameter must be set based on @ref UART_IRQ_Enable_Define

	void(*P_IRQ_CallBack)(void);	//Set the C function that will be called by the interrupt handler when the IRQ Happens
}UART_Config_t;

enum Polling_Mechanism{
	Enable,
	Disable
};

//----------------------------------------------------------------
//Reference macros
//----------------------------------------------------------------

//****************************************************************
//@ref UART_Mode_Define
#define UART_Mode_RX					(uint8_t)(1<<2)		// Bit 2 RX Receive
#define UART_Mode_TX					(uint8_t)(1<<3)		// Bit 3 TX send
#define UART_Mode_RX_TX					(uint8_t)(0b11<<2)


//****************************************************************
//@ref UART_BaudRate_Define
#define UART_BaudRate_2400				2400
#define UART_BaudRate_9600				9600
#define UART_BaudRate_19200				19200
#define UART_BaudRate_57600				57600
#define UART_BaudRate_115200			115200
#define UART_BaudRate_230400			230400
#define UART_BaudRate_460800			460800
#define UART_BaudRate_921600			921600
#define UART_BaudRate_2250000			2250000
#define UART_BaudRate_4500000			4500000


//****************************************************************
//@ref UART_Payload_Length_Define
#define UART_Payload_Length_8B			(uint16_t)(0)
#define UART_Payload_Length_9B			(uint16_t)(1<<12)


//****************************************************************
//@ref UART_Parity_Define
#define	UART_Parity_None				(uint16_t)(0)
#define	UART_Parity_Even				(uint16_t)(1<<10)
#define	UART_Parity_Odd					(uint16_t)(0b11 << 9)


//****************************************************************
//@ref UART_StopBits_Define
#define UART_StopBits_Half_Bit			(uint16_t)(1<<12)
#define UART_StopBits_1Bit				(uint16_t)(0)
#define UART_StopBits_1_Half_Bit		(uint16_t)(3<<12)
#define UART_StopBits_2Bit				(uint16_t)(2<<12)


//****************************************************************
//@ref UART_HW_Flow_CTRL_Define
#define UART_HW_Flow_CTRL_None			(uint16_t)(0)
#define UART_HW_Flow_CTRL_RTS			(uint16_t)(1<<8)
#define UART_HW_Flow_CTRL_CTS			(uint16_t)(1<<9)
#define UART_HW_Flow_CTRL_CTS_RTS		(uint16_t)(0b11<<8)


//****************************************************************
//@ref UART_IRQ_Enable_Define
#define UART_IRQ_Enable_None			(uint16_t)(0)		//
#define UART_IRQ_Enable_RXNEIE			(uint16_t)(1<<5)	//received data ready to be read or over run error detected
#define UART_IRQ_Enable_TC				(uint16_t)(1<<6)	//transmission complete
#define UART_IRQ_Enable_TXE				(uint16_t)(1<<7)	//transmission data register empty
#define UART_IRQ_Enable_PE				(uint16_t)(1<<8)	//Parity error



//----------------------------------------------------------------
//Generic Macros
//----------------------------------------------------------------

//****************************************************************
//Baud rate
#define USARTDIV(_PCLK_,_Baud_)					(uint32_t) (_PCLK_/(16*_Baud_))
#define USARTDIV_MUL100(_PCLK_,_Baud_)			(uint32_t) (25*_PCLK_/(4*_Baud_))
#define Mantissa_MUL100(_PCLK_,_Baud_)			(uint32_t) (USARTDIV(_PCLK_, _Baud_)*100)
#define Mantissa(_PCLK_,_Baud_)					(uint32_t) (USARTDIV(_PCLK_, _Baud_))
#define DIV_Fraction(_PCLK_,_Baud_)				(uint32_t) ((USARTDIV_MUL100(_PCLK_, _Baud_) - Mantissa_MUL100(_PCLK_, _Baud_)) *16/100)
#define UART_BRR_Register(_PCLK_,_Baud_)		((Mantissa(_PCLK_, _Baud_) << 4) | (DIV_Fraction(_PCLK_, _Baud_) & 0xF))



//----------------------------------------------------------------
//APIs supported by "MCAL USART driver"
//----------------------------------------------------------------

void MCAL_UART_Init(volatile USART_typedef* USARTx, UART_Config_t* UART_Config);
void MCAL_UART_Dinit(volatile USART_typedef* USARTx);
void MCAL_UART_GPIO_Set_Pins(volatile USART_typedef* USARTx);
void MCAL_UART_Send_Data(volatile USART_typedef* USARTx, uint16_t* P_TX_Buffer, enum Polling_Mechanism Polling_En);
void MCAL_UART_Receive_Data(volatile USART_typedef* USARTx, uint16_t* P_TX_Buffer, enum Polling_Mechanism Polling_En);
void MCAL_UART_Wait_TC(volatile USART_typedef* USARTx);

//to do MCAL_UART_LIN_Init()	//LIN
//to do MCAL_UsART_Init()		//synchronous
//to do MCAL_UART_LIN_Init()	//Multibuffer communication

#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
