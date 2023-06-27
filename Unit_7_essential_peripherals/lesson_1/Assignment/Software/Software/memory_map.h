
#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

#include <stdint.h>

//PortC registers
#define PORTC	*(volatile uint8_t *)(0x35)
#define DDRC	*(volatile uint8_t *)(0x34)
#define PINC	*(volatile uint8_t *)(0x33)

//PortD registers
#define PORTD	*(volatile uint8_t *)(0x32)
#define DDRD	*(volatile uint8_t *)(0x31)
#define PIND	*(volatile uint8_t *)(0x30)


#endif 