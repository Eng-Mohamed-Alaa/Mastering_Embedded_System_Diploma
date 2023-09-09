
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include"stdint.h"
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_EXTI_Driver.h"
#include "STM32F103C6_USART_Driver.h"
#include "STM32F103C6_SPI_Driver.h"

#define MCU_Act_As_Master
//#define MCU_Act_As_Slave

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

void SPI_IRQ_CallBack(struct S_IRQ_SRC irq_src)
{
#ifdef MCU_Act_As_Slave
	if(irq_src.RXNE)
	{
		ch = 'S';
	MCAL_SPI_TX_RX_Data(SPI1,  &ch, Polling_Disable);
	MCAL_UART_Send_Data(USART1, &ch, Enable);
	}
#endif
}

void UART_IRQ_CallBack(void)
{
#ifdef MCU_Act_As_Master
	MCAL_UART_Receive_Data(USART1, &ch, Disable);
	MCAL_UART_Send_Data(USART1, &ch, Enable);
	//Send to SPI
	MCAL_GPIO_Write_Pin(GPIOA, GPIO_Pin4, 0);
	MCAL_SPI_TX_RX_Data(SPI1, &ch, Polling_Enable);
	MCAL_GPIO_Write_Pin(GPIOA, GPIO_Pin4, 1);
#endif
}

int main(void)
{

	//=================UART1_Init=================
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

	//=================SPI1_Init=================

	//PA4: SPI1_NSS
	//PA5: SPI1_SCK
	//PA6: SPI1_MISO
	//PA7: SPI1_MOSI

	SPI_Config_t SPI1_CFG;

	//Common configuration for SPI1 master/slave
	SPI1_CFG.CLK_Phase = SPI_CLK_Phase_Data_Capture_at_2nd_Edge;
	SPI1_CFG.CLK_Polarity = SPI_CLK_Polarity_Idle_High;
	SPI1_CFG.Data_Size = SPI_Data_Size_8Bits;
	SPI1_CFG.Frame_Format = SPI_Frame_Format_MSB_Transmitted_First;
	//Assume by default pclk2 = 8MHZ
	SPI1_CFG.SPI_BAUDRATE_Prescaler = SPI_BAUDRATE_Prescaler_8;
	SPI1_CFG.Communication_Mode = SPI_Direction_2Lines;

#ifdef MCU_Act_As_Master

	SPI1_CFG.Device_Mode = SPI_Device_Mode_Master;
	SPI1_CFG.IRQ_Enable = SPI_IRQ_Enable_None;
	SPI1_CFG.NSS = SPI_NSS_Software_set;
	SPI1_CFG.P_IRQ_CallBack = NULL;

	MCAL_SPI_Init(SPI1, &SPI1_CFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);

	//configure ss on PA.4 by GPIO
	GPIO_Pin_Configuration_t Pin_CFG;
	Pin_CFG.GPIO_Pin_Number = GPIO_Pin4;
	Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Output_PP;
	Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
	MCAL_GPIO_Init(GPIOA, &Pin_CFG);

	//force the slave select (High) idle mode
	MCAL_GPIO_Write_Pin(GPIOA, GPIO_Pin4, 1);
#endif

#ifdef MCU_Act_As_Slave

	SPI1_CFG.Device_Mode = SPI_Device_Mode_Slave;
	SPI1_CFG.IRQ_Enable = SPI_IRQ_Enable_RENEIE;
	SPI1_CFG.NSS = SPI_NSS_Hardware_Slave;
	SPI1_CFG.P_IRQ_CallBack = SPI_IRQ_CallBack;
	MCAL_SPI_Init(SPI1, &SPI1_CFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);
#endif


	while(1)
	{
	}
	return 0;
}
