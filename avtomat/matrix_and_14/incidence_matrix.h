#ifndef incidence_matrix_h
#define incidence_matrix_h
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * File:         incidence_matrix.h
 * Description:  Матрица Инцидентности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct {
    int N;
    int M;
    int **matrix;
} incidence_matrix;

void create_inc_matrix(incidence_matrix *graph, int n, int m);

void delete_inc_matrix(incidence_matrix *graph);

void scanf_inc_matrix(incidence_matrix *graph);

void print_inc_matrix(incidence_matrix *graph);

#endif