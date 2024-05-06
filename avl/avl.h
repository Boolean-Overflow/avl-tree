#ifndef __AVL__
#define __AVL__

typedef struct Student {
  int number;
  char name[25];
  char birthdate[11];
} Student;

typedef struct Node {
  int height;
  Student* student;
  struct Node* left, * right;
} Avl;

Avl* add_student(Avl* tree, Student* student);
Avl* remove_student(Avl* tree, int key);
void print_student_data(Student* student);
void print_students(Avl* tree);
Student* find_student(Avl* tree, int key);
Avl* mirror_tree(Avl* tree);

#endif