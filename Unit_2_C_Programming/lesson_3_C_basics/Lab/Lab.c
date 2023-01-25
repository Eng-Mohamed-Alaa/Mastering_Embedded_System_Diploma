/*
 * Lab.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	int i,j;
	for (i=0; i <= 9; ++i)
	{
		for (j=i; j <= 9; ++j)
			printf ("%d ",j);
		printf ("\n");
	}
}

