#include <stdio.h>

void print_triangle (int n)
{
	int i;
	for (i=0; i <= n; ++i)
		{
		int j;
		for (j=i; j <= n; ++j)
			printf("%d ",j);
		printf("\n");
		}
}

int main()
{
	print_triangle (9);
	return 0;
}
