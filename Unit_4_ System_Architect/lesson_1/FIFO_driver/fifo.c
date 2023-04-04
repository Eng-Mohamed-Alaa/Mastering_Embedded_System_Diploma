
#include "fifo.h"
#include "stdio.h"
#include "stdint.h"

buffer_status FIFO_init(FIFO_buf_t* fifo_buf, element_type* buf, uint32_t length)
{
	/* check that buf isn't null or length is set by zero */
	if(!buf || !length)
	{
		fifo_buf->base = fifo_buf->head = fifo_buf->tail = NULL;
		return FIFO_null;
	}

	/* initialize "fifo_buf" */
	fifo_buf->base = buf;
	fifo_buf->head = buf;
	fifo_buf->tail = buf;
	fifo_buf->length = length;
	fifo_buf->count = 0;
	return FIFO_no_error;
}

buffer_status FIFO_add(FIFO_buf_t* fifo_buf, element_type item)
{
	/* check that fifo_buf isn't null or full to be able to add item */
	if(!fifo_buf->base)
		return FIFO_null;
	if(FIFO_is_full(fifo_buf) == FIFO_full)
		return FIFO_full;

	*(fifo_buf->head) = item;
	fifo_buf->count++;

	if(fifo_buf->head+1 == (fifo_buf->base+fifo_buf->length))
		fifo_buf->head = fifo_buf->base;
	else
		fifo_buf->head++;
	return FIFO_no_error;
}
buffer_status FIFO_get(FIFO_buf_t* fifo_buf, element_type* item)
{
	/* check that fifo_buf isn't null or empty to be able to get value to be stored in *item */
	if(!fifo_buf->base)
		return FIFO_null;
	if(!fifo_buf->count)
		return FIFO_empty;

	*item = *(fifo_buf->tail);
	fifo_buf->count--;

	if(fifo_buf->tail+1 == (fifo_buf->base+fifo_buf->length))
		fifo_buf->tail = fifo_buf->base;
	else
		fifo_buf->tail++;
	return FIFO_no_error;
}

void FIFO_print(FIFO_buf_t* fifo_buf)
{
	/* check that fifo_buf isn't null or empty to be able to get value to be stored in *item */
	if(!fifo_buf->base)
		printf("\nFIFO is null");
	else if(!fifo_buf->count)
		printf("\nFIFO is empty");

	else
	{
		int i;
		element_type* temp = fifo_buf->tail;
		for(i=0; i < fifo_buf->count; ++i)
		{
			printf("element%d = %d\n", i+1,*temp);
			if(temp+1 == (fifo_buf->base+fifo_buf->length))
				temp = fifo_buf->base;
			else
				temp++;
		}
	}
}

buffer_status FIFO_is_full(FIFO_buf_t* fifo_buf)
{
	/* we should check if fifo_buf isn't null before we call this function */
	if(fifo_buf->count == fifo_buf->length)
		return FIFO_full;
	return FIFO_no_error;
}



