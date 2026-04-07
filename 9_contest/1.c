#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);
    int **array = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        array[i] = (int *)calloc(m, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        int x = 0;
        for (int j = 0; j < m; j++) {
            if (array[i][j] == 1) {
                x++;
            } else if (x != 0) {
                printf("%d ", x);
                x = 0;
            }
        }
        if (x != 0)
            printf("%d", x);
        printf("\n");
    }

    for (int i = 0; i < m; i++) {
        int x = 0;
        for (int j = 0; j < n; j++) {
            if (array[j][i] == 1) {
                x++;
            } else if (x != 0) {
                printf("%d ", x);
                x = 0;
            }
        }
        if (x != 0)
            printf("%d", x);
        printf("\n");
    }
}