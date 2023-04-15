#include "CA.h"

/*1-define attributes*/
int CA_distance = 0;
int CA_speed = 0;
#define CA_threshold 50

/*2-define states pointer*/
void (*CA_state)();

/*3-define input signal get_distance*/
void get_distance(int d)
{
	CA_distance = d;
	(CA_distance > CA_threshold) ? (CA_state = state(CA_driving)) : (CA_state = state(CA_waiting));
	printf("US -----distance = %d-----> CA\n", CA_distance);

}

/*4-define states and functions*/
state_define(CA_waiting)
{
	CA_state_id = waiting;
	printf("Waiting state......distance = %d, speed = %d\n", CA_distance, CA_speed);
	CA_speed = 0;
	set_speed(CA_speed);
}

state_define(CA_driving)
{
	CA_state_id = driving;
	printf("Driving state......distance = %d, speed = %d\n", CA_distance, CA_speed);
	CA_speed = 30;
	set_speed(CA_speed);
}
