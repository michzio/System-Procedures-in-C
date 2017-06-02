#include <stdio.h>
#include <unistd.h>
#include "keyboard_events.h"
#include "virtual_key_codes.h"
#include "hot_keys_events.h"

int main() {
    printf("Keyboard Events Library\n");

    //key_down(0x41);
    //key_up(0x41);
    sleep(3);
    //key_input_modified(kVK_ANSI_O, kMFRightAlt);
    //key_input_modified(kVK_ANSI_A, kMFRightAlt);
    //key_input_modified(kVK_ANSI_S, kMFRightAlt);
    //key_input_modified(kVK_ANSI_N, kMFRightAlt);

    //multi_key_down(2, kVK_ANSI_O, kVK_RightAlt);
    //multi_key_up(2, kVK_ANSI_O, kVK_RightAlt);
    //multi_key_input(2, kVK_ANSI_O, kVK_RightAlt);
    //key_input(kVK_F2);
    //key_input_modified(9, 786432);
    /*
    for(int i=0; i<10; i++) {
        sleep(3);
        //multi_key_input(2, kVK_Control, kVK_MouseScrollUp);
        //multi_key_input(2, kVK_Control, kVK_MouseScrollDown);
    }
    */

    //key_hold_down_modified(kVK_ANSI_Comma, kMFWindows, 3);

    //system_hot_keys_event(kShowDesktopHotKeys);
    //front_app_hot_keys_event(kZoomOutHotKeys, true);

    player_play_hot_keys_event();
    enter_full_screen_hot_keys_event();

    return 0;
}
