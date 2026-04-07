#include "adjacency_matrix.h"

/*****************************************************************************
 * File:         adjacemcy_matrix.c
 * Description:  Матрица смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

adjacency_matrix *create_adj_matrix(int n, int m) {
    adjacency_matrix *graph =
        (adjacency_matrix *)malloc(sizeof(adjacency_matrix));
    graph->N = n + 1;
    graph->M = m + 1;

    graph->matrix = (int **)calloc(graph->N, sizeof(int *));
    for (int i = 0; i < graph->N; i++) {
        graph->matrix[i] = (int *)calloc(graph->N, sizeof(int));
    }
    return graph;
}

void delete_adj_matrix(adjacency_matrix **graph) {
    int N = (*graph)->N;

    for (int i = 0; i < N; i++) {
        free((*graph)->matrix[i]);
    }

    free((*graph)->matrix);
    (*graph)->matrix = NULL;
    (*graph)->N = 0;
    (*graph)->M = 0;
    free(*graph);
    graph = NULL;
}

adjacency_matrix *scanf_adj_matrix() {
    int n;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &n);

    int m;  // количество рёбер
    printf("Введите количество рёбер в графе: ");
    scanf("%d", &m);

    adjacency_matrix *graph = create_adj_matrix(n, m);

    printf("Вводите рёбра между вершинами: \n");
    for (int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        graph->matrix[v][w] = 1;
    }
    return graph;
}

void print_adj_matrix(adjacency_matrix *graph) {
    printf("Граф в виде матрицы смежности:\n");
    int N = graph->N;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

void delete_edge(adjacency_matrix *graph, int v, int w) {
    graph->matrix[v][w] = 0;
}

void add_edge(adjacency_matrix *graph, int v, int w) {
    graph->matrix[v][w] = 1;
}
