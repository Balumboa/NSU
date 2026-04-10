#ifndef tree_h
#define tree_h
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * File:         adjacemcy_list.h
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct tree tree;

struct tree {
    int key;
    tree *left;
    tree *right;
};

tree *create(int key);

tree *add(tree *a, int key);

void delete_tree(tree **free_tree);

void printTree(tree *tree, int space);

#endif