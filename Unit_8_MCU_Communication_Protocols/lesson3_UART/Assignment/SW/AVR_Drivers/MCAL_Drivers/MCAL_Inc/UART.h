
#ifndef UART_H_
#define UART_H_

//includes
#include "memory_map.h"
#include "stdint.h"
#include "avr/interrupt.h"
//interrupt call back function pointer
void(*P_UART_UDRE_ISR_CallBack)(void) ;
void(*P_UART_RX_ISR_CallBack)(void) ;


//interrupt enable/disable macros

#define UART_ISR_RXCIE_Enable()		Set_Bit(UCSRB, RXCIE)
#define UART_ISR_TXCIE_Enable()		Set_Bit(UCSRB, TXCIE)
#define UART_ISR_UDRIE_Enable()		Set_Bit(UCSRB, UDRIE)
#define UART_ISR_RXCIE_Disable()	Reset_Bit(UCSRB, RXCIE)
#define UART_ISR_TXCIE_Disable()	Reset_Bit(UCSRB, TXCIE)
#define UART_ISR_UDRIE_Disable()	Reset_Bit(UCSRB, UDRIE)

//Generic macros
#define String_Received_End	'\r'	//enter character is '\r'


//UART APIs prototypes
void UART_Init(void);
void UART_Send(uint8_t data);
uint8_t UART_Receive(void);
void UART_Send_uint32(uint32_t data);
uint32_t UART_Receive_uint32(void);
void UART_Send_string(uint8_t* data);
uint8_t UART_Receive_string(uint8_t* buffer);
void UART_Send_With_Interrupt(uint8_t data);
uint8_t UART_Receive_With_Interrupt(void);


#endif