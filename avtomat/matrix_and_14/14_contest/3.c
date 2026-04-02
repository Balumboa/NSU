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

void create(graph *graph, int n) {
    graph->list = (vert **)malloc(n * sizeof(vert *));
    for (int i = 0; i < n; i++) {
        graph->list[i] = (vert *)malloc(1 * sizeof(vert));
    }
    graph->sizes = (int *)calloc(n, sizeof(int));
    graph->capacities = (int *)calloc(n, sizeof(int));
}

void push_back(graph *graph, int x, int y, int z) {
    if (graph->capacities[x] == 0) {
        graph->capacities[x] = 10;
        graph->list[x] = (vert *)malloc(sizeof(vert) * 10);
    }
    if (graph->capacities[x] == graph->sizes[x]) {
        graph->list[x] = (vert *)realloc(
            graph->list[x], (2 * graph->capacities[x] + 1) * sizeof(vert));
        graph->capacities[x] = 2 * graph->capacities[x] + 1;
    }
    vert newvert;
    newvert.to = y;
    newvert.weight = z;
    graph->list[x][graph->sizes[x]] = newvert;
    graph->sizes[x]++;
}

void scan(graph *graph) {
    int x, y, z;
    while (scanf("%d %d %d", &x, &y, &z) == 3) {
        push_back(graph, x, y, z);
        push_back(graph, y, x, z);
        // int contin;
        // scanf("%d", &contin);
        // if (contin)
        //     break;
    }
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

void delete_graph(graph *graph) {
    for (int i = 0; i < graph->n; i++) {
        free(graph->list[i]);
    }
    free(graph->list);
    free(graph->sizes);
    free(graph->capacities);
}

// void print(graph *graph, int n) {
//     for (int i = 1; i < n; i++) {
//         printf("%d: ", i);
//         for (int j = 0; j < graph->sizes[i]; j++) {
//             printf("%d ", graph->list[i][j].to);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    n++;
    int start, finish;
    scanf("%d %d", &start, &finish);
    graph graph;
    create(&graph, n);
    scan(&graph);
    // print(&graph, n);
    dijkstra_and_solve(&graph, start, finish, n);

    delete_graph(&graph);
}
