//to selet which file's redefinition is used for of ISR(TIMER0_COMP_vect) & ISR(TIMER0_OVF_vect) 

#define Timer0_ISR_Redefinition


#include <memory_map.h>
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>
#include <stdint.h>
#include <SPI.h>
#include <I2C.h>
#include <Timer0.h>
#include <PWM0.h>


void Watchdog_Test();
void Watchdog_Disable();
void Watchdog_Kick();
void Timer0_Test();
void PWM0_Test();


void Timer0_ISR_OVF_CallBack(void)
{
	Timer0_Stop();
	static uint8_t i=0 ;
	PORTA = i++;
	if(i == 10)
		i = 0;
	_delay_ms(1000);
	Timer0_Start();
}

void Timer0_ISR_COMP_CallBack(void)
{
	
	Timer0_Stop();
	static uint8_t i=0 ;
	PORTA = i++ << 4;
	if(i == 10)
		i = 0;
	_delay_ms(1000);
	Timer0_Start();
}

void PWM0_ISR_OVF_CallBack(uint8_t Pulses_Cnt_Status)
{
	if(Pulses_Cnt_Status == Cnt_Status_Finished)
		PWM0_Reset();
}


Timer0_Configurations_t Timer0_CFG = {Timer0_Sytem_CLK_divided_by_1024, Timer0_Disconnect_OC, Timer0_Normal_Mode, Timer0_Disable_FOC, Timer0_Interrupt_Compare_Match,
									 Timer0_ISR_OVF_CallBack, Timer0_ISR_COMP_CallBack};

PWM0_Configurations_t	PWM0_CFG = {PWM0_Clear_OC, PWM0_Fast_Mode, PWM0_Interrupt_Overflow, PWM0_ISR_OVF_CallBack, NULL};

int main()
{
	DDRA = 0xFF;
	Global_ISR_Enable();
	//Watchdog_Test();
	//Timer0_Test();
	PWM0_Test();
	while(1)
	{
	}
	
	return 0;
}
	
void Timer0_Test()
{
	Timer0_Init(&Timer0_CFG);
	Timer0_Set_Output_Compare_Reg(200);
	Timer0_Start();
}

void Watchdog_Test()
{
	PORTA = 1;
	_delay_ms(1000);
	Watchdog_Kick();
	PORTA = 1 << 4;
	_delay_ms(1200);	//if time_delay is bigger than 1 second the MCU is reseted and port A will continuously change its value from 1 to 1<<4 each 1 second
						//if time_delay is smaller than 1 second PortA will equal to 1 for 1 second then will equal (1 << 4) as long as the MCU is powered on
	Watchdog_Disable();

}


void Watchdog_Disable()
{
	WDTCR |= ((1 <<  WDE) | (1 << WDTOE)); 
	WDTCR = 0;
}

void Watchdog_Kick()
{
	WDTCR = 0;
	WDTCR = (0x6 << WDPn) ;		//Watchdog time-out = 1 second	@Table 14-1.?Watchdog Timer Prescale Select 
	WDTCR |= (1 <<  WDE) ;		//Watchdog enable
}

void PWM0_Test()
{
	PWM0_Init(&PWM0_CFG);
	PWM0_Start(N_Pulses_Undefined, PWM0_T_High_1ms);	//for N_Pulses_Undefined PWM is continuously generated 
														//but we can define the number of pulses we want like this: PWM0_Start(500, PWM0_T_High_1ms);	
}
