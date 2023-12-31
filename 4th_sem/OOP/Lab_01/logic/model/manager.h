#ifndef MANAGER_H
#define MANAGER_H

#include "model3D.h"
#include "model2D.h"

typedef enum
{
    ROTATE,
    SCALE,
    PROJECTION,
    READ,
    WRITE,
    DESTROY
} task_t;

typedef union
{
    scale_params_t scale_params;
    rotate_params_t rotate_params;
    load_params_t load_params;
    projection_params_t proj_params;
} params_t;

error_t manager(model2D_t &model2D, const params_t &params, const task_t &task);


#endif // MANAGER_H
