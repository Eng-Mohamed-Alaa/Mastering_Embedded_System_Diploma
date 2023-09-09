
//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103C6_USART_Driver.h"


//----------------------------------------------------------------
//Generic macros
//----------------------------------------------------------------




//----------------------------------------------------------------
//Generic Global variables
//----------------------------------------------------------------
UART_Config_t* GP_UART_Config = NULL;


//----------------------------------------------------------------
//EXTI driver static functions
//----------------------------------------------------------------


//----------------------------------------------------------------
//APIs Implementation by "MCAL EXTI driver"
//----------------------------------------------------------------

void MCAL_UART_Init(volatile USART_typedef* USARTx, UART_Config_t* UART_Config)
{
	uint32_t BRR, PCLK;

	//set the global pointer to share the configurations with other functions
	GP_UART_Config = UART_Config;

	//UART clock enable
	if(USARTx == USART1)		{ 	RCC_USART1_Clock_Enable(); 	}
	else if(USARTx == USART2)	{ 	RCC_USART2_Clock_Enable(); 	}
	else if(USARTx == USART3)	{ 	RCC_USART3_Clock_Enable(); 	}

	//enable the USART module
	USARTx->CR1 |= 1<<13;

	//set TX/RX enable/disable value
	//USART_CR1 Bit 3 TE: transmitter enable & Bit 2 RE:receiver enable enable
	USARTx->CR1 |= UART_Config->UART_Mode;

	//Payload width
	//USART_CR1 Bit 12 M: word length
	USARTx->CR1 |= UART_Config->Payload_Length;

	//enable/disable Parity & if enabled select Odd/Even
	//USART_CR1 Bit 10 PCE: Parity control enable & Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->Parity;

	//No of stop Bits
	//USART_CR2 Bits 13:12 stop bits
	USARTx->CR2 |= UART_Config->StopBits;

	//USART hardware flow control
	//USART_CR3 Bit 9 CTSE: CTS enable & Bit8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->HW_Flow_CTRL;


	//configuration of BRR (baud rate register)
	//PCLK1 for USART 2,3
	//PCLK2 for USART 1
	if(USARTx == USART1)
	{	PCLK = MCAL_RCC_Get_PCLK2_FREQ();	}
	else
	{	PCLK = MCAL_RCC_Get_PCLK1_FREQ();	}

	BRR = UART_BRR_Register(PCLK, UART_Config->BaudRate);
	USARTx->BRR = BRR;


	//Enable/Disable the interrupt
	//USART_CR1
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_None)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable);

		//enable NVIC for USARTx IRQ
		//any flag that can generate an interrupt is cleared by the hardware when the interrupt is acknowledged in the NVIC by the processor
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;
	}

}

void MCAL_UART_Dinit(volatile USART_typedef* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Enable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Enable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Enable;
	}

}

void MCAL_UART_Send_Data(volatile USART_typedef* USARTx, uint16_t* P_TX_Buffer, enum Polling_Mechanism Polling_En)
{
	//for polling mechanism
	//wait until the transmit data register is empty if the TXE flag is set in the SR
	if(Polling_En == Enable)
		while(! (USARTx->SR & 1<<7) );

	//check the USAT word length 9B or 8B

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.

	//payload = 9 bits
	if(GP_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{	USARTx->DR = (*P_TX_Buffer & (uint16_t)0x1FF);	}

	//payload = 8 bits
	else
	{
		USARTx->DR = (*P_TX_Buffer & (uint8_t)0xFF);
	}

}

void MCAL_UART_Receive_Data(volatile USART_typedef* USARTx, uint16_t* P_RX_Buffer, enum Polling_Mechanism Polling_En)
{
	//for polling mechanism
	//wait until the data is transfered to the receive data register if the RXNE flag is set in the SR
	if(Polling_En == Enable)
		while(! (USARTx->SR & 1<<5) );

	//check the USAT word length 9B or 8B

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.


	//parity is enabled
	if(GP_UART_Config->Parity != UART_Parity_None)
	{
		//RXNE flag if not cleared by the hardware if its interrupt is enabled it will be cleared by a read to the USART_DR register
		//payload = 9 bits
		if(GP_UART_Config->Payload_Length == UART_Payload_Length_9B)
		{	*P_RX_Buffer = (USARTx->DR  & (uint8_t)0xFF);	}


		//payload = 8 bits
		else
		{	*P_RX_Buffer = (USARTx->DR & (uint8_t)0x7F);	}
	}

	//parity is disabled
	else
	{
		//payload = 9 bits
		if(GP_UART_Config->Payload_Length == UART_Payload_Length_9B)
		{	*P_RX_Buffer = (USARTx->DR  & (uint16_t)0x1FF);	}

		//payload = 8 bits
		else
		{
			*P_RX_Buffer = (USARTx->DR & (uint8_t)0xFF);
		}
	}
}




void MCAL_UART_Wait_TC(volatile USART_typedef* USARTx)
{
	//wait until transmit is complete
	while(! (USARTx->SR & 1<<6) );
}


void MCAL_UART_GPIO_Set_Pins(volatile USART_typedef* USARTx)
{
	GPIO_Pin_Configuration_t Pin_Config;

	//USART1
	if(USARTx == USART1)
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		Pin_Config.GPIO_Pin_Number = GPIO_Pin9;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOA, &Pin_Config);

		//PA10 RX
		Pin_Config.GPIO_Pin_Number = GPIO_Pin10;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_Input;
		MCAL_GPIO_Init(GPIOA, &Pin_Config);

		//check if CTS is enabled
		if(GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS || GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS_RTS)
		{
			//PA11 CTS
			Pin_Config.GPIO_Pin_Number = GPIO_Pin11;
			Pin_Config.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin_Config);
		}

		if(GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_RTS || GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS_RTS)
		{
			//PA12 RTS
			Pin_Config.GPIO_Pin_Number = GPIO_Pin12;
			Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &Pin_Config);
		}
	}

	//USART2
	if(USARTx == USART2)
	{
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX
		Pin_Config.GPIO_Pin_Number = GPIO_Pin2;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOA, &Pin_Config);

		//PA3 RX
		Pin_Config.GPIO_Pin_Number = GPIO_Pin3;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_Input;
		MCAL_GPIO_Init(GPIOA, &Pin_Config);

		//check if CTS is enabled
		if(GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS || GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS_RTS)
		{
			//PA0 CTS
			Pin_Config.GPIO_Pin_Number = GPIO_Pin0;
			Pin_Config.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin_Config);
		}

		if(GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_RTS || GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS_RTS)
		{
			//PA1 RTS
			Pin_Config.GPIO_Pin_Number = GPIO_Pin1;
			Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &Pin_Config);
		}
	}

	//USART3
	if(USARTx == USART3)
	{
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PB14 RTS

		//PB10 TX
		Pin_Config.GPIO_Pin_Number = GPIO_Pin10;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_Config);

		//PB11 RX
		Pin_Config.GPIO_Pin_Number = GPIO_Pin11;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_Input;
		MCAL_GPIO_Init(GPIOB, &Pin_Config);

		//check if CTS is enabled
		if(GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS || GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS_RTS)
		{
			//PB13 CTS
			Pin_Config.GPIO_Pin_Number = GPIO_Pin13;
			Pin_Config.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOB, &Pin_Config);
		}

		if(GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_RTS || GP_UART_Config->HW_Flow_CTRL == UART_HW_Flow_CTRL_CTS_RTS)
		{
			//PB14 RTS
			Pin_Config.GPIO_Pin_Number = GPIO_Pin14;
			Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &Pin_Config);
		}
	}
}


//ISR
//any flag that can generate an interrupt is cleared by the hardware when the interrupt is acknowledged in the NVIC by the processor
//if the flag is not enabled as interrupt it can be cleared reading from or writing to certain register or by another method according to the SPECS
void USART1_IRQHandler (void)
{
	GP_UART_Config->P_IRQ_CallBack();
}

void USART2_IRQHandler (void)
{
	GP_UART_Config->P_IRQ_CallBack();
}

void USART3_IRQHandler (void)
{
	GP_UART_Config->P_IRQ_CallBack();
}
