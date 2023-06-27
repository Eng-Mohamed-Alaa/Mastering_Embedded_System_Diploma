//By: Eng.Mohamed Alaa
//You can only build 1 lab.c at a time in this project
//from resources configuration you can choose the lab to build

#define RCC_Base	 0x40021000
#define GPIOA_Base	 0x40010800
typedef volatile unsigned long  vuint32_t;


#define RCC_APB2ENR *(vuint32_t *) (RCC_Base + 0x18 )
#define GPIOA_CRH 	*(vuint32_t *) (GPIOA_Base+0x04)
#define GPIOA_ODR 	*(vuint32_t *) (GPIOA_Base+0x0c)

int main(void)
{
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
