#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; i++)
        a[i] = 0;

    for (int i = 2; i <= n; i++) {
        if (a[i] == -1)
            continue;
        for (int j = i + i; j <= n; j += i) {
            a[j] = -1;
        }
        printf("%d ", i);
    }
}