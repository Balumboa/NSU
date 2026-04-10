#include "list_of_edges.h"

#include <stdio.h>

/*****************************************************************************
 * File:         list_of_edges.c
 * Description:  Список рёбер
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

list_of_edges *create_list_edge(int n, int m) {
    list_of_edges *graph = (list_of_edges *)malloc(sizeof(list_of_edges));
    graph = (list_of_edges *)malloc(sizeof(list_of_edges));
    graph->edges = (edge *)malloc(sizeof(edge) * (m + 1));
    graph->M = m + 1;
    graph->N = n + 1;
    return graph;
}

void delete_list_edge(list_of_edges **graph) {
    free((*graph)->edges);
    (*graph)->M = 0;
    (*graph)->N = 0;
    free(*graph);
    *graph = NULL;
}

list_of_edges *scanf_list_edge() {
    int m;
    printf("Введите количество рёбер: ");
    scanf("%d", &m);

    int n;
    printf("Введите количество вершин: ");
    scanf("%d", &n);

    list_of_edges *graph = create_list_edge(n, m);
    printf("Вводите рёбра:\n");
    for (int i = 1; i <= m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        graph->edges[i].v = v;
        graph->edges[i].w = w;
    }
    return graph;
}

void print_list_edge(list_of_edges *graph) {
    printf("Список рёбер:\n");
    int M = graph->M;
    for (int i = 1; i < M; i++) {
        printf("%d %d\n", graph->edges[i].v, graph->edges[i].w);
    }
}
