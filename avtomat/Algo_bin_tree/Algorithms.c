#include "Algorithms.h"

#include <stdio.h>

#include "queue.h"
#include "steck.h"
#include "tree.h"

/*****************************************************************************
 * File:         Algorithms.c
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

void dfs(tree* tr) {
    steck* st = NULL;
    if (tr != NULL) {
        st = add_to_steck(st, tr);
        while (st != NULL) {
            if (st->key != NULL) {
                tree* now_tree = st->key;
                int x = now_tree->key;
                printf("%d ", x);
                st = erase_from_steck(st);
                st = add_to_steck(st, now_tree->right);
                st = add_to_steck(st, now_tree->left);
            } else {
                st = erase_from_steck(st);
            }
        }
    }
}

void bfs(tree* tr) {
    queue* que = create_queue();
    if (tr != NULL) {
        add_to_queue(que, tr);
        while (que->start != NULL) {
            tree* now_tree = que->start->key;
            int x = now_tree->key;
            printf("%d ", x);
            erase_from_queue(que);
            if (now_tree->left != NULL)
                add_to_queue(que, now_tree->left);
            if (now_tree->right != NULL)
                add_to_queue(que, now_tree->right);
        }
    }
}