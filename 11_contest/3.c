#include <stdio.h>
#include <stdlib.h>

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node Node;

struct Node {  // элемент списка
    int key;
    Node *next;
};

typedef struct {
    Node *head;
} list;

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
Node *create_node(int key);  // просто создание элемента

list *create_list();  // создание списка

void delete_all_nodes(Node *node);  // удаление элемента и всех после него

void delete_list(list *arr);  // удаление списка

void push_back(list *arr, int key);  // добавление элемента "по особенному"

void print(Node *node);  // рекурсивно вывожу список

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
Node *create_node(int key) {  // просто создаю новый элемент для списка
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    return node;
}

list *create_list() {  // создаю сам список для хранения головы и конца
    list *arr = (list *)malloc(sizeof(list));
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

void push_back(
    list *arr,
    int key) {  // добавляю элемент так, чтобы список
                // оставался отсортирован(как при сортировке вставкой)
    Node *node = create_node(key);
    Node *now = arr->head;
    if (arr->head == NULL) {
        arr->head = node;
        return;
    }

    if (key < now->key) {
        node->next = now;
        arr->head = node;
    } else if (key > now->key) {
        int flag = 1;
        while (now->next != NULL) {
            if (now->next->key > key) {  // вставили в нужное место
                node->next = now->next;
                now->next = node;
                flag = 0;  // мы не дошли до конца
                break;
            } else if (now->next->key ==
                       key) {  // нашли такой же и освободили память
                free(node);
                flag = 0;  // мы не дошли до конца
                break;
            } else {  // перешли дальше искать
                now = now->next;
            }
        }
        if (flag) {  // дошли до конца
            now->next = node;
        }
    } else {  // сразу освобождаю выделенную память, если элемент равен
              // началу списка
        free(node);
    }
}

void print(Node *node) {
    if (node != NULL) {
        printf("%d ", node->key);
        print(node->next);
    }
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
    print(arr->head);
    delete_list(arr);
}