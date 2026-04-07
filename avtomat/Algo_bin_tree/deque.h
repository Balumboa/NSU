#ifndef steck_h
#define steck_h

#include <stdlib.h>

/*****************************************************************************
 * File:         deque.h
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

typedef struct {
    int size;
    int start;
    int capacity;
    int* vertex;
} deque;

deque* create_deq(int size, int capacity);

int getsize_deq(deque* st);

int getcapacity_deq(deque* st);

void push_deq(deque* st, int v);

int pop_deq(deque* st);

void delete_deq(deque** st);

#endif