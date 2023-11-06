#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "utils.h"
#include "../vector/vector.h"

void clearConsole() {
#ifdef _WIN32
  system("cls");
#elif __linux__ || __APPLE__
  system("clear");
#else
  printf("Ambiente não suportado!");
#endif
}

void validate(int* finish) {
  char ans;
  fflush(stdin);
  printf("Deseja voltar para o menu?\n[S para continuar ou qualquer outra letra pra terminar]: ");
  scanf("%c", &ans), * finish = toupper(ans) != 'S';
  fflush(stdin);
}

int header1(char* msg, int n) {
  int index = 0;
  do {
    clearConsole();
    if (index > n) printf("Indice Inválido!\n");
    printf("%s", msg);
    if (n == 1) break;
    printf("Informe o indice do vetor\n[1-%d]: ", n);
    scanf("%d", &index);
    fflush(stdin);
  } while (--index >= n || index < 0);

  return index;
}

int* header2(char* msg, int n) {
  int* index = calloc(2, sizeof(int)), valid = 1;
  index[0] = 0, index[1] = 1;

  if (n == 3)
    for (int i = 0; i < 2; ++i)
      do {
        clearConsole();
        if (index[i] >= n || index[i] < 0) printf("Indice Inválido!\n");
        if (!valid) printf("Este indice já foi escolhido\n");
        printf("%s", msg);
        printf("Informe o indice o %d vetor: ", i + 1);
        scanf("%d", &index[i]), --index[i];
        fflush(stdin);

        if (i > 0) valid = !(index[i] == index[i - 1]);
      } while (index[i] >= n || index[i] < 0 || !valid);
  else clearConsole(), printf("%s", msg);

  return index;
}

int menu(int n) {
  int option, end = 2;

  printf("1- Modulo\n");
  printf("2- Multiplicação por um escalar\n");

  if (n > 1) {
    printf("3- Somar vetores\n");
    printf("4- Subtrair vetores\n");
    printf("5- Produto escalar entre vetores\n");
    printf("6- Produto vetorial entre vetores\n");
    printf("7- Ângulo entre vetores\n");
    printf("8- Intersecção entre vetores\n");
    printf("9- Posição relativa entre vetores\n");
    end = 9;
  }

  if (n == 3) printf("10- Produto misto entre vetores\n"), end = 10;

  printf("%d- Sair\n", ++end);

  printf("[1-%d]:", end);
  scanf("%d", &option);

  return option;
}