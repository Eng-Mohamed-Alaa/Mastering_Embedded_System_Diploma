
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include"stdint.h"
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "LCD.H"
#include "Keypad.h"

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
}



int main(void)
{
	clock_init();
	Keypad_Init();
	LCD_INIT();
	while(1)
	{

		uint8_t Key;
		Key = Keypad_Get_Key();
		if(Key)
		{
			LCD_WRITE_CHAR(Key);
		}
	}
	return 0;
}
