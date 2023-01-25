/*
 * EX7.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	int a,i,fac=1;
	printf("Enter an integer: ");
	fflush(stdin); fflush (stdout);
	scanf("%d", &a);
	if (a < 0)
		printf("Error!!! factorial of negative numbers doesn't exist");
	else
	{
		for (i=2; i <= a; ++i)
			fac *= i;
		printf("Factorial = %d", fac);
	}
}
