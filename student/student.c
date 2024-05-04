#include<stdlib.h>
#include "student.h"

Student* create_student(Student studentData) {
  Student* student = (Student*)malloc(sizeof(Student));
  if (!student) return NULL;

  student->number = studentData.number;
  *(student->name) = *(studentData.name);
  *(student->birthdate) = *(studentData.birthdate);

  return student;
}