#include <stdio.h>

#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "convert_matrixes.h"
#include "incidence_matrix.h"
#include "list_of_edges.h"

int main() {
    adjacency_list *graph_al;
    adjacency_matrix *graph_am;
    incidence_matrix *graph_im;
    list_of_edges *graph_loe;
    graph_al = scanf_adj_list();
    print_adj_list(graph_al);
    graph_loe = convert_adj_list_to_list_edg(graph_al);
    print_list_edge(graph_loe);
    graph_im = convert_list_edg_to_incidence_mat(graph_loe);
    print_inc_matrix(graph_im);
    graph_am = convert_incidence_mat_to_adj_mat(graph_im);
    print_adj_matrix(graph_am);
    graph_al = convert_adj_mat_to_adj_list(graph_am);
    print_adj_list(graph_al);
    delete_adj_list(&graph_al);
    delete_adj_matrix(&graph_am);
    delete_inc_matrix(&graph_im);
    delete_list_edge(&graph_loe);
    printf("Матрицы удалены\n");
}