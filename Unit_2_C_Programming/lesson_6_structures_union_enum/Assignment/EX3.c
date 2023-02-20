
#include <stdio.h>

struct Scomplex{
	float real,imaginary;
};

struct Scomplex read_complex()
{
	struct Scomplex c;
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f %f", &c.real, &c.imaginary);
	return c;
}

struct Scomplex add_complex(struct Scomplex c1, struct Scomplex c2)
{
	struct Scomplex r;
	r.real = c1.real + c2.real;
	r.imaginary = c1.imaginary + c2.imaginary;
	return r;
}


int main()
{
	struct Scomplex c1,c2,sum;
	printf("For 1st complex number\n");
	c1=read_complex();
	printf("\nFor 2st complex number\n");
	c2=read_complex();
	sum=add_complex(c1,c2);
	printf("\nSum = %.1f + %.1fi", sum.real, sum.imaginary);
	return 0;
}

