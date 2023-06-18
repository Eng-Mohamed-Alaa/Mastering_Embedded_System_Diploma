#ifndef STUDENT_H_
#define STUDENT_H_



typedef struct
{
	char fname[50];
	char lname[50];
	int roll_number;
	int course_id[5];
	float GPA;
}student_data;

typedef struct
{
	student_data *base;
	student_data *head;
	student_data *tail;
	int length;
	int count;

}FIFO_buf;

/*APIS prototypes*/
extern void student_buffer_init(FIFO_buf *buffer_struct,student_data *students,int length);
extern void student_add_file();
extern void student_add_manually();
extern void student_find_by_roll();
extern void student_find_by_fn();
extern void student_find_by_course();;
extern void student_total();
extern void student_delete();
extern void student_update();
extern void student_show_all();
#endif
