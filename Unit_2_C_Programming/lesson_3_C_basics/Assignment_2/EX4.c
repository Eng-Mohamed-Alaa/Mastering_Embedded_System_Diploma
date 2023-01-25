/*
 * EX4.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	float a;
	printf("Enter a number: ");
	fflush(stdin); fflush (stdout);
	scanf("%f", &a);
	if (a > 0)
		printf("%f is positive", a);
	if (a < 0)
		printf("%f is negative", a);
	if (a == 0)
		printf("You entered zero.");
}

