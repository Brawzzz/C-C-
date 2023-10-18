#ifndef MATRICE_H
#define MATRICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct{

    float** tab;

    int nmb_col;
    int nmb_lig;

    char* name;

}Matrix;

Matrix create_matrice(int col , int lig , char* name);

void fill_matrice(Matrix m);

void print_matrice(Matrix m);

Matrix get_identity(int dim);

Matrix null_matrix(int col , int row);

bool is_null(Matrix m);

float trace(Matrix m);

Matrix add(Matrix m1 , Matrix m2);

Matrix mult(Matrix m1 , Matrix m2);

Matrix mult_by_scalar(Matrix m1 , float r);

Matrix get_standard_basis_vector(int index , int dim);

float euclidian_norm(Matrix v);

float det(Matrix m);

Matrix com(Matrix m);

Matrix transpose(Matrix m);

Matrix inverse(Matrix m , int* inversible);

Matrix* get_column_vectors_from(Matrix m);

Matrix* get_row_vectors_from(Matrix m);

bool is_upper_triangular(Matrix m , float* e);

bool is_lower_triangular(Matrix m , float* e);

bool is_diagonal(Matrix m);

float* get_diagonal(Matrix m);

Matrix minor_matrix(Matrix m , int col_index , int row_index);

int search_pivot(Matrix v);

Matrix swap_rows(Matrix m , int old_row_index , int new_row_index);

Matrix mult_row_by_scalar(Matrix m , int row_index , float scalar);

Matrix add_linear_combination(Matrix m , int receiver_row_index , int adding_row_index , float scalar);

Matrix gauss_jordan(Matrix m);

Matrix resolve_linear_system(Matrix A , Matrix B);

Matrix make_householder_matrix(Matrix m , int diff);

void QR_decomposition(Matrix m , Matrix* Q , Matrix* R);

float* eigenvalues(Matrix m);

Matrix* eigenvectors(Matrix m);

#endif