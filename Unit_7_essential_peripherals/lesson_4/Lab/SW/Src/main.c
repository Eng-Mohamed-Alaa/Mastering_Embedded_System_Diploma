
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include"stdint.h"
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_EXTI_Driver.h"
#include "LCD.H"
#include "Keypad.h"

uint8_t EXTI9_Flag = 0;

void my_wait(int x)
{
	for( int i=0; i < x; ++i)
		for(int j=0; j < 255; ++j);
}

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


void EXTI_IRQ_Callback (void)
{
	LCD_WRITE_STRING("ITQ EXTI9 is happened _|-");
	my_wait(1000);
	LCD_Clear_Screen();

}

int main(void)
{
	clock_init();
	LCD_INIT();
	EXTI_Pin_Configuration_t EXTI_Pin_Config;

	EXTI_Pin_Config.EXTI_Pin = EXTI9_PB9;
	EXTI_Pin_Config.IRQ_EN = EXTI_IRQ_Enable;
	EXTI_Pin_Config.Trigger_Case = EXTI_Trigger_Rising;
	EXTI_Pin_Config.P_IRQ_Callback = EXTI_IRQ_Callback;

	MCAL_EXTI_GPIO_Init(&EXTI_Pin_Config);
	while(1)
	{



	}
	return 0;
}
