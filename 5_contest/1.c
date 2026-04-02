#include <stdio.h>

void solve() {
    char a = '?', b = '?', c;
    scanf("%c", &c);
    while (c != '.') {
        a = b;
        b = c;
        scanf("%c", &c);
        if (a != '?') {
            printf("%c", a);
        }
    }
    if (b == 'e') {
        printf("er");
    } else if (a == 'e' && b == 'r') {
        printf("st");
    } else {
        printf("%cer", b);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
}