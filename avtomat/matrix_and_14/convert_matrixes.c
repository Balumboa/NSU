#include "convert_matrixes.h"

#include <stdio.h>

#include "vector.h"

/*****************************************************************************
 * File:         convert_matrixes.c
 * Description:  Перевод из разных типов графов
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

void convert_adj_list_to_list_edg(adjacency_list *a, list_of_edges *b) {
    list_of_edges c;
    int N = a->N, M = a->M;
    create_list_edge(&c, N - 1, M - 1);
    int ind = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < a->vertex[i]->size; j++) {
            edge new_edge;
            new_edge.v = i;
            new_edge.w = a->vertex[i]->list[j];
            c.edges[ind] = new_edge;
            ind++;
        }
    }

    delete_list_edge(b);
    b->N = c.N;
    b->M = c.M;
    b->edges = (edge *)malloc(sizeof(edge) * b->M);
    for (int i = 0; i < b->M; i++) {
        b->edges[i] = c.edges[i];
    }
    delete_list_edge(&c);
}

void convert_list_edg_to_incidence_mat(list_of_edges *a, incidence_matrix *b) {
    incidence_matrix c;
    int N = a->N, M = a->M;
    create_inc_matrix(&c, N - 1, M - 1);

    for (int i = 1; i < M; i++) {
        edge new_edge = a->edges[i];
        int v = new_edge.v;
        int w = new_edge.w;
        c.matrix[v][i] = 1;
        c.matrix[w][i] = -1;
    }

    delete_inc_matrix(b);

    b->N = c.N;
    b->M = c.M;
    b->matrix = (int **)malloc(b->N * sizeof(int *));
    for (int i = 0; i < b->N; i++) {
        b->matrix[i] = (int *)malloc(b->M * sizeof(int));
        for (int j = 0; j < b->M; j++) {
            b->matrix[i][j] = c.matrix[i][j];
        }
    }

    delete_inc_matrix(&c);
}

void convert_incidence_mat_to_adj_mat(incidence_matrix *a,
                                      adjacency_matrix *b) {
    adjacency_matrix c;
    int N = a->N, M = a->M;
    create_adj_matrix(&c, N - 1, M - 1);

    for (int i = 1; i < M; i++) {
        int v = 0, w = 0;
        for (int j = 1; j < N; j++) {
            if (a->matrix[j][i] == 1) {
                v = j;
            } else if (a->matrix[j][i] == -1) {
                w = j;
            }
        }
        c.matrix[v][w] = 1;
    }

    delete_adj_matrix(b);

    b->N = c.N;
    b->M = c.M;
    b->matrix = (int **)malloc(b->N * sizeof(int *));
    for (int i = 0; i < b->N; i++) {
        b->matrix[i] = (int *)malloc(b->N * sizeof(int));
        for (int j = 0; j < b->N; j++) {
            b->matrix[i][j] = c.matrix[i][j];
        }
    }

    for (int i = 0; i < c.N; i++) {
        free(c.matrix[i]);
    }
    free(c.matrix);
}

void convert_adj_mat_to_adj_list(adjacency_matrix *a, adjacency_list *b) {
    adjacency_list c;
    int N = a->N, M = a->M;
    create_adj_list(&c, N - 1, M - 1);

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (a->matrix[i][j] == 1) {
                push_back_vec(c.vertex[i], j);
            }
        }
    }

    delete_adj_list(b);

    b->N = c.N;
    b->M = c.M;
    b->vertex = (vector **)malloc(b->N * sizeof(vector *));
    for (int i = 0; i < b->N; i++) {
        b->vertex[i] = (vector *)malloc(sizeof(vector));
        create_vec(b->vertex[i], 0);
        for (int j = 0; j < get_size_vec(c.vertex[i]); j++) {
            push_back_vec(b->vertex[i], c.vertex[i]->list[j]);
        }
    }

    for (int i = 0; i < c.N; i++) {
        delete_vec(c.vertex[i]);
        free(c.vertex[i]);
    }
    free(c.vertex);
}