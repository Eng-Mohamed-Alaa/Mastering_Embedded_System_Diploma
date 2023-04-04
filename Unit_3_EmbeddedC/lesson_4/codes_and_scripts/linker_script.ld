/*ENG.Mohamed Alaa*/

MEMORY
{
flash(RX) : ORIGIN = 0X00000000, LENGTH = 512M
sram(RWX) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS
{
	.text : {
		*(.vectors) 
		*(.text) 
		*(.rodata)
		_E_text = . ;
		 }> flash
	
	/*we will copy .data section from flash to sram in startup.c here we are just trying*/
	.data : {
		_S_data = . ;
		*(.data)
		_E_data = . ;
		 }> sram AT>flash
	
	.bss : {
		_S_bss = . ;
		*(.bss*)
		_E_bss = . ;
		}> sram
	
}