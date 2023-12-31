#include <stdlib.h>
#include <check.h>


Suite* sort_and_key_suite(void);

int main(void)
{
    int success = 0;
    Suite *s;
    SRunner *runner;

    s = sort_and_key_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    success = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (success == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}