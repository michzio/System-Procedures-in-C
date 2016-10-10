//
// Created by Michal Ziobro on 10/10/2016.
//

#ifndef AUTOMATION_SCRIPTS_TEST_DISPLAY_STREAM_H
#define AUTOMATION_SCRIPTS_TEST_DISPLAY_STREAM_H

typedef struct {
    void (*run_tests)(void);
} test_display_stream_t;

extern test_display_stream_t test_display_stream;

#endif //AUTOMATION_SCRIPTS_TEST_DISPLAY_STREAM_H
