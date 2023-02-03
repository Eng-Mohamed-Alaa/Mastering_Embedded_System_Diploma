
#include <stdio.h>

void print_prime (int st, int end)
{
	int i,j;
	printf("Prime numbers between %d and %d are: ", st, end);
	for (i=st; i <=end; ++i )
	{
		int is_prime =1;
		/* no need to iterate from 2 to i if the number is not divisible till its half value it's a prime
		 *  if number 2 and three are inside the interval, they will be printed without checking*/
		for(j=2; j < i/2 +1; ++j)
			if (i%j == 0)
			{
				is_prime=0;
				break;
			}
		if (is_prime && i !=1)
			printf("%d ", i);
	}
}

int main()
{
	int st,end;
	printf ("enter two numbers (interval): ");
	fflush (stdin); fflush (stdout);
	scanf("%d %d", &st, &end);
	print_prime (st,end);
	return 0;
}

