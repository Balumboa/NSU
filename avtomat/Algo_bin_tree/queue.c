#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * File:         deque.c
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

node *create_node(tree *key) {
    node *nd = (node *)malloc(sizeof(node));
    nd->key = key;
    nd->prev = NULL;
    nd->next = NULL;
    return nd;
}

void delete_node(node **free_node) {
    if (*free_node != NULL) {
        free(*free_node);
        *free_node = NULL;
    }
}

void delete_all_node(node **free_node) {
    if (*free_node != NULL) {
        delete_all_node(&(*free_node)->next);
        delete_node(free_node);
        *free_node = NULL;
    }
}

queue *create_queue() {
    queue *que = (queue *)malloc(sizeof(queue));
    que->start = NULL;
    que->end = NULL;
    return que;
}

void delete_queue(queue **free_queue) {
    delete_all_node(&(*free_queue)->start);
    free(*free_queue);
    *free_queue = NULL;
}

queue *add_to_queue(queue *que, tree *key) {
    node *nd = create_node(key);
    if (que->start == NULL) {
        que->start = nd;
        que->end = nd;
    } else {
        node *last = que->end;
        que->end = nd;
        last->next = nd;
    }
    return que;
}

tree *erase_from_queue(queue *que) {
    if (que->start != NULL) {
        node *new_start = que->start->next;
        tree *x = que->start->key;
        delete_node(&que->start);
        que->start = new_start;
        return x;
    }
}

void print_all_node(node *nd) {
    if (nd != NULL && nd->key != NULL) {
        printf("%d ", nd->key->key);
        print_all_node(nd->next);
    }
}

void print_queue(queue *que) {
    if (que != NULL) {
        print_all_node(que->start);
    }
}
