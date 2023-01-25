/*
 * EX4.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	float a, b;
	printf("Enter two numbers: ");
	fflush(stdin); fflush (stdout);
	scanf("%f %f", &a, &b);
	printf ("Product: %f", a*b);
}

