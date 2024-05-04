#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

// Start Utility functions
Avl* create_node(Student studentData) {
  Avl* node = (Avl*)malloc(sizeof(Avl));
  if (!node) {
    perror("Insuficient memory\n");
    return NULL;
  }

  node->left = node->right = NULL;
  node->key = studentData.number;
  node->student = create_student(studentData);
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

Avl* min_value_node(Avl* root) {
  Avl* node = root;
  while (node->left)
    node = node->left;

  return node;
}

int get_bf(Avl* root) {
  if (!root) return 0;

  return get_height(root->left) - get_height(root->right);
}

// Start ADT
Avl* insert_key(Avl* root, Student studentData) {

  if (!root) return create_node(studentData);

  int key = studentData.number;

  if (key > root->key)
    root->right = insert_key(root->right, studentData);
  else if (key < root->key)
    root->left = insert_key(root->left, studentData);
  else {
    puts("Chave já existente!");
    return root;
  }

  // update Height
  root->height = update_height(root);

  // check balance
  int bf = get_bf(root);

  if (bf > 1 && key < root->left->key)
    return rotate_right(root);

  if (bf < -1 && key > root->right->key)
    return rotate_left(root);

  if (bf > 1 && key > root->left->key) {
    root->left = rotate_left(root->left);
    return rotate_right(root);
  }

  if (bf < -1 && key < root->right->key) {
    root->right = rotate_right(root->right);
    return rotate_left(root);
  }

  return root;
}

Avl* remove_key(Avl* root, int key) {
  // return NULL if tree does not exist
  if (!root) return root;

  //
  if (key < root->key)
    root->left = remove_key(root->left, key);
  else if (key > root->key)
    root->right = remove_key(root->right, key);
  else {
    // checking if both children exists
    if (root->left && root->right) {
      Avl* temp = min_value_node(root->right);
      root->key = temp->key;
      root->right = remove_key(root->right, temp->key);
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
      free(tmp->student);
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

Student* find_key(Avl* tree, int key) {
  if (!tree) return NULL;

  if (key > tree->key)
    return find_key(tree->right, key);

  if (key < tree->key)
    return find_key(tree->left, key);

  return tree->student;
}

void print_tree(Avl* tree) {
  if (!tree) return;

  // Print in order
  print_tree(tree->left);
  printf("%3d", tree->key);
  print_tree(tree->right);

}

Avl* mirror(Avl* tree, Avl* mirrored_tree) {
  if (!tree) return NULL;

  mirrored_tree = insert_key(mirrored_tree, *(tree->student));
  mirrored_tree->left = mirror(tree->right, mirrored_tree->left);
  mirrored_tree->right = mirror(tree->left, mirrored_tree->right);

  return mirrored_tree;
}

Avl* mirror_tree(Avl* tree) {
  if (!tree) return tree;
  Avl* mirrored_tree = NULL;

  return mirror(tree, mirrored_tree);
}