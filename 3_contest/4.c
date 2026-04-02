#include <stdio.h>
#include <stdlib.h>

void bin(int a[], int x, int n) {
    int l = 0, r = n;
    while (r - l > 1) {
        int k = (r + l) / 2;
        if (a[k] <= x)
            l = k;
        else
            r = k;
    }
    if (a[l] == x)
        printf("%d", l);
    else
        printf("-1");
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, x;
    scanf("%d %d", &n, &x);
    int *a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    bin(a, x, n);
}