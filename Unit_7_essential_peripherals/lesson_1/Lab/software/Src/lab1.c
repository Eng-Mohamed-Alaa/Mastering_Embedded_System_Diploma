//By: Eng.Mohamed Alaa
//You can only build 1 lab.c at a time in this project
//from resources configuration you can choose the lab to build

#include"stdint.h"

//RCC registers
#define RCC_Base	 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *) (RCC_Base + 0x18 )

//GPIOA registers
#define GPIOA_Base	 0x40010800
#define GPIOA_CRH 	*(volatile uint32_t *) (GPIOA_Base+0x04)
#define GPIOA_CRL 	*(volatile uint32_t *) (GPIOA_Base+0x00)
#define GPIOA_IDR 	*(volatile uint32_t *) (GPIOA_Base+0x08)
#define GPIOA_ODR 	*(volatile uint32_t *) (GPIOA_Base+0x0c)

//GPIOB registers
#define GPIOB_Base	 0x40010C00
#define GPIOB_CRH 	*(volatile uint32_t *) (GPIOB_Base+0x04)
#define GPIOB_CRL 	*(volatile uint32_t *) (GPIOB_Base+0x00)
#define GPIOB_IDR 	*(volatile uint32_t *) (GPIOB_Base+0x08)
#define GPIOB_ODR 	*(volatile uint32_t *) (GPIOB_Base+0x0c)

void clock_init(void)
{
	// Bit 2 IOPAEN: I/O port A clock enable
	// 1:I/O port A clock enabled
	RCC_APB2ENR |= 1<<2;

	// Bit 3 IOPBEN: I/O port B clock enable
	// 1:I/O port B clock enabled
	RCC_APB2ENR |= 1<<3;

}

void GPIO_init(void)
{
	GPIOA_CRL = GPIOA_CRH = 0;
	// pin A1: Floating input (reset state, no need to write this part of code)
	GPIOA_CRL |= 1<<6;
	// pin A13: Floating input (reset state, no need to write this part of code)
	GPIOA_CRH |= 1<<22;

	GPIOB_CRL = GPIOB_CRH = 0;
	// pin B1: push-pull output
	GPIOB_CRL |= 1<<4;
	// pin B13: push-pull output
	GPIOB_CRH |= 1<<20;
}

void my_wait(int x)
{
	for( int i=0; i < x; ++i)
		for(int j=0; j < 255; ++j);
}

int main(void)
{
	clock_init();
	GPIO_init();
	while(1)
	{
		// PA1 >>>> connected externally to pull up resistance (default = 1)
		if( (GPIOA_IDR & (1<<1)) >> 1 == 0) //press
			{
			GPIOB_ODR ^= 1<<1;
			//the while is used to make it single press (work only one time even if the button still pressed)
			//but you cannot press the two buttons at same time
			while((GPIOA_IDR & (1<<1)) >> 1 == 0);
			}
		// PA13 >>>> connected externally to pull down resistance (default = 0)
		if( ((GPIOA_IDR & (1<<13)) >> 13) == 1)//multiple press (work as long as the button is pressed)
			GPIOB_ODR ^= 1<<13;

		my_wait(1);
	}
	return 0;
}
