#include <stdio.h>
#include <stdlib.h>
void main()
{
	int i,n[1000],cnt;
	for ( i=cnt=0; i < 1000; ++i)
	{
		n[i] = rand();
		if (i >= 2 && n[i-1] > n[i] && n[i-1] > n[i-2])
			cnt++;
	}
	printf("the count of the numbers that satisfy the condition = %d", cnt);
}
