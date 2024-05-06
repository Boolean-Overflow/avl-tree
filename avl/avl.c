#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

// Start Utility functions

/**
  * Create a new student based on input data
  * @param student Pointer to the student data to be copied
  * @result Pointer to the newly created student
 */
Student* create_student(Student* student) {
  Student* createdStudent = (Student*)malloc(sizeof(Student));
  if (!createdStudent) {
    perror("Erro de Alocação");
    return NULL;
  }

  // Copy data from input student to the new one
  *createdStudent = *student;

  return createdStudent;
}

/**
  * Create a new node for AVL tree
  * @param student: Pointer to the student data to be stored in the node
  * @return Pointer to the newly created AVL node
*/
Avl* create_node(Student* student) {
  Avl* node = (Avl*)malloc(sizeof(Avl));
  if (!node) {
    perror("Erro de Alocação");
    return NULL;
  }
  // Initialize left and right pointers to NULL
  node->left = node->right = NULL;

  // Assign student data to the node
  node->student = create_student(student);
  if (!node->student) {
    free(node);
    return NULL;
  }
  // Set initial height to 1
  node->height = 1;

  return node;
}

/**
  * Get height of a node in the AVL tree
  * @param root pointer to the node whose height is to be obtained
  * @result Height of the node
*/
int get_height(Avl* root) {
  if (!root) return 0;
  return root->height;
}

// Get maximum of two integers
int max(int a, int b) {
  return a > b ? a : b;
}

/**
 * Update height of a node
 * @param node Pointer to the node whose height is to be updated
 * @result Updated height of the node
*/
int update_height(Avl* node) {
  return max(get_height(node->left), get_height(node->right)) + 1;
}

/** Rotate subtree to the right
* @param y Pointer to the root of the subtree to be rotated
* @returns Pointer to the new root of the rotated subtree
*/
Avl* rotate_right(Avl* y) {
  Avl* x = y->left;
  Avl* aux = x->right;

  // Rotate
  x->right = y;
  y->left = aux;

  // Update height
  y->height = update_height(y);
  x->height = update_height(x);

  // New root
  return x;
}

/**
 * Rotate subtree to the left
 * @param x: Pointer to the root of the subtree to be rotated
 * @returns Pointer to the new root of the rotated subtree
*/
Avl* rotate_left(Avl* x) {
  Avl* y = x->right;
  Avl* aux = y->left;

  // Rotate
  y->left = x;
  x->right = aux;

  // Update height
  x->height = update_height(x);
  y->height = update_height(y);

  // New root
  return y;
}

// Find node with minimum value in a subtree
Avl* min_value_from(Avl* root) {
  Avl* node = root;

  while (node->left)
    node = node->left;

  return node;
}

// Get balance factor of a node
int get_bf(Avl* root) {
  if (!root) return 0;

  return get_height(root->left) - get_height(root->right);
}

// Get student number (key)
int get_key(Avl* tree) {
  return tree->student->number;
}

// Start ADT

/** Add a student to the AVL tree
  * @param root Pointer to the root of the AVL tree
  * @param student Pointer to the student data to be added
  * @result Pointer to the root of the updated AVL tree
*/
Avl* add_student(Avl* root, Student* student) {
  if (!root) return create_node(student);

  int key = student->number;

  // Recursive insertion
  if (key > get_key(root))
    root->right = add_student(root->right, student);
  else if (key < get_key(root))
    root->left = add_student(root->left, student);
  else {
    puts("Número de estudante já existente!");
    return root;
  }

  // Update height
  root->height = update_height(root);

  // Check balance
  int bf = get_bf(root);

  // Perform rotations if needed
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

/** Remove a student from the AVL tree
  * @param root Pointer to the root of the AVL tree
  * @param key Key of the student to be removed
  * @return Pointer to the root of the updated AVL tree
*/
Avl* remove_student(Avl* root, int key) {
  // Return NULL if tree does not exist
  if (!root) {
    puts("Estudante não encontrado!");
    return root;
  }

  // Recursive removal
  if (key < get_key(root))
    root->left = remove_student(root->left, key);
  else if (key > get_key(root))
    root->right = remove_student(root->right, key);
  else {
    // Checking if both children exist
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
      printf("Estudante com numero %d removido com sucesso\n", key);
    }
  }

  // If the tree became empty
  if (!root) return root;

  // Update height
  root->height = update_height(root);

  // Check balance
  int bf = get_bf(root);

  // Perform rotations if needed
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

/** Find a student by their number (key)
  * @param tree Pointer to the root of the AVL tree
  * @param key Key of the student to be found
  * @return Pointer to the found student, or NULL if not found
*/
Student* find_student(Avl* tree, int key) {
  if (!tree) return NULL;

  // Recursive search
  if (key > get_key(tree))
    return find_student(tree->right, key);

  if (key < get_key(tree))
    return find_student(tree->left, key);

  return tree->student;
}

/**
 * Print student data
 * @param student: Pointer to the student data to be printed
*/
void print_student_data(Student* student) {
  if (!student) return;
  printf("[%2d] %s %s\n", student->number, student->name, student->birthdate);
}

/**
 * Print students in the AVL tree (in order)
 * @param tree: Pointer to the root of the AVL tree
*/
void print_students(Avl* tree) {
  if (!tree) return;

  // Print in order
  print_students(tree->left);

  print_student_data(tree->student);

  print_students(tree->right);
}

/**
 * Mirror a subtree
 * @param tree Pointer to the root of the original subtree
 * @param mirrored_tree Pointer to the root of the mirrored subtree
 * @result Pointer to the root of the mirrored subtree
*/
Avl* mirror(Avl* tree, Avl* mirrored_tree) {
  if (!tree) return NULL;

  // Add current node to mirrored tree
  mirrored_tree = add_student(mirrored_tree, tree->student);
  // Recursively mirror left and right subtrees
  mirrored_tree->left = mirror(tree->right, mirrored_tree->left);
  mirrored_tree->right = mirror(tree->left, mirrored_tree->right);

  return mirrored_tree;
}

/**
 * Create a mirror image of the AVL tree
 * @param tree: Pointer to the root of the AVL tree
 * @resul  - Pointer to the root of the mirrored AVL tree
*/
Avl* mirror_tree(Avl* tree) {
  if (!tree) return tree;
  Avl* mirrored_tree = NULL;

  return mirror(tree, mirrored_tree);
}
