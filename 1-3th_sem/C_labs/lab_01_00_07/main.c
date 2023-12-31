#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x)
{
    return exp(x);
}

double sum(double x, double eps)
{
    double s, a;
    long i;
    i = 1;
    s = 0.0;
    a = 1.0;

    while (fabs(a) > eps)
    {
        s += a;
        a *= x / i;
        i++;
    }

    return s;
}

int main(void)
{
    double x, eps;
    double s, f;
    double abs_disp, rltv_disp;

    if (scanf("%lf", &x) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }
    if (scanf("%lf", &eps) != 1 || eps <= 0.0 || eps >= 1.0)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    s = sum(x, eps);
    f = func(x);
    abs_disp = fabs(f - s);
    rltv_disp = (f < eps) ? 0.0 : fabs(abs_disp / f);

    printf("%.6lf %.6lf %.6lf %.6lf", s, f, abs_disp, rltv_disp);

    return EXIT_SUCCESS;
}
