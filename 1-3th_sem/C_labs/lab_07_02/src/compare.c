#include "compare.h"

int cmp_int(const void *p1, const void *p2)
{
    return *((int *) p1) - *((int *) p2);
}

int cmp_double(const void *p1, const void *p2)
{
    double eps = 1e-6;

    if (fabs(*(double *) p1 - *(double *) p2) < eps * (*((double *) p1) > *((double *) p2) ? *(double *) p1 : *(double *) p2))
        return 0;
    else if (*((double *) p1) > *((double *) p2))
        return 1;
    else if (*((double *) p1) < *((double *) p2))
        return -1;

    return 0;
}

int cmp_chr(const void *p1, const void *p2)
{
    return *((char *) p1) - *((char *) p2);
}

int cmp_str(const void *s1, const void *s2)
{
    const char *p1 = s1;
    const char *p2 = s2;

    return strcmp(p1, p2);
}

int cmp_arr(const void *a, const void *b, size_t n, size_t size, int (*cmp)(const void *, const void *))
{
    char *pb_a, *pe_a, *pb_b, *pe_b;
    int res = 0;

    if (a == NULL && b == NULL)
        return 0;
    else if (a == NULL && b != NULL)
        return -1;
    else if (a != NULL && b == NULL)
        return 1;

    pb_a = (char *) a;
    pe_a = (char *) a + n * size;
    pb_b = (char *) b;
    pe_b = (char *) b + n * size;

    for (; res == 0 && pb_a < pe_a && pb_b < pe_b; pb_a += size, pb_b += size)
        res = cmp(pb_a, pb_b);

    return res;
}