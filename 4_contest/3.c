#include <stdio.h>
#include <stdlib.h>

void cin(int* mas, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &mas[i]);
    }
}

void swap(int* a, int* b) {
    int k = *a;
    *a = *b;
    *b = k;
}

void print(int* mas, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", mas[i]);
    }
}

void sort(int* mas, int n) {
    int flag = 1;
    int direction = 0;
    while (flag > 0) {
        flag = 0;
        if (direction == 0) {
            for (int i = 0; i < n - 1; i++) {
                if (mas[i] > mas[i + 1]) {
                    swap(&mas[i], &mas[i + 1]);
                    flag++;
                }
            }
            direction = 1;
        } else {
            for (int i = n - 1; i > 0; i--) {
                if (mas[i] < mas[i - 1]) {
                    swap(&mas[i], &mas[i - 1]);
                    flag++;
                }
            }
            direction = 0;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int* mas = (int*)calloc(n, sizeof(int));
    cin(mas, n);
    sort(mas, n);
    print(mas, n);
    free(mas);
    return 0;
}