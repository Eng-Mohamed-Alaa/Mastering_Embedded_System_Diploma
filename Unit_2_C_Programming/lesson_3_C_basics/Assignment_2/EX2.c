/*
 * EX2.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	char ch;
	printf("Enter an alphabet : ");
	fflush(stdin); fflush (stdout);
	scanf("%c", &ch);
	switch (ch) /* I ignored capital letters ( ANSI c doesn't support ==> //) */
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	{
		printf("%c is a vowel.", ch);
		break;
	}
	default:
		printf("%c is a consonants.", ch);
	}
}

