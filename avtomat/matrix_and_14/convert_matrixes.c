#include "convert_matrixes.h"

#include <stdio.h>

#include "vector.h"

/*****************************************************************************
 * File:         convert_matrixes.c
 * Description:  Перевод из разных типов графов
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

list_of_edges *convert_adj_list_to_list_edg(adjacency_list *a) {
    list_of_edges *c;
    int N = a->N, M = a->M;
    c = create_list_edge(N - 1, M - 1);
    int ind = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < a->vertex[i]->size; j++) {
            edge new_edge;
            new_edge.v = i;
            new_edge.w = a->vertex[i]->list[j];
            c->edges[ind] = new_edge;
            ind++;
        }
    }
    return c;
}

incidence_matrix *convert_list_edg_to_incidence_mat(list_of_edges *a) {
    incidence_matrix *c;
    int N = a->N, M = a->M;
    c = create_inc_matrix(N - 1, M - 1);

    for (int i = 1; i < M; i++) {
        edge new_edge = a->edges[i];
        int v = new_edge.v;
        int w = new_edge.w;
        c->matrix[v][i] = 1;
        c->matrix[w][i] = -1;
    }

    return c;
}

adjacency_matrix *convert_incidence_mat_to_adj_mat(incidence_matrix *a) {
    adjacency_matrix *c;
    int N = a->N, M = a->M;
    c = create_adj_matrix(N - 1, M - 1);

    for (int i = 1; i < M; i++) {
        int v = 0, w = 0;
        for (int j = 1; j < N; j++) {
            if (a->matrix[j][i] == 1) {
                v = j;
            } else if (a->matrix[j][i] == -1) {
                w = j;
            }
        }
        if (v == 0)
            c->matrix[w][w]++;
        else
            c->matrix[v][w]++;
    }

    return c;
}

adjacency_list *convert_adj_mat_to_adj_list(adjacency_matrix *a) {
    adjacency_list *c;
    int N = a->N, M = a->M;
    c = create_adj_list(N - 1, M - 1);

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            int t = a->matrix[i][j];
            while (t--) {
                push_back_vec(c->vertex[i], j);
            }
        }
    }

    return c;
}