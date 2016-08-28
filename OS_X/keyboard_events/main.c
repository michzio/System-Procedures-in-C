#include "keyboard_events.h"
#include "virtual_key_codes.h"


void execute(void);

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

    multi_key_input(1, kVK_ANSI_E);

    return 0;
}