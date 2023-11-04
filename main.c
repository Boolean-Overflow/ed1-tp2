#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<locale.h>
#include "vector/vector.h"

typedef struct point {
  position x, y, z;
} point;

typedef struct vector {
  point start, end, coords;
} vector;

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
    end = 8;
  }

  if (n == 3) printf("9- Produto misto entre vetores\n"), end = 9;

  printf("[1-%d]:", end);
  scanf("%d", &option);

  return option;
}

int main() {
  setlocale(LC_ALL, "");
  char ans;
  int n = 0, ok;
  vector* v[3];

  do {
    ok = 1;
    printf("Sobre o vetor %d\n", n + 1);

    do {
      if (!ok) printf("Opção Inválida!\n");
      printf("Quer informar por pontos ou coordenadas?\n[P/C]:");
      scanf("%c", &ans);
      fflush(stdin);
      ok = toupper(ans) == 'C' || toupper(ans) == 'P';
      system("cls");
    } while (!ok);

    if (toupper(ans) == 'P') {
      printf("Informe as coordenadas do ponto de origem\n");
      point start = read_point();
      printf("Informe as coordenadas do ponto de extremidade\n");
      point end = read_point();
      v[n] = vector_create_by_points(start, end);
    }
    else {
      printf("Informe as coordenadas\n");
      point p = read_point();
      v[n] = vector_create_by_origin(p);
    }
    n++;

    if (n < 3) {
      fflush(stdin);
      printf("Deseja inserir outro Vector?\n[S/N]:");
      scanf("%c", &ans);
      ok = toupper(ans) != 'S';
      fflush(stdin);
    }
    else ok = 1;
    system("cls");
  } while (!ok && n < 3);


  for (int i = 0; i < n; ++i)
    printf("Vector %d (%.0f, %.0f, %.0f)\n", i + 1, v[i]->coords.x, v[i]->coords.y, v[i]->coords.z);

  int option = menu(n);

  printf("%d", option);


  while (n) free(v[--n]);

  return 0;
}
