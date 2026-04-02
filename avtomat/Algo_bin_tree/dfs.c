#include "dfs.h"

#include <stdio.h>

#include "adjacency_list.h"
#include "steck.h"
#include "vector.h"

void dfs(adjacency_list *graph) {
    vector is_used;
    create_vec(&is_used, graph->n);
    for (int j = 1; j < graph->n; j++) {
        if (is_used.list[j] == 0) {
            steck st;
            create_steck(&st, 0, 0);
            push_back(&st, j);
            is_used.list[j] = 1;
            while (getsize(&st)) {
                int v = pop_back(&st);
                printf("%d\n", v);
                vector *neighbors = graph->vertex[v];
                for (int i = 0; i < get_size_vec(neighbors); i++) {
                    int w = graph->vertex[v]->list[i];
                    if (is_used.list[w] == 0) {
                        push_back(&st, w);
                        is_used.list[w] = 1;
                    }
                }
            }
            delete_steck(&st);
        }
    }
    delete_vec(&is_used);
}