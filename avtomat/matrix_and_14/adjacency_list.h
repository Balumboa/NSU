#ifndef adjacency_list_h
#define adjacency_list_h
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/*****************************************************************************
 * File:         adjacemcy_list.h
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct {
    int N;
    int M;
    vector **vertex;
} adjacency_list;

adjacency_list *create_adj_list(int n, int m);

void delete_adj_list(adjacency_list **graph);

adjacency_list *scanf_adj_list();

void print_adj_list(adjacency_list *graph);

#endif