#include <stdio.h>
#include <stdlib.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // элемент списка
    int key;
    Node *next;
};

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
Node *create_node(int key);  // создание элемента списка

Node *merge(Node *a, Node *b);  // слияние списков

void print(Node *a);  // вывод списка

void delete_node(Node *a);  // полное удаление списка

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
Node *create_node(int key) {  // создание элемента списка
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    return node;
}

Node *merge(
    Node *a,
    Node *b) {  // слияние списков, но связи в изначальных списках пропадут
    if (a == NULL) {
        return b;
    } else if (b == NULL) {
        return a;
    } else {
        if (a->key >
            b->key) {  // ну обычно в список сначала идёт наибольший элемент
            a->next = merge(a->next, b);
            return a;
        } else {
            b->next = merge(a, b->next);
            return b;
        }
    }
}

void print(Node *a) {  // просто рекурсивный вывод списка
    if (a != NULL) {
        printf("%d ", a->key);
        print(a->next);
    }
}

void delete_node(Node *a) {
    if (a != NULL) {
        delete_node(a->next);
        free(a);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);
    Node *ahead = NULL;
    Node *bhead = NULL;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        Node *new_node = create_node(x);
        new_node->next = ahead;
        ahead = new_node;
    }

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        Node *new_node = create_node(x);
        new_node->next = bhead;
        bhead = new_node;
    }

    Node *head = merge(ahead, bhead);
    print(head);

    delete_node(head);  // удаление
    ahead = NULL;
    bhead = NULL;
    head = NULL;
}