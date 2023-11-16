
#include "HAL/LM35_Sensor/LM35_Includes/lm35_Prv.h"
#include "MCAL/ADC/ADC_Includes/ADC.h"

void LM35_getTemperature(Puint8 Add_pu8Value)
{
	uint16 ADC_Value;
	ADC_Read(&ADC_Value, SENSOR_CHANNEL);
	
	*Add_pu8Value = (uint8)(((uint32)ADC_Value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
}

