#include "steck.h"

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

steck *create_steck(tree *key) {
    steck *st = (steck *)malloc(sizeof(steck));
    st->key = key;
    st->next = NULL;
    return st;
}

void delete_steck(steck **free_st) {
    if (*free_st != NULL) {
        delete_steck(&(*free_st)->next);
        free(*free_st);
        *free_st = NULL;
    }
}

steck *add_to_steck(steck *st, tree *key) {
    steck *new = create_steck(key);
    new->next = st;
    return new;
}

steck *erase_from_steck(steck *st) {
    steck *last = NULL;
    if (st != NULL) {
        last = st->next;
        free(st);
    }
    return last;
}

void print_steck(steck *st) {
    if (st != NULL && st->key != NULL) {
        printf("%d ", st->key->key);
        print_steck(st->next);
    }
}