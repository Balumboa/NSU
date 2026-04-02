#ifndef steck_h
#define steck_h

#include <stdlib.h>

typedef struct {
    int size;
    int start;
    int capacity;
    int* vertex;
} deque;

int create_deq(deque* st, int size, int capacity);

int getsize_deq(deque* st);

int getcapacity_deq(deque* st);

void push_deq(deque* st, int v);

int pop_deq(deque* st);

void delete_deq(deque* st);

#endif