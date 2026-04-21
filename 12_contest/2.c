#include <stdio.h>
#include <stdlib.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // двусвязный список
    int key;
    Node *next;
    Node *prev;
};

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
void delete_node(Node *node);  // удаление элемента списка, но без перепривязки,
                               // просто отчистка

Node *create_node(int key);  // создание элемента для списка, но опять же без
                             // подвязки, просто выделение памяти

Node *solve(Node *node, int k, int n);  // само решение

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
void delete_node(Node *node) {  // то самое освобождение памяти
    free(node);
}

Node *create_node(int key) {  // создание нода
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Node *solve(Node *node, int k,
            int n) {  // поэлементное удаление из списка(решение)
    int cnt = 0;
    while (n > 1) {
        cnt++;
        if (cnt == k) {
            Node *next = node->next;
            Node *prev = node->prev;
            delete_node(node);  // сразу освобождаем память
            next->prev = prev;
            prev->next = next;
            node = next;
            n--;
            cnt = 0;
        } else
            node = node->next;
    }
    return node;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d %d", &n, &k);

    Node *node = create_node(1);  // создаём список
    Node *head = node;

    for (int i = 2; i <= n; i++) {  // заполняемм список
        Node *new_node = create_node(i);
        node->next = new_node;
        new_node->prev = node;
        node = new_node;
    }
    node->next = head;  // зацикливание
    head->prev = node;

    head = solve(head, k, n);  // удаление элементиков
    printf("%d", head->key);
    delete_node(head);  // остаточное освобождение памяти
}