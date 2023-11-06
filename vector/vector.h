typedef struct vector vector;
typedef struct point point;
typedef char* string;
typedef float position;

vector* vector_sum(vector* v1, vector* v2);
vector* vectorial_product(vector* v1, vector* v2);
float vectors_angle(vector* v1, vector* v2);
float distance(vector* v1, vector* v2);
vector* subtract_vectors(vector* v1, vector* v2);
float mix_product(vector* v1, vector* v2, vector* v3);
point interception(vector* v1, vector* v2);
vector* vector_create_by_points(point start, point end);
vector* vector_create_by_origin(point end);
vector* product_by_scalar(vector* v, float ß);
float scalar_product(vector* v1, vector* v2);
float vector_module(vector* v);
string relative_position(vector* v1, vector* v2);
void vector_delete(vector* v);
point read_point();
void vector_print(vector* v); // 2i + 3j + 3z = (2, 3, 3)
void print_point(point p);
point point_cpy(vector* v);
void print_vectors(vector** v, int n);

