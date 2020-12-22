#include "../lib/minunit.h"
#include "../lib/dbg.h"
#include "../lib/bstrlib.h"

#include <dlfcn.h>
#include <stdint.h>

const char *lib_file = "build/libconnect4.so";
void *lib = NULL;

char *test_dlopen() {
    lib = dlopen(lib_file, RTLD_LAZY | RTLD_GLOBAL);
    mu_assert(lib != NULL, "Failed to open library for testing!");

    return NULL;
}

char *test_top_mask() {

    typedef uint_fast64_t (*column_mask_func) (int col);
    column_mask_func func = dlsym(lib, "top_mask");

    // Testing 0 column
    mu_assert(func(0) == 32,
              "top_mask did not return 0 column mask properly!");

    // Testing nonzero column (3rd column)
    mu_assert(func(2) == 524288,
              "top_mask did not return nonzero column mask properly!");

    // Testing <0 invalid column
    mu_assert(func(-12) == 0,
              "top_mask did not fail to mask an invalid subzero column!");

    //Testing >BOARD_WIDTH-1 invalid column
    mu_assert(func(8) == 0,
             "top_mask did not fail to mask an invalid too-wide column!");

    return NULL;
}

char *test_bottom_mask() {

    typedef uint_fast64_t (*column_mask_func) (int col);
    column_mask_func func = dlsym(lib, "bottom_mask");

    // Testing 0 column
    mu_assert(func(0) == 1,
              "bottom_mask did not return 0 column mask properly!");

    // Testing nonzero column (3rd column)
    mu_assert(func(2) == 16384,
              "bottom_mask did not return nonzero column mask properly!");

    // Testing <0 invalid column
    mu_assert(func(-12) == 0,
              "bottom_mask did not fail to mask an invalid subzero column!");

    //Testing >BOARD_WIDTH-1 invalid column
    mu_assert(func(8) == 0,
              "bottom_mask did not fail to mask an invalid too-wide column!");

    return NULL;
}

char *test_dlclose() {
    int rc = dlclose(lib);
    mu_assert(rc == 0, "Failed to close library after testing.");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_dlopen);
    mu_run_test(test_top_mask);
    mu_run_test(test_bottom_mask);
    mu_run_test(test_dlclose);

    return NULL;
}

RUN_TESTS(all_tests);


