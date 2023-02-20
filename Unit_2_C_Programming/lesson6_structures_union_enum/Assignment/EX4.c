
#include <stdio.h>

struct Sstudent {
	float marks;
	int roll_number;
	char name[50];
};

struct Sstudent read_student()
{
	struct Sstudent s;
	static int roll=1;
	printf("\nFor roll number %d\n", roll);
	printf("Enter name: ");
	fflush(stdout);
	scanf("%s", s.name);
	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f", &s.marks);
	s.roll_number = roll++;
	return s;
}

void print_student(struct Sstudent s)
{
	printf("\nInformation for roll number %d\n", s.roll_number);
	printf("Name: %s\n", s.name);
	printf("Marks: %.2f\n", s.marks);
}

int main()
{
	struct Sstudent s[10];
	int i;
	printf("Enter information of students:\n");
	for(i=0; i < 10; ++i)
		s[i] = read_student();
	printf("\nDisplaying information of students:\n");
	for(i=0; i < 10; ++i)
		print_student(s[i]);
	return 0;
}

