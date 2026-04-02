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
        if (c == ' ' || c == '\n')
            continue;
        push_back(a, c);
        t++;
    }
    return t;
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

void from_b(string *str, int b) {
    int ans = 0;
    for (int i = 0; i < str->size; i++) {
        ans *= b;
        if (str->str[i] <= '9' && str->str[i] >= '0') {
            int t = (str->str[i] - '0');
            ans += t;
        } else {
            int t = (str->str[i] - 'a' + 10);
            ans += t;
        }
    }
    printf("%d", ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int b;
    scanf("%d", &b);
    string str;
    create(&str);
    scan(&str);
    from_b(&str, b);
}