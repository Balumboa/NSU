#ifndef avl_tree_h
#define avl_tree_h
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int key;
    int h;
    Node *left;
    Node *right;
};

int height(Node *node);

int max(int a, int b);
Node *createNode(int key);

void update_h(Node *node);

Node *RightRotate(Node *node);

Node *LeftRotate(Node *node);

Node *balance(Node *node);

Node *AddNode(Node *node, int key);

Node *findMin(Node *node);

Node *removeMin(Node *node);

Node *erase(Node *a, int key);

void delete_avl_tree(Node **a);

#endif