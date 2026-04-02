#include <stdio.h>
#include <stdlib.h>

void solve() {
    char c;
    int *alph = (int *)calloc(26, sizeof(int));
    int i = 0;
    int t = -1;
    while (scanf("%c", &c) == 1) {
        if (c == ' ') {
            if (t == -1 && alph[i] == 0) {
                t = i;
            }
            for (int i = 0; i < 26; i++) {
                alph[i] = 0;
            }
            i++;
        }
        alph[c - 'a']++;
    }
    if (t == -1 && alph[i] == 0) {
        t = i;
    }
    for (int i = 0; i < 26; i++) {
        alph[i] = 0;
    }
    i++;
    if (t == -1 || i >= 26) {
        printf("NO WINNER");
    } else {
        printf("PLAYER %d", 2 - t % 2);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
}