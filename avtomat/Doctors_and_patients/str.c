#include "str.h"

#include <stdio.h>
#include <stdlib.h>

void print_string(char *a) {
    int i = 0;
    while (a[i] != 0) {
        printf("%c", a[i]);
        i++;
    }
    printf("\n");
}

char clean_buffer() {
    char c;
    while (((c = getchar()) == '\n' || c == ' ') && c != EOF)
        ;
    return c;
}

char *get_string(int n) {
    char c = clean_buffer();
    char *str = (char *)calloc(n, sizeof(char));
    str[0] = c;
    int i = 1;
    while (scanf("%c", &c) == 1) {
        if (c == '\n')
            break;
        str[i] = c;
        i++;
        if (i > n - 1)
            break;
    }
    return str;
}