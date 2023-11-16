/*
 * ADC.c
 *
 * Created: 10/23/2023 11:02:28 AM
 *  Author: computer store
 */ 


#include <MCAL/ADC/ADC_Includes/ADC.h>
#include <MCAL/ADC/ADC_Includes/ADC_CFG.h>
#include <MCAL/ADC/ADC_Includes/ADC_Private.h>
#include <Services/Bit_utils.h>

void (*ADC_GP_CallBack)(void) = 0;
ADC_Config_t* GPS_ADC_Config =0;


void ADC_Disable(void)
{
	CLR_BIT(ADCSRA, ADEN);
}

// void ADC_Start(void)
// {
// 	SET_BIT(ADCSRA, ADSC);
// }

void ADC_Read(Puint16 ADC_value, uint8 ADC_Channel_Selection)
{
	ADMUX &= ~(0x1F << MUXn);
	ADMUX |= (ADC_Channel_Selection << MUXn);
	SET_BIT(ADCSRA, ADSC);
	while(GET_BIT(ADCSRA, ADSC) != 1);
	*ADC_value = (uint16)ADCL | ((uint16)( 0x03 & ADCH) << 8);
}

void ADC_Set_Config(ADC_Config_t* PS_ADC_Config)
{

	if(PS_ADC_Config->ADC_Interrupt_State == ADC_Interrupt_State_EN)
	{
		ADC_GP_CallBack = PS_ADC_Config->ADC_P_CallBack;
	}
	else
	{
		ADC_GP_CallBack = PTR_NULL;

	}
	
	ADMUX = 0;
	ADCSRA = 0;

	//select vref source
	//ADMUX &= ~(0x03 << REFSn);
	ADMUX |= ((PS_ADC_Config->ADC_VREF) << REFSn);
	
	//select ADC channel
	//ADMUX &= ~(0x0F << MUXn);
	ADMUX |= (PS_ADC_Config->ADC_Channel_Selection << MUXn);
	
	//select vref source
	//CLR_BIT(ADMUX, ADATE);
	ADCSRA |= (PS_ADC_Config->ADC_Auto_Trigger_Mode << ADATE);	
	
	//ADC interrupt Enable/Disable
	//CLR_BIT(ADMUX, ADIE);
	ADCSRA |= (PS_ADC_Config->ADC_Interrupt_State << ADIE);
	
	//ADC Prescaler Select
	//ADMUX &= ~(0b111 << ADPSn);
	ADCSRA |= (PS_ADC_Config->ADC_Prescale << ADPSn);
	
	SFIOR &= (0x7 << ADTSn);
	SFIOR |= ((PS_ADC_Config->ADC_Trigger_Source) << ADTSn);
	
	SET_BIT(ADCSRA, ADEN);
}