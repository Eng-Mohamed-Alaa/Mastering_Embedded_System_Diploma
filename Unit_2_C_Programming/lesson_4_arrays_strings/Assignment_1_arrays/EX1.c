
#include <stdio.h>

void main()
{
	int i,j;
	float a[2][2], b[2][2], res[2][2];
	printf("Enter the elements of the 1st matrix\n");
	for (i=0; i < 2; ++i)
		for (j=0; j < 2; ++j)
		{
			printf("Enter a%d%d: ", i+1, j+1);
			fflush(stdin);	fflush(stdout);
			scanf("%f", &a[i][j]);
		}
	printf("Enter the elements of the 2nd matrix:\n");
	for (i=0; i < 2; ++i)
		for (j=0; j < 2; ++j)
		{
			printf("Enter a%d%d: ", i+1, j+1);
			fflush(stdin);	fflush(stdout);
			scanf("%f", &b[i][j]);
			res[i][j] = a[i][j]+b[i][j];
		}
	printf("\r\nSum Of Matrix:\n");
	for (i=0; i < 2; ++i)
		printf("%.1f	%.1f\n", res[i][0], res[i][1]);

}

