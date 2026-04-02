#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, x;
    scanf("%d %d", &n, &x);
    int *a = (int *)malloc(sizeof(int) * (n + 1));
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] += a[i - 1];
    }
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (x == a[i] - a[j])
                answer++;
        }
    }
    printf("%d\n", answer);
}