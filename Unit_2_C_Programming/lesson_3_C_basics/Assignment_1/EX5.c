/*
 * EX5.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	char a;
	printf("Enter a character: ");
	fflush(stdin); fflush (stdout);
	scanf("%c", &a);
	printf ("ASCII value of %c = %d", a, a);
}

