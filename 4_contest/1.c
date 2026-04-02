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

void sort(int* mas, int n) {
    for (int i = 0; i < n; i++) {
        int ind = i;
        for (int j = i; j < n; j++) {
            if (mas[ind] > mas[j]) {
                ind = j;
            }
        }
        swap(&mas[ind], &mas[i]);
    }
}

void print(int* mas, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", mas[i]);
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