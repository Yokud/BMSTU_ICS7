#ifndef POINT3D_H
#define POINT3D_H

#include <cmath>
#include <stdio.h>

#include "logic/model/errors.h"
#include "logic/points/point2D/point2D.h"
#include "logic/model/model_params.h"

#define EPS 1e-6

typedef struct
{
    double x, y, z;
} point3D_t;

error_t read_point3D(point3D_t &point, FILE * const f);

void write_point3D(const point3D_t &point, FILE * const f);

void scale_point3D(point3D_t &point, const scale_params_t &params, const point3D_t &center);

void rotate_point3D(point3D_t &point, const rotate_params_t &params, const point3D_t &center);

point2D_t projection_point3D(const point3D_t &point3D, const scene_params_t &params);

int comp_coords(const double &lhs, const double &rhs);

#endif
