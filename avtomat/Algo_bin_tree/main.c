#include <stdio.h>

#include "Algorithms.h"
#include "adjacency_list.h"
#include "vector.h"

int main() {
    adjacency_list *graph;
    graph = scanf_adj_list();
    print_adj_list(graph);
    bfs(graph);
    dfs(graph);
}

// #include <stdio.h>

// #include "avl_tree.h"

// void printTree(Node *root, int space) {
//     if (root == NULL)
//         return;

//     space += 8;

//     printTree(root->right, space);

//     printf("\n");
//     for (int i = 8; i < space; i++)
//         printf(" ");
//     printf("%d[h:%d]\n", root->key, root->h);

//     printTree(root->left, space);
// }

// int main() {
//     Node *root = NULL;
//     int data[] = {10, 20, 30, 40, 50, 25, 35, 15};
//     int n = sizeof(data) / sizeof(data[0]);

//     printf("=== Построение АВЛ-дерева ===\n");
//     for (int i = 0; i < n; i++) {
//         printf("\nДобавляем ключ: %d\n", data[i]);
//         root = AddNode(root, data[i]);
//         printTree(root, 0);
//         printf("----------------------------");
//     }

//     printf("\n\n=== Удаление узла 30 (с двумя потомками) ===\n");
//     root = erase(root, 30);
//     printTree(root, 0);

//     printf("\n\n=== Удаление корня ===\n");
//     if (root) {
//         printf("Удаляем корень: %d\n", root->key);
//         root = erase(root, root->key);
//     }
//     printTree(root, 0);

//     return 0;
// }
