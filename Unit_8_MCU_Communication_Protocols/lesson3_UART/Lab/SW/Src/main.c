
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include"stdint.h"
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_EXTI_Driver.h"
#include "STM32F103C6_USART_Driver.h"


void clock_init(void)
{
	// Bit 2 IOPAEN: I/O port A clock enable
	// 1:I/O port A clock enabled
	RCC_GPIOA_Clock_Enable();

	// Bit 3 IOPBEN: I/O port B clock enable
	// 1:I/O port B clock enabled
	RCC_GPIOB_Clock_Enable();

	//AFIO clock enable
	RCC_AFIO_Clock_Enable();
}

uint16_t ch;

void UART_IRQ_CallBack(void)
{
	MCAL_UART_Receive_Data(USART1, &ch, Disable);
	MCAL_UART_Send_Data(USART1, &ch, Enable);
}

int main(void)
{
	UART_Config_t UART_CFG;
	clock_init();
	UART_CFG.BaudRate = UART_BaudRate_115200;
	UART_CFG.HW_Flow_CTRL = UART_HW_Flow_CTRL_None;
	UART_CFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	UART_CFG.P_IRQ_CallBack = UART_IRQ_CallBack;
	UART_CFG.Parity = UART_Parity_None;
	UART_CFG.Payload_Length = UART_Payload_Length_8B;
	UART_CFG.StopBits = UART_StopBits_1Bit;
	UART_CFG.UART_Mode = UART_Mode_RX_TX;

	MCAL_UART_Init(USART1, &UART_CFG);
	MCAL_UART_GPIO_Set_Pins(USART1);

	while(1)
	{

	}
	return 0;
}
