#include <stdio.h>

void solve() {
    char c;
    int sum = 0;
    int last = 1;
    scanf("%c", &c);
    while (c != '.') {
        last = c - '0';
        sum += last;
        scanf("%c", &c);
    }
    if (sum % 3 == 0 && last % 5 == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
}