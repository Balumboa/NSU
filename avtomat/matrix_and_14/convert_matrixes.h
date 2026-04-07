#ifndef CONVERT_MATRIXES_H
#define CONVERT_MATRIXES_H

#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "incidence_matrix.h"
#include "list_of_edges.h"

/*****************************************************************************
 * File:         convert_matrixes.h
 * Description:  Перевод из разных типов графов
 * Created:      31 mar 2026
 * Author:       Ivan Arbuzov
 *****************************************************************************/

list_of_edges *convert_adj_list_to_list_edg(adjacency_list *a);

incidence_matrix *convert_list_edg_to_incidence_mat(list_of_edges *a);

adjacency_matrix *convert_incidence_mat_to_adj_mat(incidence_matrix *a);

adjacency_list *convert_adj_mat_to_adj_list(adjacency_matrix *a);

#endif