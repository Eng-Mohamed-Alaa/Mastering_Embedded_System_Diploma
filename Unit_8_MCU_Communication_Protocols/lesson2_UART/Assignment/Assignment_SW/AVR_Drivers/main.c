
#define F_CPU 8000000UL
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>

int main()
{
	LCD_INIT();
	UART_Init();
	LCD_WRITE_STRING("UART TX");
	uint8_t ch;
	UART_Send('M');
	UART_Send('o');
	UART_Send('h');
	uint32_t str = UART_Receive_uint32();
	LCD_WRITE_STRING(&str);
	UART_Send_uint32(1633771873);

	LCD_GOTO_XY(2,0);

	while(1)
	{
		ch = UART_Receive();
		LCD_WRITE_CHAR(ch);
	}
	
	return 0;
}