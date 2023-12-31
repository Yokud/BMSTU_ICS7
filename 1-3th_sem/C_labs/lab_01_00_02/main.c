#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	double a, b, h;
	double c, x;
	double p;
	double eps = 1e-8;
	
	if (scanf("%lf", &a) != 1 || a < eps)
		return EXIT_FAILURE;
	
	if (scanf("%lf", &b) != 1 || b < eps)
		return EXIT_FAILURE;
	
	if (scanf("%lf", &h) != 1 || h < eps)
		return EXIT_FAILURE;

	c = fabs(a - b) / 2.0;
	x = sqrt(h * h + c * c);
	p = a + b + 2.0 * x;

	printf("%.5f", p);

	return EXIT_SUCCESS;
}
