//
// Created by Michal Ziobro on 08/10/2016.
//

#ifndef AUTOMATION_SCRIPTS_TEST_DISPLAY_H
#define AUTOMATION_SCRIPTS_TEST_DISPLAY_H

typedef struct {
    void (*run_tests)(void);
} test_display_t;

extern test_display_t test_display;

#endif //AUTOMATION_SCRIPTS_TEST_DISPLAY_H
