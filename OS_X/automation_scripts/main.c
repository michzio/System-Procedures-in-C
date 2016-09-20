#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "system/windows.h"
#include "system/events.h"
#include "system/display.h"
#include "system/audio.h"

int main(void) {

    printf("Automation scripts\n");

    /*
    sleep(5);
    char *window_owner = front_window_owner();
    printf("front window owner: %s\n", window_owner);
    */

    //system_sleep();
    //system_shutdown();

    //display_set_brightness(1.0);
    //printf("Brightness level: %.2f\n", display_get_brightness());

    //audio_output_mute(true);

    /*
    printf("Output volume level - initial: %.2f\n", audio_output_get_volume());
    audio_output_set_volume(0.5);
    printf("Output volume level - after setting: %.2f\n", audio_output_get_volume());
    */

    /*
    printf("Output mute value - initial: %d\n", audio_output_is_muted());
    sleep(3);
    audio_output_mute(true);
    printf("Output mute value - after muting: %d\n", audio_output_is_muted());
    sleep(3);
    audio_output_mute(false);
    printf("Output mute value - after unmuting: %d\n", audio_output_is_muted());
    */

    //printf("Output volume level: %.2f\n", audio_output_get_volume());

    //audio_input_mute(true);
    //printf("Input mute value: %d\n", audio_input_is_muted());

    /*
    printf("Input volume level - initial: %.2f\n", audio_input_get_volume());
    audio_input_set_volume(0.5);
    printf("Input volume level - after setting: %.2f\n", audio_input_get_volume());
    */

    /*
    printf("Input mute value - initial: %d\n", audio_input_is_muted());
    sleep(3);
    audio_input_mute(true);
    printf("Input mute value - after muting: %d\n", audio_input_is_muted());
    sleep(3);
    audio_input_mute(false);
    printf("Input mute value - after unmuting: %d\n", audio_input_is_muted());
    */

    //printf("Input volume level: %.2f\n", audio_input_get_volume());

    display_capture();

    return 0;
}