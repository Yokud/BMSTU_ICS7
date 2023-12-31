#include "rectangles.h"

int fread_rect(FILE *f, void *rect)
{
    if (!rect)
        return INPUT_ERROR;

    if (fscanf(f, "%lf %lf", &((rect_t *) rect)->width, &((rect_t *) rect)->height) != 2 || ((rect_t *) rect)->width < 0 || ((rect_t *) rect)->height < 0)
        return INPUT_ERROR;
    
    return OK;
}

void print_rect(void *rect)
{
    if (!rect)
        return;

    printf("%.6lf %.6lf\n", ((rect_t *) rect)->width, ((rect_t *) rect)->height);
}

double square(void *rect)
{
    if (!rect)
        return INPUT_ERROR;

    return ((rect_t *) rect)->width * ((rect_t *) rect)->height;
}

double perimeter(void *rect)
{
    if (!rect)
        return INPUT_ERROR;

    return 2 * (((rect_t *) rect)->width + ((rect_t *) rect)->height);
}

double diagonal(void *rect)
{
    if (!rect)
        return INPUT_ERROR;

    return sqrt(((rect_t *) rect)->width * ((rect_t *) rect)->width + ((rect_t *) rect)->height * ((rect_t *) rect)->height);
}

int rects_equal(void *rect_a, void *rect_b)
{
    double eps = 1e-6;

    return !(fabs(((rect_t *) rect_a)->width - ((rect_t *) rect_b)->width) < eps && fabs(((rect_t *) rect_a)->height - ((rect_t *) rect_b)->height) < eps);
}