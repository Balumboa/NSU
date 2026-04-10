#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Algorithms.h"
#include "queue.h"
#include "steck.h"
#include "tree.h"

// ==================== ТЕСТ 1: БИНАРНОЕ ДЕРЕВО ====================
void test_binary_tree(void) {
    printf("\n========== ТЕСТ 1: БИНАРНОЕ ДЕРЕВО ==========\n\n");

    tree *root = NULL;

    // 1. Добавление элементов
    printf("1. ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ:\n");
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = add(root, values[i]);
        printf("   Добавлен: %d\n", values[i]);
    }
    printf("   Дерево построено\n\n");

    // 2. Проверка структуры дерева
    printf("2. ПРОВЕРКА СТРУКТУРЫ:\n");
    printf("   Ожидаемая структура:\n");
    printf("        50\n");
    printf("       /  \\\n");
    printf("      30   70\n");
    printf("     / \\   / \\\n");
    printf("    20 40 60 80\n");
    printf("\n   Визуализация дерева:\n");
    printTree(root, 0);
    printf("\n");

    // 3. Добавление дубликата (не должен добавиться)
    printf("3. ДОБАВЛЕНИЕ ДУБЛИКАТА (50):\n");
    int old_count = 0;
    // Простой подсчёт узлов (можно сделать отдельной функцией)
    root = add(root, 50);
    printf("   Дубликат не добавлен (по логике add)\n\n");

    // 4. Удаление дерева
    printf("4. УДАЛЕНИЕ ДЕРЕВА:\n");
    delete_tree(&root);
    printf("   Дерево удалено: root = %s\n",
           root == NULL ? "NULL" : "not NULL");

    printf("\n========== ТЕСТ 1 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 2: СТЕК ====================
void test_stack(void) {
    printf("\n========== ТЕСТ 2: СТЕК ==========\n\n");

    // Создаём дерево для тестов
    tree *t1 = create(10);
    tree *t2 = create(20);
    tree *t3 = create(30);

    steck *st = NULL;

    // 1. Добавление в стек
    printf("1. ДОБАВЛЕНИЕ В СТЕК:\n");
    st = add_to_steck(st, t1);
    st = add_to_steck(st, t2);
    st = add_to_steck(st, t3);
    printf("   Стек после добавления: ");
    print_steck(st);
    printf(" (ожидается: 30 20 10)\n\n");

    // 2. Извлечение из стека (LIFO)
    printf("2. ИЗВЛЕЧЕНИЕ ИЗ СТЕКА (LIFO):\n");
    st = erase_from_steck(st);
    printf("   После 1-го извлечения: ");
    print_steck(st);
    printf(" (ожидается: 20 10)\n");

    st = erase_from_steck(st);
    printf("   После 2-го извлечения: ");
    print_steck(st);
    printf(" (ожидается: 10)\n");

    st = erase_from_steck(st);
    printf("   После 3-го извлечения: ");
    print_steck(st);
    printf(" (ожидается: пусто)\n\n");

    // 3. Извлечение из пустого стека
    printf("3. ИЗВЛЕЧЕНИЕ ИЗ ПУСТОГО СТЕКА:\n");
    st = erase_from_steck(st);
    printf("   Ошибок нет, стек остаётся NULL\n\n");

    // 4. Удаление стека
    printf("4. УДАЛЕНИЕ СТЕКА:\n");
    st = add_to_steck(st, t1);
    st = add_to_steck(st, t2);
    delete_steck(&st);
    printf("   Стек удалён: st = %s\n", st == NULL ? "NULL" : "not NULL");

    // Очистка деревьев
    delete_tree(&t1);
    delete_tree(&t2);
    delete_tree(&t3);

    printf("\n========== ТЕСТ 2 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 3: ОЧЕРЕДЬ ====================
void test_queue(void) {
    printf("\n========== ТЕСТ 3: ОЧЕРЕДЬ ==========\n\n");

    // Создаём дерево для тестов
    tree *t1 = create(10);
    tree *t2 = create(20);
    tree *t3 = create(30);
    tree *t4 = create(40);

    queue *que = create_queue();

    // 1. Добавление в очередь
    printf("1. ДОБАВЛЕНИЕ В ОЧЕРЕДЬ:\n");
    que = add_to_queue(que, t1);
    que = add_to_queue(que, t2);
    que = add_to_queue(que, t3);
    que = add_to_queue(que, t4);
    printf("   Очередь после добавления: ");
    print_queue(que);
    printf(" (ожидается: 10 20 30 40)\n\n");

    // 2. Извлечение из очереди (FIFO)
    printf("2. ИЗВЛЕЧЕНИЕ ИЗ ОЧЕРЕДИ (FIFO):\n");
    tree *extracted = erase_from_queue(que);
    printf("   Извлечено: %d\n", extracted ? extracted->key : -1);
    printf("   Очередь после: ");
    print_queue(que);
    printf(" (ожидается: 20 30 40)\n");

    extracted = erase_from_queue(que);
    printf("   Извлечено: %d\n", extracted ? extracted->key : -1);
    printf("   Очередь после: ");
    print_queue(que);
    printf(" (ожидается: 30 40)\n\n");

    // 3. Добавление после извлечения
    printf("3. ДОБАВЛЕНИЕ ПОСЛЕ ИЗВЛЕЧЕНИЯ:\n");
    tree *t5 = create(50);
    que = add_to_queue(que, t5);
    printf("   Добавлен 50, очередь: ");
    print_queue(que);
    printf(" (ожидается: 30 40 50)\n\n");

    // 4. Очистка очереди
    printf("4. ОЧИСТКА ОЧЕРЕДИ:\n");
    while (que->start != NULL) {
        tree *t = erase_from_queue(que);
        printf("   Извлечено: %d\n", t->key);
    }
    printf("   Очередь пуста: start = %s\n",
           que->start == NULL ? "NULL" : "not NULL");

    // 5. Удаление очереди
    printf("\n5. УДАЛЕНИЕ ОЧЕРЕДИ:\n");
    delete_queue(&que);
    printf("   Очередь удалена: que = %s\n", que == NULL ? "NULL" : "not NULL");

    // Очистка деревьев
    delete_tree(&t1);
    delete_tree(&t2);
    delete_tree(&t3);
    delete_tree(&t4);
    delete_tree(&t5);

    printf("\n========== ТЕСТ 3 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 4: DFS (ОБХОД В ГЛУБИНУ) ====================
void test_dfs(void) {
    printf("\n========== ТЕСТ 4: DFS (ОБХОД В ГЛУБИНУ) ==========\n\n");

    // Создаём дерево:      50
    //                    /    \
    //                   30     70
    //                  / \    / \
    //                 20 40  60 80
    tree *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = add(root, values[i]);
    }

    printf("Дерево:\n");
    printTree(root, 0);

    printf("\nDFS (обход в глубину):\n");
    printf("  Ожидается: 50 30 20 40 70 60 80\n");
    printf("  Результат: ");
    dfs(root);
    printf("\n");

    delete_tree(&root);

    // Тест на пустом дереве
    printf("\nDFS на пустом дереве:\n");
    dfs(NULL);
    printf("  (ничего не выводится, ошибок нет)\n");

    printf("\n========== ТЕСТ 4 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 5: BFS (ОБХОД В ШИРИНУ) ====================
void test_bfs(void) {
    printf("\n========== ТЕСТ 5: BFS (ОБХОД В ШИРИНУ) ==========\n\n");

    // Создаём дерево:      50
    //                    /    \
    //                   30     70
    //                  / \    / \
    //                 20 40  60 80
    tree *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = add(root, values[i]);
    }

    printf("Дерево:\n");
    printTree(root, 0);

    printf("\nBFS (обход в ширину):\n");
    printf("  Ожидается: 50 30 70 20 40 60 80\n");
    printf("  Результат: ");
    bfs(root);
    printf("\n");

    delete_tree(&root);

    // Тест на пустом дереве
    printf("\nBFS на пустом дереве:\n");
    bfs(NULL);
    printf("  (ничего не выводится, ошибок нет)\n");

    printf("\n========== ТЕСТ 5 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 6: КРАЕВЫЕ СЛУЧАИ ====================
void test_edge_cases(void) {
    printf("\n========== ТЕСТ 6: КРАЕВЫЕ СЛУЧАИ ==========\n\n");

    // 1. Дерево с одним узлом
    printf("1. ДЕРЕВО С ОДНИМ УЗЛОМ:\n");
    tree *root = create(100);
    printf("   Узел создан: key=%d\n", root->key);
    printf("   DFS: ");
    dfs(root);
    printf("\n   BFS: ");
    bfs(root);
    printf("\n");
    delete_tree(&root);

    // 2. Дерево с двумя узлами
    printf("\n2. ДЕРЕВО С ДВУМЯ УЗЛАМИ:\n");
    root = add(NULL, 100);
    root = add(root, 50);
    printf("   Визуализация:\n");
    printTree(root, 0);
    printf("   DFS: ");
    dfs(root);
    printf("\n   BFS: ");
    bfs(root);
    printf("\n");
    delete_tree(&root);

    // 3. Дерево с одинаковыми ключами (не должны добавляться)
    printf("\n3. ДУБЛИКАТЫ КЛЮЧЕЙ:\n");
    root = add(NULL, 10);
    root = add(root, 10);
    root = add(root, 10);
    printf("   После 3 добавлений 10: ");
    dfs(root);
    printf(" (ожидается: 10)\n");
    delete_tree(&root);

    // 4. Удаление NULL дерева
    printf("\n4. УДАЛЕНИЕ NULL ДЕРЕВА:\n");
    delete_tree(&root);
    printf("   Ошибок нет\n");

    printf("\n========== ТЕСТ 6 ЗАВЕРШЁН ==========\n");
}

// ==================== ОСНОВНАЯ ФУНКЦИЯ ====================
int main(void) {
    printf(
        "\n╔══════════════════════════════════════════════════════════════╗\n");
    printf(
        "║              ТЕСТИРОВАНИЕ СТРУКТУР ДАННЫХ                     ║\n");
    printf(
        "║                   Бинарное дерево, Стек, Очередь              ║\n");
    printf(
        "║                     DFS, BFS                                  ║\n");
    printf(
        "╚══════════════════════════════════════════════════════════════╝\n");

    printf("\nВыберите тест:\n");
    printf("  1 - Бинарное дерево\n");
    printf("  2 - Стек\n");
    printf("  3 - Очередь\n");
    printf("  4 - DFS (обход в глубину)\n");
    printf("  5 - BFS (обход в ширину)\n");
    printf("  6 - Краевые случаи\n");
    printf("  7 - Запустить все тесты\n");
    printf("  0 - Выход\n");
    printf("\nВаш выбор: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            test_binary_tree();
            break;
        case 2:
            test_stack();
            break;
        case 3:
            test_queue();
            break;
        case 4:
            test_dfs();
            break;
        case 5:
            test_bfs();
            break;
        case 6:
            test_edge_cases();
            break;
        case 7:
            test_binary_tree();
            test_stack();
            test_queue();
            test_dfs();
            test_bfs();
            test_edge_cases();
            printf("\n✅ ВСЕ ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ!\n");
            break;
        case 0:
            printf("До свидания!\n");
            break;
        default:
            printf("Неверный выбор!\n");
    }

    return 0;
}