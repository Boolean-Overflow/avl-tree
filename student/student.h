#ifndef __STUDENT__
#define __STUDENT__

typedef struct Student {
  int number;
  char name[25];
  char birthdate[10];
} Student;

Student* create_student(Student data);
// Student* delete_student(Student* student);

#endif
