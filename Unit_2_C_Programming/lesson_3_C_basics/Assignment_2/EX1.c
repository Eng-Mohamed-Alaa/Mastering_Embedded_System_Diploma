/*
 * EX1.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	int n;
	printf("Enter an integer you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	if (n%2 == 0)
		printf("%d is even.", n);
	else
		printf("%d is odd.", n);
}

