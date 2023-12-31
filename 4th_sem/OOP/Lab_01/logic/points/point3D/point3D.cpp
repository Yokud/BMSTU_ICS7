#include "logic/points/point3D/point3D.h"

error_t read_point3D(point3D_t &point, FILE * const f)
{
    if (fscanf(f, "%lf", &point.x) != 1)
        return READ_POINTS_ERROR;
    if (fscanf(f, "%lf", &point.y) != 1)
        return READ_POINTS_ERROR;
    if (fscanf(f, "%lf", &point.z) != 1)
        return READ_POINTS_ERROR;
    return OK;
}

void write_point3D(const point3D_t &point, FILE * const f)
{
    fprintf(f, "%lf %lf %lf", point.x, point.y, point.z);
}

static void move_point_to_center(point3D_t &point, const point3D_t &center)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;
}

static void move_point_from_center(point3D_t &point, const point3D_t &center)
{
    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

void scale_point3D(point3D_t &point, const scale_params_t &params, const point3D_t &center)
{
    move_point_to_center(point, center);

    point.x *= params.kx;
    point.y *= params.ky;
    point.z *= params.kz;

    move_point_from_center(point, center);
}

static void rotate_around_x(point3D_t &point, double angle)
{
    point3D_t tmp;
    tmp.x = point.x;
    tmp.y = point.y * cos(angle) - point.z * sin(angle);
    tmp.z = point.y * sin(angle) + point.z * cos(angle);
    point.x = tmp.x;
    point.y = tmp.y;
    point.z = tmp.z;
}

static void rotate_around_y(point3D_t &point, double angle)
{
    point3D_t tmp;
    tmp.x = point.x * cos(angle) - point.z * sin(angle);
    tmp.y = point.y;
    tmp.z = point.x * sin(angle) + point.z * cos(angle);
    point.x = tmp.x;
    point.y = tmp.y;
    point.z = tmp.z;
}

static void rotate_around_z(point3D_t &point, double angle)
{
    point3D_t tmp;
    tmp.x = point.x * cos(angle) - point.y * sin(angle);
    tmp.y = point.x * sin(angle) + point.y * cos(angle);
    tmp.z = point.z;
    point.x = tmp.x;
    point.y = tmp.y;
    point.z = tmp.z;
}

void rotate_point3D(point3D_t &point, const rotate_params_t &params, const point3D_t &center)
{
    move_point_to_center(point, center);

    if (params.axis == AXIS_X)
        rotate_around_x(point, params.angle);
    else if (params.axis == AXIS_Y)
        rotate_around_y(point, params.angle);
    else if (params.axis == AXIS_Z)
        rotate_around_z(point, params.angle);

    move_point_from_center(point, center);
}

point2D_t projection_point3D(const point3D_t &point3D, const scene_params_t &params)
{
    point3D_t proj_point;

    proj_point.x = point3D.x * cos(params.alpha) - point3D.y * sin(params.alpha);
    proj_point.y = point3D.x * sin(params.alpha) * cos(params.betta) +
              point3D.y * cos(params.alpha) * cos(params.betta) -
              point3D.z * sin(params.betta);
    proj_point.z = point3D.x * sin(params.alpha) * sin(params.betta) +
              point3D.y * cos(params.alpha) * sin(params.betta) +
              point3D.z * cos(params.betta);

    // projection (based on similar triangles)
    proj_point.x = proj_point.x * (params.camera_z - params.plane_z) / (params.camera_z - point3D.z);
    proj_point.y = proj_point.y * (params.camera_z - params.plane_z) / (params.camera_z - point3D.z);
    proj_point.z = proj_point.z  - params.plane_z;

    point2D_t point_in_2D;
    point_in_2D.x = proj_point.x;
    point_in_2D.y = proj_point.y;

    return point_in_2D;
}

int comp_coords(const double &lhs, const double &rhs)
{
    if (lhs - rhs > EPS)
        return 1;
    else if (rhs - lhs > EPS)
        return -1;
    else
        return 0;
}
