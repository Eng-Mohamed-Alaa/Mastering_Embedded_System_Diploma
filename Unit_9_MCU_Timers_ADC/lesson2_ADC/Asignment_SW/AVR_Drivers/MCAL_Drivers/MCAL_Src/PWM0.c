
//----------------------------------------------------------------------
//includes
//----------------------------------------------------------------------
#include "PWM0.h"
#include "avr/interrupt.h"



//----------------------------------------------------------------------
//Global variables
//----------------------------------------------------------------------
PWM0_Configurations_t G_PWM0_Config;
uint32_t G_N_Pulses = 0;

//----------------------------------------------------------------------
//APIs implementation
//----------------------------------------------------------------------

void PWM0_Init(PWM0_Configurations_t* PWM_CFG)
{
	G_PWM0_Config = *PWM_CFG;
	
	TCCR0 = 0; //stop timer and reset all configurations
	TCCR0 = (PWM_CFG->Compare_Output_Mode) | (PWM_CFG->Operation_Mode);		//all configurations are set for TCCR0 except the Timer clock is set in API :PWM0_Start
																			//PWM0 is not working yet
	if (PWM_CFG->Compare_Output_Mode != PWM0_Disconnect_OC)
	{
		DDRB |= 1<<3;
	}
	
	TIMSK = 0;
	TIMSK = PWM_CFG->Select_Interrupt;
}



void PWM0_Start(uint32_t N_Pulses, uint8_t T_High)
{
	if (G_PWM0_Config.Operation_Mode == PWM0_Fast_Mode)
	{
		OCR0 = (uint8_t)( (T_High * F_CPU / 1000) / 64);					//OCR = (T_High * F_CPU)/Prescaler
	}else if (G_PWM0_Config.Operation_Mode == PWM0_Phase_Correct_Mode)
	{
		OCR0 = (uint8_t)( (T_High * F_CPU / 1000 ) / (2*64));				//OCR = (T_High * F_CPU)/(2*Prescaler)
	}

	G_N_Pulses = N_Pulses;
	TCCR0 |= PWM0_Sytem_CLK_divided_by_64;
}

void PWM0_Reset(void)
{
	TCCR0 = TCNT0 = TIMSK = 0;
}


//----------------------------------------------------------------------
//ISR
//----------------------------------------------------------------------

ISR(TIMER0_OVF_vect)
{
	static uint32_t Cnt_OVF = 0;
	uint8_t Pulses_Cnt_Status = Cnt_Status_Working;
	if(G_N_Pulses != N_Pulses_Undefined)
	{
		Cnt_OVF++;
		if (Cnt_OVF == (G_N_Pulses+1) && G_PWM0_Config.Operation_Mode == PWM0_Fast_Mode)
		{
			Pulses_Cnt_Status = Cnt_Status_Finished;
			Cnt_OVF =0;
		}else if (Cnt_OVF == (G_N_Pulses+2) && G_PWM0_Config.Operation_Mode == PWM0_Phase_Correct_Mode)
		{
			Pulses_Cnt_Status = Cnt_Status_Finished;
			Cnt_OVF =0;
		}
	}
	
	if(G_PWM0_Config.PTR_ISR_OVF_CallBack != NULL)
		G_PWM0_Config.PTR_ISR_OVF_CallBack(Pulses_Cnt_Status);
}


ISR(TIMER0_COMP_vect)
{
	if(G_PWM0_Config.PTR_ISR_COMP_CallBack != NULL)
		G_PWM0_Config.PTR_ISR_COMP_CallBack();
}
