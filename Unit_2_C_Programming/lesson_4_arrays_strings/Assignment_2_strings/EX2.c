
#include <stdio.h>

void main()
{
	char text[100];
	int i=1;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	while (text[i-1] != 0)
		++i;
	printf("\nLength of string: %d", i-1);
}

