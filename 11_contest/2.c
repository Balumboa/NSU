#include <stdio.h>
#include <stdlib.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // элемент списка
    int key;
    Node *next;
};

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
Node *create_node(int key);  // просто создание элемента

void delete_all_nodes(Node *node);  // удаление элемента и всех после него

Node *push(Node *node,
           int key);  // добавление элемента в голову

int get_ans(
    Node *node);  // нахождение количества отрицательных чисел кратных семи

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
Node *create_node(int key) {  // просто создаю новый элемент для списка
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    return node;
}

void delete_all_nodes(
    Node *node) {  // удаляю рекурсивно все элементы после нужного
    if (node != NULL) {
        delete_all_nodes(node->next);
        free(node);
    }
}

Node *push(Node *node,
           int key) {  // добавляю элемент в начало, при этом подвязывая его
    Node *new_node = create_node(key);
    new_node->next = node;
    return new_node;
}

int get_ans(Node *node) {  // получаю количество нужных элементов в списке
    if (node != NULL) {
        return get_ans(node->next) + (node->key < 0 && node->key % 7 == 0);
    }
    return 0;
}

//---------ОСНОВНАЯ ЧАСТЬ КОДА, ВЫЗОВЫ-------------
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Node *head = NULL;
    int x;
    while (scanf("%d", &x) == 1) {
        head = push(head, x);
    }
    int ans = get_ans(head);
    printf("%d", ans);
    delete_all_nodes(head);
}