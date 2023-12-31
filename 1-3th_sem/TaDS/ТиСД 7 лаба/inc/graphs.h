#ifndef GRAPHS_H
#define GRAPHS_H


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "time.h"

#define OK 0
#define INPUT_ERROR -1
#define ALLOC_ERROR -2
#define GRAPH_ERROR -3


typedef struct graph
{
    int **adjacency;
    int *markers;
    int vertexes_count;
} graph_t;

int input_graph(graph_t **graph);
int get_min_costs(graph_t *graph, int num_of_vrtx);
int is_connective(graph_t *graph);
void print_graph(graph_t *graph);
void cities_on_dist_at_least_T(graph_t *graph, int capital, int T);
void free_graph(graph_t *graph);

#endif