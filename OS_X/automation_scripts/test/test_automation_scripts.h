//
// Created by Michal Ziobro on 22/10/2016.
//

#ifndef AUTOMATION_SCRIPTS_TEST_AUTOMATION_SCRIPTS_H
#define AUTOMATION_SCRIPTS_TEST_AUTOMATION_SCRIPTS_H

typedef struct {
    void (*run_tests)(void);
} test_automation_scripts_t;

test_automation_scripts_t test_automation_scripts;

#endif //AUTOMATION_SCRIPTS_TEST_AUTOMATION_SCRIPTS_H
