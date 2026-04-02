#ifndef adjacency_list_h
#define adjacency_list_h
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

typedef struct {
    int n;
    vector **vertex;
} adjacency_list;

void create(adjacency_list *graph, int n);

void delete_matrix(adjacency_list *graph);

void scanf_matrix(adjacency_list *graph);

void print_matrix(adjacency_list *graph);

#endif