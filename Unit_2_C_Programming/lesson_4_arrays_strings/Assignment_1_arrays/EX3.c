
#include <stdio.h>

void main()
{
	int i,j,r,c;
	int mat[10][10],t_mat[10][10];
	printf("Enter rows and columns of matrix: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &r, &c);
	printf("Enter elements of matrix:\n");
	for(i=0; i < r; ++i)
		for(j=0; j < c; ++j)
		{
			printf("Enter element a%d%d: ", i+1, j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d", &mat[i][j]);
			t_mat[j][i] = mat[i][j];
		}
	printf("\nEntered Matrix:\n");
	for(i=0; i < r; ++i)
	{
		for(j=0; j < c; ++j)
			printf("%d ",mat[i][j]);
		printf("\n");
	}
	printf("\nTranspose of Matrix:\n");
	for(i=0; i < c; ++i)
	{
		for(j=0; j < r; ++j)
			printf("%d ",t_mat[i][j]);
		printf("\n");
	}
}
