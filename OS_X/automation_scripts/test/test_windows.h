//
// Created by Michal Ziobro on 08/10/2016.
//

#ifndef AUTOMATION_SCRIPTS_TEST_WINDOWS_H
#define AUTOMATION_SCRIPTS_TEST_WINDOWS_H

typedef struct {
    void (*run_tests)(void);
} test_windows_t;

test_windows_t test_windows;

#endif //AUTOMATION_SCRIPTS_TEST_WINDOWS_H
