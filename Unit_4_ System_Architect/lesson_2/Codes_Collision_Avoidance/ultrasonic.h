#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*1-include headers needed in this module*/
#include "state.h"
#include "stdlib.h"
#include "stdio.h"

/*2-declare global pointer as extern to be used in the module and main file */
extern void (* US_state)();

/*3-define enum for the existing states of this module*/
enum {
	reading
}US_state_id;

/*4-create prototypes for the functions and the states of this module*/
unsigned int generate_rand_distance(int r, int l, int count);
extern void US_init();
state_define(US_reading);

#endif
