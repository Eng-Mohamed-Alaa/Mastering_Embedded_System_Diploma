
#include <memory_map.h>
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>
#include <stdint.h>

char data[100] = "Learn in depth ";
char buffer[100];

uint8_t Send_Flag = 0;
uint8_t string_Flag = 0;


void UDRE_ISR_CallBack(void)
{	
	uint8_t i=0;
	if(!Send_Flag)
	{
		while(data[i])
		{
			UART_Send_With_Interrupt(data[i]);
			_delay_ms(100);
			++i;
		}
	}
	Send_Flag=1;
}

void RX_ISR_CallBack(void)
{
	static uint8_t i=0;
	if(!string_Flag)
	{
		buffer[i] = UART_Receive_With_Interrupt();
		
		if(buffer[i] != String_Received_End)
		{
			++i;
		}
		else
		{	
			buffer[i] = 0;
			string_Flag = 1;
			i = 0;
		}
	}
}

int main()
{
	uint8_t i='0';
	LCD_INIT();
	UART_Init();
	Global_ISR_Enable();
	
	P_UART_UDRE_ISR_CallBack = UDRE_ISR_CallBack;
	P_UART_RX_ISR_CallBack = RX_ISR_CallBack;
	
	//enable RX interrupts
	UART_ISR_RXCIE_Enable();
		
	while(1)
	{	
		if(string_Flag)
		{
			LCD_Clear_Screen();
			LCD_GOTO_XY(1,0);
			LCD_WRITE_STRING(buffer);
			LCD_GOTO_XY(2,0);		
			string_Flag = 0;
		}
		LCD_GOTO_XY(2,0);
		LCD_WRITE_CHAR(i);

		if(i == '4')
		{
			//enable UDRE interrupt
			UART_ISR_UDRIE_Enable();
		}
		if(Send_Flag )
		{
			//disable UDRE interrupts
			UART_ISR_UDRIE_Disable();
			Send_Flag = 0;
		}
		
		++i;
		_delay_ms(1000);
	
		if(i == '9')
		{
			LCD_GOTO_XY(2,0);
			LCD_WRITE_CHAR(i);
			_delay_ms(1000);
			i='0';
		}		
	} 
	
	return 0;
}
	
	

	
