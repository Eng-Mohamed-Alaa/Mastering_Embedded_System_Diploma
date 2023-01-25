/*
 * EX6.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	float a, b, temp;
	printf("Enter value of a: ");
	fflush(stdin); fflush (stdout);
	scanf("%f", &a);
	printf("Enter value of b: ");
	fflush(stdin); fflush (stdout);
	scanf("%f", &b);
	temp = a;
	a = b;
	b = temp;
	printf("\nAfter swapping, value of a = %f \n", a);
	printf("After swapping, value of b = %f \n", b);
}

