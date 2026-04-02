#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    int *list;
} vector;

int get_size_vec(vector *vec) {
    return vec->size;
}

int get_capacity_vec(vector *vec) {
    return vec->capacity;
}

void push_back_vec(vector *vec, int x) {
    int capacity = get_capacity_vec(vec);
    int size = get_size_vec(vec);
    if (size == capacity) {
        vec->capacity = capacity * 2 + 1;
        vec->list = (int *)realloc(vec->list, vec->capacity * sizeof(int));
    }
    vec->list[size] = x;
    vec->size++;
}

void pop_back_vec(vector *vec) {
    if (vec->size == 0)
        return;
    vec->size--;
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

typedef struct {
    int n;
    vector **vertex;
} adjacency_list;

void create(adjacency_list *graph, int n) {
    graph->n = n;
    graph->vertex = (vector **)calloc(n, sizeof(vector *));
    for (int i = 0; i < n; i++) {
        graph->vertex[i] = (vector *)malloc(sizeof(vector));
        create_vec(graph->vertex[i], 0);
    }
}

void delete_matrix(adjacency_list *graph) {
    int n = graph->n;
    for (int i = 0; i < n; i++) {
        delete_vec(graph->vertex[i]);
        free(graph->vertex[i]);
    }
    free(graph->vertex);
    graph->vertex = NULL;
    graph->n = 0;
    // printf("Матрица удалена\n");
}

// void print_matrix(adjacency_list *graph) {
//     int n = graph->n;
//     for (int i = 1; i < n; i++) {
//         printf("%d: ", i);
//         for (int j = 0; j < get_size_vec(graph->vertex[i]); j++) {
//             printf("%d ", graph->vertex[i]->list[j]);
//         }
//         printf("\n");
//     }
// }

void scanf_graph(adjacency_list *graph, int m) {
    for (int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        push_back_vec(graph->vertex[w], v);
        push_back_vec(graph->vertex[v], w);
        // print_matrix(graph);
    }
}

void dfs(int v, vector *used, vector *ans, adjacency_list *graph, int comp) {
    if (used->list[v] == 1) {
        return;
    }

    used->list[v] = 1;
    ans->list[v] = comp;
    for (int i = 0; i < graph->vertex[v]->size; i++) {
        int w = graph->vertex[v]->list[i];
        dfs(w, used, ans, graph, comp);
    }
}

void solve(adjacency_list *graph, vector *ans) {
    int count_comp = 0;
    vector used;

    create_vec(&used, get_size_vec(ans));
    for (int i = 1; i < get_size_vec(ans); i++) {
        if (used.list[i] == 0) {
            count_comp++;
            dfs(i, &used, ans, graph, count_comp);
        }
    }
    printf("%d\n", count_comp);
    for (int i = 1; i < used.size; i++) {
        printf("%d ", ans->list[i]);
    }
    delete_vec(&used);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    adjacency_list graph;
    create(&graph, n + 1);
    scanf_graph(&graph, m);
    vector ans;
    create_vec(&ans, n + 1);
    solve(&graph, &ans);
    delete_matrix(&graph);
    delete_vec(&ans);
}