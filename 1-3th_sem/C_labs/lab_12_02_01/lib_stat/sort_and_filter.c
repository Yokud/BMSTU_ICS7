#include "sort_and_filter.h"


void swap(int8_t *a, int8_t *b, size_t size)
{
    for (; size > 0; size--)
    {
        int8_t temp = *a;
        *a++ = *b;
        *b++ = temp;
    }
}

// Сортировка вставками с бинарным поиском
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void *index;
    int8_t *pa, *pa_temp;

    if (!nmemb || base == NULL)
        return;

    pa = (int8_t *) base + size;

    while (pa < (int8_t *) base + nmemb * size)
    {
        index = bin_search(base, (pa - (int8_t *) base) / size + 1, size, pa, compar);
        
        swap(pa, index, size);

        pa_temp = pa; 
        while (pa_temp > (int8_t *) index + size)
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

        if (compar(key, (int8_t *) base + middle * size) < 0)
            high = middle;
        else
            low = middle + 1;
    }

    return (int8_t *) base + low * size;
}

int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src == pe_src || pb_dst == NULL || pe_dst == NULL)
        return DATA_ERROR;

    int *first_negp = (int *) pb_src;

    while (first_negp < pe_src && *first_negp >= 0)
        first_negp++;

    for (int *pa_dst = pb_dst, *pa_src = (int *) pb_src; pa_src < first_negp; pa_dst++, pa_src++)
        *pa_dst = *pa_src;

    return first_negp - pb_src;
}
