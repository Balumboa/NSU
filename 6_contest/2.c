#include <stdio.h>
#include <stdlib.h>

void scan_1(char *color) {
    char c = '.';
    int i = 0;
    while (c != ' ') {
        scanf("%c", &c);
        color[i] = c;
        i++;
    }
}

void scan_2(char *kit) {
    char c;
    int i = 1;
    while (scanf("%c", &c) == 1) {
        kit[c - 'A'] = i;
        i++;
    }
}

int eq(char *a, char *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a + b - min(a, b);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char *color = (char *)calloc(6, sizeof(char));
    scan_1(color);
    char *kit = (char *)calloc(26, sizeof(char));
    scan_2(kit);
    char *p = (char *)("purple");
    char *g = (char *)("green");
    char *o = (char *)("orange");
    if (eq(color, p, 6) == 1) {
        int a = kit['B' - 'A'], b = kit['R' - 'A'];
        printf("%d %d", min(a, b), max(a, b));
    }
    if (eq(color, g, 5) == 1) {
        int a = kit['B' - 'A'], b = kit['Y' - 'A'];
        printf("%d %d", min(a, b), max(a, b));
    }
    if (eq(color, o, 6) == 1) {
        int a = kit['Y' - 'A'], b = kit['R' - 'A'];
        printf("%d %d", min(a, b), max(a, b));
    }
}