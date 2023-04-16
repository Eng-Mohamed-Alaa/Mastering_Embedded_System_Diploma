#include "DC_motor.h"

/*1-define attributes*/
int DC_speed = 0;

/*2-define states pointer*/
void (* DC_state)();

/*3-define input signal set_speed*/
void set_speed(int s)
{
	DC_speed = s;
	DC_state = state(DC_busy);
	printf("CA -----speed = %d-----> DC motor\n", DC_speed);
}

/*4-define states and functions*/
void DC_init()
{
	/*1-init PWM*/
	DC_state = idle;
	printf("DC_init\n");
}

state_define(DC_idle)
{
	DC_state_id = idle;
	/*1-call PWM to run DC motor on idle state*/
	printf("DC_idle......the current speed = %d\n",DC_speed);
}

state_define(DC_busy)
{
	DC_state_id = busy;
	/*1-call PWM to set motor speed*/
	printf("DC_busy......the current speed = %d\n",DC_speed);
}






