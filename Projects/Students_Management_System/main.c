#include "stdio.h"
#include "student.h"
#include "stdlib.h"

#define length 50
#define DPRINTF(...) {fflush(stdin); fflush(stdout);\
					  printf(__VA_ARGS__);\
					  fflush(stdin); fflush(stdout);}

student_data students[length];
FIFO_buf buffer_struct;

int menu()
{
	int choice;
	DPRINTF("Choose the task that you want to perform\n");
	DPRINTF("1. Add the student details from text file\n");
	DPRINTF("2. Add the student details manually\n");
	DPRINTF("3. Find the student details by roll number\n");
	DPRINTF("4. Find the student details by first name\n");
	DPRINTF("5. Find the student details by course ID\n");
	DPRINTF("6. Find the Total number of students\n");
	DPRINTF("7. Delete the student details by roll number\n");
	DPRINTF("8. Update the student details by roll number\n");
	DPRINTF("9. Show all students\n");
	DPRINTF("10. Exit\n");
	DPRINTF("Enter your choice number: ");
	scanf("%d",&choice);
	return choice;
}

int main(void)
{
	student_buffer_init(&buffer_struct, students,length);
	DPRINTF("Welcome to the student management system\n\n");
	while(1)
	{

		switch(menu())
		{
		case 1:
			student_add_file();
			break;
		case 2:
			student_add_manually();
			break;
		case 3:
			student_find_by_roll();
			break;
		case 4:
			student_find_by_fn();
			break;
		case 5:
			student_find_by_course();
			break;
		case 6:
			student_total();
			break;
		case 7:
			student_delete();
			break;
		case 8:
			student_update();
			break;
		case 9:
			student_show_all();
			break;
		case 10:
			exit(1);
			break;
		}
	}
	return 0;
}









