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

int scan(string *a) {
    char c = '.';
    int t = 0;
    while (scanf("%c", &c) == 1) {
        if (c == ' ')
            break;
        push_back(a, c);
        t++;
    }
    return t;
}

int have(string *a, string *b) {
    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < b->size; j++) {
            if (a->str[i] == b->str[j]) {
                return 0;
            }
        }
    }
    return 1;
}

void print(string *str) {
    for (int i = 0; i < str->size; i++) {
        printf("%c", str->str[i]);
    }
    printf("\n");
}

void del(string *c) {
    c->size = 0;
    c->capacity = 0;
    c->str = NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string first;
    create(&first);
    scan(&first);
    string c;
    create(&c);
    while (scan(&c) != 0) {
        if (have(&first, &c) == 1) {
            print(&c);
        }
        del(&c);
    }
}