#ifndef MODEL3D_H
#define MODEL3D_H

#include <stdio.h>
#include <stdlib.h>

#include "logic/edges/edges.h"
#include "logic/points/point2D/points2D.h"
#include "logic/points/point3D/points3D.h"
#include "logic/model/model2D.h"
#include "logic/scene/scene_init.h"

typedef struct
{
    bool loaded;
    points3D_t points;
    edges_t edges;
    scene_params_t scene_params;
} model3D_t;

model3D_t init_model3D();

void delete_model3D(model3D_t &model);

error_t read_model(model3D_t &model, const load_params_t &params);

error_t write_model(model3D_t &model, const load_params_t &params);

error_t scale_model(model3D_t &model, const scale_params_t &params);

error_t rotate_model(model3D_t &model, const rotate_params_t &params);

error_t projection_model(model2D_t &model2D, const projection_params_t &params, const model3D_t &model);

#endif // MODEL3D_H
