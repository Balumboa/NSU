#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int k = *a;
    *a = *b;
    *b = k;
}

int partition(int *mas, int l, int r) {
    int v = mas[l + r / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (mas[i] < v)
            i++;
        while (mas[j] > v)
            j--;
        if (i >= j)
            break;
        swap(&mas[i++], &mas[j--]);
    }
    return j;
}

void qqsort(int *mas, int l, int r) {
    for (int i = 0; i < r; i++) {
        printf("%d", mas[i]);
    }
    printf("\n");
    if (l < r) {
        int q = partition(mas, l, r);
        qqsort(mas, l, q);
        qqsort(mas, q, r);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int *mas = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &mas[i]);
    }
    qqsort(mas, 0, n);
    for (int i = 0; i < n; i++) {
        printf("%d", mas[i]);
    }
}