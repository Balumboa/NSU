#include <stdio.h>
#include <stdlib.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // элемент списка
    int key;
    Node *next;
};

typedef struct {  // список
    Node *head;
    Node *end;
} list;

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------

void delete_node(Node *node);  // удаление элемента списка

void delete_list(list *arr);  // удаление всего списка

list *create_list();  // конструктор для списка

Node *create_node(int key);  // просто конструктор для элементов массива

void push_back(
    list *arr,
    int key);  // такое добавление элемента сразу учитывает повторения

void print_list(list *arr);  // вывожу элементы массива

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
void delete_node(Node *node) {  // удаление
    if (node != NULL) {
        delete_node(node->next);
        free(node);
    }
}

void delete_list(list *arr) {  // удаление
    if (arr != NULL) {
        delete_node(arr->head);
        free(arr);
    }
}

list *create_list() {  // конструктор для списка
    list *array = (list *)malloc(sizeof(list));
    array->head = NULL;
    array->end = NULL;
    return array;
}

Node *create_node(int key) {  // просто конструктор для элементов массива
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    return node;
}

void push_back(
    list *arr,
    int key) {  // такое добавление элемента сразу учитывает повторения
    if (arr->head == NULL) {  // задаю начало списка
        Node *node = create_node(key);
        arr->head = node;
        arr->end = node;
    } else if (arr->end->key != key) {  // добавляю элемент в конец списка, если
                                        // по значению он не совпадает с концом
        Node *node = create_node(key);
        arr->end->next = node;
        arr->end = node;
    }
}

void print_list(list *arr) {  // вывожу элементы массива
    Node *node = arr->head;
    while (node != NULL) {
        printf("%d ", node->key);
        node = node->next;
    }
}

//---------ОСНОВНАЯ ЧАСТЬ КОДА, ВЫЗОВЫ-------------
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    list *array = create_list();
    int x;
    while (scanf("%d", &x) == 1) {
        if (x == -1) {
            break;
        }
        push_back(array, x);
    }
    print_list(array);
    delete_list(array);
}