#include "lifo.h"
#include "stdio.h"
#include "stdint.h"

buffer_status LIFO_init(LIFO_buf_t* lifo_buf, element_type* buf, uint32_t length)
{
	/* check that buf isn't null or length is set by zero */
	if(!buf || !length)
	{
		lifo_buf->base = lifo_buf->head = NULL;
		return LIFO_null;
	}

	/* initialize "lifo_buf" */
	lifo_buf->base = buf;
	lifo_buf->head = buf;
	lifo_buf->length = length;
	lifo_buf->count = 0;
	return LIFO_no_error;
}

buffer_status LIFO_add(LIFO_buf_t* lifo_buf, element_type item)
{
	/* check that lifo_buf isn't null or full to be able to add item */
	if(!lifo_buf->base)
		return LIFO_null;
	if(LIFO_is_full(lifo_buf) == LIFO_full)
		return LIFO_full;

	*(lifo_buf->head++) = item;
	lifo_buf->count++;
	return LIFO_no_error;
}
buffer_status LIFO_get(LIFO_buf_t* lifo_buf, element_type* item)
{
	/* check that lifo_buf isn't null or empty to be able to get value to be stored in *item */
	if(!lifo_buf->base)
		return LIFO_null;
	if(!lifo_buf->count)
		return LIFO_empty;

	*item = *(--lifo_buf->head);
	lifo_buf->count--;

	return LIFO_no_error;
}

void LIFO_print(LIFO_buf_t* lifo_buf)
{
	/* check that lifo_buf isn't null or empty to be able to get value to be stored in *item */
	if(!lifo_buf->base)
		printf("\nLIFO is null");
	else if(!lifo_buf->count)
		printf("\nLIFO is empty");

	else
	{
		int i;
		element_type* temp = lifo_buf->head;
		for(i=0; i < lifo_buf->count; ++i)
		{
			printf("element%d = %d\n", i+1,*(--temp));
		}
	}
}

buffer_status LIFO_is_full(LIFO_buf_t* lifo_buf)
{
	/* we should check if lifo_buf isn't null before we call this function */
	if(lifo_buf->count == lifo_buf->length)
		return LIFO_full;
	return LIFO_no_error;
}



