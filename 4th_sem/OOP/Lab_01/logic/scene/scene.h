#ifndef SCENE_H
#define SCENE_H

typedef struct
{
    double alpha, betta;
    double camera_z, plane_z;
    double scene_xmin, scene_xmax;
    double scene_ymin, scene_ymax;
} scene_params_t;

#endif // SCENE_H
