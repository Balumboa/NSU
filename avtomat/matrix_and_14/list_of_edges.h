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

list_of_edges *create_list_edge(int n, int m);

void delete_list_edge(list_of_edges **graph);

list_of_edges *scanf_list_edge();

void print_list_edge(list_of_edges *graph);

#endif

// добавление ребра/вершины...
// удаление ребра/вершины...
// перевод из одного в другой