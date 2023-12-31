#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double h, t, m;
    double normal_weight, body_mass_index;
    double eps = 1e-8;

    if (scanf("%lf", &h) != 1 || h < eps)
        return EXIT_FAILURE;

    if (scanf("%lf", &t) != 1 || t < eps)
        return EXIT_FAILURE;

    if (scanf("%lf", &m) != 1 || m < eps)
        return EXIT_FAILURE;


    normal_weight = h * t / 240.0;
    body_mass_index = m / (h * h / 10000.0);

    printf("%.5lf %.5lf", normal_weight, body_mass_index);

    return EXIT_SUCCESS;
}
