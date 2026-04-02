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
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j > 0 && mas[j] < mas[j - 1]) {
            swap(&mas[j], &mas[j - 1]);
            j--;
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