#include <stdio.h>
#include <stdlib.h>
#include "list_type.h"
#include "rectangles.h"


#define ARGS_ERROR 2
#define ALLOC_ERROR 3

int main(int argc, char **argv)
{
    int n;
    FILE *f;
    node_t *rectangles = NULL;

    if (argc != 2)
        return ARGS_ERROR;

    if (!(f = fopen(argv[1], "r")))
        return INPUT_ERROR;

    if (fscanf(f, "%d", &n) != 1 || n <= 0)
    {
        fclose(f);
        return INPUT_ERROR;
    }

    rect_t *rectangles_array = malloc(n * sizeof(rect_t));

    if (!rectangles_array)
    {
        fclose(f);
        return ALLOC_ERROR;
    }

    for (int i = 0; i < n; i++)
    {
        if (fread_rect(f, &rectangles_array[i]))
        {
            free_list(rectangles);
            free(rectangles_array);
            fclose(f);
            return INPUT_ERROR;
        }
        rectangles = push_back(rectangles, (void *) &rectangles_array[i]);
    }

    rectangles = reverse(rectangles);

    print_list(rectangles, print_rect);
    free_list(rectangles);
    free(rectangles_array);
    fclose(f);

    return EXIT_SUCCESS;
}