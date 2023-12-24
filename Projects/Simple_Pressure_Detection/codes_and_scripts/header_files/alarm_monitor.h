#ifndef ALARM_H_
#define ALARM_H_

#include "state.h"
extern void (* AM_state)();
extern void AM_init();
state_define(AM_waiting);

#endif
