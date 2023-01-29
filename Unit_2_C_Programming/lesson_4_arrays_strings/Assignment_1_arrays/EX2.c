
#include <stdio.h>

void main()
{
	int i,n;
	float num[10], sum;
	printf("Enter the numbers of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	for (i=sum=0; i < n; ++i)
	{
		printf("%d. Enter number: ", i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f", &num[i]);
		sum += num[i];
	}
	printf("Average = %.2f",sum/n);
}

