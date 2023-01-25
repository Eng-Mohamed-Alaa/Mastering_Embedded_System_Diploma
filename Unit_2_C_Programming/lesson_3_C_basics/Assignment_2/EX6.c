/*
 * EX6.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Mohamed Alaa
 */

#include <stdio.h>

void main()
{
	int i=1,a, sum=0;
	printf("Enter an integer: ");
	fflush(stdin); fflush (stdout);
	scanf("%d", &a);
	for (i=1; i <= a; ++i) /* declaration inside for loop is not supported in ANSI C*/
		sum += i;
	printf("Sum = %d", sum);
}
/* method2 which is faster
 * int a, sum=0;
 * printf("Enter an integer: ");
 * fflush(stdin); fflush (stdout);
 * scanf("%d", &a);
 * sum = a/2 * (a+1);
 * printf("Sum = %d", sum);
 * */
