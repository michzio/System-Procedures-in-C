//
// Created by Michal Ziobro on 08/10/2016.
//

#include <stdbool.h>
#include <printf.h>
#include <unistd.h>
#include "test_audio.h"
#include "../system/audio.h"
#include "../../../../unit_tests/test/assertion.h"

static void test_audio_output_mute(void) {

    audio_output_mute(true);
    assert_equal_int(audio_output_is_muted(), true, "audio output muted");

    audio_output_mute(false);
    assert_equal_int(audio_output_is_muted(), false, "audio output unmuted");
}

static void test_audio_input_mute(void) {

    audio_input_mute(true);
    assert_equal_int(audio_input_is_muted(), true, "audio input muted");

    audio_input_mute(false);
    assert_equal_int(audio_input_is_muted(), false, "audio input unmuted");
}

static void test_audio_output_volume(void) {

    float init_volume = 0.0f;
    float volume = 0.0f;

    // get current output volume
    volume = init_volume = audio_output_get_volume();
    printf("Output volume level - initial: %.2f\n", volume);

    // set half of current output volume
    audio_output_set_volume(init_volume*0.5);
    volume = audio_output_get_volume();

    assert_not_equal_int((int) (volume*100), (int) (init_volume*100), "Output volume changed!");
    assert_equal_int((int) (volume*100), (int) (init_volume*0.5*100), "Output volume reduced by half");
    printf("Output volume level - after setting: %.2f\n", volume);
    sleep(1);

    // reset output volume to previous value
    audio_output_set_volume(init_volume);
    volume =  audio_output_get_volume();

    assert_equal_int( (int) (volume*100), (int) (init_volume*100), "Output volume reset to init value!");
    printf("Output volume level - after resetting: %.2f\n", volume);
}

static void test_audio_input_volume(void) {

    float init_volume = 0.0f;
    float volume = 0.0f;

    // get current input volume
    volume = init_volume = audio_input_get_volume();
    printf("Input volume level - initial: %.2f\n", volume);

    // set half of current input volume
    audio_input_set_volume(init_volume*0.5);
    volume = audio_input_get_volume();

    assert_not_equal_int((int) (volume*100), (int) (init_volume*100), "Input volume changed!");
    assert_equal_int((int) (volume*100), (int) (init_volume*0.5*100), "Input volume reduced by half");
    printf("Input volume level - after setting: %.2f\n", volume);
    sleep(1);

    // reset input volume to previous value
    audio_input_set_volume(init_volume);
    volume = audio_input_get_volume();

    assert_equal_int((int) (volume*100), (int) (init_volume*100), "Input volume reset to init value!");
    printf("Input volume level - after resetting: %.2f\n", volume);
}

static void run_tests(void) {
    test_audio_output_mute();
    test_audio_input_mute();
    test_audio_output_volume();
    test_audio_input_volume();
}

test_audio_t test_audio = { .run_tests = run_tests };