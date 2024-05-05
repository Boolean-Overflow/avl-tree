#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

// Start Utility functions
Student* create_student(Student* student) {
  Student* createdStudent = (Student*)malloc(sizeof(Student));
  if (!createdStudent) {
    perror("Erro de Alocação");
    return NULL;
  }

  *createdStudent = *student;

  return createdStudent;
}

Avl* create_node(Student* student) {
  Avl* node = (Avl*)malloc(sizeof(Avl));
  if (!node) {
    perror("Erro de Alocação");
    return NULL;
  }
  node->left = node->right = NULL;
  node->student = create_student(student);
  node->height = 1;

  return node;
}




int get_height(Avl* root) {
  if (!root) return 0;
  return root->height;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int update_height(Avl* node) {
  return max(get_height(node->left), get_height(node->right)) + 1;
}

Avl* rotate_right(Avl* y) {
  Avl* x = y->left;
  Avl* aux = x->right;

  //rotate
  x->right = y;
  y->left = aux;

  // update height
  y->height = update_height(y);
  x->height = update_height(x);

  // new root
  return x;
}

Avl* rotate_left(Avl* x) {
  Avl* y = x->right;
  Avl* aux = y->left;

  //rotate
  y->left = x;
  x->right = aux;

  // update height
  x->height = update_height(x);
  y->height = update_height(y);

  // new root
  return y;
}

Avl* min_value_from(Avl* root) {
  Avl* node = root;

  while (node->left)
    node = node->left;

  return node;
}

int get_bf(Avl* root) {
  if (!root) return 0;

  return get_height(root->left) - get_height(root->right);
}

int get_key(Avl* tree) {
  return tree->student->number;
}

// Start ADT
Avl* add_student(Avl* root, Student* student) {
  if (!root) return create_node(student);

  int key = student->number;

  if (key > get_key(root))
    root->right = add_student(root->right, student);
  else if (key < get_key(root))
    root->left = add_student(root->left, student);
  else {
    puts("Chave já existente!");
    return root;
  }

  // update Height
  root->height = update_height(root);

  // check balance
  int bf = get_bf(root);

  if (bf > 1 && key < get_key(root->left))
    return rotate_right(root);

  if (bf < -1 && key > get_key(root->right))
    return rotate_left(root);

  if (bf > 1 && key > get_key(root->left)) {
    root->left = rotate_left(root->left);
    return rotate_right(root);
  }

  if (bf < -1 && key < get_key(root->right)) {
    root->right = rotate_right(root->right);
    return rotate_left(root);
  }

  return root;
}

Avl* remove_student(Avl* root, int key) {
  // return NULL if tree does not exist
  if (!root) return root;

  //
  if (key < get_key(root))
    root->left = remove_student(root->left, key);
  else if (key > get_key(root))
    root->right = remove_student(root->right, key);
  else {
    // checking if both children exists
    if (root->left && root->right) {
      Avl* temp = min_value_from(root->right);
      root->student = temp->student;
      root->right = remove_student(root->right, get_key(temp));
    }
    else {
      Avl* tmp = root->left ? root->left : root->right;
      if (!tmp) {
        tmp = root;
        root = NULL;
      }
      else
        *root = *tmp;

      free(tmp);
    }
  }

  // if the tree became empty
  if (!root) return root;

  root->height = update_height(root);

  int bf = get_bf(root);

  if (bf > 1 && get_bf(root->left) >= 0)
    return rotate_right(root);

  if (bf > 1 && get_bf(root->left) < 0) {
    root->left = rotate_left(root->left);
    return rotate_right(root);
  }

  if (bf < -1 && get_bf(root->right) <= 0)
    return rotate_left(root);

  if (bf < -1 && get_bf(root->right) > 0) {
    root->right = rotate_right(root->right);
    return rotate_left(root);
  }

  return root;
}

Student* find_student(Avl* tree, int key) {
  if (!tree) return NULL;

  if (key > get_key(tree))
    return find_student(tree->right, key);

  if (key < get_key(tree))
    return find_student(tree->left, key);

  return tree->student;
}

void print_student(Student* student) {
  if (!student) return;
  printf("[%2d] ", student->number);
  puts(student->name);
  puts(student->birthdate);
  puts("");
}

void print_in_order(Avl* tree) {
  if (!tree) return;

  // Print in order
  print_students(tree->left);

  print_student(tree->student);

  print_students(tree->right);
}

void print_students(Avl* tree) {
  if (!tree) return;

  // Print in order
  print_in_order(tree);
  puts("");
}

Avl* mirror(Avl* tree, Avl* mirrored_tree) {
  if (!tree) return NULL;

  mirrored_tree = add_student(mirrored_tree, tree->student);
  mirrored_tree->left = mirror(tree->right, mirrored_tree->left);
  mirrored_tree->right = mirror(tree->left, mirrored_tree->right);

  return mirrored_tree;
}

Avl* mirror_tree(Avl* tree) {
  if (!tree) return tree;
  Avl* mirrored_tree = NULL;

  return mirror(tree, mirrored_tree);
}