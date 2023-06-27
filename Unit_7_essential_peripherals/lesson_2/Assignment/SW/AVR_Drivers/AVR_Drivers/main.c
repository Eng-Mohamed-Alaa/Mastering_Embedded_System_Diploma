
#define F_CPU 1000000UL

#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>


int main()
{
	Keypad_Init();
	LCD_INIT();
	LCD_WRITE_CHAR('1');
	
	uint8_t ch;
	ch = Keypad_Get_Button();
	while(1)
	{
		ch = 0;
		ch = Keypad_Get_Button();
		_delay_ms(10);
		if(ch)
		{
			LCD_WRITE_CHAR(ch);
		}
	}
	
	return 0;
}