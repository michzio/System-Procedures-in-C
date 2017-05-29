#include <stdio.h>
#include <unistd.h>
#include "keyboard_events.h"
#include "virtual_key_codes.h"

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
    return 0;
}


