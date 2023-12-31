#include "logic/points/point3D/points3D.h"

void init_points3D(points3D_t &points)
{
    points.points_arr = NULL;
    points.points_count = 0;
}

error_t alloc_points3D(points3D_t &points)
{
    error_t err = OK;
    points.points_arr = (point3D_t *) calloc(points.points_count, sizeof(point3D_t));
    if (points.points_arr == NULL)
        err = MEMORY_ALLOCATION_ERROR;
    return err;
}

void delete_points3D(points3D_t &points)
{
    free(points.points_arr);
    points.points_arr = NULL;
    points.points_count = 0;
}

error_t read_points_num(size_t &n, FILE *const f)
{
    error_t err = OK;
    if (fscanf(f, "%zu", &n) != 1 || n < 1)
    {
        n = 0;
        err = READ_POINTS_ERROR;
    }
    return err;
}

error_t read_points3D(points3D_t &points, FILE *const f)
{
    error_t err = read_points_num(points.points_count, f);

    if (err == OK)
        err = alloc_points3D(points);

    for (size_t i = 0; err == OK && i < points.points_count; i++)
        err = read_point3D(points.points_arr[i], f);

    if (err != OK)
        delete_points3D(points);

    return err;
}

void write_points_num(FILE * const f, size_t n)
{
    fprintf(f, "%zu\n", n);
}

void write_points3D(FILE * const f, const points3D_t &points)
{
    write_points_num(f, points.points_count);
    for (size_t i = 0; i < points.points_count; i++)
    {
        write_point3D(points.points_arr[i], f);
        fprintf(f, "\n");
    }
}

point3D_t find_min_coords(const points3D_t &points)
{
    point3D_t min_coords = points.points_arr[0];
    for (size_t i = 0; i < points.points_count; i++)
    {
        if (comp_coords(points.points_arr[i].x, min_coords.x) < 0)
            min_coords.x = points.points_arr[i].x;

        if (comp_coords(points.points_arr[i].y, min_coords.y) < 0)
            min_coords.y = points.points_arr[i].y;

        if (comp_coords(points.points_arr[i].z, min_coords.z) < 0)
            min_coords.z = points.points_arr[i].z;
    }

    return min_coords;
}

point3D_t find_max_coords(const points3D_t &points)
{
    point3D_t max_coords = points.points_arr[0];
    for (size_t i = 0; i < points.points_count; i++)
    {
        if (comp_coords(points.points_arr[i].x, max_coords.x) > 0)
            max_coords.x = points.points_arr[i].x;

        if (comp_coords(points.points_arr[i].y, max_coords.y) > 0)
            max_coords.y = points.points_arr[i].y;

        if (comp_coords(points.points_arr[i].z, max_coords.z) > 0)
            max_coords.z = points.points_arr[i].z;
    }

    return max_coords;
}

static point3D_t find_center(const points3D_t &points)
{
    point3D_t center;
    point3D_t min_point, max_point;
    min_point = find_min_coords(points);
    max_point = find_max_coords(points);

    center.x = (max_point.x + min_point.x) / 2;
    center.y = (max_point.y + min_point.y) / 2;
    center.z = (max_point.z + min_point.z) / 2;

    return center;
}

void scale_points3D(points3D_t &points, const scale_params_t &params)
{
    point3D_t center = find_center(points);
    for (size_t i = 0; i < points.points_count; i++)
        scale_point3D(points.points_arr[i], params, center);
}

void rotate_points3D(points3D_t &points, const rotate_params_t &params)
{
    point3D_t center = find_center(points);
    for (size_t i = 0; i < points.points_count; i++)
        rotate_point3D(points.points_arr[i], params, center);
}

error_t projection_points3D(points2D_t &points2D, const points3D_t &points3D, const scene_params_t &params)
{
    error_t err = alloc_points2D(points2D, points3D.points_count);
    if (err == OK)
        for (size_t i = 0; i < points3D.points_count; i++)
            points2D.points_arr[i] = projection_point3D(points3D.points_arr[i], params);
    return err;
}
