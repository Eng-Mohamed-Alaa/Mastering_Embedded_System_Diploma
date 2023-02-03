
#include <stdio.h>
#include <string.h>

void print_reverse (char str[], int index)
{
	if (index >=0)
	{
		printf ("%c", str[index]);
		print_reverse (str, index-1);
	}
	return;
}
int main()
{
	char str[100];
	printf ("Enter a sentence: ");
	fflush (stdin); fflush (stdout);
	gets (str);
	printf("\n");
	print_reverse (str, strlen(str)-1);
	return 0;
}

