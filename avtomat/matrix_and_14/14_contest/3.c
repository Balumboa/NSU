#include <stdio.h>
#include <stdlib.h>

int const INF = 1000000;

typedef struct {
    int to;
    int weight;
} vert;

typedef struct {
    vert **list;
    int *sizes;
    int *capacities;
    int n;
} graph;

graph *create(int n);

void push_back(graph *graph, int x, int y, int z);

graph *scan(int n);

int min(int *vertex, int *used, int n);

void update(graph *graph, int *vertex, int v, int N);

void solve(int *vertex, int finish);

void dijkstra_and_solve(graph *graph, int start, int finish, int n);

void delete_graph(graph **free_graph);

graph *create(int n) {
    graph *gp = (graph *)malloc(sizeof(graph));
    gp->n = n;
    gp->list = (vert **)malloc(n * sizeof(vert *));
    gp->sizes = (int *)calloc(n, sizeof(int));
    gp->capacities = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        gp->list[i] = (vert *)malloc(10 * sizeof(vert));
        gp->capacities[i] = 10;
    }
    return gp;
}

void push_back(graph *graph, int x, int y, int z) {
    if (graph->capacities[x] == graph->sizes[x]) {
        graph->list[x] = (vert *)realloc(
            graph->list[x], (2 * graph->capacities[x]) * sizeof(vert));
        graph->capacities[x] = 2 * graph->capacities[x];
    }
    vert newvert;
    newvert.to = y;
    newvert.weight = z;
    graph->list[x][graph->sizes[x]] = newvert;
    graph->sizes[x]++;
}

graph *scan(int n) {
    graph *gp = create(n + 1);
    int x, y, z;
    while (scanf("%d %d %d", &x, &y, &z) == 3) {
        push_back(gp, x, y, z);
        push_back(gp, y, x, z);
        // int contin;
        // scanf("%d", &contin);
        // if (contin)
        //     break;
    }
    return gp;
}

int min(int *vertex, int *used, int n) {
    int ind = 0;
    for (int i = 1; i < n; i++) {
        if (used[i] == 0) {
            if (vertex[i] < vertex[ind]) {
                ind = i;
            }
        }
    }
    return ind;
}

void update(graph *graph, int *vertex, int v, int N) {
    int n = graph->sizes[v];
    for (int i = 0; i < n; i++) {
        int w = graph->list[v][i].to;
        int weight = graph->list[v][i].weight;
        int newr = vertex[v] + weight;
        vertex[w] = (newr < vertex[w]) ? newr : vertex[w];
    }
    // for (int i = 0; i < N; i++) {
    //     if (vertex[i] == INF)
    //         printf("INF ");
    //     else
    //         printf("%d ", vertex[i]);
    // }
}

void solve(int *vertex, int finish) {
    if (vertex[finish] == INF)
        printf("no");
    else
        printf("%d", vertex[finish]);
}

void dijkstra_and_solve(graph *graph, int start, int finish, int n) {
    int *vertex = (int *)calloc(n, sizeof(int));
    int *used = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        vertex[i] = INF;
    }
    vertex[start] = 0;
    for (int i = 0; i < n; i++) {
        int ind = min(vertex, used, n);
        if (vertex[ind] == INF) {
            break;
        }
        used[ind] = 1;
        update(graph, vertex, ind, n);
    }
    solve(vertex, finish);
    free(vertex);
    free(used);
}

void delete_graph(graph **free_graph) {
    for (int i = 0; i < (*free_graph)->n; i++) {
        free((*free_graph)->list[i]);
    }
    free((*free_graph)->list);
    free((*free_graph)->sizes);
    free((*free_graph)->capacities);
    free(*free_graph);
    *free_graph = NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    n++;
    int start, finish;
    scanf("%d %d", &start, &finish);
    graph *graph;
    graph = scan(n);
    dijkstra_and_solve(graph, start, finish, n);
    delete_graph(&graph);
}
