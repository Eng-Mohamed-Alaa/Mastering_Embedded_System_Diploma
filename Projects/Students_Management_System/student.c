#include "stdio.h"
#include "student.h"
#include "string.h"
#include "stdlib.h"

#define upper_limit (students_buf->base+students_buf->length-1)
#define DPRINTF(...) {fflush(stdin); fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdin); fflush(stdout);}



FIFO_buf *students_buf;

typedef enum {
	new,
	taken
}roll_status;

static roll_status roll_check(int roll_number);
static void move_head();
static void move_tail();
static void print_student(student_data *student);
static void shift_up(student_data *student);

static roll_status roll_check(int roll_number)
{
	student_data *student = students_buf->tail;
	for(int i=0; i < students_buf->count; ++i)
	{
		if(student->roll_number == roll_number)
		{
			return taken;
		}

		((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
	}
	return new;
}

static void move_head()
{
	((students_buf->head+1) <= upper_limit) ?
			(students_buf->head++) : (students_buf->head = students_buf->base);
	students_buf->count++;
}

static void move_tail()
{
	((students_buf->tail+1) <= upper_limit) ?
			(students_buf->tail++) : (students_buf->tail = students_buf->base);
	students_buf->count--;
}

static void print_student(student_data *student)
{
	DPRINTF("*****The student details are*****\n");
	DPRINTF("Roll number: %d\n",student->roll_number);
	DPRINTF("First name: %s\n",student->fname);
	DPRINTF("Last name: %s\n",student->lname);
	DPRINTF("GPA: %.1f\n",student->GPA);

	for(int i=0; i < 5; ++i)
	{
		DPRINTF("course %d ID: %d\n",i+1,student->course_id[i]);
	}
	DPRINTF("----------------------------------------------------------\n");
}

static void shift_up(student_data *student)
{
	student_data *previous_student = student;
	while(student != students_buf->tail)
	{
		//calculate the previous student pointer
		((previous_student-1) < students_buf->base)?
				(previous_student = upper_limit) : (previous_student--);
		//replace the current student data by the previous student data
		*student = *previous_student;
		//move the current student pointer to the previous student
		student = previous_student;
	}
	move_tail();
}

void student_buffer_init(FIFO_buf *buffer_struct,student_data *students,int length)
{
	//initialize the FIFO buffer called  students_buf
	students_buf = buffer_struct;
	students_buf->base = students;
	students_buf->head = students;
	students_buf->tail = students;
	students_buf->length = length;
	students_buf->count = 0;
}

void student_add_file()
{
	//check if the there is a space to add a student
	if(students_buf->count < students_buf->length)
	{
		FILE *students_file = NULL;
		students_file = fopen("Students_list.txt","r");

		//check if the file is not opened
		if(!students_file)
		{
			DPRINTF("File can not be opened\n");
			DPRINTF("----------------------------------------------------------\n");
			return;
		}

		char data[200];
		int roll_to_check;

		//loop to read and store data
		//till the end of the file and the count of the students < the maximum
		while(!feof(students_file) && students_buf->count < students_buf->length)
		{
			fscanf(students_file,"%s",data);
			roll_to_check = atoi(data);

			//check if the roll number is taken by another student
			//if true read the line without storing data
			if(roll_check(roll_to_check) == taken)
			{
				DPRINTF("[Error] roll number %d is already taken\n",roll_to_check);
				fgets(data,200,students_file);
			}
			//if roll number is new read and store the data of the student
			else
			{
				students_buf->head->roll_number = roll_to_check;
				fscanf(students_file,"%s",students_buf->head->fname);
				fscanf(students_file,"%s",students_buf->head->lname);
				fscanf(students_file,"%s",data);
				students_buf->head->GPA = atof(data);
				for(int i=0; i < 5; ++i)
				{
					fscanf(students_file,"%s",data);
					students_buf->head->course_id[i] = atoi(data);
				}
				DPRINTF("Roll number %d is saved successfully\n", students_buf->head->roll_number);
				//move the head
				move_head();
			}
		}
		DPRINTF("----------------------------------------------------------\n");
		//close the file
		fclose(students_file);
		return;
	}
	DPRINTF("The list is full, can not add a student\n");
	DPRINTF("----------------------------------------------------------\n");
}

void student_add_manually()
{
	//check if the there is a space to add a student
	if(students_buf->count < students_buf->length)
	{
		int roll_to_check;
		DPRINTF("Enter the roll number: ");
		scanf("%d",&roll_to_check);

		//check if the roll number is taken by another student
		if(roll_check(roll_to_check) == taken)
		{
			DPRINTF("[Error] roll number %d is already taken\n",roll_to_check);
			DPRINTF("----------------------------------------------------------\n");
			return;
		}

		//if roll number is new read and store the data of the student
		students_buf->head->roll_number = roll_to_check;
		DPRINTF("Enter the first name of the student: ");
		scanf("%s",students_buf->head->fname);
		DPRINTF("Enter the last name of the student: ");
		scanf("%s",students_buf->head->lname);
		DPRINTF("Enter the GPA obtained: ");
		scanf("%f",&students_buf->head->GPA);
		for(int i=0; i < 5; ++i)
		{
			DPRINTF("Course %d ID: ",i+1);
			scanf("%d",&students_buf->head->course_id[i]);
		}
		DPRINTF("Roll number %d is saved successfully\n", students_buf->head->roll_number);
		DPRINTF("----------------------------------------------------------\n");

		//move the head
		move_head();
		return;
	}

	DPRINTF("The list is full, can not add a student\n");
	DPRINTF("----------------------------------------------------------\n");
}

void student_find_by_roll()
{
	//read the roll number
	int roll_number;
	DPRINTF("Enter the roll number of the student: ");
	scanf("%d",&roll_number);

	//navigate the stored data to find the roll number
	student_data *student = students_buf->tail;
	for(int i=0; i < students_buf->count; ++i)
	{
		if(student->roll_number == roll_number)
		{
			print_student(student);
			return;
		}

		((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
	}
	DPRINTF("No student has this roll number\n");
	DPRINTF("----------------------------------------------------------\n");
}

void student_find_by_fn()
{
	//read the first name
	char fname[50];
	char not_found = 1;
	DPRINTF("Enter the first name of the student: ");
	scanf("%s",fname);

	//navigate the stored data to find the students have this first_name
	student_data *student = students_buf->tail;
	for(int i=0; i < students_buf->count; ++i)
	{
		if(!strcmp(student->fname, fname))
		{
			print_student(student);
			not_found = 0;
		}

		((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
	}
	if(not_found)
	{
		DPRINTF("No student has this first name\n");
		DPRINTF("----------------------------------------------------------\n");

	}
}
void student_find_by_course()
{
	//read the course ID
	int course_id,count=0;
	DPRINTF("Enter the course ID of the student: ");
	scanf("%d",&course_id);

	//navigate the stored data to find the students have this course ID
	student_data *student = students_buf->tail;
	for(int i=0; i < students_buf->count; ++i)
	{
		for(int j=0; j < 5; ++j)
		{
			if(student->course_id[j] == course_id)
			{
				print_student(student);
				count++;
				break;
			}
		}
		((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
	}
	if(count)
	{
		DPRINTF("The total number of enrolled students in the course = %d\n",count);
		DPRINTF("----------------------------------------------------------\n");
		return;
	}
	DPRINTF("No student is enrolled in this course\n");
	DPRINTF("----------------------------------------------------------\n");
}

void student_total()
{
	DPRINTF("The total number of the students is %d\n",students_buf->count);
	DPRINTF("You can add up to %d students\n",students_buf->length);
	DPRINTF("You can add %d more students\n",students_buf->length-students_buf->count);
	DPRINTF("----------------------------------------------------------\n");

}

void student_delete()
{
	//read the roll number of the student to be deleted
	int roll_number;
	DPRINTF("Enter the roll number of the student to be deleted: ");
	scanf("%d",&roll_number);

	//navigate the stored data to find the roll number
	student_data *student = students_buf->tail;
	for(int i=0; i < students_buf->count; ++i)
	{
		if(student->roll_number == roll_number)
		{
			shift_up(student);
			DPRINTF("The student with roll number %d is deleted successfully\n", roll_number);
			DPRINTF("----------------------------------------------------------\n");
			return;
		}

		((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
	}
	DPRINTF("No student has this roll number\n");
	DPRINTF("----------------------------------------------------------\n");
}

void student_update()
{
	int roll_number;
	DPRINTF("Enter the roll number to update the entry: ");
	scanf("%d", &roll_number);
	student_data *student = students_buf->tail;
	for(int i=0; i < students_buf->count; ++i)
	{
		if(student->roll_number == roll_number)
		{
			int choice;
			DPRINTF("1. First name\n");
			DPRINTF("2. Last name\n");
			DPRINTF("3. roll no\n");
			DPRINTF("4. GPA\n");
			DPRINTF("5. Courses\n");
			DPRINTF("Enter your choice number: ");
			scanf("%d",&choice);
			switch(choice)
			{
			case 1:
				DPRINTF("Enter the new first name: ");
				scanf("%s",student->fname);
				break;
			case 2:
				DPRINTF("Enter the new last name: ");
				scanf("%s",student->lname);
				break;
			case 3:
				DPRINTF("Enter the new roll number: ");
				scanf("%d",&student->roll_number);
				break;
			case 4:
				DPRINTF("Enter the new GPA: ");
				scanf("%f",&student->GPA);
				break;
			case 5:
				for(int i=0; i < 5; ++i)
				{
					DPRINTF("Course %d ID: ",i+1);
					scanf("%d",&student->course_id[i]);
				}
				break;
			}
			DPRINTF("Updated successfully\n");
			DPRINTF("----------------------------------------------------------\n");
			return;
		}

		((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
	}
	DPRINTF("No student has this roll number\n");
	DPRINTF("----------------------------------------------------------\n");
}

void student_show_all()
{
	if(students_buf->count)
	{
		student_data *student = students_buf->tail;
		for(int i=0; i < students_buf->count; ++i)
		{
			print_student(student);
			((student+1) <= upper_limit) ? student++ : (student = students_buf->base);
		}
		return;
	}

	DPRINTF("No students are stored in the system\n")
	DPRINTF("----------------------------------------------------------\n");
}


