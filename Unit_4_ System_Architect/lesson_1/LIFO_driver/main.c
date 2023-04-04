#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "LIFO.h"
#define size 5

uint16_t buffer1 [size];

int main(void)
{
	int i, status;
	uint16_t *buffer2 = malloc(size*sizeof(uint16_t)), item;
	LIFO_buf_t uart_buf, I2C_buf;
	LIFO_init(&uart_buf, buffer1, size);
	LIFO_init(&I2C_buf, buffer2, size);

	printf("\n********* uart buffer **********\n\n======= adding values =======\n");
	for(i=0; i < 7; ++i)
	{
		status = LIFO_add(&uart_buf, i);
		if(status == LIFO_no_error)
			printf("adding value %d .....done\n",i);
		if(status != LIFO_no_error)
			printf("adding value %d .....failed\n",i);
	}

	printf("\n======= getting two values =======\n");
	status = LIFO_get(&uart_buf,&item);
	if(status == LIFO_no_error)
		printf("value1 = %d\n", item);
	else
		printf("getting value failed\n");

	status = LIFO_get(&uart_buf,&item);
	if(status == LIFO_no_error)
		printf("value2 = %d\n", item);
	else
		printf("getting value failed\n");

	printf("\n======= printing remaining elements =======\n");
	LIFO_print(&uart_buf);

	printf("\n********* I2C buffer **********\n\n======= adding values =======\n");
	for(i=0; i < 7; ++i)
	{
		status = LIFO_add(&I2C_buf, i);
		if(status == LIFO_no_error)
			printf("adding value %d .....done\n",i);
		if(status != LIFO_no_error)
			printf("adding value %d .....failed\n",i);
	}

	printf("\n======= getting two values =======\n");
	status = LIFO_get(&I2C_buf,&item);
	if(status == LIFO_no_error)
		printf("value1 = %d\n", item);
	else
		printf("getting value failed\n");

	status = LIFO_get(&I2C_buf,&item);
	if(status == LIFO_no_error)
		printf("value2 = %d\n", item);
	else
		printf("getting value failed\n");

	printf("\n======= printing remaining elements =======\n");
	LIFO_print(&I2C_buf);
	return 0;
}

