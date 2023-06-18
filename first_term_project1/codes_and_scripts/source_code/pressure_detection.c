/* stdint.h is included in state.h
 * which is included in pressure_detection.h*/
#include "pressure_detection.h"

#define Pressure_threshold 	20
#define Low_pressure_delay	1000000
#define High_pressure_delay 300000

uint32_t PD_pressure = 0;

void (* PD_state)() = state(PD_waiting);

state_define(PD_waiting)
{

	if(PD_pressure > Pressure_threshold)
	{
		Delay(High_pressure_delay);
	}

	PD_pressure = getPressureVal();
	
	if(PD_pressure > Pressure_threshold)
	{
		High_pressure();
	}

	else
	{
		Delay(Low_pressure_delay);
	}
}


