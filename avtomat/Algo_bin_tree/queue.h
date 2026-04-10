#ifndef steck_h
#define steck_h

#include <stdlib.h>

#include "tree.h"

/*****************************************************************************
 * File:         deque.h
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct node node;

typedef struct queue queue;

struct node {
    tree *key;
    node *prev;
    node *next;
};

struct queue {
    node *start;
    node *end;
};

node *create_node(tree *key);

void delete_node(node **free_node);

void delete_all_node(node **free_node);

queue *create_queue();

void delete_queue(queue **free_queue);

queue *add_to_queue(queue *que, tree *key);

tree *erase_from_queue(queue *que);

void print_all_node(node *nd);

void print_queue(queue *que);

#endif