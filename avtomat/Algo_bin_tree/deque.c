#include "deque.h"

#include <stdio.h>
#include <stdlib.h>

int create_deq(deque* st, int size, int capacity) {
    st->size = size;
    st->capacity = capacity;
    st->vertex = (int*)calloc(capacity, sizeof(int));
    st->start = 0;
}

int getsize_deq(deque* st) {
    return st->size - st->start;
}

int getcapacity_deq(deque* st) {
    return st->capacity;
}

void push_deq(deque* st, int v) {
    int capacity = getcapacity_deq(st);
    int size = st->size;
    if (capacity == size) {
        st->vertex = realloc(st->vertex, (2 * size + 1) * sizeof(int));
        st->capacity = capacity * 2 + 1;
    }
    st->vertex[size] = v;
    st->size++;
}

int pop_deq(deque* st) {
    int size = getsize_deq(st);
    if (size == 0) {
        return -1;
    }
    int v = st->vertex[st->start];
    st->vertex[st->start] = 0;
    st->start++;
    return v;
}

void delete_deq(deque* st) {
    st->size = 0;
    st->capacity = 0;
    st->start = 0;
    free(st->vertex);
}