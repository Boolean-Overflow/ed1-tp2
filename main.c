#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<locale.h>
#include "vector/vector.h"
#include "utils/utils.h"

typedef struct point {
  position x, y, z;
} point;

typedef struct vector {
  point start, end, coords;
} vector;

int main() {
  setlocale(LC_ALL, "");
  char ans;
  int n = 0, ok, * index = NULL;
  vector** v = calloc(3, sizeof(vector));

  do {
    ok = 1;
    do {
      if (n) print_vectors(v, n);
      if (!ok) printf("Opção Inválida!\n");
      printf("Sobre o vetor %d\n", n + 1);
      printf("Quer informar por pontos ou coordenadas?\n[P/C]:");
      scanf("%c", &ans);
      fflush(stdin);
      ok = toupper(ans) == 'C' || toupper(ans) == 'P';
      clearConsole();
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
      scanf("%c", &ans), ok = toupper(ans) != 'S';
      fflush(stdin);
    }
    else ok = 1;
    clearConsole();
  } while (!ok && n < 3);

  int finish = 0;
  do {
    ok = 1;
    if (!ok) printf("Opção Inválida\n");

    print_vectors(v, n);

    int option = menu(n);
    if (option == 1) {
      int index = header1("========== MODULO ==========\n", n);

      printf("||"), print_point(v[index]->coords);
      printf("|| = %.2f\n", vector_module(v[index]));
    }
    else if (option == 2) {
      int index = header1("========== MULTIPLICAÇÃO POR UM ESCALAR ==========\n", n);
      float ß;
      point p = point_cpy(v[index]);
      do {
        clearConsole();
        if (!ß) printf("O valor deve ser diferente de 0\n");
        printf("Informe o valor a ser multiplicado: ");
        scanf("%f", &ß);
      } while (!ß);
      product_by_scalar(v[index], ß);

      printf("%.2f ", ß), print_point(p), printf(" = ");
      print_point(v[index]->coords), printf("\n");
    }
    else if (option == 3 && n > 1) {
      index = header2("========== SOMAR VETORES ==========\n", n);

      vector* result = vector_sum(v[index[0]], v[index[1]]);

      print_point(v[index[0]]->coords), printf(" + ");
      print_point(v[index[1]]->coords), printf(" = ");
      print_point(result->coords), printf("\n");
      vector_delete(result);
    }
    else if (option == 4 && n > 1) {
      index = header2("========== SUBTRAIR VETORES ==========\n", n);

      vector* result = subtract_vectors(v[index[0]], v[index[1]]);

      print_point(v[index[0]]->coords), printf(" - ");
      print_point(v[index[1]]->coords), printf(" = ");
      print_point(result->coords), printf("\n");
      vector_delete(result);
    }
    else if (option == 5 && n > 1) {
      index = header2("========== PRODUTO ESCALAR ==========\n", n);
      float result = scalar_product(v[index[0]], v[index[1]]);

      print_point(v[index[0]]->coords), printf(".");
      print_point(v[index[1]]->coords), printf(" = %.2f\n", result);
    }
    else if (option == 6) {
      index = header2("========== PRODUTO VETORIAL ==========\n", n);
      vector* result = vectorial_product(v[index[0]], v[index[1]]);

      print_point(v[index[0]]->coords), printf(" X ");
      print_point(v[index[1]]->coords), printf(" = ");
      print_point(result->coords), printf("\n");
    }
    else if (option == 7 && n > 1) {
      index = header2("========== ÂNGULO ENTRE VETORES ==========\n", n);
      float result = vectors_angle(v[index[0]], v[index[1]]);

      print_point(v[index[0]]->coords), printf("∠");
      print_point(v[index[1]]->coords), printf(" = %.2f°\n", result);
    }
    else if (option == 8 && n > 1) {
      index = header2("========== INTERSECÇÃO ==========\n", n);
      point result = interception(v[index[0]], v[index[1]]);

      float aux = (v[index[1]]->coords.y - (v[index[0]]->coords.y) * (v[index[1]]->coords.x));

      if (!aux) printf("Não existe intersecção!\n");
      else {
        print_point(v[index[0]]->coords), printf(" ∠ ");
        print_point(v[index[1]]->coords), printf(" = ");
        print_point(result), printf("\n");
      }
    }
    else if (option == 9 && n > 1) {
      index = header2("========== POSIÇÃO RELATIVA ==========\n", n);

      print_point(v[index[0]]->coords), printf(" e ");
      print_point(v[index[1]]->coords);
      printf(" são %s \n", relative_position(v[index[0]], v[index[1]]));
    }
    else if (option == 10 && n == 3) {
      printf("========== PRODUTO MISTO ==========\n");
      float result = mix_product(v[0], v[1], v[2]);
      print_point(v[2]->coords), printf(".[");
      print_point(v[0]->coords), printf(" X ");
      print_point(v[1]->coords), printf("] = %.2f\n", result);
    }
    else if (n == 1 && option == 3 || n == 2 && option == 10 || n == 3 && option == 11) break;
    else {
      ok = 0, clearConsole();
      printf("Opção Inválida!\n");
      continue;
    }
    validate(&finish), clearConsole();
  } while (!finish);

  // Destructors
  while (n > 0) vector_delete(v[--n]);
  free(index), free(v);

  return 0;
}
