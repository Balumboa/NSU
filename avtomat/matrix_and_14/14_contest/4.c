#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int const INF = 100000000;

int min(int a, int b) {
    return (a < b) ? a : b;
}

typedef struct {
    int **list;
    int n;
} graph;

void create(graph *graph, int n) {
    graph->n = n;
    graph->list = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        graph->list[i] = (int *)calloc(n + 1, sizeof(int));
        for (int j = 0; j <= n; j++) {
            graph->list[i][j] = INF;
        }
        graph->list[i][i] = 0;
    }
}

void push_back(graph *graph, int v, int w, int weight) {
    graph->list[v][w] = min(weight, graph->list[v][w]);
}

void cin(graph *graph) {
    int n, m;
    scanf("%d %d", &n, &m);
    create(graph, n);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        push_back(graph, from, to, weight);
        push_back(graph, to, from, weight);
    }
}

void floid(graph *graph) {
    int n = graph->n;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph->list[i][j] = min(graph->list[i][j],
                                        graph->list[i][k] + graph->list[k][j]);
            }
        }
    }
}

void solve(graph *graph) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        printf("%d\n", graph->list[v][w]);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    graph graph;
    cin(&graph);
    floid(&graph);
    solve(&graph);

    for (int i = 0; i <= graph.n; i++) {
        free(graph.list[i]);
    }
    free(graph.list);
}