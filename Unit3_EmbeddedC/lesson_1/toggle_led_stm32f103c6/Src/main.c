
#define RCC_Base 	 0x40021000
#define GPIOA_Base	 0x40010800
typedef volatile unsigned long  vuint32_t;

#define RCC_APB2ENR *(vuint32_t *) (RCC_Base + 0x18 )
#define GPIOA_CRH *(vuint32_t *) (GPIOA_Base+0x04)
#define GPIOA_ODR *(vuint32_t *) (GPIOA_Base+0x0c)

typedef union
{
	vuint32_t fields;
	struct
	{
		vuint32_t reserved : 13;
		vuint32_t p_13: 1;
	}pin;
}R_ODR_t;

int main(void)
{
	RCC_APB2ENR |= 1<<2;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;
	/****method1****
	while(1)
	{
		GPIOA_ODR |= 1<<13;
		int i;
		for(i=0; i < 5000; ++i){}
		GPIOA_ODR &= ~(1<<13);
		for(i=0; i < 5000; ++i){}
	}
	 ****************/

	/****method2****/
	volatile R_ODR_t *R_ODR = (R_ODR_t *) (GPIOA_Base+0x0c);
	while(1)
		{
			GPIOA_ODR |= 1<<13;
			R_ODR -> pin.p_13 = 1;
			int i;
			for(i=0; i < 5000; ++i){}
			R_ODR -> pin.p_13 = 0;
			for(i=0; i < 5000; ++i){}
		}
	return 0;

}
