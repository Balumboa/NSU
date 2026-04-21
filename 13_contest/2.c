#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // просто элемент дерева, число и два ребёнка
    int key;
    Node *left;
    Node *right;
};

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
Node *create_node(int key);  // создание вершины в дереве

Node *push_node(Node *head,
                int key);  // добавление новой вершины в дереве

void print_Direct_order(Node *head);  // печать в прямом порядке

void print_Reverse_order(Node *head);  // печать в обратном порядке

void delete_nodes(Node *head);  // освобождение памяти

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
Node *create_node(int key) {  // создание вершины в дереве
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *push_node(Node *head, int key) {  // добавляю в дерево вершину
    if (head == NULL) {
        return create_node(key);
    }
    if (head->key > key) {
        head->left = push_node(head->left, key);
    } else if (head->key < key) {
        head->right = push_node(head->right, key);
    }
    return head;
}

void print_Direct_order(
    Node *head) {  // вывожу в прямом порядке(сначала вершина, а потом её дети)
    if (head != NULL) {
        printf("%d ", head->key);  // сначала вывожу саму вершину
        print_Direct_order(head->left);  // потом все, которые меньше
        print_Direct_order(head->right);  // а потом все, которые больше
    }
}

void print_Reverse_order(Node *head) {  // вывожу в обратном порядке(сначала
                                        // дети, а потом сама вершина)
    if (head != NULL) {
        print_Reverse_order(head->left);  // все, которые меньше
        print_Reverse_order(head->right);  // а потом все, которые больше
        printf("%d ", head->key);  // в конце вывожу саму вершину
    }
}

void delete_nodes(Node *head) {  // удаляю рекурсивно всё дерево
    if (head != NULL) {
        delete_nodes(head->left);
        delete_nodes(head->right);
        free(head);
    }
}

// основная часть программы
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Node *head = NULL;
    int x;
    while (scanf("%d", &x) == 1) {
        if (x == -1)
            break;
        head = push_node(head, x);
    }
    print_Direct_order(head);
    printf("\n");
    print_Reverse_order(head);
    delete_nodes(head);
}