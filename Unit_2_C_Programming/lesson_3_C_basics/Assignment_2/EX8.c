/*
 * EX8.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	float a,b;
	char op;
	printf("Enter operator either + or - or * or divide: ");
	fflush(stdin); fflush (stdout);
	scanf("%c", &op);
	printf("Enter two operands: ");
	fflush(stdin); fflush (stdout);
	scanf("%f %f", &a, &b);

	switch (op)
	{
	case '+':
		printf("%f + %f = %f", a, b, a+b);
		break;
	case '-':
		printf("%f - %f = %f", a, b, a-b);
		break;
	case '*':
		printf("%f * %f = %f", a, b, a*b);
		break;
	case '/':
		if (b == 0)
			printf("Can't divide by zero.");
		else
			printf("%f / %f = %f", a, b, a/b);
		break;
	}
}
