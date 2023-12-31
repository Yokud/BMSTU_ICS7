#include <stdio.h>
#include <stdlib.h>

long mypow(long a, long n)
{
    long s = 1;
    for (long i = 0; i < n; i++)
        s *= a;

    return s;
}

int main(void)
{
    long a, n;
    long ans;

    if (scanf("%ld", &a) != 1)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    if (scanf("%ld", &n) != 1 || n <= 0)
    {
        printf("Wrong data");
        return EXIT_FAILURE;
    }

    ans = mypow(a, n);

    printf("%ld", ans);

    return EXIT_SUCCESS;
}
