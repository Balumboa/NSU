#include "bfs.h"

#include <stdio.h>

#include "adjacency_list.h"
#include "deque.h"
#include "vector.h"

void bfs(adjacency_list *graph) {
    vector is_used;
    create_vec(&is_used, graph->n);
    for (int j = 1; j < graph->n; j++) {
        if (is_used.list[j] == 0) {
            deque deq;
            create_deq(&deq, 0, 10);
            push_deq(&deq, j);
            is_used.list[j] = 1;
            while (getsize_deq(&deq) > deq.start) {
                int v = pop_deq(&deq);
                printf("%d\n", v);
                vector *neighbors = graph->vertex[v];
                for (int i = 0; i < get_size_vec(neighbors); i++) {
                    int w = graph->vertex[v]->list[i];
                    if (is_used.list[w] == 0) {
                        push_deq(&deq, w);
                        is_used.list[w] = 1;
                    }
                }
            }
            delete_deq(&deq);
        }
    }
    delete_vec(&is_used);
}