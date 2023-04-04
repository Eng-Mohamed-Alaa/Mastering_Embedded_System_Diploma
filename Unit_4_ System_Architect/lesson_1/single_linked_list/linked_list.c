#include"linked_list.h"

list_status Student_List_init(student_t* base)
{
	/*check if list base exist as the base structure can be in heap*/
	if(!base)
		return list_null;

	/*before initializing the list we should check if the list is enabled
	 * by adding a member to the structure of student_t and is enabled by user in main.c but i ignored it
	 * initialize the list list*/
	base->next_student = NULL;
	return list_no_error;
}

list_status Student_add(student_t* base)
{
	/*check if list base exist*/
	if(!base)
		return list_null;

	/*allocate storage in heap for a new student and check if it's done*/
	student_t* new_student = (student_t*)malloc(sizeof(student_t));
	if(!new_student)
		return list_student_not_added;

	/*find the last_student*/
	student_t* last_student = base;
	while(last_student->next_student)
		last_student = last_student->next_student;

	/*last student will point to the new student
	 * the new student will be the real last student by pointing to null*/
	last_student->next_student = new_student;
	new_student->next_student = NULL;

	/*tell user to enter the data to be stored*/
	char input[12];
	dprintf("Enter the ID: ");
	gets(input);
	new_student->data.id = atoi(input);

	dprintf("Enter the student full name: ");
	gets((char *)new_student->data.name);

	dprintf("Enter the height: ");
	gets(input);
	new_student->data.height = atof(input);
	return list_no_error;
}

list_status Student_delete(student_t* base)
{
	uint32_t id;
	dprintf("Enter student ID to be deleted: ");
	scanf("%d",&id);

	/*check if list base exist*/
	if(!base)
		return list_null;

	/*check if the list isn't empty*/
	if(!base->next_student)
		return list_empty;

	/*find the student with the desired id to be deleted*/
	student_t *student_delete = base->next_student, *student_previous_delete=base;
	while(student_delete->data.id != id)
	{

		student_previous_delete = student_delete;
		student_delete = student_delete->next_student;
		/*check if you reached the end of the list*/
		if(!student_delete)
			return list_no_such_id;
	}
	/*student before the one to be deleted points to the one after the deleted student
	 * student is deleted and it's location is free*/
	student_previous_delete->next_student = student_delete->next_student;
	free(student_delete);
	return list_no_error;
}

void Student_view(student_t* base)
{
	/*check if list exist*/
	if(!base)
		dprintf("\nList doesn't exist\n");

	/*check if list isn't empty*/
	if(!base->next_student)
		dprintf("\nList is empty\n");

	/*create new pointer to student_t for looping and printing elements*/
	student_t* student = base->next_student;
	int i=0;
	while(student)
	{
		dprintf("\nRecord number %d\n",++i);
		dprintf("ID: %d\n", student->data.id);
		dprintf("name: %s\n", student->data.name);
		dprintf("height: %.1f\n", student->data.height);

		student = student->next_student;
	}
}

list_status Student_delete_all(student_t* base)
{
	/*check if list base exist*/
	if(!base)
		return list_null;

	/*check if the list isn't empty*/
	if(!base->next_student)
		return list_empty;

	student_t *student_delete=base->next_student, *student_next_delete=(student_delete->next_student);
	while(1)
	{
		free(student_delete);
		if(student_next_delete)
		{
			student_delete = student_next_delete;
			student_next_delete = student_next_delete->next_student;
			continue;
		}
		break;
	}

	/*reset the base member next_student to point to null*/
	base->next_student=NULL;
	return list_no_error;
}

void Student_view_Nth_from_start(student_t* base)
{
	/*check if list exist*/
	if(!base)
		dprintf("\nList doesn't exist\n");

	/*check if list isn't empty*/
	if(!base->next_student)
		dprintf("\nList is empty\n");

	uint32_t index,count=1;
	dprintf("Enter the student order form the start: ");
	scanf("%d",&index);

	student_t* student = base->next_student;

	/*looping until count = index or no such index*/
	while(student)
	{
		if(count == index)
		{
			dprintf("\nStudent number %d from start\n",index);
			dprintf("ID: %d\n", student->data.id);
			dprintf("name: %s\n", student->data.name);
			dprintf("height: %.1f\n", student->data.height);
			return;
		}
		student = student->next_student;
		count++;
	}
	dprintf("\nNo such student with this order\n");
}

void Student_view_Nth_from_end(student_t* base)
{
	/*check if list exist*/
	if(!base)
		dprintf("\nList doesn't exist\n");

	/*check if list isn't empty*/
	if(!base->next_student)
		dprintf("\nList is empty\n");

	uint32_t index,count;
	dprintf("Enter the student order form the end: ");
	scanf("%d",&index);
	count = index-1;
	student_t *last_student = base->next_student, *ref_student = base->next_student;

	while(count--)
	{
		/*check if the length is less than the index*/
		if(!last_student->next_student)
		{
			dprintf("\nNo such student with this order\n");
			return;
		}
		/*else last_student moves till it reaches the required start
		 *to measure the difference in the next block of code when it reaches the null*/
		last_student = last_student->next_student;
	}

	/*looping until count = index or no such index*/
	while(last_student->next_student)
	{
		last_student = last_student->next_student;
		ref_student = ref_student->next_student;
	}

	dprintf("\nStudent number %d from the end\n",index);
	dprintf("ID: %d\n", ref_student->data.id);
	dprintf("name: %s\n", ref_student->data.name);
	dprintf("height: %.1f\n", ref_student->data.height);

	/*there is another method but slower by looping to find the length
	 *calculate the order from the start
	 *loop with counter till reach the element */
}

uint32_t Student_list_length_iterative(student_t* base)
{

	/*check if list base exist*/
	if(!base)
		return -1;

	/*check if the list isn't empty*/
	if(!base->next_student)
		return 0;

	student_t *student=base->next_student;
	uint32_t length = 1;
	while(student->next_student)
	{
		student = student->next_student;
		++length;
	}
	return length;
}

uint32_t Student_list_length_recursive(student_t* base)
{
	/*check if list base exist*/
	if(!base)
		return -1;

	/*check if the list isn't empty*/
	if(!base->next_student)
		return 0;

	student_t *student = base->next_student;
	uint32_t length = 1 + Student_list_length_recursive(student);



	return length;
}

void Student_view_middle(student_t* base)
{
	/*check if list exist*/
	if(!base)
	{
		dprintf("\nList doesn't exist\n");
		return;
	}

	/*check if list isn't empty*/
	if(!base->next_student)
	{
		dprintf("\nList is empty\n");
		return;
	}

	student_t *middle_student = base->next_student, *last_student = base->next_student;
	while(last_student->next_student)
	{
		middle_student = middle_student->next_student;
		last_student = last_student->next_student;
		if(!last_student->next_student)
			break;
		last_student = last_student->next_student;
	}

	dprintf("The student at the middle\n");
	dprintf("ID: %d\n", middle_student->data.id);
	dprintf("name: %s\n", middle_student->data.name);
	dprintf("height: %.1f\n", middle_student->data.height);
}

extern list_status Student_list_reverse(student_t* base)
{
	/*check if list base exist*/
	if(!base)
		return list_null;

	/*check if the list isn't empty*/
	if(!base->next_student)
		return list_empty;

	student_t *previous_student = base->next_student, *student = NULL;
	void* temp = NULL;

	/*check there is more than 1 student
	 *move student to the 2nd student
	 *store the address of the 3rd student in temp
	 *1st points to null
	 *2nd points to 1st
	 *move previous_student and student one step forward*/
	if(previous_student->next_student)
	{
		student = previous_student->next_student;
		temp = student->next_student;
		previous_student->next_student = NULL;
		student->next_student = previous_student;
		previous_student = student;
		student = temp;
	}

	/*check student doesn't reached the null
	 *store the address of the student after the current one in temp
	 *make the current student points to the previous
	 *move previous_student and student one step forward
	 *repeat*/
	while(student)
	{
		temp = student->next_student;
		student->next_student = previous_student;
		previous_student = student;
		student = temp;
	}

	/*check there is more than 1 student
	 *make the 1st student after the base the last one in old list which is previous_student*/

	if(previous_student->next_student)
		base->next_student = previous_student;

	return list_no_error;
}





