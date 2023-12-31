#include "scene_init.h"

void init_scene(scene_params_t &params, const points3D_t &points3D)
{
    if (points3D.points_count == 0)
        return;

    point3D_t min_point, max_point;

    min_point = find_min_coords(points3D);
    max_point = find_max_coords(points3D);

    params.scene_xmin = min_point.x;
    params.scene_xmax = max_point.x;
    params.scene_ymin = min_point.y;
    params.scene_ymax = max_point.y;
    params.plane_z = min_point.z + (max_point.z - min_point.z) * 2;
    params.camera_z = min_point.z + (max_point.z - min_point.z) * 4;
}
