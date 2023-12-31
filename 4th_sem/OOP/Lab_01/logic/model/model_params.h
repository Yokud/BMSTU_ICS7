#ifndef MODEL_PARAMS_H
#define MODEL_PARAMS_H


#include "logic/scene/screen.h"


typedef enum
{
    AXIS_X,
    AXIS_Y,
    AXIS_Z
} axis_t;

typedef struct
{
    double kx, ky, kz;
} scale_params_t;

typedef struct
{
    double angle;
    axis_t axis;
} rotate_params_t;

typedef struct
{
    const char *filename;
} load_params_t;

typedef struct
{
    screen_params_t screen_params;
} projection_params_t;

#endif // MODEL_PARAMS_H
