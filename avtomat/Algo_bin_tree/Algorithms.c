#include "Algorithms.h"

#include <stdio.h>

#include "adjacency_list.h"
#include "deque.h"
#include "stack.h"
#include "vector.h"

/*****************************************************************************
 * File:         Algorithms.c
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

void bfs(adjacency_list *graph) {
    vector *is_used;
    is_used = create_vec(graph->N + 10);
    printf("Обход бфс:\n");
    for (int j = 1; j < graph->N; j++) {
        if (is_used->list[j] == 0) {
            deque *deq;
            deq = create_deq(0, 10);
            push_deq(deq, j);
            is_used->list[j] = 1;
            while (getsize_deq(deq)) {
                int v = pop_deq(deq);
                printf("%d\n", v);
                vector *neighbors = graph->vertex[v];
                for (int i = 0; i < get_size_vec(neighbors); i++) {
                    int w = graph->vertex[v]->list[i];
                    if (is_used->list[w] == 0) {
                        push_deq(deq, w);
                        is_used->list[w] = 1;
                    }
                }
            }
            delete_deq(&deq);
        }
    }
    delete_vec(&is_used);
}

void dfs(adjacency_list *graph) {
    vector *is_used;
    is_used = create_vec(graph->N);
    printf("Обход дфс\n");
    for (int j = 1; j < graph->N; j++) {
        if (is_used->list[j] == 0) {
            stack *st;
            st = create_steck(0, 0);
            push_back(st, j);
            is_used->list[j] = 1;
            while (getsize(st) > 0) {
                int v = pop_back(st);
                printf("%d\n", v);
                vector *neighbors = graph->vertex[v];
                for (int i = 0; i < get_size_vec(neighbors); i++) {
                    int w = graph->vertex[v]->list[i];
                    if (is_used->list[w] == 0) {
                        push_back(st, w);
                        is_used->list[w] = 1;
                    }
                }
            }
            delete_steck(&st);
        }
    }
    delete_vec(&is_used);
}