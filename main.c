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
  printf("Deseja voltar para o menu?\n[S/N]: ");
  scanf("%c", &ans), * finish = toupper(ans) == 'N';
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

point point_cpy(vector* v) {
  point p;
  p.x = v->coords.x;
  p.y = v->coords.y;
  p.z = v->coords.z;

  return p;
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

  // printf("0- Sair\n");

  printf("[1-%d]:", end);
  scanf("%d", &option);

  return option;
}

int main() {
  setlocale(LC_ALL, "");
  char ans;
  int n = 0, ok, * index = NULL;
  vector** v = calloc(3, sizeof(vector));

  do {
    ok = 1;
    do {
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
    char* letters[] = { "𝐴⃗", "𝐵⃗", "𝐶⃗" };

    for (int i = 0; i < n; ++i)
      printf("[%d]: %s", i + 1, letters[i]), print_point(v[i]->coords), printf("\n");

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
        printf("Informe o valor a ser multiplicado: ");
        scanf("%f", &ß);
        product_by_scalar(v[index], ß);
      } while (ß < 0);

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
      print_point(result->coords);
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

      if (!vectors_angle(v[index[0]], v[index[1]])) printf("Não existe intersecção!\n");
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
      printf("são %s \n", relative_position(v[index[0]], v[index[1]]));
    }
    else if (option == 10 && n == 3) {
      printf("========== PRODUTO MISTO ==========\n");
      float result = mix_product(v[0], v[1], v[2]);
      print_point(v[2]->coords), printf(".[");
      print_point(v[0]->coords), printf(" X ");
      print_point(v[1]->coords), printf("] = %.2f\n", result);
    }
    else if (option == 0) break;
    else ok = 0;
    validate(&finish), clearConsole();
  } while (!finish);

  // Destructors
  while (n) vector_delete(v[--n]);
  free(index), free(v);

  return 0;
}
