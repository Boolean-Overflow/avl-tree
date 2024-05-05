#include <stdio.h>
#include "./avl/avl.h"

void pause(char* str) {
  puts(*str ? str : "\nClique em qualquer tecla para continuar.");
  getchar();
}

void clearConsole() {
  printf("\033[2J\033[H");
}

int isValid(int* v, int lower, int upper) {
  fflush(stdin);
  return scanf("%d", v) && (*v >= lower && *v <= upper);
}

int main() {
  int valid = 0, option, key;
  Avl* root = NULL;
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
      puts(" ====== INSERÇÃO ======");
      puts("Digite um numero para inserir: ");
      while (!scanf("%d", &key)) {
        puts("Digite uma numero válido: ");
      }
      // root = insert_key(root, key);
    }
    break;
    case 2:
    remove: {
      puts(" ====== REMOÇÃO ======");
      puts("Digite um numero para remover: ");
      while (!scanf("%d", &key)) {
        puts("Digite uma numero válido: ");
      }
      // root = remove_key(root, key);
    }
    break;
    case 3:
    find: {
      puts(" ====== BUSCA ======");
      puts("Digite o numero que deseja procurar: ");
      while (!scanf("%d", &key)) {
        puts("Digite uma numero válido: ");
      }
      // puts((find_key(root, key) ? "Valor encontrado" : "Valor nao encontrado"));
    }
    break;
    case 4:
    print: {
      puts(" ====== IMPRESSÃO ======");
    }
    break;
    case 5:
    mirror: {
      puts(" ====== ESPELHO ======");
    }
    break;
    default:
    }
  } while (option != 6);

  return 0;
}