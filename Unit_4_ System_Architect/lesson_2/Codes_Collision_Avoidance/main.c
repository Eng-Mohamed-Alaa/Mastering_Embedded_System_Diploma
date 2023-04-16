# include "ultrasonic.h"
#include"CA.h"
#include "DC_motor.h"
#include "stdio.h"

void setup()
{
	US_init();
	DC_init();
	US_state = state(US_reading);
	CA_state  = state(CA_waiting);
	DC_state  = state(DC_idle);
}

int main()
{
	setup();
	while(1)
	{
		CA_state();
		DC_state();
		US_state();
	}
	return 0;
}
