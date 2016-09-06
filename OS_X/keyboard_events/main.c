#include "keyboard_events.h"
#include "virtual_key_codes.h"
#include "symbolic_hot_keys.h"
#include "hot_keys_events.h"

int main() {

    /*
    //key_down(kVK_Shift);
    key_down_modified(kVK_ANSI_C, kCGEventFlagMaskShift);
    //usleep(10000);
    key_up_modified(kVK_ANSI_C, kCGEventFlagMaskShift);
    //key_up(kVK_Shift);
    */

    //key_input(kVK_ANSI_C);

    /*
    key_down(kVK_Command);
    key_down(kVK_Shift);
    key_input_modified(kVK_ANSI_Minus, kCGEventFlagMaskCommand | kCGEventFlagMaskShift);
    key_up(kVK_Shift);
    key_up(kVK_Command);
    */

    /*
    for(int i=0; i<20; ++i) {
        key_input(kVK_ANSI_Z);
        key_input_modified(kVK_ANSI_B, kCGEventFlagMaskShift);
    }
    */

    //key_input_modified(kVK_Space, kCGEventFlagMaskCommand);

    /*
    while(1) {
        multi_key_input(3, kVK_Shift, kVK_Command, kVK_ANSI_Minus);
        sleep(2);
        multi_key_input(3, kVK_Shift, kVK_Command, kVK_ANSI_Equal);
        sleep(2);
    }
    */

    //multi_key_input(1, kVK_ANSI_E);

    //symbolic_hot_keys_event(kSHKShowSpotlightSearch);

    /*
    while(1) {
        sleep(3);
        //zoom_hot_keys_event(kZoomOut);
        zoom_hot_keys_event(kZoomIn);
    }
    */

    /*
    while(1) {
        sleep(3);
        //rotate_hot_keys_event(kRotateClockWise);
        rotate_hot_keys_event(kRotateCounterClockWise);
    }
    */

    /*
    while(1) {
        sleep(3);
        swipe_hot_keys_event(kSwipeLeft);
        sleep(3);
        swipe_hot_keys_event(kSwipeRight);
        sleep(3);
        swipe_hot_keys_event(kSwipeUp);
    }
    */  

    return 0;
}