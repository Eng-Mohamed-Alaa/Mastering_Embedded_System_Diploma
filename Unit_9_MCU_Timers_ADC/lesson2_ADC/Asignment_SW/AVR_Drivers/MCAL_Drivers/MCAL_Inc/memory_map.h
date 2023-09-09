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

#define SFIOR	*(volatile uint8_t *)(0x50)

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


//***************************************
//SPI registers
//***************************************
#define SPDR	*(volatile uint8_t *)(0x2F)
#define SPSR	*(volatile uint8_t *)(0x2E)
#define SPCR	*(volatile uint8_t *)(0x2D)


//***************************************
//I2C registers
//***************************************
#define TWCR	*(volatile uint8_t *)(0x56)
#define TWDR	*(volatile uint8_t *)(0x23)
#define TWAR	*(volatile uint8_t *)(0x22)
#define TWSR	*(volatile uint8_t *)(0x21)
#define TWBR	*(volatile uint8_t *)(0x20)


//***************************************
//Timer0 registers
//***************************************
#define OCR0	*(volatile uint8_t *)(0x5C)
#define TIMSK	*(volatile uint8_t *)(0x59)
#define TIFR	*(volatile uint8_t *)(0x58)
#define TCCR0	*(volatile uint8_t *)(0x53)
#define TCNT0	*(volatile uint8_t *)(0x52)

//***************************************
//Watchdog timer registers
//***************************************
#define WDTCR	*(volatile uint8_t *)(0x41)

//***************************************
//ADC registers
//***************************************
#define ADCL	*(volatile uint8_t *)(0x24)
#define ADCH	*(volatile uint8_t *)(0x25)
#define ADCSRA	*(volatile uint8_t *)(0x26)
#define ADMUX	*(volatile uint8_t *)(0x27)


//----------------------------------------------------------------------
//3-Pins mapping
//----------------------------------------------------------------------


//***************************************
//register: SFIOR Pins
//***************************************
#define PUD		2
#define ADTSn	5		//Bits 7:5 – ADTSn: ADC Auto Trigger Source [n = 2:0]

//***************************************
//USART register: UCSRA Pins
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
//USART register: UCSRB Pins
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
//USART register: UCSRC Pins
//*************************************** 
#define UCPOL		0
#define UCSZ0		1
#define UCSZ1		2
#define USBS		3
#define UPM0		4
#define UPM1		5
#define UMSEL		6
#define URSEL		7	


//***************************************
//SPI register: SPSR Pins
//***************************************
#define SPI2X		0
#define WCOL		6
#define SPIF		7

//***************************************
//SPI register: SPCR Pins
//***************************************
#define SPR0		0
#define SPR1		1
#define CPHA		2
#define CPOL		3
#define MSTR		4
#define DORD		5
#define SPE			6
#define SPIE		7

//***************************************
//SPI Interfacing pins referred to portB
//***************************************
#define SCK			7
#define MISO		6
#define MOSI		5
#define SS			4

//***************************************
//I2C register: TWCR Pins
//***************************************
#define TWIE		0
#define TWEN		2
#define TWWC		3
#define TWSTO		4
#define TWSTA		5
#define TWEA		6
#define TWINT		7

//***************************************
//I2C register: TWAR Pins
//***************************************
#define TWGCE		0
#define TWAn		(0X7F << 1)
 
//***************************************
//I2C register: TWSR Pins
//***************************************
#define TWPSn		(0x3)
#define TWSn		(0x1F << 3)
 
//***************************************
//Timer0 register: TIMSK Pins
//***************************************
#define TOIE0		0
#define OCIE0		1
      

//***************************************
//Timer0 register: TIFR Pins
//***************************************
#define TOV0		0
#define OCF0		1

//***************************************
//Timer0 register: TCCR0 Pins
//***************************************
#define CS0n		0
#define WGM01		3
#define COM0n		4
#define WGM00		6
#define FOC0		7

//***************************************
//Watchdog register: WDTCR Pins
//***************************************
#define WDPn		0
#define WDE			3
#define WDTOE		4

//***************************************
//ADC register: ADMUX Pins
//***************************************
#define MUXn		0	//Bits 4:0 – MUXn:?Analog Channel Selection [n = 4:0]
#define ADLAR		5	//Bit 5 – ADLAR:?ADC Left Adjust Result
#define REFSn		6	//Bits 7:6 – REFSn:?Reference Selection [n = 1:0]


//***************************************
//ADC register: ADCSRA Pins
//***************************************
#define ADPSn		0	//Bits 2:0 – ADPSn:?ADC Prescaler Select [n = 2:0]
#define ADIE		3	//Bit 3 – ADIE:?ADC Interrupt Enable
#define ADIF		4	//Bit 4 – ADIF:?ADC Interrupt Flag
#define ADATE		5	//Bit 5 – ADATE:?ADC Auto Trigger Enable
#define ADSC		6	//Bit 6 – ADSC:?ADC Start Conversion
#define ADEN		7	//Bit 7 – ADEN:?ADC Enable



//Global interrupt enable/disable >>> //bit No 7 in SREG(0x5F) reg must be set to allow the enabled interrupts in each peripheral to be enabled globaly in the MCU 
									 //if the bit is cleared the interrupts will not be enabled globally even if they are enabled in their peripheral
#define Global_ISR_Enable()		(*(volatile uint8_t*)(0x5F) |= 1 << 7)	
#define Global_ISR_Disable()	(*(volatile uint8_t*)(0x5F) &= ~(1 << 7))
	
	      
//generic macros
#define Set_Bit(Reg, Bit_No)		(Reg |= 1 << Bit_No)
#define Reset_Bit(Reg, Bit_No)		(Reg &= ~(1 << Bit_No))
#define Toggle_Bit(Reg, Bit_No)		(Reg ^= 1 << Bit_No)
#define Read_Bit(Reg, Bit_No)		((Reg >> Bit_No) & 1)

#define NULL						(void*)(0)

#endif 