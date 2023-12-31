#ifndef POINT2D_H
#define POINT2D_H

#include "logic/model/errors.h"
#include "logic/scene/scene.h"
#include "logic/scene/screen.h"

typedef struct
{
    double x, y;
} point2D_t;


void transl_to_screen_coords_point2D(point2D_t &point,
                                     const scene_params_t &scene_params,
                                     const screen_params_t &screen_params);


#endif // POINT2D_H
