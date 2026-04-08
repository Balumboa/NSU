#include <stdio.h>
#include <stdlib.h>

// дек
typedef struct {
    int x;
    int y;
} vertex;

typedef struct {
    int size;
    int start;
    int capacity;
    vertex *vertex;
} deque;

typedef struct {
    int **list;
    int **used;
    int n;
    int m;
} graph;

deque *create_deq(int size, int capacity);

int getsize_deq(deque *st);

int getcapacity_deq(deque *st);

void push_deq(deque *st, int x, int y);

vertex pop_deq(deque *st);

void delete_deq(deque **free_st);

graph *create(int n, int m);

graph *cin_graph(int *x1, int *y1, int *x2, int *y2);

void print(graph *vec);

void bfs(graph *graph, int x, int y);

void get_ans(graph *graph, int x, int y);

void delete_graph(graph **free_graph);

void delete_graph(graph **free_graph) {
    int n = (*free_graph)->n;
    for (int i = 0; i < n; i++) {
        free((*free_graph)->list[i]);
        free((*free_graph)->used[i]);
    }
    free((*free_graph)->list);
    free((*free_graph)->used);
    free(*free_graph);
    *free_graph = NULL;
}

deque *create_deq(int size, int capacity) {
    deque *st = (deque *)malloc(sizeof(deque));
    st->size = size;
    st->capacity = capacity;
    st->vertex = (vertex *)calloc(capacity, sizeof(vertex));
    st->start = 0;
    return st;
}

int getsize_deq(deque *st) {
    return st->size - st->start;
}

int getcapacity_deq(deque *st) {
    return st->capacity;
}

void push_deq(deque *st, int x, int y) {
    int capacity = getcapacity_deq(st);
    if (capacity == st->size) {
        st->vertex =
            (vertex *)realloc(st->vertex, (2 * st->size + 1) * sizeof(vertex));
        st->capacity = capacity * 2 + 1;
    }
    st->vertex[st->size].x = x;
    st->vertex[st->size].y = y;
    st->size++;
}

vertex pop_deq(deque *st) {
    vertex ret = st->vertex[st->start];
    st->start++;
    return ret;
}

void delete_deq(deque **free_deq) {
    free((*free_deq)->vertex);
    free(*free_deq);
    *free_deq = NULL;
}

graph *create(int n, int m) {
    graph *vec = (graph *)malloc(sizeof(graph));
    vec->n = n;
    vec->m = m;
    vec->list = (int **)malloc(sizeof(int *) * n);
    vec->used = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        vec->list[i] = (int *)calloc(m, sizeof(int));
        vec->used[i] = (int *)calloc(m, sizeof(int));
    }
    return vec;
}

graph *cin_graph(int *x1, int *y1, int *x2, int *y2) {
    int n, m;
    scanf("%d %d", &n, &m);
    graph *vec;
    vec = create(n, m);
    for (int i = 0; i < n; i++) {
        char c;
        scanf("%c", &c);
        for (int j = 0; j < m; j++) {
            char c;
            scanf("%c", &c);
            if (c == '.')
                vec->list[i][j] = 0;
            else if (c == 'X')
                vec->list[i][j] = -1;
            else if (c == 'S') {
                *x1 = i, *y1 = j;
                vec->list[i][j] = 0;
            } else if (c == 'F') {
                *x2 = i, *y2 = j;
                vec->list[i][j] = 0;
            }
        }
    }
    return vec;
}

void print(graph *vec) {
    int n = vec->n;
    int m = vec->m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", vec->list[i][j]);
        }
        printf("\n");
    }
}

void bfs(graph *graph, int x, int y) {
    int n = graph->n;
    int m = graph->m;
    deque *deq;
    deq = create_deq(0, 10);
    push_deq(deq, x, y);
    graph->used[x][y] = 1;
    while (getsize_deq(deq) != 0) {
        vertex vert = pop_deq(deq);
        x = vert.x, y = vert.y;
        if (x > 0) {
            int i = x - 1, j = y;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(deq, i, j);
            }
        }
        if (y < m - 1) {
            int i = x, j = y + 1;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(deq, i, j);
            }
        }
        if (y > 0) {
            int i = x, j = y - 1;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(deq, i, j);
            }
        }
        if (x < n - 1) {
            int i = x + 1, j = y;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(deq, i, j);
            }
        }
    }
    delete_deq(&deq);
}

void get_ans(graph *graph, int x, int y) {
    if (graph->used[x][y] == 0)
        printf("-1\n");
    else
        printf("%d\n", graph->list[x][y]);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    graph *graph;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    graph = cin_graph(&x1, &y1, &x2, &y2);
    bfs(graph, x1, y1);
    get_ans(graph, x2, y2);
    delete_graph(&graph);
}
