#include "alarm_monitor.h"

#define On_time 1000000

static enum
{
	On = 0,
	Off = 1
}AM_status;

void (* AM_state)() = state(AM_waiting);

void AM_init()
{
	GPIO_INITIALIZATION();
	AM_status = Off;
	Set_Alarm_actuator(AM_status);
}

void High_pressure()
{
	AM_status = On;
}

state_define(AM_waiting)
{
	if(AM_status == On)
	{
		Set_Alarm_actuator(AM_status);
		Delay(On_time);
		AM_status = Off;
		Set_Alarm_actuator(AM_status);
	}
}
