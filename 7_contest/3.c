#include <stdio.h>
#include <stdlib.h>

void double_to_b(double a, int b, int k) {
    char *c = (char *)calloc(k, sizeof(char));
    if (!c)
        return;

    int i = 0;
    double eps = 1e-12;

    while (i < k) {
        a *= b;
        int digit = (int)(a + eps);
        if (digit >= b)
            digit = b - 1;
        c[i] = (digit <= 9) ? ('0' + digit) : ('a' + digit - 10);
        a -= digit;
        i++;

        if (a < eps)
            break;
    }

    int size = i;
    while (size > 0 && c[size - 1] == '0') {
        size--;
    }

    for (int j = 0; j < size; j++) {
        printf("%c", c[j]);
    }

    free(c);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int b, k;
    double N;
    scanf("%d %d %lf", &b, &k, &N);

    printf("0.");
    double_to_b(N, b, k);
    printf("\n");

    return 0;
}
