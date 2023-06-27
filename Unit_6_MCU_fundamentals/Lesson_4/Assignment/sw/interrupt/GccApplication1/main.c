/*
 * GccApplication1.c
 *
 * Created: 25/05/2023 4:54:45 PM
 * Author: Eng. Mohamed Alaa
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define IO_Base 0X20

//external interrupt registers
#define MCUCR	*(volatile uint8_t*)(IO_Base + 0x35)
#define MCUCSR	*(volatile uint8_t*)(IO_Base + 0x34)
#define GICR	*(volatile uint8_t*)(IO_Base + 0x3B)

//I/O registers
#define PORTD	*(volatile uint8_t*)(IO_Base + 0x12)
#define DDRD	*(volatile uint8_t*)(IO_Base + 0x11)

//The AVR Status Register
#define SREG	*(volatile uint8_t*)(IO_Base + 0x3F)

void IO_port_init(void)
{
	//adjust PD5,PD6,PD7 as output pins
	DDRD |= (0b111 << 5);
}

void EXTI_init()
{
	//adjust sense control for interrupt request of int0 to any logical change, and int1 to the rising edge
	MCUCR |= (uint8_t)( 1 | 0b11 << 2); // MCUCR |= (uint8_t)0xd
	
	//adjust sense control for interrupt request of int2 to the falling edge
	MCUCSR &= ~(uint8_t)(1 << 6); //is set to zero by default according to the datasheet
	
	//Enable int0, int1, and int2 as external interrupts; 
	GICR |= (uint8_t)(0b111<<5);
	
	//Enable the interrupts for the AVR CPU
	SREG |= (uint8_t)(1<<7);
}


int main(void)
{
	IO_port_init();
	EXTI_init();
    while (1);
}

ISR(INT0_vect)
{
	PORTD |= (uint8_t)(1 << 5);
	_delay_ms(1000);
	PORTD &= ~(uint8_t)(1 << 5);
}

ISR(INT1_vect)
{
	PORTD |= (uint8_t)(1 << 6);
	_delay_ms(1000);
	PORTD &= ~(uint8_t)(1 << 6);
}

ISR(INT2_vect)
{
	PORTD |= (uint8_t)(1 << 7);
	_delay_ms(1000);
	PORTD &= ~(uint8_t)(1 << 7);
}