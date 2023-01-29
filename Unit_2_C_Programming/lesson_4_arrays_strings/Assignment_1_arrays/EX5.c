
#include <stdio.h>

void main()
{
	int i, no_elements, num[10], n_search;
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &no_elements);
	printf("\n");
	fflush(stdin); fflush(stdout);

	for (i=0; i < no_elements; ++i)
		scanf("%d", &num[i]);

	printf("\nEnter the element to be searched: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n_search);

	for (i=0; i < no_elements; ++i)
		if (num[i] == n_search)
			break;
	if (i == no_elements)
		printf("\nNumber not found");
	else
		printf("\nNumber found at the location = %d", i+1);

}

