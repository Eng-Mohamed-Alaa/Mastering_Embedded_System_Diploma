/*
 * EX3.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	int a, b;
	printf("Enter two integers: ");
	fflush(stdin); fflush (stdout);
	scanf("%d %d", &a, &b);
	printf ("Sum: %d", a+b);
}

