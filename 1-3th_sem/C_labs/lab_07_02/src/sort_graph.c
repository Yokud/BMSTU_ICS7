#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "sort_and_filter.h"
#include "compare.h"

#define __USE_MINGW_ANSI_STDIO 1

#define N_MAX 1000
#define NUM_PER 500

typedef struct
{
    size_t n;
    int array[N_MAX];
} arr_t;


int gen_rand_arr(int arr[], size_t n)
{
    if (n > N_MAX)
        return EXIT_FAILURE;

    for (size_t i = 0; i < n; i++)
        arr[i] = rand() % 100 + 1;

    return EXIT_SUCCESS;
}

double get_time_of_sort(size_t n, void (*sort)(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)))
{
    if (n > N_MAX)
        return 0.0;

    arr_t orig_arr, arr_copy;

    orig_arr.n = n;

    if (gen_rand_arr(orig_arr.array, orig_arr.n))
        return 0.0;

    double summary_time = 0.0;
    clock_t t_b, t_e;
    t_b = clock();
    for (size_t i = 0; i < NUM_PER; i++)
    {
        arr_copy = orig_arr;
        sort(arr_copy.array, arr_copy.n, sizeof(int), cmp_int);
    }
    t_e = clock();

    summary_time = t_e - t_b;

    return summary_time / (CLOCKS_PER_SEC * NUM_PER);
}

int main(void)
{
    double time_01, time_02;
    FILE *gp, *output_01, *output_02;

    output_01 = fopen("./out/mysort.temp", "w");
    output_02 = fopen("./out/qsort.temp", "w");
    gp = popen("gnuplot -persistent", "w");

    for (size_t n = 100; n <= N_MAX; n += 100)
    {
        time_01 = get_time_of_sort(n, mysort);
        time_02 = get_time_of_sort(n, qsort);
        fprintf(output_01, "%zu %lf \n", n, time_01);
        fprintf(output_02, "%zu %lf \n", n, time_02);
    }

    fprintf(gp, "set title \"Dependence time of sorting from len of array\" \n");
    fprintf(gp, "set xlabel \"Count of elements(len) in array\" \n");
    fprintf(gp, "set ylabel \"Time of sorting in seconds\" \n");
    fprintf(gp, "set logscale y 10 \n");
    fprintf(gp, "plot './out/mysort.temp' with lines title \"insertion sort(binary)\", './out/qsort.temp' with lines title \"qsort\" \n");
    fclose(output_01);
    fclose(output_02);
    pclose(gp);

    return EXIT_SUCCESS;
}