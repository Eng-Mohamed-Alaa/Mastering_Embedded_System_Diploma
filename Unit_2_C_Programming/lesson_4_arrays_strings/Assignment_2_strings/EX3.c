
#include <stdio.h>
#include <string.h>

void main()
{
	char text[100];
	int i;
	printf("Enter the string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	printf("Reverse string is: ");
	for (i = strlen(text)-1; i >=0; --i)
		printf("%c", text[i]);
}

