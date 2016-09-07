//
// Created by Michal Ziobro on 28/08/2016.
//

#include "hot_keys_events.h"
#include "keyboard_events.h"
#include "symbolic_hot_keys.h"
#include "../automation_scripts/system/windows.h"
#include "../cocoa_helper/property_list.h"

static const CFStringRef kHotKeysPlist = CFSTR("resources/hotkeys.plist");
static const CFStringRef kDefaultApplicationKey = CFSTR("Default Application");
static const CFStringRef kVirtualKeyCodeKey = CFSTR("key_code");
static const CFStringRef kModifierKeysFlagsKey = CFSTR("modifier_flags");

static hot_keys_t *hot_keys_get(const char *hot_keys_name, const char *application_name, bool consider_default) {

    // get property list of hot keys
    CFPropertyListRef plist = CFPropertyListCopyFromFileInMainBundle(kHotKeysPlist);
    // make sure property list is a dictionary
    if( CFGetTypeID(plist) != CFDictionaryGetTypeID() ) {
        fprintf(stderr, "%s: property list is not of the dictionary type.\n", __func__);
        return NULL;
    }

    CFStringRef hot_keys_name_key = CFStringCreateWithCString(kCFAllocatorDefault, hot_keys_name, kCFStringEncodingUTF8);
    CFDictionaryRef hot_keys_dict = CFDictionaryGetValue(plist, hot_keys_name_key);
    CFRelease(hot_keys_name_key);
    if(hot_keys_dict == NULL) {
        fprintf(stderr, "%s: Could not get hot keys value for given hot keys name key from property list.\n", __func__);
        return NULL;
    }

    CFStringRef application_name_key = CFStringCreateWithCString(kCFAllocatorDefault, application_name, kCFStringEncodingUTF8);
    CFDictionaryRef app_hot_keys_dict = CFDictionaryGetValue(hot_keys_dict, application_name_key);
    CFRelease(application_name_key);
    if(app_hot_keys_dict == NULL) {
        fprintf(stderr, "%s: Could not get app hot keys value for given application name key from property list.\n", __func__);
        // try get default hot keys combination if user consider it
        if(consider_default) {
            CFDictionaryRef default_hot_keys_dict = CFDictionaryGetValue(hot_keys_dict, kDefaultApplicationKey);
            if(default_hot_keys_dict == NULL) {
                fprintf(stderr, "%s: Could not get default hot keys value for default application name key from property list.\n", __func__);
                return NULL;
            }
            app_hot_keys_dict = default_hot_keys_dict;
        } else {
            return NULL;
        }
    }

    CFNumberRef hk_virtual_key_code = CFDictionaryGetValue(app_hot_keys_dict, kVirtualKeyCodeKey);
    CFNumberRef hk_modifier_keys_flags = CFDictionaryGetValue(app_hot_keys_dict, kModifierKeysFlagsKey);

    int64_t virtual_key_code; CFNumberGetValue(hk_virtual_key_code, kCFNumberSInt64Type, &virtual_key_code);
    int64_t modifier_keys_flags; CFNumberGetValue(hk_modifier_keys_flags, kCFNumberSInt64Type, &modifier_keys_flags);

    hot_keys_t *hot_keys = malloc(sizeof(hot_keys_t));
    hot_keys->virtual_key_code = virtual_key_code;
    hot_keys->modifier_keys_flags = modifier_keys_flags;

    return hot_keys;
}

void front_app_hot_keys_event(const char *hot_keys_name, bool consider_default) {

    char *application_name = front_window_owner();
    hot_keys_t *hk = hot_keys_get(hot_keys_name, application_name, consider_default);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name and front application (if considered, including default hot keys definition).\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

void app_hot_keys_event(const char *hot_keys_name, const char *application_name, bool consider_default) {

    hot_keys_t *hk = hot_keys_get(hot_keys_name, application_name, consider_default);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name and application name (if considered, including default hot keys definition).\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

// functions mimic common mouse gestures using hot keys
void zoom_hot_keys_event(zoom_direction_t zoom_direction) {

    switch (zoom_direction) {
        case kZoomIn:
            front_app_hot_keys_event(kZoominHotKeys, true);
            break;
        case kZoomOut:
            front_app_hot_keys_event(kZoomOutHotKeys, true);
            break;
        default:
            return;
    }
}

void rotate_hot_keys_event(rotate_direction_t rotate_direction) {

    switch (rotate_direction) {
        case kRotateClockWise:
            front_app_hot_keys_event(kRotateCWHotKeys, false);
            break;
        case kRotateCounterClockWise:
            front_app_hot_keys_event(kRotateCCWHotKeys, false);
            break;
        default:
            return;
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

// other common hot keys
void zoom_actual_size_hot_keys_event(void) {
    front_app_hot_keys_event(kZoomActualSizeHotKeys, true);
}
void enter_full_screen_hot_keys_event(void) {
    front_app_hot_keys_event(kEnterFullScreenHotKeys, true);
}
void player_play_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerPlayHotKeys, true);
}
void player_stop_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerStopHotKeys, true);
}
void player_next_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerNextHotKeys, true);
}
void player_previous_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerPreviousHotKeys, true);
}
void player_step_forward_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerStepForwardHotKeys, true);
}
void player_step_backward_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerStepBackwardHotKeys, true);
}
void player_loop_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerLoopHotKeys, true);
}
void player_volume_up_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerVolumeUpHotKeys, true);
}
void player_volume_down_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerVolumeDownHotKeys, true);
}
void player_mute_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerMuteHotKeys, true);
}