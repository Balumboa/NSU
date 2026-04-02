#include "/home/balumboa/AaSD/nsu_prog/avtomat/matrix_and_14/vector.h"

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * File:         vector.c
 * Description:  Реализация вектора(динамический список)
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

void push_back_vec(vector *vec, int x) {
    int capacity = get_capacity_vec(vec);
    int size = get_size_vec(vec);
    if (size == capacity) {
        vec->capacity = capacity * 2 + 1;
        vec->list = realloc(vec->list, vec->capacity * sizeof(int));
    }
    vec->list[size] = x;
    vec->size++;
}

void pop_back_vec(vector *vec) {
    if (vec->size == 0)
        return;
    vec->size--;
}

int get_size_vec(vector *vec) {
    return vec->size;
}

int get_capacity_vec(vector *vec) {
    return vec->capacity;
}

void print_vec(vector *vec) {
    int n = get_size_vec(vec);
    for (int i = 0; i < n; i++) {
        printf("%d ", vec->list[i]);
    }
    printf("\n");
}

void scan_vec(vector *vec) {
    int n;
    printf("Введите число элементов вектора: ");
    scanf("%d", &n);
    create_vec(vec, n);
    printf("Введите %d чисел: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &vec->list[i]);
    }
    printf("Все элементы введены\n");
}

void create_vec(vector *vec, int n) {
    vec->size = n;
    vec->capacity = n;
    vec->list = (int *)calloc(n, sizeof(int));
}

void delete_vec(vector *vec) {
    free(vec->list);
    vec->size = 0;
    vec->capacity = 0;
}