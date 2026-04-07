#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    char *str;
} string;

int check(int **arr, int n);

string *create_string();

void push_back(string *str, char c);

void update(string *str, int **arr, char **strings, int n);

void rotate(int ***arr, int n);

void cout(string *str);

void delete_strings(char ***strings, int n);

void delete_array(int ***array, int n);

void delete_string(string **str);

int check(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int i1 = j, j1 = 2 * n - 1 - i;
            int i2 = 2 * n - 1 - i, j2 = 2 * n - 1 - j;
            int i3 = 2 * n - 1 - j, j3 = i;
            if (arr[i][j] + arr[i1][j1] + arr[i2][j2] + arr[i3][j3] > 1) {
                return 0;
            }
        }
    }
    return 1;
}

string *create_string() {
    string *str = (string *)malloc(sizeof(string));
    str->size = 0;
    str->capacity = 10;
    str->str = (char *)calloc(10, sizeof(char));
    return str;
}

void push_back(string *str, char c) {
    if (str->size == str->capacity) {
        str->capacity = str->capacity * 2 + 1;
        str->str = (char *)realloc(str->str, str->capacity * sizeof(char));
    }
    str->str[str->size] = c;
    str->size++;
}

void update(string *str, int **arr, char **strings, int n) {
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (arr[i][j] == 1) {
                push_back(str, strings[i][j]);
            }
        }
    }
}

void rotate(int ***arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = (*arr)[i][j];

            int i1 = j, j1 = 2 * n - 1 - i;
            int i2 = 2 * n - 1 - i, j2 = 2 * n - 1 - j;
            int i3 = 2 * n - 1 - j, j3 = i;

            (*arr)[i][j] = (*arr)[i3][j3];
            (*arr)[i3][j3] = (*arr)[i2][j2];
            (*arr)[i2][j2] = (*arr)[i1][j1];
            (*arr)[i1][j1] = x;
        }
    }
}

void cout(string *str) {
    for (int i = 0; i < str->size; i++) {
        printf("%c", str->str[i]);
    }
}

void delete_strings(char ***strings, int n) {
    for (int i = 0; i < 2 * n; i++) {
        free((*strings)[i]);
    }
    free(*strings);
}

void delete_array(int ***array, int n) {
    for (int i = 0; i < 2 * n; i++) {
        free((*array)[i]);
    }
    free(*array);
}

void delete_string(string **str) {
    free((*str)->str);
    free(*str);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);
    int **arr = (int **)calloc(2 * n, sizeof(int *));
    for (int i = 0; i < 2 * n; i++) {
        arr[i] = (int *)calloc(2 * n, sizeof(int));
    }

    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    char **strings = (char **)calloc(2 * n, sizeof(char *));
    for (int i = 0; i < 2 * n; i++) {
        strings[i] = (char *)calloc(2 * n, sizeof(char));
    }

    for (int i = 0; i < 2 * n; i++) {
        char c;
        scanf("%c", &c);
        for (int j = 0; j < 2 * n; j++) {
            scanf("%c", &strings[i][j]);
        }
    }

    int is_valid = check(arr, n);
    if (is_valid == 0) {
        printf("No\n");
    } else {
        string *str = create_string();
        for (int i = 0; i < 4; i++) {
            update(str, arr, strings, n);
            rotate(&arr, n);
        }
        cout(str);
        delete_string(&str);
    }

    delete_strings(&strings, n);
    delete_array(&arr, n);
}