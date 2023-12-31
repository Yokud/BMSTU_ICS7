#ifndef EDGES_H
#define EDGES_H

#include <stdio.h>
#include <stdlib.h>

#include "edge.h"
#include "logic/points/point3D/points3D.h"

typedef struct
{
    edge_t *edges_arr;
    size_t n;
} edges_t;

void init_edges(edges_t &edges);

error_t alloc_edges(edges_t &edges, size_t n);

void delete_edges(edges_t &edges);

error_t read_edges(edges_t &edges, FILE * const f);

void write_edges(FILE * const f, const edges_t &edges);

error_t copy_edges(edges_t &edges_dst, const edges_t &edges_src);

error_t are_correct_edges(const edges_t &edges, const points3D_t &points);

#endif // EDGES_H
