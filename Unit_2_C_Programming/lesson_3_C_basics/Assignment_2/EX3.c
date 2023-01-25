/*
 * EX3.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	float a, b, c, max;
	printf("Enter three numbers: ");
	fflush(stdin); fflush (stdout);
	scanf("%f %f %f", &a, &b, &c);
	max = a;
	if (max < b)
		max = b;
	if (max < c)
		max = c;
	printf ("Largest number = %f", max);
}

