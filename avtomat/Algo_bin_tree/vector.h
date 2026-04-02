#ifndef vector_h
#define vector_h

typedef struct {
    int size;
    int capacity;
    int *list;
} vector;

void push_back_vec(vector *vec, int x);

void pop_back_vec(vector *vec);

int get_size_vec(vector *vec);

int get_capacity_vec(vector *vec);

void print_vec(vector *vec);

void scan_vec(vector *vec);

void create_vec(vector *vec, int n);

void delete_vec(vector *vec);

#endif