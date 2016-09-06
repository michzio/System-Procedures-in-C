//
// Created by Michal Ziobro on 28/08/2016.
//

#include "hot_keys_events.h"
#include "keyboard_events.h"
#include "virtual_key_codes.h"
#include "symbolic_hot_keys.h"
#include "../automation_scripts/system/windows.h"
#include "applications/photos/photos_hot_keys_events.h"
#include "applications/preview/preview_hot_keys_events.h"
#include "applications/acrobat_reader/acrobat_reader_hot_keys_events.h"

void zoom_hot_keys_event(zoom_direction_t zoom_direction) {

    switch (zoom_direction) {
        case kZoomIn:
            // hot keys: Cmd, + (=)
            key_input_modified(kVK_ANSI_Equal, kMFCommand);
            break;
        case kZoomOut:
            // hot keys: Cmd, -
            key_input_modified(kVK_ANSI_Minus, kMFCommand);
            break;
        default:
            return;
    }
}

void rotate_hot_keys_event(rotate_direction_t rotate_direction) {

    // different hot keys combinations in different applications
    char *window_owner = front_window_owner();
    if (strcmp(window_owner, "Photos") == 0) {
        photos_rotate_hot_keys_event(rotate_direction);
    } else if (strcmp(window_owner, "Preview") == 0) {
        preview_rotate_hot_keys_event(rotate_direction);
    } else if (strcmp(window_owner, "Acrobat Reader") == 0) {
        acrobat_reader_rotate_hot_keys_event(rotate_direction);
    }
}

void swipe_hot_keys_event(swipe_direction_t swipe_direction) {

    switch (swipe_direction) {

        case kSwipeUp:
            symbolic_hot_keys_event(kSHKMissionControl);
            break;
        case kSwipeLeft:
            symbolic_hot_keys_event(kSHKMoveRightASpace);
            break;
        case kSwipeRight:
            symbolic_hot_keys_event(kSHKMoveLeftASpace);
            break;
        default:
            return;
    }
}