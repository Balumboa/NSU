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

graph *create(int n);

void push_back(graph *graph, int v, int w, int weight);

graph *cin();

void floid(graph *graph);

void solve(graph *graph);

void delete_graph(graph **free_graph);

graph *create(int n) {
    graph *gp = (graph *)malloc(sizeof(graph));
    gp->n = n;
    gp->list = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        gp->list[i] = (int *)calloc(n + 1, sizeof(int));
        for (int j = 0; j <= n; j++) {
            gp->list[i][j] = INF;
        }
        gp->list[i][i] = 0;
    }
    return gp;
}

void push_back(graph *graph, int v, int w, int weight) {
    graph->list[v][w] = min(weight, graph->list[v][w]);
}

graph *cin() {
    int n, m;
    scanf("%d %d", &n, &m);
    graph *gp;
    gp = create(n);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        push_back(gp, from, to, weight);
        push_back(gp, to, from, weight);
    }
    return gp;
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

void delete_graph(graph **free_graph) {
    for (int i = 0; i <= (*free_graph)->n; i++) {
        free((*free_graph)->list[i]);
    }
    free((*free_graph)->list);
    free(*free_graph);
    *free_graph = NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    graph *graph;
    graph = cin();
    floid(graph);
    solve(graph);
    delete_graph(&graph);
}
