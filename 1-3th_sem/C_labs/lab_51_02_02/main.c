#include "files.h"

double get_average(FILE *f, size_t *count)
{
    double num, sum = 0.0;
    *count = 0;

    while (fscanf(f, "%lf", &num) == 1)
    {
        sum += num;
        (*count)++;
    }

    if (*count == 0)
        return 0.0;

    return sum / (*count);
}

double get_dispersion(FILE *f, double avg, size_t count)
{
    double num, sigma, sum = 0.0;

    while (fscanf(f, "%lf", &num) == 1)
    {
        sigma = num - avg;
        sum += sigma * sigma;
    }

    return sum / count;
}

int main(int argc, char **argv)
{
    FILE *f = NULL;
    size_t count;
    double average, dispersion;
    int rc = 0;

    if (argc != 2)
        rc = ARGS_INPUT_ERROR;
    else
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            average = get_average(f, &count);
            rewind(f);
            if (count)
            {
                dispersion = get_dispersion(f, average, count);
                printf("%.6lf", dispersion);                
            }
            else
                rc = INPUT_ERROR;
        }
        else
            rc = FILE_ERROR;
        fclose(f);
    }

    return rc;
}