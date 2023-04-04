#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include"stdint.h"
#include"stdio.h"
#include"stdlib.h"

#define dprintf(...) 	{fflush(stdout);fflush(stdin);\
						printf(__VA_ARGS__);\
						fflush(stdout);fflush(stdin);}

typedef struct{
	uint32_t id;
	int8_t name[80];
	float height;
}data_t;

typedef struct{
	data_t data;
	void* next_student;
}student_t;

typedef enum{
	list_empty ,list_no_error, list_null, list_student_not_added, list_no_such_id, list_init
}list_status;

extern list_status Student_List_init(student_t* base);
extern list_status Student_add(student_t* base);
extern list_status Student_delete(student_t* base);
extern void Student_view(student_t* base);
extern list_status Student_delete_all(student_t* base);
extern void Student_view_Nth_from_start(student_t* base);
extern void Student_view_Nth_from_end(student_t* base);
uint32_t Student_list_length_iterative(student_t* base);
uint32_t Student_list_length_recursive(student_t* base);
void Student_view_middle(student_t* base);
extern list_status Student_is_loop(student_t* base);
extern list_status Student_list_reverse(student_t* base);

#endif


