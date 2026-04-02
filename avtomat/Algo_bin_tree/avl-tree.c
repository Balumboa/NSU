#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int height(Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *create_node(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int get_balance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node *rotate_right(Node *y) {
    Node *x = y->left;
    Node *z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *rotate_left(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node *insert(Node *node, int key) {
    if (node == NULL)
        return create_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key)
        return rotate_right(node);

    if (balance < -1 && key > node->right->key)
        return rotate_left(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

void print_in_order(Node *root) {
    if (root != NULL) {
        print_in_order(root->left);
        printf("%d(h:%d) ", root->key, root->height);
        print_in_order(root->right);
    }
}

// int main() {
//     Node *root = NULL;

//     printf("Вставляем числа от 1 до 7 по порядку...\n");
//     for (int i = 1; i <= 7; i++) {
//         root = insert(root, i);
//     }

//     printf("Результат (Ключ и его высота): ");
//     print_in_order(root);

//     if (root) {
//         printf("\n\nКорень дерева: %d", root->key);
//         printf("\nВысота всего дерева: %d\n", root->height);
//     }

//     return 0;
// }
