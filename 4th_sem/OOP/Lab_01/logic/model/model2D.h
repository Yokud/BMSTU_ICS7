#ifndef MODEL2D_H
#define MODEL2D_H

#include "logic/edges/edges.h"
#include "logic/points/point2D/points2D.h"

typedef struct
{
    points2D_t points2D;
    edges_t edges;
} model2D_t;

#endif // MODEL2D_H
