#include "ultrasonic.h"

/*1-define attributes*/
static unsigned int US_distance=0;

/*2-define a state pointer*/
void (* US_state)();


/*3-define states and functions*/
unsigned int generate_rand_distance(int r, int l, int count)
{
	unsigned int i, value;
	for(i=0; i < count; ++i)
	{
		value = l+(rand()%(r-l+1));
	}
	return value;
}

void US_init()
{
	/*1-init US driver*/
	printf("US_init\n");
}

state_define(US_reading)
{

	US_state_id = reading;
	US_distance = generate_rand_distance(55,45,1);
	printf("US reading......distance = %d\n",US_distance);
	get_distance(US_distance);
}
