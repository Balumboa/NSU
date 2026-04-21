#include <stdio.h>
#include <stdlib.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // элемент списка
    int key;
    Node *next;
};

typedef struct {
    int count;
    Node *head;
    Node *end;
} list;

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
Node *create_node(int key);  // просто создание элемента

list *create_list();  // создание списка

void delete_all_nodes(Node *node);  // удаление элемента и всех после него

void delete_list(list *arr);  // удаление списка

void push_back(list *arr, int key);  // добавление элемента в конец списка

int get_sum(Node *node);  // нахождение суммы всех элементов после(рекурсивно)

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
Node *create_node(int key) {  // просто создаю новый элемент для списка
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    return node;
}

list *create_list() {  // создаю сам список для хранения головы и конца
    list *arr = (list *)malloc(sizeof(list));
    arr->count = 0;
    arr->end = NULL;
    arr->head = NULL;
    return arr;
}

void delete_all_nodes(
    Node *node) {  // удаляю рекурсивно все элементы после нужного
    if (node != NULL) {
        delete_all_nodes(node->next);
        free(node);
    }
}

void delete_list(list *arr) {  // удаляю все элементы запуская удаление с головы
    delete_all_nodes(arr->head);
}

void push_back(list *arr, int key) {  // добавляю в конец списка элемент
    Node *node = create_node(key);
    if (arr->head == NULL) {
        arr->head = node;
    } else {
        arr->end->next = node;
    }
    arr->end = node;
    arr->count++;
}

int get_sum(Node *node) {  // получаю сумму элементов по списку
    if (node == NULL) {
        return 0;
    }
    int sum = get_sum(node->next) + node->key;
    return sum;
}

//---------ОСНОВНАЯ ЧАСТЬ КОДА, ВЫЗОВЫ-------------
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    list *arr = create_list();
    int x;
    while (scanf("%d", &x) == 1) {
        push_back(arr, x);
    }
    int sum = get_sum(arr->head);
    printf("%d", sum / arr->count);
    delete_list(arr);
}