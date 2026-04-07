#ifndef Algorithms_h
#define Algorithms_h

#include <stdio.h>

#include "adjacency_list.h"
#include "deque.h"
#include "stack.h"
#include "vector.h"

/*****************************************************************************
 * File:         Algorithms.h
 * Description:  Список смежности
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

void bfs(adjacency_list *graph);

void dfs(adjacency_list *graph);

#endif