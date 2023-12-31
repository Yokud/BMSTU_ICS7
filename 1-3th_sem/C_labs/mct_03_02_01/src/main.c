#include "data_structure.h"


int main(void)
{
    inttype *arr;
    size_t len, rc;

    if ((rc = input(&arr, &len)))
        return rc;
    output(arr, len);

    del_elems_with_prime_indexes(&arr, &len);
    output(arr, len);

    set_len(&arr, len, 0);

    return rc;
}