#ifndef UART_H_
#define UART_H_

//includes
#include "memory_map.h"
#include "stdint.h"
#include "util/delay.h"

//UART APIs prototypes
void UART_Init(void);
void UART_Send(uint8_t data);
uint8_t UART_Receive(void);
void UART_Send_uint32(uint32_t data);
uint32_t UART_Receive_uint32(void);
#endif