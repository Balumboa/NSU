#include "adjacency_list.h"

#include <stdio.h>

#include "vector.h"

/*****************************************************************************
 * File:         adjacemcy_list.c
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

adjacency_list *create_adj_list(int n, int m) {
    adjacency_list *graph = (adjacency_list *)malloc(sizeof(adjacency_list));
    graph->N = n + 1;
    graph->M = m + 1;

    graph->vertex = (vector **)calloc(graph->N, sizeof(vector *));

    for (int i = 0; i < graph->N; i++) {
        graph->vertex[i] = (vector *)malloc(sizeof(vector));
        graph->vertex[i] = create_vec(0);
    }
    return graph;
}

void delete_adj_list(adjacency_list **graph) {
    int N = (*graph)->N;

    for (int i = 0; i < N; i++) {
        delete_vec(&((*graph)->vertex[i]));
    }

    free((*graph)->vertex);
    (*graph)->vertex = NULL;
    (*graph)->N = 0;
    (*graph)->M = 0;
    free(*graph);
    *graph = NULL;
}

void print_adj_list(adjacency_list *graph) {
    printf("Вывод графа в списке смежности:\n");
    int N = graph->N;
    for (int i = 1; i < N; i++) {
        printf("%d: ", i);
        for (int j = 0; j < get_size_vec(graph->vertex[i]); j++) {
            printf("%d ", graph->vertex[i]->list[j]);
        }
        printf("\n");
    }
}

adjacency_list *scanf_adj_list() {
    int n;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &n);

    int m;  // количество рёбер
    printf("Введите количество рёбер в графе: ");
    scanf("%d", &m);

    adjacency_list *graph = create_adj_list(n, m);

    printf("Вводите рёбра между вершинами: \n");
    for (int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        push_back_vec(graph->vertex[v], w);
    }
    return graph;
}