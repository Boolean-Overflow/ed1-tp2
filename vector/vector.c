#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "vector.h"

struct point {
  position x, y, z;
};

struct vector {
  point start, end, coords;
};

vector* vector_create_by_points(point start, point end) {
  vector* v = malloc(sizeof(vector));
  if (!v) {
    printf("Erro de alocação\n");
    return NULL;
  }
  v->coords.x = end.x - start.x;
  v->coords.y = end.y - start.y;
  v->coords.z = end.z - start.z;
  v->start = start;
  v->end = end;

  return v;
}

vector* vector_create_by_origin(point end) {
  point p;
  p.x = p.y = p.z = 0;
  return vector_create_by_points(p, end);
}

void print_point(point p) {
  printf("(%.2f, %.2f, %.2f)", p.x, p.y, p.z);
}

point read_point() {
  point p;
  printf("X:"), scanf("%f", &p.x);
  printf("Y:"), scanf("%f", &p.y);
  printf("Z:"), scanf("%f", &p.z);

  return p;
}

void vector_print(vector* v) {
  printf("%.2fi + %.2fj + %.2fk", v->coords.x, v->coords.y, v->coords.z);
}

vector* vector_sum(vector* v1, vector* v2) {
  vector* result = vector_create_by_points(v1->start, v2->end);

  result->coords.x = v1->coords.x + v2->coords.x;

  result->coords.y = v1->coords.y + v2->coords.y;

  result->coords.z = v1->coords.z + v2->coords.z;

  return result;
}

vector* subtract_vectors(vector* v1, vector* v2) {
  vector* result = vector_create_by_points(v1->start, v2->end);

  result->coords.x = v1->coords.x - v2->coords.x;

  result->coords.y = v1->coords.y - v2->coords.y;

  result->coords.z = v1->coords.z - v2->coords.z;

  return result;
}

float vectors_angle(vector* v1, vector* v2) {

  float result = scalar_product(v1, v2) / (vector_module(v1) * vector_module(v2));

  return (180.0 / (acos(-1))) * acos(result);
}

vector* vectorial_product(vector* v1, vector* v2) {
  point p;
  p.x = v1->coords.y * v2->coords.z - v2->coords.y * v1->coords.z;

  p.y = -1 * (v1->coords.x * v2->coords.z - v2->coords.x * v1->coords.z);

  p.z = v1->coords.x * v2->coords.y - v2->coords.x * v1->coords.y;

  return vector_create_by_origin(p);
}

vector* product_by_scalar(vector* v, float ß) {
  if (!v) {
    printf("\nVetor deve possuir coordenadas.\n");
    return NULL;
  }
  if (!ß) {
    printf("\n O escalar deve ser diferente de zero\n");
    return NULL;
  }

  v->coords.x *= ß;
  v->coords.y *= ß;
  v->coords.z *= ß;

  return v;
}

float scalar_product(vector* v1, vector* v2) {
  return(
    v1->coords.x * v2->coords.x +
    v1->coords.y * v2->coords.y +
    v1->coords.z * v2->coords.z
    );
}

float vector_module(vector* v) {
  if (!v) {
    printf("\nVetor deve possuir coordenadas.\n");
    return -1;
  }
  float x = v->coords.x, y = v->coords.y, z = v->coords.z;

  return sqrt(x * x + y * y + z * z);
}

string relative_position(vector* v1, vector* v2) {
  float scalarProduct = scalar_product(v1, v2);

  if (scalarProduct == 0) return "ortogonais";
  else if (scalarProduct == -1) return "colineares";
  else if (cos(vectors_angle(v1, v2)) == 1) return "paralelos";
  else return "coincidentes";
}

void vector_delete(vector* v) {
  if (!v) printf("\nVetor inexistente!\n");
  else free(v);
}

float distance(vector* v1, vector* v2) {
  float d = 0;
  d = (float)(sqrt(pow(v2->coords.x - v1->coords.x, 2) + pow(v2->coords.y - v1->coords.y, 2) + pow(v2->coords.z - v1->coords.z, 2)));
  return d;
}

float mix_product(vector* v1, vector* v2, vector* v3) {
  float result = 0;
  result = scalar_product(v3, vectorial_product(v1, v2));
  return result;
}

point interception(vector* v1, vector* v2) {
  float incog1 = 0, incog2 = 0;
  incog1 = ((v2->start.x) - (v1->start.x)) / (v1->coords.x);
  incog2 = ((v2->start.y) - (v1->start.y) - ((v1->coords.y) * incog1)) / (v1->coords.y - v2->coords.y);
  incog1 += incog2;
  point Point_Interc;
  Point_Interc.x = (v1->start.x + (v1->coords.x) * incog1);
  Point_Interc.y = (v1->start.y + (v1->coords.y) * incog1);
  Point_Interc.z = (v1->start.z + (v1->coords.z) * incog1);
  return Point_Interc;

}
