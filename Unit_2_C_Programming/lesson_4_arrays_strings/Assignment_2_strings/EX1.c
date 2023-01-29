
#include <stdio.h>
#include <string.h>
void main()
{
	char text[100], ch;
	int i, freq;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	printf("\nEnter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&ch);
	for (i=0, freq=0; i < strlen(text); ++i)
		if (ch == text[i])
			++freq;
	printf("\nFrequency of %c = %d", ch, freq);
}

