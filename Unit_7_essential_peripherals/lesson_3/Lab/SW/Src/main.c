
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

//By: Eng.Mohamed Alaa
//You can only build 1 lab.c at a time in this project
//from resources configuration you can choose the lab to build

#include"stdint.h"
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Driver.h"


void clock_init(void)
{
	// Bit 2 IOPAEN: I/O port A clock enable
	// 1:I/O port A clock enabled
	RCC_GPIOA_Clock_Enable();

	// Bit 3 IOPBEN: I/O port B clock enable
	// 1:I/O port B clock enabled
	RCC_GPIOB_Clock_Enable();
}

void GPIO_Init()
{
		GPIO_Pin_Configuration_t Pin_CNFG;

		// pin A1: Floating input (reset state, no need to write this part of code)
		Pin_CNFG.GPIO_Pin_Number = GPIO_Pin1;
		Pin_CNFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
		MCAL_GPIO_Init(GPIOA, &Pin_CNFG);

		// pin A13: Floating input (reset state, no need to write this part of code)
		Pin_CNFG.GPIO_Pin_Number = GPIO_Pin13;
		Pin_CNFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
		MCAL_GPIO_Init(GPIOA, &Pin_CNFG);

		// pin B1: push-pull output
		Pin_CNFG.GPIO_Pin_Number = GPIO_Pin1;
		Pin_CNFG.GPIO_Pin_Mode = GPIO_Mode_Output_PP;
		Pin_CNFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_CNFG);

		// pin B13: push-pull output
		Pin_CNFG.GPIO_Pin_Number = GPIO_Pin13;
		Pin_CNFG.GPIO_Pin_Mode = GPIO_Mode_Output_PP;
		Pin_CNFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_CNFG);

}

void my_wait(int x)
{
	for( int i=0; i < x; ++i)
		for(int j=0; j < 255; ++j);
}

int main(void)
{
	clock_init();
	GPIO_Init();

	while(1)
	{
		// PA1 >>>> connected externally to pull up resistance (default = 1)
		if(MCAL_GPIO_Read_Pin(GPIOA, GPIO_Pin1) == 0) //press
		{
			MCAL_GPIO_Toggle_Pin(GPIOB, GPIO_Pin1);
			//the while is used to make it single press (work only one time even if the button still pressed)
			//but you cannot press the two buttons at same time
			while(MCAL_GPIO_Read_Pin(GPIOA, GPIO_Pin1) == 0);
		}

		// PA13 >>>> connected externally to pull down resistance (default = 0)
		if(MCAL_GPIO_Read_Pin(GPIOA, GPIO_Pin13))//multiple press (work as long as the button is pressed)
		{MCAL_GPIO_Toggle_Pin(GPIOB, GPIO_Pin13);}

		my_wait(1);
	}
	return 0;
}
