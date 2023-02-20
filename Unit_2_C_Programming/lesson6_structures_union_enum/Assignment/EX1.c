
#include <stdio.h>

struct Sstudent {
	float marks;
	int roll_number;
	char name[50];
};

struct Sstudent read_student()
{
	struct Sstudent s;
	printf("Enter information of student:\n\n");
	printf("Enter name: ");
	fflush(stdout);
	scanf("%s", s.name);
	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d", &s.roll_number);
	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f", &s.marks);
	return s;
}

void print_student(struct Sstudent s)
{
	printf("\nDisplaying information:\n");
	printf("Name: %s\n", s.name);
	printf("Roll: %d\n", s.roll_number);
	printf("Marks: %.2f", s.marks);
}

int main()
{
	struct Sstudent s;
	s = read_student();
	print_student(s);
	return 0;
}

