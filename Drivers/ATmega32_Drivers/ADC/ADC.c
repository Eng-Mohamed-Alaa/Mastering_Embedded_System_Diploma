//----------------------------------------------------------------------
//includes
//----------------------------------------------------------------------
#include "ADC.h"



//----------------------------------------------------------------------
//APIs implementation
//----------------------------------------------------------------------
void ADC_Init(ADC_Configurations_t* ADC_CFG)
{
	ADMUX = 0;
	ADMUX = ADC_CFG->Left_Adjust_Result | ADC_CFG->Voltage_Reference_SRC;
	
	ADCSRA = 0;
	ADCSRA = ADC_CFG->Interrupt_Status | ADC_CFG->Prescaler;
	
	if (ADC_CFG->Auto_Trigger_Source != ADC_Auto_Trigger_None)
	{
		ADCSRA = (1 << ADATE);
		SFIOR &= ~(0b111 << ADTSn);
		SFIOR |= ADC_CFG->Auto_Trigger_Source;
	}
	ADCSRA |= 1 << ADEN;
}



uint16_t ADC_Read_Single_Conversion(uint8_t ADC_Channel)
{
	uint16_t ADC_value=0;
	ADMUX  |= ADC_Channel;
	ADCSRA |= 1 << ADSC; 
	
	while (Read_Bit(ADCSRA,ADSC));
	
	if(!Read_Bit(ADMUX, ADLAR))
	{
		ADC_value = ADCL | ((uint16_t)( 0x03 & ADCH) << 8);
	}else
	{
		ADC_value = (( 0xC0 & ADCL) >> 6) | ((uint16_t)ADCH << 2);
	}
	return ADC_value;
}