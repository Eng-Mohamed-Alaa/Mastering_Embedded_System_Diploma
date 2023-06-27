//By: Eng.Mohamed Alaa (STM32CubeIDE)
//You can only build 1 lab.c at a time in this project
//from resources configuration you can choose the lab to build

#define RCC_Base	 0x40021000
#define GPIOA_Base	 0x40010800
typedef volatile unsigned long  vuint32_t;

#define RCC_CFGR 	*(vuint32_t *) (RCC_Base + 0x04 )
#define RCC_APB2ENR *(vuint32_t *) (RCC_Base + 0x18 )
#define GPIOA_CRH 	*(vuint32_t *) (GPIOA_Base+0x04)
#define GPIOA_ODR 	*(vuint32_t *) (GPIOA_Base+0x0c)

int main(void)
{
	//AHB clock(HCLK) and system clock are by default equal to HSI RC clock 8 MHz
	/*Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
	100: HCLK divided by 2*/
	RCC_CFGR |= (0b100) << 8;

	/*Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
	101: HCLK divided by 4*/
	RCC_CFGR |= (0b101) << 11;

	/*Bit 2 IOPAEN: I/O port A clock enable
	Set and cleared by software.
	0: I/O port A clock disabled
	1:I/O port A clock enabled*/
	RCC_APB2ENR |= 1<<2;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;
	while(1)
	{
		GPIOA_ODR |= 1<<13;
		for(int i=0; i < 5000; ++i){}
		GPIOA_ODR &= ~(1<<13);
		for(int i=0; i < 5000; ++i){}
	}
	return 0;
}
