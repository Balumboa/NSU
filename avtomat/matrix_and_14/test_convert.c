#include <stdio.h>
#include <stdlib.h>

#include "convert_matrixes.h"

/*****************************************************************************
 * File:         test_convert.c
 * Description:  Проверка корректности работы алгоритмов перевода из одного вида
 *в другой Created:      31 mar 2026 Author:       Ivan Arbuzov
 *****************************************************************************/

// Функция для сравнения списков смежности
int compare_adj_lists(adjacency_list *a, adjacency_list *b) {
    if (a->N != b->N || a->M != b->M) {
        printf("Размеры не совпадают: N=%d vs %d, M=%d vs %d\n", a->N, b->N,
               a->M, b->M);
        return 0;
    }

    int n = a->N - 1;
    for (int i = 1; i <= n; i++) {
        if (a->vertex[i]->size != b->vertex[i]->size) {
            printf("Вершина %d: размеры не совпадают: %d vs %d\n", i,
                   a->vertex[i]->size, b->vertex[i]->size);
            return 0;
        }

        for (int j = 0; j < a->vertex[i]->size; j++) {
            if (a->vertex[i]->list[j] != b->vertex[i]->list[j]) {
                printf("Вершина %d: значения не совпадают: %d vs %d\n", i,
                       a->vertex[i]->list[j], b->vertex[i]->list[j]);
                return 0;
            }
        }
    }
    return 1;
}

// Тест 1: Полный цикл преобразований
void test_full_cycle() {
    printf("\n=== Тест 1: Полный цикл преобразований ===\n");

    // Создаём исходный список смежности
    adjacency_list original;
    create_adj_list(&original, 5, 5);

    // Добавляем рёбра: 1-2, 1-3, 2-4, 3-4
    push_back_vec(original.vertex[1], 2);
    push_back_vec(original.vertex[1], 3);
    push_back_vec(original.vertex[2], 4);
    push_back_vec(original.vertex[3], 4);
    push_back_vec(original.vertex[2], 5);

    printf("Исходный список смежности:\n");
    print_adj_list(&original);

    // Преобразуем в список рёбер
    list_of_edges edges;
    create_list_edge(&edges, 0, 0);
    convert_adj_list_to_list_edg(&original, &edges);
    printf("\nСписок рёбер:\n");
    print_list_edge(&edges);

    // Преобразуем в матрицу инцидентности
    incidence_matrix inc;
    create_inc_matrix(&inc, 0, 0);
    convert_list_edg_to_incidence_mat(&edges, &inc);
    printf("\nМатрица инцидентности:\n");
    print_inc_matrix(&inc);

    // Преобразуем в матрицу смежности
    adjacency_matrix adj_mat;
    create_adj_matrix(&adj_mat, 0, 0);
    convert_incidence_mat_to_adj_mat(&inc, &adj_mat);
    printf("\nМатрица смежности:\n");
    print_adj_matrix(&adj_mat);

    // Преобразуем обратно в список смежности
    adjacency_list result;
    create_adj_list(&result, 0, 0);
    convert_adj_mat_to_adj_list(&adj_mat, &result);
    printf("\nРезультирующий список смежности:\n");
    print_adj_list(&result);

    // Проверяем, что результат совпадает с исходным
    if (compare_adj_lists(&original, &result)) {
        printf("\n✓ ТЕСТ ПРОЙДЕН: результат совпадает с исходным!\n");
    } else {
        printf("\n✗ ТЕСТ НЕ ПРОЙДЕН: результат не совпадает с исходным!\n");
    }

    // Очищаем память
    delete_adj_list(&original);
    delete_list_edge(&edges);
    delete_inc_matrix(&inc);
    delete_adj_matrix(&adj_mat);
    delete_adj_list(&result);
}

// Тест 2: Преобразование списка рёбер в матрицу инцидентности
void test_edges_to_incidence() {
    printf("\n=== Тест 2: Список рёбер -> Матрица инцидентности ===\n");

    // Создаём список рёбер
    list_of_edges edges;
    create_list_edge(&edges, 3, 3);
    edges.edges[1].v = 1;
    edges.edges[1].w = 2;
    edges.edges[2].v = 1;
    edges.edges[2].w = 3;
    edges.edges[3].v = 2;
    edges.edges[3].w = 3;

    printf("Список рёбер:\n");
    print_list_edge(&edges);

    // Преобразуем в матрицу инцидентности
    incidence_matrix inc;
    convert_list_edg_to_incidence_mat(&edges, &inc);

    printf("\nПолученная матрица инцидентности:\n");
    print_inc_matrix(&inc);

    printf("\nОжидаемая матрица инцидентности:\n");
    printf("  Р1 Р2 Р3\n");
    printf("1: 1  1  0\n");
    printf("2: -1 0  1\n");
    printf("3: 0  -1 -1\n");

    delete_list_edge(&edges);
    delete_inc_matrix(&inc);
}

// Тест 3: Преобразование матрицы смежности в список смежности
void test_adj_matrix_to_adj_list() {
    printf("\n=== Тест 3: Матрица смежности -> Список смежности ===\n");

    // Создаём матрицу смежности
    adjacency_matrix adj_mat;
    create_adj_matrix(&adj_mat, 3, 3);
    adj_mat.matrix[1][2] = 1;
    adj_mat.matrix[1][3] = 1;
    adj_mat.matrix[2][3] = 1;

    printf("Исходная матрица смежности:\n");
    print_adj_matrix(&adj_mat);

    // Преобразуем в список смежности
    adjacency_list adj_list;
    convert_adj_mat_to_adj_list(&adj_mat, &adj_list);

    printf("\nПолученный список смежности:\n");
    print_adj_list(&adj_list);

    printf("\nОжидаемый список смежности:\n");
    printf("1: 2 3\n");
    printf("2: 3\n");
    printf("3: \n");

    delete_adj_matrix(&adj_mat);
    delete_adj_list(&adj_list);
}

int main() {
    printf("========================================\n");
    printf("    ЗАПУСК ТЕСТОВ ПРЕОБРАЗОВАНИЙ\n");
    printf("========================================\n");

    test_full_cycle();
    test_edges_to_incidence();
    test_adj_matrix_to_adj_list();

    printf("\n========================================\n");
    printf("    ТЕСТЫ ЗАВЕРШЕНЫ\n");
    printf("========================================\n");

    return 0;
}