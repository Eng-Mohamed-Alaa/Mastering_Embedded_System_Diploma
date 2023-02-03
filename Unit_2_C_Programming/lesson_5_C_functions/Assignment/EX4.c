
#include <stdio.h>
#include <string.h>

int power (int n, int p)
{
	if (p==1)
		return n;
	else if(p==0)
		return 1;
	return n*power(n, p-1);

}
int main()
{
	int n,p;
	printf("Enter base number: ");
	fflush (stdin); fflush (stdout);
	scanf("%d", &n);
	printf("Enter power number(positive integer): ");
	fflush (stdin); fflush (stdout);
	scanf("%d", &p);
	printf("%d^%d = %d",n, p, power(n,p));
}

