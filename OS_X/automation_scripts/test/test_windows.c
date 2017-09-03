//
// Created by Michal Ziobro on 08/10/2016.
//

#include <printf.h>
#include "test_windows.h"
#include "test/assertion.h"
#include "comparer.h"
#include "system/windows.h"

static void test_front_window_owner(void) {
    char *window_owner = front_window_owner();
    printf("Front window owner is: %s\n", window_owner);
    assert_equal(window_owner, "CLion", str_cmp_func, __func__);
}

static void run_tests(void) {
    test_front_window_owner();
}

test_windows_t test_windows = { .run_tests = run_tests };