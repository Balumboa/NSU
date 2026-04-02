#include <stdio.h>

void to_bin_1(unsigned int x, unsigned int *y, int count) {
    if (count > 0) {
        *y *= 2;
        *y += x % 2;
        to_bin_1(x / 2, y, count - 1);
        printf("%d", x % 2);
    }
}

void solve(unsigned int x) {
    unsigned int ans = 0;
    unsigned int b = 0;
    to_bin_1(x, &ans, 32);
    printf("\n");
    printf("%d", ans);
    printf("\n");
    to_bin_1(ans, &b, 32);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    unsigned int n;
    scanf("%d", &n);
    solve(n);
}