#include "stdint.h"

/*declaring symbols of sections boundaries existed in linker_scrip*/
extern _text_end;
extern _data_start;
extern _data_end;
extern _bss_start;
extern _bss_end;
extern _stack_top;

/*prototypes of interrupt handler*/
void reset();
void Dafault_handler();
void NMI_handler()__attribute__((weak, alias("Dafault_handler")));
void Hard_fault_handler()__attribute__((weak, alias("Dafault_handler")));

/*define interrrupt vector table as array of uint32_t in new section called vector*/
uint32_t Vector_table [] __attribute__((section(".vectors"))) = {
	
	(uint32_t) &_stack_top,
	(uint32_t) reset,
	(uint32_t) NMI_handler,
	(uint32_t) Hard_fault_handler,
};

/*functions definition*/

void Dafault_handler()
{
	reset();
}

void reset()
{
	uint32_t section_size;
	uint8_t *p_src_section,*p_dst_section;
	int32_t i;
	
	/*copy .data section from Flash to SRAM*/
	p_dst_section = (uint8_t *) &_text_end;
	p_src_section = (uint8_t *) &_data_start;
	section_size = (uint32_t) &_data_end - (uint32_t) &_data_start;
	for(i = 0; i < section_size; ++i)
	{
		*(p_src_section++) = *(p_dst_section++);
	}

	/*initialize .bss section by zero in SRAM*/
	p_src_section = (uint8_t *) &_bss_start;
	section_size = (uint32_t) &_bss_end - (uint32_t) &_bss_start;
	for(i = 0; i < section_size; ++i)
	{
		*(p_src_section++) = (uint8_t)0;  
	}

	/*jump to main*/
	main();
}

