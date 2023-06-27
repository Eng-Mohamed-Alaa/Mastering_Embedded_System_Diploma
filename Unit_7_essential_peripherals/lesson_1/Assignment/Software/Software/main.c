
#define F_CPU 8000000
#include <util/delay.h>
#include <memory_map.h>
#include <utils.h>


// each press by the PB >>> a LED is on, after all the LEDs are on, each press by the PB  >>> a LED is off in the same order of turning on 
void task1(void);
// a single press by the PB >>> all LEDs are on with certain order, after all the LEDs are on, a single press by the PB >>> all LEDs are off in reverse order of turning on
void task2(void);
// the buzzer is on as long as PB (PD0) is pressed
void task3(void);
// when the PB is pressed the MCU count from 0 to 9 seconds and the count is displayed on the 7 segment on the kit
void task4(void);


void GPIO_init(void)
{
	// configure PD0: floating input (By default all pins are floating input)
	Reset_Bit(DDRD,0);
	// configure PDx x[7:4] : Push-Pull output
	DDRD |= 0xf<<4;
	// configure PCx x[7:2]: Push-Pull output
	DDRC |= 0b11111100;
}

int main(void)
{
	GPIO_init();
	while(1)
	{
		
		//task1();
		//task2();
		//task3();
		task4();
	}
	return 0;
}

void task1(void)
{
	while(!Read_Bit(PIND,0));
	Toggle_Bit(PORTD, 5);
	while(Read_Bit(PIND,0));
	while(!Read_Bit(PIND,0));
	Toggle_Bit(PORTD, 6);
	while(Read_Bit(PIND,0));
	while(!Read_Bit(PIND,0));
	Toggle_Bit(PORTD, 7);
	while(Read_Bit(PIND,0));
}

void task2(void)
{
	static uint8_t off_flag=1;
	if(off_flag)
	{
		while(!Read_Bit(PIND,0));
		Toggle_Bit(PORTD, 5);
		_delay_ms(300);
		Toggle_Bit(PORTD, 6);
		_delay_ms(300);
		Toggle_Bit(PORTD, 7);
		_delay_ms(300);
		while(Read_Bit(PIND,0));
		off_flag = 0;
		return;
	}
	while(!Read_Bit(PIND,0));
	Toggle_Bit(PORTD, 7);
	_delay_ms(300);
	Toggle_Bit(PORTD, 6);
	_delay_ms(300);
	Toggle_Bit(PORTD, 5);
	_delay_ms(300);
	while(Read_Bit(PIND,0));
	off_flag = 1;
}

void task3(void)
{
	if(Read_Bit(PIND,0))
		Set_Bit(PORTD,4);
	while(Read_Bit(PIND,0));
	Reset_Bit(PORTD,4);
}

void task4(void)
{
	while(!Read_Bit(PIND,0));
	uint8_t i;
	Set_Bit(PORTC,3);
	for(i=0; i < 10; ++i)
	{
		PORTC &= ~(0xf<<4);
		PORTC |= i<<4;
		_delay_ms(1000);
	}
	Reset_Bit(PORTC,3);
}
