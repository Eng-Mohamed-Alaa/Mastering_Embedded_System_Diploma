
//----------------------------------------------------------------------
//includes
//----------------------------------------------------------------------
#include "Timer0.h"
#include "avr/interrupt.h"



//----------------------------------------------------------------------
//Global variables
//----------------------------------------------------------------------
Timer0_Configurations_t G_Timer0_Config;


//----------------------------------------------------------------------
//APIs implementation
//----------------------------------------------------------------------

void Timer0_Init(Timer0_Configurations_t* Timer_CFG)
{
	G_Timer0_Config = *Timer_CFG;
	
	TCCR0 = 0; //stop timer and reset all configurations
	TCCR0 = (Timer_CFG->Compare_Output_Mode) | (Timer_CFG->Force_Output_Compare) | (Timer_CFG->Operation_Mode);		 	//all configurations are set for TCCR0 except the Timer clock is set in API :Timer0_Start
																														//Timer is not working yet
	TIMSK = 0;
	TIMSK = Timer_CFG->Select_Interrupt;
}

void Timer0_Set_Timer_Reg(uint8_t Ticks)
{
	TCNT0 = Ticks;
}

void Timer0_Set_Output_Compare_Reg(uint8_t Ticks)
{
	OCR0 = Ticks;
}

void Timer0_Start(void)
{
	TCCR0 |= G_Timer0_Config.Clock_Select;
}

void Timer0_Stop(void)
{
	TCCR0 &= ~(0x7 << CS0n);
	TCNT0 = 0;
}

void Timer0_Pause(void)
{
	TCCR0 &= ~(0x7 << CS0n);
}

uint8_t Timer0_Get_Ticks(void)
{
	return TCNT0;
}

//----------------------------------------------------------------------
//ISR
//----------------------------------------------------------------------

// ISR(TIMER0_OVF_vect)
// {
// 	if(G_Timer0_Config.PTR_ISR_OVF_CallBack != NULL)
// 		G_Timer0_Config.PTR_ISR_OVF_CallBack();
// }
// 
// 
// ISR(TIMER0_COMP_vect)
// {
// 	if(G_Timer0_Config.PTR_ISR_COMP_CallBack!= NULL)
// 		G_Timer0_Config.PTR_ISR_COMP_CallBack();
// }


