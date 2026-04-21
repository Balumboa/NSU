#include <stdio.h>
#include <stdlib.h>

// ВНИМАНИЕ!!!! В ЭТОЙ ЗАДАЧЕ НУЖНО ИСПОЛЬЗОВАТЬ ТИП INT ТК ИНАЧЕ У ВАС НЕ БУДУТ
// ПРОХОДИТ ВСЕ ТЕСТЫ В ТЕСТАХ ЕСТЬ ПЕРЕПОЛНЕНИЕ, ПОЭТОМУ ТАМ ПОЛНЫЙ КРИНЖ

//---------НУЖНЫЕ СТРУКТУРЫ ДЛЛЯ РЕШЕНИЯ ЗАДАНИЯ-------------
typedef struct Node {
    int is_num;
    int num;
    char op;
    struct Node *left;
    struct Node *right;
} Node;

//---------ФУНКЦИИ, КОТОРЫЕ ИСПОЛЬЗУЮТСЯ ДЛЯ РЕШЕНИЯ ЗАДАЧИ-------------
Node *build_tree(char *s, int *pos);  // рекурсивное построение бинарного дерева

int evaluate(Node *n, int *error);  // нахождение ответа по построенному дереву

void free_tree(Node *n);  // освобождение памяти(удаление дерева)

//---------РЕАЛИЗАЦИЯ ФУНКЦИЙ-------------
Node *build_tree(char *s, int *pos) {  // рекурсивное заполнение дерева
    char c = s[(*pos)++];
    Node *n = (Node *)malloc(sizeof(Node));
    if (c >= '0' && c <= '9') {  // если дали цифру, то просто создаём лист
        n->is_num = 1;
        n->num = c - '0';
        n->left = n->right = NULL;
    } else {
        n->is_num = 0;
        n->op = c;
        n->left = build_tree(s, pos);  // создаём левое поддерева для операции
        n->right =
            build_tree(s, pos);  // создаём правое поддерево для операции, если
                                 // в левом уже нельзя добавить листы
    }
    return n;
}

int evaluate(Node *n, int *error) {  // нахождение ответа рекурсивное
    if (n->is_num)
        return n->num;
    int l = evaluate(n->left, error);  // подсчёт для левого поддерева
    int r = evaluate(n->right, error);  // подсчёт для правого поддерева
    if (n->op == '+')  // просто расписал операции
        return l + r;
    if (n->op == '-')
        return l - r;
    if (n->op == '*')
        return l * r;
    if (n->op == '/') {
        if (r == 0) {
            *error = 1;  // тот самый NO
            return 0;
        }
        return l / r;
    }
    return 0;
}

void free_tree(Node *n) {  // освобождение памяти
    if (!n)
        return;
    free_tree(n->left);
    free_tree(n->right);
    free(n);
}

// основная часть кода
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char s[1010];
    scanf("%s", s);
    int pos = 0;
    Node *root = build_tree(s, &pos);
    int error = 0;
    int ans = evaluate(root, &error);
    if (error)
        printf("NO\n");
    else
        printf("%d\n", ans);
    free_tree(root);
    return 0;
}