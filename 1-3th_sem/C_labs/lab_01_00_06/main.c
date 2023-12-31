#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double len(double x, double y)
{
    return sqrt(x * x + y * y);
}

int main(void)
{
    double x1, y1;
    double x2, y2; 
    double x3, y3;
    double abx, aby;
    double bcx, bcy;
    double acx, acy;
    double ab, bc, ac;
    double alpha, beta, gamma;
    double eps = 1e-8;
    long tp;

    if (scanf("%lf", &x1) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &y1) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &x2) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &y2) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &x3) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &y3) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    abx = x2 - x1;
    aby = y2 - y1;
    bcx = x3 - x2;
    bcy = y3 - y2;
    acx = x3 - x1;
    acy = y3 - y1;
    ab = len(abx, aby);
    bc = len(bcx, bcy);
    ac = len(acx, acy);

    if (ab + bc > ac && bc + ac > ab && ab + ac > bc)
    {
        alpha = ab * ab + ac * ac - bc * bc;
        beta = ab * ab + bc * bc - ac * ac;
        gamma = ac * ac + bc * bc - ab * ab;

        if (fabs(alpha) < eps || fabs(beta) < eps\
            || fabs(gamma) < eps)
            tp = 1;
        else if (alpha < 0.0 || beta < 0.0 || gamma < 0.0)
            tp = 2;
        else
            tp = 0; 
		
        printf("%ld", tp);
		
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Such triangle doesn't exist");
        return EXIT_FAILURE;
    }
}
