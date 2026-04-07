#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack* create_steck(int size, int capacity) {
    stack* st = (stack*)malloc(sizeof(stack));
    st->size = size;
    st->capacity = capacity;
    st->vertex = (int*)calloc(capacity, sizeof(int));
    return st;
}

int getsize(stack* st) {
    return st->size;
}

int getcapacity(stack* st) {
    return st->capacity;
}

void push_back(stack* st, int v) {
    int capacity = getcapacity(st);
    int size = getsize(st);
    if (capacity == size) {
        st->vertex = realloc(st->vertex, (2 * size + 1) * sizeof(int));
        st->capacity = capacity * 2 + 1;
    }
    st->vertex[size] = v;
    st->size++;
}

int pop_back(stack* st) {
    int size = getsize(st);
    if (size == 0) {
        return -1;
    }
    int v = st->vertex[size - 1];
    st->vertex[size - 1] = 0;
    st->size--;
    return v;
}

void delete_steck(stack** st) {
    (*st)->size = 0;
    (*st)->capacity = 0;
    free((*st)->vertex);
    free((*st));
}