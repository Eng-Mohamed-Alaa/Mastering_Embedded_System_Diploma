#ifndef SPI_H_
#define SPI_H_

//includes
#include "memory_map.h"
#include "stdint.h"
#include "avr/interrupt.h"



//configuration macros	

#define SPI_Mode_Master()		Set_Bit(SPCR, MSTR);
#define SPI_Mode_Slave()		Reset_Bit(SPCR, MSTR);

#define SPI_CLKIdle_Low()				Reset_Bit(SPCR, CPOL)	//leading is rising edge, trailing is falling edge
#define SPI_CLKIdle_High()				Set_Bit(SPCR, CPOL)		//leading is falling, trailing is rising edge,

#define SPI_Sample_Laeding()			Reset_Bit(SPCR, CPHA)	//sample input data at clock leading edge whether it was rising or falling 
#define SPI_Sample_Trailing()			Set_Bit(SPCR, CPHA)	

#define SPI_CLKRate_Fosc_over4()		{	Reset_Bit(SPSR, SPI2X) , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(0);	}
#define SPI_CLKRate_Fosc_over16()		{	Reset_Bit(SPSR, SPI2X) , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(1);	}
#define SPI_CLKRate_Fosc_over64()		{	Reset_Bit(SPSR, SPI2X) , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(2);	}
#define SPI_CLKRate_Fosc_over128()		{	Reset_Bit(SPSR, SPI2X) , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(3);	}
#define SPI_CLKRate_Fosc_over2()		{	Set_Bit(SPSR, SPI2X)   , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(0);	}
#define SPI_CLKRate_Fosc_over8()		{	Set_Bit(SPSR, SPI2X)   , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(1);	}
#define SPI_CLKRate_Fosc_over32()		{	Set_Bit(SPSR, SPI2X)   , SPCR &= ~(uint8_t)(0b11) , SPCR |= (uint8_t)(2);	}



//UART APIs prototypes
void SPI_Master_Init(void);
void SPI_Slave_Init(void);
uint8_t SPI_Send_Receive(uint8_t Data);
void SPI_Send(uint8_t Data);




#endif /* SPI_H_ */