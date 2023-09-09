//includes
#include "UART.h"
#include "LCD.h"

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

//used in Polling mechanism >>> this method has better overrun handling than Periodic check mechanism but the processor is busy 
void UART_Send_Polling(uint8_t data)
{
	while(!Read_Bit(UCSRA, UDRE));
	UDR = data;
}

uint8_t UART_Receive_Polling(void)
{
	while(!Read_Bit(UCSRA, RXC));
	return UDR;
}


//used in Periodic check mechanism >>> this method provides more time for processor to work on something else but not good for large amount of data beacuse of data overrun
void UART_Send_Periodic(uint8_t data)
{
	if(Read_Bit(UCSRA, UDRE))
		UDR = data;
}

uint8_t UART_Receive_Periodic(void)
{
	if(Read_Bit(UCSRA, RXC))
		return UDR;
	return String_Received_End;
}


//used in interrupt mechanism >>>	// in case of small amount of data this method provides good time for processor to work on something else
							//but not good for large amount of data because processor will continuously be interrupted
							
void UART_Send_With_Interrupt(uint8_t data)
{
	UDR = data;
}

uint8_t UART_Receive_With_Interrupt(void)
{
	return UDR;
}


void UART_Send_uint32(uint32_t data)
{
	// 	method 1 by shifting with casting
	// 	for(uint8_t i=0; i < sizeof(uint32_t)*8; i+=8)
	// 	{	UART_Send( (uint8_t)(data >> i) );	}
	
	//method 2 by a pointer
	uint8_t *p_data = (uint8_t*) &data;
	for(uint8_t i=0; i < sizeof(uint32_t); i++)
	{	UART_Send_Polling(p_data[i]);	}
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

void UART_Send_string(uint8_t* data)
{
	uint8_t i = 0;
	while(data[i])
	{
		UART_Send_Polling(data[i]);
		++i;
	}
}

uint8_t UART_Receive_string(uint8_t* buffer)
{
	uint8_t Data_Received = 0;
	uint8_t i = 0;
	*buffer = UART_Receive_Periodic();
	while(buffer[i] != String_Received_End)
	{
		i++;
		buffer[i] = UART_Receive_Periodic();
		Data_Received = 1;
	}
	buffer[i] = 0; 
	return Data_Received;
}


ISR(USART_UDRE_vect)
{
	P_UART_UDRE_ISR_CallBack();
}


ISR(USART_RXC_vect)
{
	P_UART_RX_ISR_CallBack();
}