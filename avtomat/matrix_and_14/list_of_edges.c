#include "list_of_edges.h"

#include <stdio.h>

/*****************************************************************************
 * File:         list_of_edges.c
 * Description:  Список рёбер
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

void create_list_edge(list_of_edges *graph, int n, int m) {
    graph = (list_of_edges *)malloc(sizeof(list_of_edges));
    graph->edges = (edge *)malloc(sizeof(edge) * (m + 1));
    graph->M = m + 1;
    graph->N = n + 1;
}

void delete_list_edge(list_of_edges *graph) {
    free(graph->edges);
    graph->M = 0;
    graph->N = 0;
}

void scanf_list_edge(list_of_edges *graph) {
    int m;
    printf("Введите количество рёбер: ");
    scanf("%d", &m);

    int n;
    printf("Введите количество вершин: ");
    scanf("%d", &n);

    create_list_edge(graph, n, m);
    printf("Вводите рёбра:\n");
    for (int i = 1; i <= m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        graph->edges[i].v = v;
        graph->edges[i].w = w;
    }
}

void print_list_edge(list_of_edges *graph) {
    int M = graph->M;
    printf("Граф:\n");
    for (int i = 1; i < M; i++) {
        printf("%d %d\n", graph->edges[i].v, graph->edges[i].w);
    }
}

int main() {}