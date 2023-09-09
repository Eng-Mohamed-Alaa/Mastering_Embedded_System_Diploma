
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include"stdint.h"
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_EXTI_Driver.h"
#include "STM32F103C6_USART_Driver.h"
#include "STM32F103C6_SPI_Driver.h"
#include "STM32F103C6_I2C_Driver.h"
#include "I2C_Slave_EEPROM.h"



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

int main(void)
{
	clock_init();

	//test case1
	uint8_t ch1[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7};
	uint8_t ch2[7] = {0};

	EEPROM_Init();
	EEPROM_Write_Nbytes(0xAF, ch1, 7);
	EEPROM_Read_Nbytes(0xAF, ch2, 7);

	//test case2
	ch1[0]=0xA;
	ch1[1]=0xB;
	ch1[2]=0xC;
	ch1[3]=0xD;

	EEPROM_Write_Nbytes(0xFFF, ch1, 4);
	EEPROM_Read_Nbytes(0xFFF, ch2, 4);
	while(1)
	{
	}
	return 0;
}
