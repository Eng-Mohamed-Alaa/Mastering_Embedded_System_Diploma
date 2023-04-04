
#ifndef LIFO_H_
#define LIFO_H_
#include "stdint.h"

/*user configuration to set data type for the elements to be stored*/
#define element_type uint16_t

/*define structure to control lifo and implement API*/
typedef struct{
	element_type* base;
	element_type* head;
	uint32_t length;
	uint32_t count;
}LIFO_buf_t;

/* define enum to show the status for each API executed*/
typedef enum{
	LIFO_null, LIFO_full, LIFO_empty, LIFO_no_error
}buffer_status;

/* define lifo API*/
extern buffer_status LIFO_init(LIFO_buf_t* lifo_buf, element_type* buf, uint32_t length);
extern buffer_status LIFO_add(LIFO_buf_t* lifo_buf, element_type item);
extern buffer_status LIFO_get(LIFO_buf_t* lifo_buf, element_type* item);
extern void LIFO_print(LIFO_buf_t* lifo_buf);
extern buffer_status LIFO_is_full(LIFO_buf_t* lifo_buf);

#endif
