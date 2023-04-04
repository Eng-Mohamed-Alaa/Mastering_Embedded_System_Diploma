#include "stdio.h"
#include "linked_list.h"
#include "stdint.h"

unsigned int choice;

void front_end()
{
	dprintf("1: Add student\n");
	dprintf("2: Delete student\n");
	dprintf("3: View students\n");
	dprintf("4: Delete all\n");
	dprintf("5: View the Nth element from start\n");
	dprintf("6: View the Nth element from end\n");
	dprintf("7: View the total number of students by iterative function\n");
	dprintf("8: View the total number of students by recursive function\n");
	dprintf("9: Reverse the order of the list\n");
	dprintf("10: View the student at the middle\n");

	dprintf("Enter option number: ");
	scanf("%d",&choice);
}

int main(void)
{
	student_t list1;
	Student_List_init(&list1);
	uint32_t length;
	while(1)
	{
		front_end();
		switch(choice)
		{
		case 1:
			Student_add(&list1);
			break;
		case 2:
			Student_delete(&list1);
			break;
		case 3:
			Student_view(&list1);
			break;
		case 4:
			Student_delete_all(&list1);
			break;
		case 5:
			Student_view_Nth_from_start(&list1);
			break;
		case 6:
			Student_view_Nth_from_end(&list1);
			break;
		case 7:
			length = Student_list_length_iterative(&list1);
			dprintf("total number of students in the list = %d\n",length);
			break;
		case 8:
			length = Student_list_length_recursive(&list1);
			dprintf("total number of students in the list = %d\n",length);
			break;
		case 9:
			Student_list_reverse(&list1);
			break;
		case 10:
			Student_view_middle(&list1);
		}

		dprintf("===========================================\n");
	}
	return 0;
}
