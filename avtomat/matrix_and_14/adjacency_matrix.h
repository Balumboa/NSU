#ifndef adjacency_matrix_h
#define adjacency_matrix_h
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * File:         adjacemcy_matrix.c
 * Description:  Матрица смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct {
    int N;
    int M;
    int **matrix;
} adjacency_matrix;

void create_adj_matrix(adjacency_matrix *graph, int n, int m);

void delete_adj_matrix(adjacency_matrix *graph);

void scanf_adj_matrix(adjacency_matrix *graph);

void print_adj_matrix(adjacency_matrix *graph);

void delete_edge(adjacency_matrix *graph, int v, int w);

void add_edge(adjacency_matrix *graph, int v, int w);

#endif