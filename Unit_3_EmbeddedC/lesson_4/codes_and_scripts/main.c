
typedef volatile unsigned long vuint32_t;

#define SYSCTL_RCGC2_R 		(*(vuint32_t *) 0X400FE108)
#define GPIO_PORTF_DATA_R 	(*(vuint32_t *) 0X400253FC)
#define GPIO_PORTF_DIR_R 	(*(vuint32_t *) 0X40025400)
#define GPIO_PORTF_DEN_R 	(*(vuint32_t *) 0X4002551C)

int main (void)
{
	SYSCTL_RCGC2_R = (vuint32_t) 0X00000020;
	unsigned int delay_count;
	for(delay_count=0; delay_count < 200; ++delay_count)
	GPIO_PORTF_DIR_R |= (unsigned long) (1<<3);
	GPIO_PORTF_DEN_R |= (unsigned long) (1<<3);
	while(1)
	{
		GPIO_PORTF_DATA_R |= (unsigned long) (1<<3);
		for(delay_count=0; delay_count < 2000; ++delay_count);
		GPIO_PORTF_DATA_R &= (unsigned long) ~(1<<3);
		for(delay_count=0; delay_count < 2000; ++delay_count);
	}
	return 0;
}