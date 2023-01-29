
#include <stdio.h>

void main()
{
	int i, no_elements, insert_location, insert_n, num[10];
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&no_elements);
	printf("\n");
	fflush(stdin); fflush(stdout);
	for (i=0; i < no_elements; ++i)
		scanf("%d",&num[i]);

	printf("\nEnter the element to be inserted: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&insert_n);
	printf("\nEnter the location: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&insert_location);

	for (i = no_elements-1; i >= insert_location-1; --i)
		num[i+1] = num[i];

	/* assuming user will not enter location larger than no_elements+1*/
	num[insert_location-1] = insert_n;
	no_elements++;
	printf("\n");
	for (i=0; i < no_elements; ++i)
		printf("%d ",num[i]);

}

