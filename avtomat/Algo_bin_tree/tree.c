#include "tree.h"

#include <stdio.h>

/*****************************************************************************
 * File:         tree.c
 * Description:  Дервео
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

tree *create(int key) {
    tree *tr = (tree *)malloc(sizeof(tree));
    tr->left = NULL;
    tr->right = NULL;
    tr->key = key;
    return tr;
}

tree *add(tree *a, int key) {
    if (a == NULL) {
        a = create(key);
    } else {
        if (a->key > key) {
            a->left = add(a->left, key);
        } else if (a->key < key) {
            a->right = add(a->right, key);
        }
    }
    return a;
}

void delete_tree(tree **free_tree) {
    if (*free_tree != NULL) {
        delete_tree(&(*free_tree)->left);
        delete_tree(&(*free_tree)->right);
    }
    free(*free_tree);
    *free_tree = NULL;
}

void printTree(tree *tree, int space) {
    if (tree == NULL)
        return;

    space += 10;

    printTree(tree->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", tree->key);

    printTree(tree->left, space);
}