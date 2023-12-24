#ifndef STATE_H_
#define STATE_H_
#include "driver.h"
#include "stdint.h"
/* 1st macro to generate state function prototype
 * 2nd macro to generate state function name (address)*/
#define state_define(name) void ST_##name()
#define state(name) ST_##name

/*High level signals (not driver signals)*/
extern void High_pressure();

#endif
