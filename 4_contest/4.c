#include <stdio.h>

int gcd(int a, int b) {
    if (a < b) {
        int k = b;
        b = a;
        a = k;
    }
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int a, b;
    scanf("%d %d", &a, &b);
    int t = gcd(a, b);
    printf("%d", t);
}