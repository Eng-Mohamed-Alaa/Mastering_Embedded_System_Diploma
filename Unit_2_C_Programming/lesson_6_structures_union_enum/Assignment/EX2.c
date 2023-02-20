
#include <stdio.h>

struct Sdistance {
	int feet;
	float inch;
};

int main()
{
	struct Sdistance d1,d2,sum;
	printf("Enter information for 1st disatance\n");
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d",&d1.feet);
	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f",&d1.inch);
	printf("\nEnter information for 2nd disatance\n");
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d",&d2.feet);
	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f",&d2.inch);
	sum.feet = d1.feet + d2.feet+(d1.inch+d2.inch)/12;
	sum.inch = (d1.inch+d2.inch)-12;
	printf("sum of distance = %d'-%.1f\"", sum.feet, sum.inch);
	return 0;
}

