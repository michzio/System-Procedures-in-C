//
// Created by Michal Ziobro on 08/10/2016.
//

#include "test_system_events.h"
#include "../system/events.h"

static void test_system_shutdown(void) { system_shutdown(); }
static void test_system_restart(void) { system_restart(); }
static void test_system_sleep(void) { system_sleep(); }
static void test_system_logout(void) { system_logout(); }

static void run_tests(void) {
    //test_system_shutdown();
    //test_system_restart();
    //test_system_sleep();
    //test_system_logout();
}

test_system_events_t test_system_events = { .run_tests = run_tests };