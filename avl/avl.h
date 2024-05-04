#ifndef __AVL__
#define __AVL__
#include "../student/student.h"

typedef struct Node {
  int key;
  int height;
  Student* student;
  struct Node* left, * right;
} Avl;

Avl* insert_key(Avl* tree, int key);
Avl* remove_key(Avl* tree, int key);
void print_tree(Avl* tree);
int find_key(Avl* tree, int key);
Avl* mirror_tree(Avl* tree);

#endif