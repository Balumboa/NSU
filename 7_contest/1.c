#include <stdio.h>

void to_b(long long n, long long b) {
    if (n == 0)
        return;
    else {
        long long t = n % b;
        to_b(n / b, b);
        if (t <= 9) {
            printf("%d", t);
        } else {
            printf("%c", 'a' + t - 10);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    long long b;
    scanf("%lld", &b);
    long long n;
    scanf("%lld", &n);
    if (n == 0)
        printf("0");
    else
        to_b(n, b);
}