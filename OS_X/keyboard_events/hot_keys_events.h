//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H
#define KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H

enum zoom_direction {
    kZoomIn,
    kZoomOut,
};
typedef enum zoom_direction zoom_direction_t;

enum rotate_direction {
    kRotateClockWise,
    kRotateCounterClockWise,
};
typedef enum rotate_direction rotate_direction_t;

enum swipe_direction {
    kSwipeLeft,
    kSwipeRight,
    kSwipeUp,
    kSwipeDown,
};
typedef enum swipe_direction swipe_direction_t;

// functions mimic common mouse gestures using hot keys
void zoom_hot_keys_event(zoom_direction_t zoom_direction);
void rotate_hot_keys_event(rotate_direction_t rotate_direction);
void swipe_hot_keys_event(swipe_direction_t swipe_direction);

#endif //KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H
