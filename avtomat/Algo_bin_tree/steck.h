#ifndef steck_lib_h
#define steck_lib_h

#include <stdlib.h>

#include "tree.h"

typedef struct steck steck;

struct steck {
    tree *key;
    steck *next;
};

steck *create_steck(tree *key);

void delete_steck(steck **free_st);

steck *add_to_steck(steck *st, tree *key);

steck *erase_from_steck(steck *st);

void print_steck(steck *st);

#endif