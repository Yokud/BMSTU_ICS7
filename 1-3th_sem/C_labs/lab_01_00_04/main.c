#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long s;
    long count;

    if (scanf("%ld", &s) != 1 || s < 0)
        return EXIT_FAILURE;

    count = (s - 20) / 25;

    printf("%ld", count);
    
    return EXIT_SUCCESS;
}
