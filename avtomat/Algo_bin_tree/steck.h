#ifndef steck_h
#define steck_h

#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    int* vertex;
} steck;

int create_steck(steck* st, int size, int capacity);

int getsize(steck* st);

int getcapacity(steck* st);

void push_back(steck* st, int v);

int pop_back(steck* st);

void delete_steck(steck* st);

#endif