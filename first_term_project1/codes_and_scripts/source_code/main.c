#include "pressure_detection.h"
#include "alarm_monitor.h"
int main ()
{
	AM_init();
	while (1)
	{
		PD_state();
		AM_state();
	}

}
