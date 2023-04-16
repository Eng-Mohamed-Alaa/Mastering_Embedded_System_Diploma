#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*1-include headers needed in this module*/
#include "state.h"
#include "stdio.h"

/*2-declare global pointer as extern to be used in the module and main file */
extern void (* DC_state)();

/*3-define enum for the existing states of this module*/
enum{
	idle,
	busy
}DC_state_id;

/*4-create prototypes for the functions and states of this module*/
void DC_init();
state_define(DC_idle);
state_define(DC_busy);

#endif
