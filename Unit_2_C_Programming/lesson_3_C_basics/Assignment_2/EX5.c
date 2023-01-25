/*
 * EX5.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	char ch;
	printf("Enter a character: ");
	fflush(stdin); fflush (stdout);
	scanf("%c", &ch);
	if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
		printf ("%c is an alphabet.", ch);
	else
	printf ("%c is not an alphabet.", ch);
}

