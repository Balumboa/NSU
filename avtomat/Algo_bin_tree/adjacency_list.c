#include "adjacency_list.h"

void create(adjacency_list *graph, int n) {
    graph->n = n;
    graph->vertex = (vector **)calloc(n, sizeof(vector *));
    for (int i = 0; i < n; i++) {
        graph->vertex[i] = (vector *)malloc(sizeof(vector));
        create_vec(graph->vertex[i], 0);
    }
}

void delete_matrix(adjacency_list *graph) {
    int n = graph->n;
    for (int i = 0; i < n; i++) {
        delete_vec(graph->vertex[i]);
        free(graph->vertex[i]);
    }
    free(graph->vertex);
    graph->vertex = NULL;
    graph->n = 0;
    printf("Матрица удалена\n");
}

void scanf_matrix(adjacency_list *graph) {
    int n, is_directed;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &n);
    printf("Введите 1, если граф ориентированный, а иначе введите 0: ");
    scanf("%d", &is_directed);
    create(graph, n + 1);
    int m;  // количество рёбер
    printf("Введите количество рёбер в графе: ");
    scanf("%d", &m);
    printf("Вводите рёбра между вершинами: \n");
    for (int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        if (is_directed == 0) {
            push_back_vec(graph->vertex[w], v);
        }
        push_back_vec(graph->vertex[v], w);
    }
}

void print_matrix(adjacency_list *graph) {
    int n = graph->n;
    for (int i = 1; i < n; i++) {
        printf("%d: ", i);
        for (int j = 0; j < get_size_vec(graph->vertex[i]); j++) {
            printf("%d ", graph->vertex[i]->list[j]);
        }
        printf("\n");
    }
}