typedef struct vector vector;
typedef struct point point;
typedef char* string;
typedef float position;

// Matateu
vector* vector_create(point start, point end);
vector* sum_vectors(vector* v1, vector* v2);
vector* vectorial_product(vector* v1, vector* v2);
float vectors_angle(vector* v1, vector* v2);
void print_vector(vector* v); // 2i + 3j + 3z = (2, 3, 3)

// Lukeny
float distance(vector* v1, vector* v2);
vector* subtract_vectors(vector* v1, vector* v2);
float mix_product(vector* v1, vector* v2, vector* v3);
point interception(vector* v1, vector* v2);

// Kélsio
vector* product_by_scalar(vector* v, float ß);
float scalar_product(vector* v1, vector* v2);
float vector_module(vector* v);
string relative_position(vector* v1, vector* v2);
void vector_delete(vector* v);
