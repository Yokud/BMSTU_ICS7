#include "my_string.h"
#include <string.h>

int main(void)
{    
    // TEST_01
    ///////////////////////////////////////////////////////////////////////////

    if (my_strpbrk("Deathclaw", "Death") != strpbrk("Deathclaw", "Death"))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }
   
    if (my_strspn("Deathclaw", "Death") != strspn("Deathclaw", "Death"))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strcspn("Deathclaw", "Death") != strcspn("Deathclaw", "Death"))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strchr("Deathclaw", 'l') != strchr("Deathclaw", 'l'))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strrchr("Deathclaw", 'l') != strrchr("Deathclaw", 'l'))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    ///////////////////////////////////////////////////////////////////////////

    // TEST_02
    ///////////////////////////////////////////////////////////////////////////

    if (my_strpbrk("", "") != strpbrk("", ""))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }
   
    if (my_strspn("", "") != strspn("", ""))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strcspn("", "") != strcspn("", ""))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strchr("", '\0') != strchr("", '\0'))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strrchr("", '\0') != strrchr("", '\0'))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    ///////////////////////////////////////////////////////////////////////////

    // TEST_03
    ///////////////////////////////////////////////////////////////////////////

    if (my_strpbrk("The Transcendent One", "NCR") != strpbrk("The Transcendent One", "NCR"))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }
   
    if (my_strspn("The Transcendent One", "NCR") != strspn("The Transcendent One", "NCR"))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strcspn("The Transcendent One", "NCR") != strcspn("The Transcendent One", "NCR"))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strchr("The Transcendent One", 'b') != strchr("The Transcendent One", 'b'))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    if (my_strrchr("The Transcendent One", 'b') != strrchr("The Transcendent One", 'b'))
    {
        puts("Results do not coincide\n");
        return EXIT_FAILURE;
    }

    ///////////////////////////////////////////////////////////////////////////

    return EXIT_SUCCESS;
}