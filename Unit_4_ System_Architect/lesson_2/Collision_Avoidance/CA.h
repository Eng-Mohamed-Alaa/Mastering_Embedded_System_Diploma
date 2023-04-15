#ifndef CA_H_
#define CA_H_

/*1-include headers needed in this module*/
#include "state.h"
#include "stdio.h"

/*2-declare global pointer as extern to be used in the module and main file */
extern void (*CA_state)();

/*3-define enum for the existing states of this module*/
enum{
	waiting,
	driving
}CA_state_id;

/*4-create prototypes for the functions and states of this module*/
state_define(CA_waiting);
state_define(CA_driving);

#endif
