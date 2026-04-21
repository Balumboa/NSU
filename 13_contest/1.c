#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // просто элемент дерева, строка и два ребёнка
    char str[110];  //
    Node *left;
    Node *right;
};

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
int compare(Node *a, Node *b);  // сравнение двух строк

Node *create_node(char *str);  // создание вершины в дереве

Node *push_node(Node *head,
                Node *new_node);  // добавление новой вершины в дереве

void print(Node *head);  // печать в лексикографическом порядке

void delete_nodes(Node *head);  // освобождение памяти

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
int compare(Node *a, Node *b) {  // обычное сравнение 0: a < b 1: b < a 2: a ==
                                 // b
    int i = 0;
    while (a->str[i] != '\0' && b->str[i] != '\0') {
        if (a->str[i] > b->str[i]) {
            return 0;
        }
        if (a->str[i] < b->str[i]) {
            return 1;
        }
        i++;
    }
    if (a->str[i] == '\0' && b->str[i] == '\0') {
        return 2;
    }
    if (a->str[i] == '\0') {
        return 1;
    }
    return 0;
}

Node *create_node(char *str) {  // создание вершины в дереве
    Node *node = (Node *)malloc(sizeof(Node));
    memset(node->str, 0,
           sizeof(node->str));  // сразу отчищаю строку, чтобы мусора не было
    strcpy(node->str, str);
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *push_node(Node *head, Node *new_node) {  // добавляю в дерево вершину
    if (head == NULL) {
        return new_node;
    }
    int t = compare(head, new_node);
    if (t == 0) {
        head->left = push_node(head->left, new_node);
    } else if (t == 1) {
        head->right = push_node(head->right, new_node);
    }
    return head;
}

void print(Node *head) {  // вывожу в лексикографическом порядке
    if (head != NULL) {
        print(head->left);          // сначала меньшие
        printf("%s\n", head->str);  // далее саму вершину
        print(head->right);  // а потом все, которые больше
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

    char str[110];
    Node *head = NULL;
    while (fgets(str, sizeof(str), stdin) != NULL) {
        Node *new_node = create_node(str);
        if (str[0] == 'z') {
            break;
        }
        head = push_node(head, new_node);
    }
    print(head);
    delete_nodes(head);
}