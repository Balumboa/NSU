#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

// Вспомогательная функция для проверки высоты
int is_balanced(Node *node) {
    if (node == NULL)
        return 1;

    int left_h = height(node->left);
    int right_h = height(node->right);
    int balance_factor = left_h - right_h;

    // Проверка фактора баланса
    if (balance_factor < -1 || balance_factor > 1)
        return 0;

    // Проверка корректности высоты
    int expected_h = max(left_h, right_h) + 1;
    if (node->h != expected_h)
        return 0;

    // Рекурсивная проверка поддеревьев
    return is_balanced(node->left) && is_balanced(node->right);
}

// Проверка BST свойства
int is_bst(Node *node, int min, int max) {
    if (node == NULL)
        return 1;

    if (node->key < min || node->key > max)
        return 0;

    return is_bst(node->left, min, node->key - 1) &&
           is_bst(node->right, node->key + 1, max);
}

// Подсчет количества узлов
int count_nodes(Node *node) {
    if (node == NULL)
        return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

// Поиск узла
Node *find_node(Node *node, int key) {
    if (node == NULL)
        return NULL;
    if (key == node->key)
        return node;
    if (key < node->key)
        return find_node(node->left, key);
    return find_node(node->right, key);
}

// Тест 1: Создание дерева и добавление одного узла
void test_create_and_single_node() {
    printf("\n========== Тест 1: Создание и один узел ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 10);

    printf("Дерево с одним узлом:\n");
    print_avl_tree(tree, 0);

    assert(tree != NULL);
    assert(tree->key == 10);
    assert(tree->left == NULL);
    assert(tree->right == NULL);
    assert(tree->h == 1);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 1 пройден\n");
}

// Тест 2: Добавление элементов с балансировкой (правый поворот)
void test_right_rotation() {
    printf("\n========== Тест 2: Правый поворот ==========\n");
    Node *tree = NULL;

    // Добавляем элементы, которые вызовут правый поворот
    tree = AddNode(tree, 30);
    tree = AddNode(tree, 20);
    tree = AddNode(tree, 10);

    printf("Дерево после добавления 30, 20, 10:\n");
    print_avl_tree(tree, 0);

    // Корнем должен стать 20
    assert(tree->key == 20);
    assert(tree->left->key == 10);
    assert(tree->right->key == 30);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 2 пройден\n");
}

// Тест 3: Добавление элементов с балансировкой (левый поворот)
void test_left_rotation() {
    printf("\n========== Тест 3: Левый поворот ==========\n");
    Node *tree = NULL;

    // Добавляем элементы, которые вызовут левый поворот
    tree = AddNode(tree, 10);
    tree = AddNode(tree, 20);
    tree = AddNode(tree, 30);

    printf("Дерево после добавления 10, 20, 30:\n");
    print_avl_tree(tree, 0);

    // Корнем должен стать 20
    assert(tree->key == 20);
    assert(tree->left->key == 10);
    assert(tree->right->key == 30);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 3 пройден\n");
}

// Тест 4: Сложная балансировка (левый-правый поворот)
void test_left_right_rotation() {
    printf("\n========== Тест 4: Левый-правый поворот ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 30);
    tree = AddNode(tree, 10);
    tree = AddNode(tree, 20);

    printf("Дерево после добавления 30, 10, 20:\n");
    print_avl_tree(tree, 0);

    // Корнем должен стать 20
    assert(tree->key == 20);
    assert(tree->left->key == 10);
    assert(tree->right->key == 30);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 4 пройден\n");
}

// Тест 5: Сложная балансировка (правый-левый поворот)
void test_right_left_rotation() {
    printf("\n========== Тест 5: Правый-левый поворот ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 10);
    tree = AddNode(tree, 30);
    tree = AddNode(tree, 20);

    printf("Дерево после добавления 10, 30, 20:\n");
    print_avl_tree(tree, 0);

    // Корнем должен стать 20
    assert(tree->key == 20);
    assert(tree->left->key == 10);
    assert(tree->right->key == 30);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 5 пройден\n");
}

// Тест 6: Добавление множества элементов
void test_multiple_insertions() {
    printf("\n========== Тест 6: Множественные вставки ==========\n");
    Node *tree = NULL;

    int keys[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        tree = AddNode(tree, keys[i]);
    }

    printf("Дерево после добавления 15 элементов:\n");
    print_avl_tree(tree, 0);

    assert(is_bst(tree, -1000, 1000));
    assert(is_balanced(tree));
    assert(count_nodes(tree) == n);

    delete_avl_tree(&tree);
    printf("✓ Тест 6 пройден\n");
}

// Тест 7: Удаление листового узла
void test_delete_leaf() {
    printf("\n========== Тест 7: Удаление листового узла ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 20);
    tree = AddNode(tree, 10);
    tree = AddNode(tree, 30);

    printf("Исходное дерево:\n");
    print_avl_tree(tree, 0);

    tree = erase(tree, 10);

    printf("После удаления 10:\n");
    print_avl_tree(tree, 0);

    assert(find_node(tree, 10) == NULL);
    assert(count_nodes(tree) == 2);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 7 пройден\n");
}

// Тест 8: Удаление узла с одним ребенком
void test_delete_node_with_one_child() {
    printf("\n========== Тест 8: Удаление узла с одним ребенком ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 20);
    tree = AddNode(tree, 10);
    tree = AddNode(tree, 5);

    printf("Исходное дерево:\n");
    print_avl_tree(tree, 0);

    tree = erase(tree, 10);

    printf("После удаления 10:\n");
    print_avl_tree(tree, 0);

    assert(find_node(tree, 10) == NULL);
    assert(find_node(tree, 5) != NULL);
    assert(find_node(tree, 20) != NULL);
    assert(count_nodes(tree) == 2);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 8 пройден\n");
}

// Тест 9: Удаление узла с двумя детьми
void test_delete_node_with_two_children() {
    printf("\n========== Тест 9: Удаление узла с двумя детьми ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 20);
    tree = AddNode(tree, 10);
    tree = AddNode(tree, 30);
    tree = AddNode(tree, 25);
    tree = AddNode(tree, 35);

    printf("Исходное дерево:\n");
    print_avl_tree(tree, 0);

    tree = erase(tree, 30);

    printf("После удаления 30:\n");
    print_avl_tree(tree, 0);

    assert(find_node(tree, 30) == NULL);
    assert(find_node(tree, 25) != NULL);
    assert(find_node(tree, 35) != NULL);
    assert(count_nodes(tree) == 4);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 9 пройден\n");
}

// Тест 10: Удаление корня
void test_delete_root() {
    printf("\n========== Тест 10: Удаление корня ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 20);
    tree = AddNode(tree, 10);
    tree = AddNode(tree, 30);

    printf("Исходное дерево:\n");
    print_avl_tree(tree, 0);

    tree = erase(tree, 20);

    printf("После удаления корня 20:\n");
    print_avl_tree(tree, 0);

    assert(find_node(tree, 20) == NULL);
    assert(count_nodes(tree) == 2);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 10 пройден\n");
}

// Тест 11: Удаление несуществующего элемента
void test_delete_nonexistent() {
    printf(
        "\n========== Тест 11: Удаление несуществующего элемента ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 10);
    tree = AddNode(tree, 20);

    printf("Исходное дерево:\n");
    print_avl_tree(tree, 0);

    int old_count = count_nodes(tree);
    tree = erase(tree, 999);

    printf("После попытки удаления 999 (дерево не изменилось):\n");
    print_avl_tree(tree, 0);

    assert(count_nodes(tree) == old_count);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 11 пройден\n");
}

// Тест 12: Краевой случай - пустое дерево
void test_empty_tree() {
    printf("\n========== Тест 12: Пустое дерево ==========\n");
    Node *tree = NULL;

    printf("Пустое дерево:\n");
    print_avl_tree(tree, 0);

    assert(tree == NULL);
    assert(count_nodes(tree) == 0);

    // Попытка удалить из пустого дерева
    tree = erase(tree, 10);
    assert(tree == NULL);

    printf("✓ Тест 12 пройден\n");
}

// Тест 13: Добавление дубликатов
void test_duplicate_keys() {
    printf("\n========== Тест 13: Добавление дубликатов ==========\n");
    Node *tree = NULL;

    tree = AddNode(tree, 10);
    tree = AddNode(tree, 10);  // Дубликат
    tree = AddNode(tree, 10);  // Еще один дубликат

    printf("После добавления дубликатов 10:\n");
    print_avl_tree(tree, 0);

    // Должен быть только один узел
    assert(count_nodes(tree) == 1);
    assert(tree->key == 10);
    assert(is_balanced(tree));

    delete_avl_tree(&tree);
    printf("✓ Тест 13 пройден\n");
}

// Тест 14: Добавление в обратном порядке
void test_reverse_order() {
    printf("\n========== Тест 14: Добавление в обратном порядке ==========\n");
    Node *tree = NULL;

    for (int i = 10; i >= 1; i--) {
        tree = AddNode(tree, i);
    }

    printf("Дерево после добавления 10,9,8,...,1:\n");
    print_avl_tree(tree, 0);

    assert(is_bst(tree, -1000, 1000));
    assert(is_balanced(tree));
    assert(count_nodes(tree) == 10);

    delete_avl_tree(&tree);
    printf("✓ Тест 14 пройден\n");
}

// Тест 15: Чередование вставок и удалений
void test_mixed_operations() {
    printf("\n========== Тест 15: Чередование вставок и удалений ==========\n");
    Node *tree = NULL;

    // Вставка
    tree = AddNode(tree, 50);
    tree = AddNode(tree, 30);
    tree = AddNode(tree, 70);
    tree = AddNode(tree, 20);
    tree = AddNode(tree, 40);

    printf("После вставок:\n");
    print_avl_tree(tree, 0);

    // Удаление
    tree = erase(tree, 30);
    printf("После удаления 30:\n");
    print_avl_tree(tree, 0);

    // Снова вставка
    tree = AddNode(tree, 35);
    printf("После добавления 35:\n");
    print_avl_tree(tree, 0);

    assert(is_balanced(tree));
    assert(is_bst(tree, -1000, 1000));

    delete_avl_tree(&tree);
    printf("✓ Тест 15 пройден\n");
}

int main() {
    printf("========================================\n");
    printf("     ТЕСТИРОВАНИЕ AVL ДЕРЕВА\n");
    printf("========================================\n");

    test_create_and_single_node();
    test_right_rotation();
    test_left_rotation();
    test_left_right_rotation();
    test_right_left_rotation();
    test_multiple_insertions();
    test_delete_leaf();
    test_delete_node_with_one_child();
    test_delete_node_with_two_children();
    test_delete_root();
    test_delete_nonexistent();
    test_empty_tree();
    test_duplicate_keys();
    test_reverse_order();
    test_mixed_operations();

    printf("\n========================================\n");
    printf("     ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n");
    printf("========================================\n");

    return 0;
}