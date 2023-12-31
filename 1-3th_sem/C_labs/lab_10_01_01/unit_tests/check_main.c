#include <check.h>
#include <stdlib.h>

Suite *list_funcs_suite(void);

int main(void)
{
    int success = 0;
    Suite *s;
    SRunner *runner;

    s = list_funcs_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    success = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (success == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}