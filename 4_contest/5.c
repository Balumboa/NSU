#include <stdio.h>

long long gcd(long long a, long long b) {
    if (a < b) {
        long long k = b;
        b = a;
        a = k;
    }
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void solve() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    long long t = gcd(a, b);
    printf("%lld\n", a * b / t);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        solve();
    }
}