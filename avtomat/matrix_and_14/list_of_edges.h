#ifndef list_of_edges_h
#define list_of_edges_h
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * File:         list_of_edges.h
 * Description:  Список рёбер
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct {
    int v;
    int w;
} edge;

typedef struct {
    int N;
    int M;
    edge *edges;
} list_of_edges;

void create_list_edge(list_of_edges *graph, int n, int m);

void delete_list_edge(list_of_edges *graph);

void scanf_list_edge(list_of_edges *graph);

void print_list_edge(list_of_edges *graph);

#endif

// добавление ребра/вершины...
// удаление ребра/вершины...
// перевод из одного в другой