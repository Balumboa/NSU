#include "avl_tree.h"

#include <stdio.h>
#include <stdlib.h>

int height(Node *node) {
    return node ? node->h : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->h = 1;
    return node;
}

void update_h(Node *node) {
    int left_h = height(node->left);
    int right_h = height(node->right);
    node->h = max(left_h, right_h) + 1;
}

Node *RightRotate(Node *node) {
    Node *a = node->left;
    node->left = a->right;
    a->right = node;
    update_h(node);
    update_h(a);
    return a;
}

Node *LeftRotate(Node *node) {
    Node *a = node->right;
    node->right = a->left;
    a->left = node;
    update_h(node);
    update_h(a);
    return a;
}

Node *balance(Node *node) {
    update_h(node);
    int t = height(node->left) - height(node->right);

    if (t > 1) {
        if (height(node->left->left) < height(node->left->right)) {
            node->left = LeftRotate(node->left);
        }
        return RightRotate(node);
    }
    if (t < -1) {
        if (height(node->right->right) < height(node->right->left)) {
            node->right = RightRotate(node->right);
        }
        return LeftRotate(node);
    }
    return node;
}

Node *AddNode(Node *node, int key) {
    if (node == NULL)
        return createNode(key);
    if (key < node->key)
        node->left = AddNode(node->left, key);
    else if (key > node->key)
        node->right = AddNode(node->right, key);
    return balance(node);
}

Node *findMin(Node *node) {
    return (node->left == NULL) ? node : findMin(node->left);
}

Node *removeMin(Node *node) {
    if (node->left == NULL)
        return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

Node *erase(Node *a, int key) {
    if (a == NULL)
        return NULL;
    if (key < a->key)
        a->left = erase(a->left, key);
    else if (key > a->key)
        a->right = erase(a->right, key);
    else {
        Node *r = a->right;
        Node *l = a->left;
        free(a);

        if (r == NULL)
            return l;

        Node *min = findMin(r);
        min->right = removeMin(r);
        min->left = l;
        return balance(min);
    }
    return balance(a);
}

void delete_avl_tree(Node **a) {
    if (*a == NULL)
        return;

    delete_avl_tree(&(*a)->left);
    delete_avl_tree(&(*a)->right);
    free(*a);
    *a = NULL;
}

void print_avl_tree(Node *a, int space) {
    if (a == NULL) {
        return;
    }

    print_avl_tree(a->right, space + 10);
    printf("\n");
    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%d", a->key);
    printf("\n");
    print_avl_tree(a->left, space + 10);
}