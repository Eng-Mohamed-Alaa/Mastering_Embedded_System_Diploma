
#ifndef FIFO_H_
#define FIFO_H_
#include "stdint.h"

/*user configuration to set data type for the elements to be stored*/
#define element_type uint16_t

/*define structure to control FIFo and implement API*/
typedef struct{
	element_type* base;
	element_type* head;
	element_type* tail;
	uint32_t length;
	uint32_t count;
}FIFO_buf_t;

/* define enum to show the status for each API executed*/
typedef enum{
	FIFO_null, FIFO_full, FIFO_empty, FIFO_no_error
}buffer_status;

/* define FIFO API*/
extern buffer_status FIFO_init(FIFO_buf_t* fifo_buf, element_type* buf, uint32_t length);
extern buffer_status FIFO_add(FIFO_buf_t* fifo_buf, element_type item);
extern buffer_status FIFO_get(FIFO_buf_t* fifo_buf, element_type* item);
extern void FIFO_print(FIFO_buf_t* fifo_buf);
extern buffer_status FIFO_is_full(FIFO_buf_t* fifo_buf);

#endif
