#ifndef stack_h
#define stack_h

#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    int* vertex;
} stack;

stack* create_steck(int size, int capacity);

int getsize(stack* st);

int getcapacity(stack* st);

void push_back(stack* st, int v);

int pop_back(stack* st);

void delete_steck(stack** st);

#endif