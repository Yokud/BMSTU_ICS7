#include "sort_and_filter.h"


void swap(char *a, char *b, size_t size)
{
    for (; size > 0; size--)
    {
        char temp = *a;
        *a++ = *b;
        *b++ = temp;
    }
}

// Сортировка вставками с бинарным поиском
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void *index;
    char *pa, *pa_temp;

    if (!nmemb || base == NULL)
        return;

    pa = (char *) base + size;

    while (pa < (char *) base + nmemb * size)
    {
        index = bin_search(base, (pa - (char *) base) / size + 1, size, pa, compar);
        
        swap(pa, index, size);

        pa_temp = pa; 
        while (pa_temp > (char *) index + size)
        {
            swap(pa_temp, pa_temp - size, size);
            pa_temp -= size;
        }

        pa += size;
    }
}

void *bin_search(void *base, size_t nmemb, size_t size, void *key, int (*compar)(const void *, const void *))
{
    size_t low, high, middle;

    low = 0;
    high = nmemb - 1;
    
    while (low < high)
    {
        middle = low + (high - low) / 2;

        if (compar(key, (char *) base + middle * size) < 0)
            high = middle;
        else
            low = middle + 1;
    }

    return (char *) base + low * size;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src == pe_src || pb_dst == NULL || pe_dst == NULL)
        return DATA_ERROR;

    int *first_negp = (int *) pb_src;

    while (first_negp < pe_src && *first_negp >= 0)
        first_negp++;

    if (first_negp == pb_src)
        return FILTER_VOID_ERROR;

    if (create_arr(pb_dst, pe_dst, first_negp - pb_src) != OK)
        return ALLOC_ERROR;

    for (int *pa_dst = *pb_dst, *pa_src = (int *) pb_src; pa_dst < *pe_dst; pa_dst++, pa_src++)
        *pa_dst = *pa_src;

    return OK;
}
