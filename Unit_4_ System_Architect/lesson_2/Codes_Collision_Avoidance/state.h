#ifndef STATE_H_
#define STATE_H_
#include "stdio.h"

/* 1st macro to generate state_function prototype
 * 2nd macro to generate state_function name/symbol (address)*/
#define state_define(state_name) void ST_##state_name()
#define state(state_name) ST_##state_name


/*connections (input/output)*/
extern void get_distance(int d);
extern void set_speed(int s);


#endif
