#include <stdio.h>

void solve() {
    char c;
    long long sum = 0;
    long long last = 0;
    scanf("%c", &c);
    while (c != '.') {
        if (c >= '0' && c <= '9') {
            last *= 10;
            last += c - '0';
        } else {
            sum += last;
            last = 0;
        }
        scanf("%c", &c);
    }
    sum += last;
    printf("%lld", sum);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
}