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

void create_deq(deque *st, int size, int capacity) {
    st->size = size;
    st->capacity = capacity;
    st->vertex = (vertex *)calloc(capacity, sizeof(vertex));
    st->start = 0;
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

void delete_deq(deque *st) {
    st->size = 0;
    st->capacity = 0;
    st->start = 0;
    free(st->vertex);
}

// реализация самой задачи
typedef struct {
    int **list;
    int **used;
    int n;
    int m;
} graph;

void create(graph *vec, int n, int m) {
    vec->n = n;
    vec->m = m;
    vec->list = (int **)malloc(sizeof(int *) * n);
    vec->used = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        vec->list[i] = (int *)calloc(m, sizeof(int));
        vec->used[i] = (int *)calloc(m, sizeof(int));
    }
}

void cin_graph(graph *vec, int *x1, int *y1, int *x2, int *y2) {
    int n, m;
    scanf("%d %d", &n, &m);
    create(vec, n, m);
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
    deque deq;
    create_deq(&deq, 0, 10);
    push_deq(&deq, x, y);
    graph->used[x][y] = 1;
    while (getsize_deq(&deq) != 0) {
        vertex vert = pop_deq(&deq);
        x = vert.x, y = vert.y;
        if (x > 0) {
            int i = x - 1, j = y;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(&deq, i, j);
            }
        }
        if (y < m - 1) {
            int i = x, j = y + 1;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(&deq, i, j);
            }
        }
        if (y > 0) {
            int i = x, j = y - 1;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(&deq, i, j);
            }
        }
        if (x < n - 1) {
            int i = x + 1, j = y;
            if (graph->used[i][j] == 0 && graph->list[i][j] != -1) {
                graph->used[i][j] = 1;
                graph->list[i][j] = graph->list[x][y] + 1;
                push_deq(&deq, i, j);
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
    graph graph;
    int x1, y1, x2, y2;
    cin_graph(&graph, &x1, &y1, &x2, &y2);
    bfs(&graph, x1, y1);
    get_ans(&graph, x2, y2);
    for (int i = 0; i < graph.n; i++) {
        free(graph.list[i]);
    }
    free(graph.list);
}
