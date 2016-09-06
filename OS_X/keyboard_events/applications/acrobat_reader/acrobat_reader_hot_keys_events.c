//
// Created by Michal Ziobro on 06/09/2016.
//
#include "acrobat_reader_hot_keys_events.h"
#include "../../virtual_key_codes.h"
#include "../../symbolic_hot_keys.h"
#include "../../keyboard_events.h"

void acrobat_reader_rotate_hot_keys_event(rotate_direction_t rotate_direction) {

    switch (rotate_direction) {
        case kRotateClockWise:
            // hot keys: Cmd, Shift, + (=)
            key_input_modified(kVK_ANSI_Equal, kMFCommand | kMFShift);
            break;
        case kRotateCounterClockWise:
            // hot keys: Cmd, Shift, -
            key_input_modified(kVK_ANSI_Minus, kMFCommand | kMFShift);
            break;
        default:
            return;
    }
}