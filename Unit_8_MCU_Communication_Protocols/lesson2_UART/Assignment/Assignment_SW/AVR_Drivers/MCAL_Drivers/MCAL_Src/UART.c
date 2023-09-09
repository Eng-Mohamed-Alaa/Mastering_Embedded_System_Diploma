//includes
#include "UART.h"

//UART APIs implementation
void UART_Init(void)
{
	//1-Baud rate configuration
	//at system frequency = 8 MHz
	//the baud rate will be 9600 bps if U2X pin = 0 and UBRRL = 51
	Set_Bit(UCSRC, URSEL);			// select the UCSRC register 
	Reset_Bit(UCSRC, UMSEL);		//Asynchronous mode
	Reset_Bit(UCSRA, U2X);			//U2X pin = 0 >>> normal speed mode
	UBRRL = 51;						//UBRRL = 51, 
	
	//2-Frame configuration
	//data = 8 bits
	Set_Bit(UCSRC, UCSZ0);
	Set_Bit(UCSRC, UCSZ1);
	Reset_Bit(UCSRB, UCSZ2);
	
	//no parity
	Reset_Bit(UCSRC, UPM0);
	Reset_Bit(UCSRC, UPM1);
	
	//stop = 1 bit
	Reset_Bit(UCSRC, USBS);

	//3-enable TX and RX of the UART 
	Set_Bit(UCSRB, TXEN);
	Set_Bit(UCSRB, RXEN);
}

void UART_Send(uint8_t data)
{
	while(!Read_Bit(UCSRA, UDRE));
	UDR = data;
}

uint8_t UART_Receive(void)
{
	while(!Read_Bit(UCSRA, RXC));
	return UDR;
}

void UART_Send_uint32(uint32_t data)
{
	// 	method 1 by shifting with casting
	// 	for(uint8_t i=0; i < sizeof(uint32_t)*8; i+=8)
	// 	{	UART_Send( (uint8_t)(data >> i) );	}
	
	//method 2 by a pointer
	uint8_t *p_data = &data;
	for(uint8_t i=0; i < sizeof(uint32_t); i++)
	{	UART_Send(p_data[i]);	}
}

uint32_t UART_Receive_uint32(void)
{
	uint32_t data=0;
// 	method 1 by shifting with casting
// 	for(uint8_t i=0; i < sizeof(uint32_t)*8; i+=8)
// 	{	data |= ((uint32_t)UART_Receive() << i) ;	}
	
	//method 2 by a pointer
	uint8_t *p_data = (uint8_t*) &data;
	for(uint8_t i=0; i < sizeof(uint32_t); i++)
	{	p_data[i] = UART_Receive();	}
	
	return data;
}