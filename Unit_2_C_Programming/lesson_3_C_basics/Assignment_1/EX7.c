/*
 * EX7.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	float a, b;
	printf("Enter value of a: ");
	fflush(stdin); fflush (stdout);
	scanf("%f", &a);
	printf("Enter value of b: ");
	fflush(stdin); fflush (stdout);
	scanf("%f", &b);
	a = a+b;
	b = a-b; // b = a+b-b = a
	a = a-b; // a= a+b-a=b
	printf("\nAfter swapping, value of a = %f \n", a);
	printf("After swapping, value of b = %f \n", b);
}

