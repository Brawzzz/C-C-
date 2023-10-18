#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

struct Vector {
	int dim;
	float* elements;
};

typedef struct Vector Vector;

//============================== VECTOR FUNCTIONS ==============================//
Vector init_vector(int dim) {

	int i = 0;

	Vector v;

	v.dim = dim;
	v.elements = (float*)malloc(v.dim * sizeof(float));
	if (v.elements == NULL) {
		exit(-1);
	}

	for (i = 0; i < v.dim; i++) {
		v.elements[i] = 0.f;
	}

	return v;
}

void print_vector(Vector v) {

	for (int i = 0; i < v.dim; i++) {
		printf("%f\n", v.elements[i]);
	}
}

Vector fill_vector(int dim, float* values) {

	int i = 0;

	Vector v = init_vector(dim);

	for (i = 0; i < v.dim; i++) {
		v.elements[i] = values[i];
	}

	return v;
}

Vector add_dim(Vector v, int new_dim) {

	Vector upgrade_v = init_vector(new_dim);

	return upgrade_v;
}

Vector copy_from_to(Vector u, Vector v) {

	Vector v_copy = init_vector(v.dim);

	if (u.dim <= v_copy.dim) {
		for (int i = 0; i < u.dim; i++) {
			v_copy.elements[i] = u.elements[i];
		}
	}
	else {
		printf("vetor u need the same or ... dimmensions\n");
	}

	return v_copy;
}

float scalar_product(Vector u, Vector v) {

	int dim = 0;

	float product = 0.f;

	if (u.dim > v.dim) {
		dim = v.dim;
	}
	else if (u.dim < v.dim) {
		dim = u.dim;
	}
	else {
		dim = u.dim;
	}

	for (int i = 0; i < dim; i++) {
		product += u.elements[i] * v.elements[i];
	}

	return product;
}

void fill_values(float* values, int dim) {

	for (int i = 0; i < dim; i++) {
		values[i] = rand() % 100;
	}
}

void print_int_tab(int* tab, int size) {

	int i = 0;

	for (i = 0; i < size; i++) {
		printf("%d , ", tab[i]);
	}
}

void print_float_tab(float* tab, int size) {

	int i = 0;

	for (i = 0; i < size; i++) {
		printf("%f , ", tab[i]);
	}
}

//============================== MAIN ==============================//
int main() {

	srand(time(NULL));

	int n = 10;
	int dim = 3;

	float x_u = 0;
	float y_u = 0;
	float z_u = 0;

	float x_v = 0;
	float y_v = 0;
	float z_v = 0;

	float scalar = 0.f;

	float* values;

	Vector u = init_vector(dim);
	Vector v = init_vector(2 * dim);

	// SET VECTOR U
	values = (float*)malloc(u.dim * sizeof(float));
	if (values == NULL) {
		exit(EXIT_FAILURE);
	}
	fill_values(values, u.dim);
	u = fill_vector(u.dim, values);
	free(values);

	// SET VECTOR V
	values = (float*)malloc(v.dim * sizeof(float));
	if (values == NULL) {
		exit(EXIT_FAILURE);
	}
	fill_values(values, v.dim);
	v = fill_vector(v.dim, values);
	free(values);

	printf("u : \n");
	print_vector(u);

	printf("\n");

	printf("v : \n");
	print_vector(v);

	printf("\n");

	scalar = scalar_product(u, v);
	printf("u . v = %f \n", scalar);

	return 0;
}