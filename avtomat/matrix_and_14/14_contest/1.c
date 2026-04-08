#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    int *list;
} vector;

typedef struct {
    int n;
    vector **vertex;
} adjacency_list;

int get_size_vec(vector *vec);

int get_capacity_vec(vector *vec);

void push_back_vec(vector *vec, int x);

void pop_back_vec(vector *vec);

vector *create_vec(int n);

void delete_vec(vector **free_vec);

adjacency_list *create(int n);

void delete_matrix(adjacency_list **free_graph);

adjacency_list *scanf_graph(int n, int m);

void dfs(int v, vector *used, vector *ans, adjacency_list *graph, int comp);

void solve(adjacency_list *graph, vector *ans);

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

vector *create_vec(int n) {
    vector *vec = (vector *)malloc(sizeof(vector));
    vec->size = n;
    vec->capacity = n;
    vec->list = (int *)calloc(n, sizeof(int));
    return vec;
}

void delete_vec(vector **free_vec) {
    free((*free_vec)->list);
    free(*free_vec);
    *free_vec = NULL;
}

adjacency_list *create(int n) {
    adjacency_list *graph = (adjacency_list *)malloc(sizeof(adjacency_list));
    graph->n = n;
    graph->vertex = (vector **)calloc(n, sizeof(vector *));
    for (int i = 0; i < n; i++) {
        graph->vertex[i] = create_vec(0);
    }
    return graph;
}

void delete_matrix(adjacency_list **free_graph) {
    int n = (*free_graph)->n;
    for (int i = 0; i < n; i++) {
        delete_vec(&((*free_graph)->vertex[i]));
    }
    free((*free_graph)->vertex);
    free(*free_graph);
    *free_graph = NULL;
}

adjacency_list *scanf_graph(int n, int m) {
    adjacency_list *graph = create(n + 1);
    for (int i = 0; i < m; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        push_back_vec(graph->vertex[w], v);
        push_back_vec(graph->vertex[v], w);
    }
    return graph;
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
    vector *used;
    used = create_vec(get_size_vec(ans));
    for (int i = 1; i < get_size_vec(ans); i++) {
        if (used->list[i] == 0) {
            count_comp++;
            dfs(i, used, ans, graph, count_comp);
        }
    }
    printf("%d\n", count_comp);
    for (int i = 1; i < used->size; i++) {
        printf("%d ", ans->list[i]);
    }
    delete_vec(&used);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    adjacency_list *graph;
    graph = scanf_graph(n, m);
    vector *ans;
    ans = create_vec(n + 1);
    solve(graph, ans);
    delete_matrix(&graph);
    delete_vec(&ans);
}