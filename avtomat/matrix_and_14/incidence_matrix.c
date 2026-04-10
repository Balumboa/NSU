#include "incidence_matrix.h"

/*****************************************************************************
 * File:         incidence_matrix.c
 * Description:  Матрица Инцидентности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

incidence_matrix *create_inc_matrix(int n, int m) {
    incidence_matrix *graph =
        (incidence_matrix *)malloc(sizeof(incidence_matrix));
    graph->N = n + 1;
    graph->M = m + 1;

    graph->matrix = (int **)calloc(graph->N, sizeof(int *));
    for (int i = 0; i < graph->N; i++) {
        graph->matrix[i] = (int *)calloc(graph->M, sizeof(int));
    }
    return graph;
}

void delete_inc_matrix(incidence_matrix **graph) {
    int N = (*graph)->N;
    for (int i = 0; i < N; i++) {
        free((*graph)->matrix[i]);
    }

    free((*graph)->matrix);
    (*graph)->matrix = NULL;
    (*graph)->N = 0;
    (*graph)->M = 0;
    free(*graph);
    *graph = NULL;
}

incidence_matrix *scanf_inc_matrix() {
    int n;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &n);

    int m;  // количество рёбер
    printf("Введите количество рёбер в графе: ");
    scanf("%d", &m);

    incidence_matrix *graph = create_inc_matrix(n, m);

    printf("Вводите рёбра между вершинами: \n");
    for (int i = 1; i <= m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        graph->matrix[v][i] = 1;
        graph->matrix[w][i] = -1;
    }
    return graph;
}

void print_inc_matrix(incidence_matrix *graph) {
    printf("Матрица инцидентности:\n");
    int N = graph->N;
    int M = graph->M;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}