#include <stdio.h>

#include "adjacency_list.h"

int main() {
    adjacency_list *graph;
    scanf_adj_list(graph);
    print_adj_list(graph);
    delete_adj_list(graph);
}