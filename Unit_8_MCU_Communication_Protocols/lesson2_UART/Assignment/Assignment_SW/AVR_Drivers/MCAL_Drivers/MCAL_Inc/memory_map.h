#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

//----------------------------------------------------------------------
//1-includes
//----------------------------------------------------------------------

#include <stdint.h>

//----------------------------------------------------------------------
//2-registers mapping
//----------------------------------------------------------------------

//***************************************
//PortA registers
//***************************************
#define PORTA	*(volatile uint8_t *)(0x3B)
#define DDRA	*(volatile uint8_t *)(0x3A)
#define PINA	*(volatile uint8_t *)(0x39)

//***************************************
//PortB registers
//***************************************
#define PORTB	*(volatile uint8_t *)(0x38)
#define DDRB	*(volatile uint8_t *)(0x37)
#define PINB	*(volatile uint8_t *)(0x36)

//***************************************
//PortC registers
//***************************************
#define PORTC	*(volatile uint8_t *)(0x35)
#define DDRC	*(volatile uint8_t *)(0x34)
#define PINC	*(volatile uint8_t *)(0x33)

//***************************************
//PortD registers
//***************************************
#define PORTD	*(volatile uint8_t *)(0x32)
#define DDRD	*(volatile uint8_t *)(0x31)
#define PIND	*(volatile uint8_t *)(0x30)

//***************************************
//USART registers
//***************************************
#define UDR		*(volatile uint8_t *)(0x2C)
#define UCSRA	*(volatile uint8_t *)(0x2B)
#define UCSRB	*(volatile uint8_t *)(0x2A)
#define UCSRC	*(volatile uint8_t *)(0x40) //UCSRC and UBRRH have the same address
#define UBRRL	*(volatile uint8_t *)(0x29)
#define UBRRH	*(volatile uint8_t *)(0x40)	//UCSRC and UBRRH have the same address

//----------------------------------------------------------------------
//3-Pins mapping
//----------------------------------------------------------------------

//***************************************
//USART registers: UCSRA Pins
//***************************************
#define MPCM	0
#define U2X		1
#define PE		2
#define DOR		3
#define FE		4
#define UDRE	5
#define TXC		6
#define RXC		7

//***************************************
//USART registers: UCSRB Pins
//***************************************
#define TXB8		0
#define RXB8		1
#define UCSZ2		2
#define TXEN		3
#define RXEN		4
#define UDRE		5
#define UDRIE		6
#define TXCIE		7
   
//***************************************
//USART registers: UCSRC Pins
//*************************************** 
#define UCPOL		0
#define UCSZ0		1
#define UCSZ1		2
#define USBS		3
#define UPM0		4
#define UPM1		5
#define UMSEL		6
#define URSEL		7	
	       
//generic macros
#define Set_Bit(Address, Bit_No)		(Address |= 1 << Bit_No)
#define Reset_Bit(Address, Bit_No)		(Address &= ~(1 << Bit_No))
#define Toggle_Bit(Address, Bit_No)		(Address ^= 1 << Bit_No)
#define Read_Bit(Address, Bit_No)		((Address >> Bit_No) & 1)


#endif 