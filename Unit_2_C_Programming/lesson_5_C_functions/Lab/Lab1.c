#include <stdio.h>
#include <string.h>
int findName(char names [][14],int n, char name [14])
{
	for (; n-1 >= 0; --n)
		if (!strcmp(names [n-1], name))
			return 1;
	return 0;

}

int main()
{
	char name [14];
	char names [5][14] = {"Alaa", "Osama", "Mamdouh", "Samy", "Hossain"};
	printf ("Enter your first name: ");
	fflush(stdin); fflush(stdout);
	gets (name);
	if (findName (names, 5, name)==1)
		printf("Welcome");
	else
		printf("Goodbye");
	return 0;
}
