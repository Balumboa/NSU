#include <stdio.h>

void solve() {
    char c;
    int flag = 0;
    int t = 0;
    scanf("%c", &c);
    while (c != '.') {
        t++;
        if (t == 2 && c == 'A') {
            flag = 1;
        }
        if (t == 3 && flag == 1) {
            flag = 2;
        } else if (t > 3) {
            flag = 0;
        }
        scanf("%c", &c);
    }
    if (flag == 2) {
        printf("FITS\n");
    } else {
        printf("DOES NOT FIT\n");
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
}