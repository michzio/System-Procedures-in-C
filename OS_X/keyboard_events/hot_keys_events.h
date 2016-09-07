//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H
#define KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H

#include <stdint.h>
#include <stdbool.h>

struct hot_keys {
    int64_t virtual_key_code;       // virtual key code for the character
    int64_t modifier_keys_flags;    // the sum of modifier key flags: Shift 17 bit, Ctrl 18 bit, Opt 19 bit, Cmd 20 bit
};
typedef struct hot_keys hot_keys_t;

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

void front_app_hot_keys_event(const char *hot_keys_name, bool consider_default);
void app_hot_keys_event(const char *hot_keys_name, const char *application_name, bool consider_default);

// functions mimic common mouse gestures using hot keys
void zoom_hot_keys_event(zoom_direction_t zoom_direction);
void rotate_hot_keys_event(rotate_direction_t rotate_direction);
void swipe_hot_keys_event(swipe_direction_t swipe_direction);

// other common hot keys
void zoom_actual_size_hot_keys_event(void);
void enter_full_screen_hot_keys_event(void);
void player_play_hot_keys_event(void);
void player_stop_hot_keys_event(void);
void player_next_hot_keys_event(void);
void player_previous_hot_keys_event(void);
void player_step_forward_hot_keys_event(void);
void player_step_backward_hot_keys_event(void);
void player_loop_hot_keys_event(void);
void player_volume_up_hot_keys_event(void);
void player_volume_down_hot_keys_event(void);
void player_mute_hot_keys_event(void);

// constant hot keys names
static const char *kDefaultApplication = "Default Application";
static const char *kZoomOutHotKeys = "ZoomOutHotKeys";
static const char *kZoominHotKeys = "ZoomInHotKeys";
static const char *kRotateCCWHotKeys = "RotateCCWHotKeys";
static const char *kRotateCWHotKeys = "RotateCWHotKeys";
static const char *kZoomActualSizeHotKeys = "ZoomActualSizeHotKeys";
static const char *kEnterFullScreenHotKeys = "EnterFullScreenHotKeys";
static const char *kPlayerPlayHotKeys = "PlayerPlayHotKeys";
static const char *kPlayerStopHotKeys = "PlayerStopHotKeys";
static const char *kPlayerNextHotKeys = "PlayerNextHotKeys";
static const char *kPlayerPreviousHotKeys = "PlayerPreviousHotKeys";
static const char *kPlayerStepForwardHotKeys = "PlayerStepForwardHotKeys";
static const char *kPlayerStepBackwardHotKeys = "PlayerStepBackwardHotKeys";
static const char *kPlayerLoopHotKeys = "PlayerLoopHotKeys";
static const char *kPlayerVolumeUpHotKeys = "PlayerVolumeUpHotKeys";
static const char *kPlayerVolumeDownHotKeys = "PlayerVolumeDownHotKeys";
static const char *kPlayerMuteHotKeys = "PlayerMuteHotKeys";

#endif //KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H