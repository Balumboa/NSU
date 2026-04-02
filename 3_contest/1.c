#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int a, b;
    scanf("%d %d", &a, &b);
    if (b >= 0 && a > b) {
        printf("legal\n");
    } else {
        printf("out of bounds\n");
    }
}