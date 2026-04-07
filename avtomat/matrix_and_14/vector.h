#ifndef vector_h
#define vector_h

/*****************************************************************************
 * File:         vector.h
 * Description:  Реализация вектора(динамический список)
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

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

vector *scan_vec();

vector *create_vec(int n);

void delete_vec(vector **vec);

#endif