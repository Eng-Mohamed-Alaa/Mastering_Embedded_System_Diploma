#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

#define F_CPU 8000000UL


//----------------------------------------------------------------------
//1-includes
//----------------------------------------------------------------------

#include <stdint.h>
#include <util/delay.h>


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
#define UDRIE		5
#define TXCIE		6
#define RXCIE		7 
   
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


//Global interrupt enable/disable >>> //bit No 7 in SREG(0x5F) reg must be set to allow the enabled interrupts in each peripheral to be enabled globaly in the MCU 
									 //if the bit is cleared the interrupts will not be enabled globally even if they are enabled in their peripheral
#define Global_ISR_Enable()	(*(volatile uint8_t*)(0x5F) |= 1 << 7)	
	
	      
//generic macros
#define Set_Bit(Reg, Bit_No)		(Reg |= 1 << Bit_No)
#define Reset_Bit(Reg, Bit_No)		(Reg &= ~(1 << Bit_No))
#define Toggle_Bit(Reg, Bit_No)		(Reg ^= 1 << Bit_No)
#define Read_Bit(Reg, Bit_No)		((Reg >> Bit_No) & 1)


#endif 