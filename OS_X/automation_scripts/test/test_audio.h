//
// Created by Michal Ziobro on 08/10/2016.
//

#ifndef AUTOMATION_SCRIPTS_TEST_AUDIO_H
#define AUTOMATION_SCRIPTS_TEST_AUDIO_H

typedef struct {
    void (*run_tests)(void);
} test_audio_t;

test_audio_t test_audio;

#endif //AUTOMATION_SCRIPTS_TEST_AUDIO_H
