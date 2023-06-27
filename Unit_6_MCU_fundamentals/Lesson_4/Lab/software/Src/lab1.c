//By: Eng.Mohamed Alaa
//You can only build 1 lab.c at a time in this project
//from resources configuration you can choose the lab to build

#include"stdint.h"

//RCC registers
#define RCC_Base	 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *) (RCC_Base + 0x18 )

//GPIO registers
#define GPIOA_Base	 0x40010800
#define GPIOA_CRH 	*(volatile uint32_t *) (GPIOA_Base+0x04)
#define GPIOA_CRL 	*(volatile uint32_t *) (GPIOA_Base+0x00)
#define GPIOA_ODR 	*(volatile uint32_t *) (GPIOA_Base+0x0c)

//AFIO registers
#define AFIO_Base 	 0x40010000
#define AFIO_EXTICR1 *(volatile uint32_t *) (AFIO_Base+0x08)

//EXIT registers
#define EXTI_Base 	0x40010400
#define EXTI_IMR 	*(volatile uint32_t *) (EXTI_Base+0x00)
#define EXTI_RTSR 	*(volatile uint32_t *) (EXTI_Base+0x08)
#define EXTI_PR 	*(volatile uint32_t *) (EXTI_Base+0x14)

//NVIC register
#define NVIC_EXTIE0 *(volatile uint32_t *) (0XE000E100)

void clock_init(void)
{
	/*Bit 2 IOPAEN: I/O port A clock enable
	Set and cleared by software.
	0: I/O port A clock disabled
	1:I/O port A clock enabled*/
	RCC_APB2ENR |= 1<<2;

	/*Bit 0 AFIOEN: Alternate function I/O clock enable
	Set and cleared by software.
	0: Alternate Function I/O clock disabled
	1:Alternate Function I/O clock enabled*/
	RCC_APB2ENR |= 1;

	// the clock of EXTI module is not controlled, by default is enabled
}

void GPIO_init(void)
{
	//pin A13
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;

	//pin A0: Floating input (reset state)
	GPIOA_CRL |= 1<<2;
}

void AFIO_init(void)
{
	//EXTI0 configuration to portA pin 0
	AFIO_EXTICR1 |= 0x0;
}

void EXIT_init(void)
{
	//detect the rising edge at the input line 0
	EXTI_RTSR |= 1;

	//enable the interrupt (not masked) for the line 0
	EXTI_IMR |= 1;


}

void NVIC_init(void)
{
	NVIC_EXTIE0 |= (1<<6);
}

void EXTI0_IRQHandler(void)
{
	//toggle pin 13 in the GPIOA
	GPIOA_ODR ^= (1<<13);

	//clear pending request for the line 0
	EXTI_PR |= 1;
}



int main(void)
{
	clock_init();
	GPIO_init();
	AFIO_init();
	EXIT_init();
	NVIC_init();
	while(1);
	return 0;
}
