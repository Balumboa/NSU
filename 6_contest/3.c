#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *str;
    int size;
    int capacity;
} string;

void create(string *a) {
    a->capacity = 0;
    a->size = 0;
    a->str = NULL;
}

void push_back(string *a, char c) {
    if (a->size == a->capacity) {
        a->str = (char *)realloc(a->str, (2 * a->size + 1) * sizeof(char));
        a->capacity = 2 * a->capacity + 1;
    }
    a->str[a->size] = c;
    a->size++;
}

void scan(string *a) {
    char c = '.';
    while (scanf("%c", &c) == 1) {
        if (c == ' ')
            break;
        push_back(a, c);
    }
}

void print(int *mas) {
    for (int i = 0; i < 26; i++) {
        if (mas[i] == 1)
            printf("%c", 'A' + i);
    }
}

void minus(string *a, string *b) {
    int mas[26];
    int size = 0;
    for (int i = 0; i < a->size; i++) {
        int flag = 1;
        for (int j = 0; j < b->size; j++) {
            if (a->str[i] == b->str[j]) {
                flag = 0;
            }
        }
        mas[a->str[i] - 'A'] = flag;
        size += flag;
    }
    if (size == 0)
        printf("Empty Set\n");
    else {
        print(mas);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string a, b;
    create(&a);
    create(&b);
    scan(&a);
    scan(&b);
    minus(&a, &b);
}