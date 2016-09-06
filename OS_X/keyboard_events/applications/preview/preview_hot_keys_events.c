//
// Created by Michal Ziobro on 06/09/2016.
//

#include "preview_hot_keys_events.h"
#include "../../virtual_key_codes.h"
#include "../../keyboard_events.h"
#include "../../symbolic_hot_keys.h"

void preview_rotate_hot_keys_event(rotate_direction_t rotate_direction) {

    switch (rotate_direction) {
        case kRotateClockWise:
            // hot keys: Cmd, R
            key_input_modified(kVK_ANSI_R, kMFCommand);
            break;
        case kRotateCounterClockWise:
            // hot keys: Cmd, L
            key_input_modified(kVK_ANSI_L, kMFCommand);
            break;
        default:
            return;
    }
}