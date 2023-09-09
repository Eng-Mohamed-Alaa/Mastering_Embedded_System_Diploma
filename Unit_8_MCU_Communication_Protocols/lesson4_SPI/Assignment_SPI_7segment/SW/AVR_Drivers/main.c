
#include <memory_map.h>
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>
#include <stdint.h>
#include <SPI.h>


void Execute(uint8_t Command, uint8_t Data)
{
	Reset_Bit(PORTB, SS);
	SPI_Send(Command);
	SPI_Send(Data);
	Set_Bit(PORTB, SS);

}


int main()
{
	SPI_Master_Init();
		
	unsigned char counter;
	unsigned char index_display;	
	Execute(0x09, 0xFF);
	Execute(0x0A, 0xFF);
	Execute(0x0B, 0xF7);
	Execute(0x0C, 0x01);
	
	while (1)
	{
		for (index_display = 1, counter = 1; index_display < 9; index_display++)
		{	
			Execute(index_display, counter++);			
			_delay_ms(500);
		}
		
		for (index_display = 1, counter = 0; index_display < 9; index_display++)
		{
			Execute(index_display, counter);
			_delay_ms(500);
		}
	 }
	return 0;
}
	
	

	
