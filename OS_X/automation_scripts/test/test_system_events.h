//
// Created by Michal Ziobro on 08/10/2016.
//

#ifndef AUTOMATION_SCRIPTS_TEST_SYSTEM_EVENTS_H
#define AUTOMATION_SCRIPTS_TEST_SYSTEM_EVENTS_H

typedef struct {
    void (*run_tests)(void);
} test_system_events_t;

test_system_events_t test_system_events;

#endif //AUTOMATION_SCRIPTS_TEST_SYSTEM_EVENTS_H
