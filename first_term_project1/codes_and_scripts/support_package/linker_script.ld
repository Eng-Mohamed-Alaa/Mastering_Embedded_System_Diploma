/*Mohamed Alaa
*Mastering Embedded Systems Online Diploma
*Linker script file for the first final project of the 1st term (pressure detection)*/


/*define memory*/
MEMORY
{
	Flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
	.text : 
	{
		startup.o(.vectors)
		*(.text)
		*(.rodata)
		_text_end = .;
	}> Flash

	.data :
	{
		_data_start = . ;
		*(.data)
		_data_end = . ;
	}> SRAM AT> Flash

	.bss :
	{
		_bss_start = . ;
		*(.bss)
		_bss_end = . ;
	}> SRAM
	. = ALIGN(4);
	_stack_top = . + 0x1000;

}