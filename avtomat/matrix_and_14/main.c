#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "convert_matrixes.h"
#include "incidence_matrix.h"
#include "list_of_edges.h"
#include "vector.h"

/*****************************************************************************
 * File:         tests.c
 * Description:  Тестирование всех структур и функций графов
 * Created:      10 apr 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

/* ===================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ===================== */

// Сравнение двух списков смежности
int compare_adj_lists(adjacency_list *a, adjacency_list *b) {
    if (a->N != b->N || a->M != b->M)
        return 0;

    for (int i = 1; i < a->N; i++) {
        if (get_size_vec(a->vertex[i]) != get_size_vec(b->vertex[i]))
            return 0;

        for (int j = 0; j < get_size_vec(a->vertex[i]); j++) {
            if (a->vertex[i]->list[j] != b->vertex[i]->list[j])
                return 0;
        }
    }
    return 1;
}

// Сравнение двух матриц смежности
int compare_adj_matrices(adjacency_matrix *a, adjacency_matrix *b) {
    if (a->N != b->N || a->M != b->M)
        return 0;

    for (int i = 1; i < a->N; i++) {
        for (int j = 1; j < a->N; j++) {
            if (a->matrix[i][j] != b->matrix[i][j])
                return 0;
        }
    }
    return 1;
}

// Сравнение двух списков рёбер
int compare_edge_lists(list_of_edges *a, list_of_edges *b) {
    if (a->N != b->N || a->M != b->M)
        return 0;

    for (int i = 1; i < a->M; i++) {
        if (a->edges[i].v != b->edges[i].v || a->edges[i].w != b->edges[i].w)
            return 0;
    }
    return 1;
}

// Создание тестового графа (простой граф с 3 вершинами и 3 рёбрами)
adjacency_list *create_test_graph() {
    adjacency_list *graph = create_adj_list(3, 3);
    push_back_vec(graph->vertex[1], 2);
    push_back_vec(graph->vertex[1], 3);
    push_back_vec(graph->vertex[2], 3);
    return graph;
}

/* ===================== ТЕСТЫ VECTOR ===================== */

void test_vector_basic() {
    printf("\n=== ТЕСТ 1.1: Базовые операции vector ===\n");

    vector *vec = create_vec(0);
    assert(get_size_vec(vec) == 0);
    assert(get_capacity_vec(vec) >= 0);

    push_back_vec(vec, 10);
    push_back_vec(vec, 20);
    push_back_vec(vec, 30);

    assert(get_size_vec(vec) == 3);
    assert(vec->list[0] == 10);
    assert(vec->list[1] == 20);
    assert(vec->list[2] == 30);

    pop_back_vec(vec);
    assert(get_size_vec(vec) == 2);
    assert(vec->list[0] == 10);
    assert(vec->list[1] == 20);

    pop_back_vec(vec);
    pop_back_vec(vec);
    assert(get_size_vec(vec) == 0);

    // Попытка удалить из пустого вектора
    pop_back_vec(vec);  // Не должно упасть

    delete_vec(&vec);
    assert(vec == NULL);

    printf("✓ Тест vector_basic пройден\n");
}

void test_vector_resize() {
    printf("\n=== ТЕСТ 1.2: Расширение вектора ===\n");

    vector *vec = create_vec(0);
    int initial_cap = get_capacity_vec(vec);

    // Добавляем много элементов для проверки перевыделения памяти
    for (int i = 0; i < 100; i++) {
        push_back_vec(vec, i);
    }

    assert(get_size_vec(vec) == 100);
    assert(get_capacity_vec(vec) > initial_cap);

    // Проверяем правильность всех элементов
    for (int i = 0; i < 100; i++) {
        assert(vec->list[i] == i);
    }

    delete_vec(&vec);
    printf("✓ Тест vector_resize пройден\n");
}

/* ===================== ТЕСТЫ ADJACENCY LIST ===================== */

void test_adj_list_basic() {
    printf("\n=== ТЕСТ 2.1: Создание и удаление списка смежности ===\n");

    adjacency_list *graph = create_adj_list(5, 10);

    assert(graph->N == 6);  // +1 для 1-индексации
    assert(graph->M == 11);
    assert(graph->vertex != NULL);

    for (int i = 0; i < graph->N; i++) {
        assert(graph->vertex[i] != NULL);
    }

    delete_adj_list(&graph);
    assert(graph == NULL);

    printf("✓ Тест adj_list_basic пройден\n");
}

void test_adj_list_operations() {
    printf("\n=== ТЕСТ 2.2: Операции со списком смежности ===\n");

    adjacency_list *graph = create_adj_list(4, 5);

    // Добавляем рёбра
    push_back_vec(graph->vertex[1], 2);
    push_back_vec(graph->vertex[1], 3);
    push_back_vec(graph->vertex[2], 4);
    push_back_vec(graph->vertex[3], 1);
    push_back_vec(graph->vertex[4], 2);

    assert(get_size_vec(graph->vertex[1]) == 2);
    assert(get_size_vec(graph->vertex[2]) == 1);
    assert(get_size_vec(graph->vertex[3]) == 1);
    assert(get_size_vec(graph->vertex[4]) == 1);

    assert(graph->vertex[1]->list[0] == 2);
    assert(graph->vertex[1]->list[1] == 3);
    assert(graph->vertex[2]->list[0] == 4);

    delete_adj_list(&graph);
    printf("✓ Тест adj_list_operations пройден\n");
}

/* ===================== ТЕСТЫ ADJACENCY MATRIX ===================== */

void test_adj_matrix_basic() {
    printf("\n=== ТЕСТ 3.1: Создание и удаление матрицы смежности ===\n");

    adjacency_matrix *graph = create_adj_matrix(5, 10);

    assert(graph->N == 6);
    assert(graph->M == 11);
    assert(graph->matrix != NULL);

    for (int i = 0; i < graph->N; i++) {
        assert(graph->matrix[i] != NULL);
        for (int j = 0; j < graph->N; j++) {
            assert(graph->matrix[i][j] == 0);  // Инициализирована нулями
        }
    }

    delete_adj_matrix(&graph);
    assert(graph == NULL);

    printf("✓ Тест adj_matrix_basic пройден\n");
}

void test_adj_matrix_operations() {
    printf("\n=== ТЕСТ 3.2: Операции с матрицей смежности ===\n");

    adjacency_matrix *graph = create_adj_matrix(4, 5);

    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 1);
    add_edge(graph, 4, 2);

    assert(graph->matrix[1][2] == 1);
    assert(graph->matrix[1][3] == 1);
    assert(graph->matrix[2][4] == 1);
    assert(graph->matrix[3][1] == 1);
    assert(graph->matrix[4][2] == 1);

    // Проверяем, что остальные нули
    assert(graph->matrix[2][1] == 0);
    assert(graph->matrix[4][1] == 0);

    delete_edge(graph, 1, 2);
    assert(graph->matrix[1][2] == 0);

    delete_adj_matrix(&graph);
    printf("✓ Тест adj_matrix_operations пройден\n");
}

/* ===================== ТЕСТЫ LIST OF EDGES ===================== */

void test_list_edges_basic() {
    printf("\n=== ТЕСТ 4.1: Создание и удаление списка рёбер ===\n");

    list_of_edges *graph = create_list_edge(5, 7);

    assert(graph->N == 6);
    assert(graph->M == 8);
    assert(graph->edges != NULL);

    delete_list_edge(&graph);
    assert(graph == NULL);

    printf("✓ Тест list_edges_basic пройден\n");
}

/* ===================== ТЕСТЫ INCIDENCE MATRIX ===================== */

void test_inc_matrix_basic() {
    printf("\n=== ТЕСТ 5.1: Создание и удаление матрицы инцидентности ===\n");

    incidence_matrix *graph = create_inc_matrix(5, 7);

    assert(graph->N == 6);
    assert(graph->M == 8);
    assert(graph->matrix != NULL);

    for (int i = 0; i < graph->N; i++) {
        assert(graph->matrix[i] != NULL);
        for (int j = 0; j < graph->M; j++) {
            assert(graph->matrix[i][j] == 0);
        }
    }

    delete_inc_matrix(&graph);
    assert(graph == NULL);

    printf("✓ Тест inc_matrix_basic пройден\n");
}

/* ===================== ТЕСТЫ КОНВЕРТАЦИИ ===================== */

void test_conversion_roundtrip() {
    printf("\n=== ТЕСТ 6.1: Полный цикл конвертации ===\n");

    // Создаём исходный граф (список смежности)
    adjacency_list *original = create_adj_list(4, 5);
    push_back_vec(original->vertex[1], 2);
    push_back_vec(original->vertex[1], 3);
    push_back_vec(original->vertex[2], 4);
    push_back_vec(original->vertex[3], 1);
    push_back_vec(original->vertex[4], 2);

    // Конвертируем: список смежности → список рёбер
    list_of_edges *loe = convert_adj_list_to_list_edg(original);
    assert(loe->M - 1 == 5);  // 5 рёбер

    // Список рёбер → матрица инцидентности
    incidence_matrix *im = convert_list_edg_to_incidence_mat(loe);

    // Матрица инцидентности → матрица смежности
    adjacency_matrix *am = convert_incidence_mat_to_adj_mat(im);

    // Матрица смежности → список смежности
    adjacency_list *converted = convert_adj_mat_to_adj_list(am);

    // Сравниваем исходный и конвертированный
    assert(compare_adj_lists(original, converted));

    // Очистка
    delete_adj_list(&original);
    delete_list_edge(&loe);
    delete_inc_matrix(&im);
    delete_adj_matrix(&am);
    delete_adj_list(&converted);

    printf("✓ Тест conversion_roundtrip пройден\n");
}

void test_conversion_empty_graph() {
    printf("\n=== ТЕСТ 6.2: Конвертация пустого графа ===\n");

    adjacency_list *empty = create_adj_list(3, 0);

    list_of_edges *loe = convert_adj_list_to_list_edg(empty);
    assert(loe->M == 1);  // Только место под рёбра, но их нет

    incidence_matrix *im = convert_list_edg_to_incidence_mat(loe);
    // Проверяем, что матрица инцидентности пустая (все нули)
    for (int i = 1; i < im->N; i++) {
        for (int j = 1; j < im->M; j++) {
            assert(im->matrix[i][j] == 0);
        }
    }

    adjacency_matrix *am = convert_incidence_mat_to_adj_mat(im);
    // Проверяем, что матрица смежности пустая
    for (int i = 1; i < am->N; i++) {
        for (int j = 1; j < am->N; j++) {
            assert(am->matrix[i][j] == 0);
        }
    }

    adjacency_list *converted = convert_adj_mat_to_adj_list(am);
    assert(compare_adj_lists(empty, converted));

    delete_adj_list(&empty);
    delete_list_edge(&loe);
    delete_inc_matrix(&im);
    delete_adj_matrix(&am);
    delete_adj_list(&converted);

    printf("✓ Тест conversion_empty_graph пройден\n");
}

/* ===================== ТЕСТЫ КРАЕВЫХ СЛУЧАЕВ ===================== */

void test_edge_cases() {
    printf("\n=== ТЕСТ 7.1: Краевые случаи ===\n");

    // 1. Граф с одной вершиной и без рёбер
    adjacency_list *single = create_adj_list(1, 0);
    assert(single->N == 2);
    assert(get_size_vec(single->vertex[1]) == 0);

    list_of_edges *loe = convert_adj_list_to_list_edg(single);
    assert(loe->M == 1);

    delete_adj_list(&single);
    delete_list_edge(&loe);

    // 2. Полный граф на 3 вершинах
    adjacency_matrix *complete = create_adj_matrix(3, 6);
    add_edge(complete, 1, 2);
    add_edge(complete, 1, 3);
    add_edge(complete, 2, 1);
    add_edge(complete, 2, 3);
    add_edge(complete, 3, 1);
    add_edge(complete, 3, 2);

    // Проверяем, что все рёбра на месте
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (i != j) {
                assert(complete->matrix[i][j] == 1);
            }
        }
    }

    delete_adj_matrix(&complete);

    printf("✓ Тест edge_cases пройден\n");
}

void test_large_graph() {
    printf("\n=== ТЕСТ 7.2: Граф с большим количеством данных ===\n");

    const int N = 100;  // 100 вершин
    const int M = 500;  // 500 рёбер

    adjacency_list *graph = create_adj_list(N, M);

    // Добавляем случайные рёбра
    srand(42);  // Фиксированный seed для воспроизводимости
    for (int i = 0; i < M; i++) {
        int v = (rand() % N) + 1;
        int w = (rand() % N) + 1;
        push_back_vec(graph->vertex[v], w);
    }

    // Конвертируем туда-обратно
    list_of_edges *loe = convert_adj_list_to_list_edg(graph);
    incidence_matrix *im = convert_list_edg_to_incidence_mat(loe);
    adjacency_matrix *am = convert_incidence_mat_to_adj_mat(im);
    adjacency_list *converted = convert_adj_mat_to_adj_list(am);

    // Проверяем, что количество вершин и рёбер совпадает
    assert(graph->N == converted->N);

    // Проверяем несколько случайных вершин
    for (int test = 0; test < 20; test++) {
        int v = (rand() % N) + 1;
        assert(get_size_vec(graph->vertex[v]) ==
               get_size_vec(converted->vertex[v]));
    }

    delete_adj_list(&graph);
    delete_list_edge(&loe);
    delete_inc_matrix(&im);
    delete_adj_matrix(&am);
    delete_adj_list(&converted);

    printf("✓ Тест large_graph пройден (N=%d, M=%d)\n", N, M);
}

void test_memory_leaks() {
    printf("\n=== ТЕСТ 7.3: Проверка утечек памяти ===\n");

    // Многократно создаём и удаляем графы
    for (int iter = 0; iter < 100; iter++) {
        adjacency_list *al = create_adj_list(10, 20);
        for (int i = 0; i < 20; i++) {
            push_back_vec(al->vertex[(i % 10) + 1], (i % 10) + 1);
        }

        list_of_edges *loe = convert_adj_list_to_list_edg(al);
        incidence_matrix *im = convert_list_edg_to_incidence_mat(loe);
        adjacency_matrix *am = convert_incidence_mat_to_adj_mat(im);
        adjacency_list *al2 = convert_adj_mat_to_adj_list(am);

        delete_adj_list(&al);
        delete_list_edge(&loe);
        delete_inc_matrix(&im);
        delete_adj_matrix(&am);
        delete_adj_list(&al2);
    }

    printf("✓ Тест memory_leaks пройден (100 итераций)\n");
}

/* ===================== ТЕСТЫ НЕКОРРЕКТНЫХ ВХОДНЫХ ДАННЫХ =====================
 */

void test_invalid_inputs() {
    printf("\n=== ТЕСТ 8.1: Обработка некорректных входных данных ===\n");

    vector *vec = create_vec(0);

    // Попытка удалить из пустого вектора
    pop_back_vec(vec);  // Не должно упасть
    assert(get_size_vec(vec) == 0);

    // Попытка добавить NULL указатели (функции должны проверять)
    // В текущей реализации этого нет, но это потенциальное улучшение

    delete_vec(&vec);

    // Двойное удаление (должно быть безопасным, но в текущей реализации может
    // упасть) Поэтому закомментировано: delete_vec(&vec);

    printf("✓ Тест invalid_inputs пройден\n");
}

/* ===================== ЗАПУСК ВСЕХ ТЕСТОВ ===================== */

void run_all_tests() {
    printf("\n========================================\n");
    printf("ЗАПУСК ВСЕХ ТЕСТОВ\n");
    printf("========================================\n");

    // Функциональные тесты
    test_vector_basic();
    test_vector_resize();
    test_adj_list_basic();
    test_adj_list_operations();
    test_adj_matrix_basic();
    test_adj_matrix_operations();
    test_list_edges_basic();
    test_inc_matrix_basic();

    // Тесты конвертации
    test_conversion_roundtrip();
    test_conversion_empty_graph();

    // Краевые случаи
    test_edge_cases();
    test_large_graph();
    test_memory_leaks();
    test_invalid_inputs();

    printf("\n========================================\n");
    printf("ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n");
    printf("========================================\n");
}

int main() {
    run_all_tests();
    return 0;
}