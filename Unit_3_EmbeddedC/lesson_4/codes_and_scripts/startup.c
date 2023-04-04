
typedef unsigned long uint32_t;
void Reset_Handler (void);
void Default_Handler(void);
extern int main(void);
void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));
void H_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));

extern _E_text;
extern _S_data;
extern _E_data;
extern _S_bss;
extern _E_bss;

static uint32_t stack_top[256];

void (* const g_arr_p_2_f[])(void) __attribute__((section(".vectors"))) = 
{
	(void (*)(void)) ((unsigned long) stack_top + sizeof(stack_top)),
	&Reset_Handler,
	&NMI_Handler,
	&H_Fault_Handler,
};

void Reset_Handler(void)
{
	//copy .data section from flash to sram
	uint32_t data_size = (uint32_t)&_E_data - (uint32_t)&_S_data;
	unsigned char *p_src = (unsigned char*) &_E_text;
	unsigned char *p_dst = (unsigned char*) &_S_data;
	int i;
	for (i = 0; i < data_size; ++i)
	{
		*(p_dst++) = *(p_src++);
	}
	
	//initializing .bss section from in sram by 0
	uint32_t bss_size = (uint32_t)&_E_bss - (uint32_t)&_S_bss;	
	p_dst = (unsigned char*) &_S_bss;

	for (i = 0; i < bss_size; ++i)
	{
		*(p_dst++) = (unsigned char)0;
	}

	//jump to main function
	main ();
}

void Default_Handler(void)
{
	Reset_Handler();
}