#include <stdio.h>
#include<locale.h>
#include "./avl/avl.h"

void clearConsole() {
  printf("\033[2J\033[H");
}

void pause(char* str) {
  puts(*str ? str : "\nClique em qualquer tecla para continuar.");
  fflush(stdin);
  getchar();
  clearConsole();
}

int isValid(int* v, int lower, int upper) {
  fflush(stdin);
  return scanf("%d", v) && (*v >= lower && *v <= upper);
}

int valid_date(int day, int month, int year) {
  return 1;
}

int main() {
  setlocale(0, "Portuguese");
  int valid = 1, option;
  Avl* tree = NULL;
  Student st, * foundStudent = NULL;
  do {
    puts(" ====== MENU ======");
    puts("1 - Inserir");
    puts("2 - Remover");
    puts("3 - Procurar");
    puts("4 - Imprimir");
    puts("5 - Espelhar a Árvore");
    puts("6 - Sair");
    printf("[1-6]: ");
    while (!isValid(&option, 1, 6)) {
      puts("Digite uma opção válida.");
      printf("[1-6]: ");
    }
    clearConsole();
    switch (option) {
    case 1:
    insert: {

      int day, month, year;
      puts(" ====== INSERÇÃO ======");

      printf("Informe o numero do estudante: ");
      while (!isValid(&st.number, 0, __INT32_MAX__) || !!(foundStudent = find_student(tree, st.number))) {
        clearConsole();
        puts("Numero de estudante inválido!");
        if (foundStudent) puts("Estudante já existente!");
        printf("Digite novamente: ");
        fflush(stdin);
      }

      printf("Informe o nome do estudante: ");
      fflush(stdin);
      scanf("%24[^\n]", st.name);

      valid = 1;
      do {
        if (!valid) puts("Data inválida!");

        printf("Informe a data[dd/mm/yyyy]: ");
        fflush(stdin);
        scanf("%10[^\n]", st.birthdate);
        valid = sscanf(st.birthdate, "%d/%d/%d", &day, &month, &year) == 3 && valid_date(day, month, year);
      } while (!valid);
      sprintf(st.birthdate, "%d/%d/%d", day, month, year);

      tree = add_student(tree, &st);
      printf("Estudante com numero %d adicionado com sucesso!", st.number);

      pause("");
    }
    break;
    case 2:
    remove: {
      int key;
      puts(" ====== REMOÇÃO ======");
      printf("Digite um numero de estudante: ");
      scanf("%d", &key);
      tree = remove_student(tree, key);
      pause("");
    }
    break;
    case 3:
    find: {
      int key;
      puts(" ====== BUSCA ======");
      puts("Digite o número de estudante: ");
      scanf("%d", &key);
      foundStudent = find_student(tree, key);

      if (foundStudent) print_student(foundStudent);
      else puts("Estudante inexistente!");
      pause("");
    }
    break;
    case 4:
    print: {
      puts(" ====== IMPRESSÃO ======");
      if (!tree) puts("Sem estudantes cadastrados!");
      else print_students(tree);
      pause("");
    }
    break;
    case 5:
    mirror: {
      puts(" ====== ESPELHO ======");
      Avl* mirrored_tree = mirror_tree(tree);
      puts("Arvore Original");
      print_students(tree);
      puts("");
      puts("Arvore espelhada");
      print_students(mirrored_tree);
      pause("");
    }
    break;
    default:
      puts("By: Grupo 2");
      pause("");
    }
  } while (option != 6);

  return 0;
}