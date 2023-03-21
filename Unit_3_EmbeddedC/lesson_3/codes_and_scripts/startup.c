
typedef unsigned int uint32_t;
 
void Reset_Handler (void);
void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));
void H_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void MM_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void Bud_Fault(void) __attribute__((weak,alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));

extern _E_text;
extern _S_data;
extern _E_data;
extern _S_bss;
extern _E_bss;
extern _stack_top;

uint32_t vectors[] __attribute__((section(".vectors"))) = 
{
	(uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bud_Fault,
	(uint32_t) &Usage_Fault_Handler
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

Default_Handler()
{
	Reset_Handler();
}