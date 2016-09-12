//
// Created by Michal Ziobro on 28/08/2016.
//

#include "hot_keys_events.h"
#include "keyboard_events.h"
#include "symbolic_hot_keys.h"
#include "../automation_scripts/system/windows.h"
#include "../cocoa_helper/property_list.h"
#include "virtual_key_codes.h"

static const CFStringRef kSystemHotKeysPlist = CFSTR("resources/system_hotkeys.plist");
static const CFStringRef kApplicationHotKeysPlist = CFSTR("resources/application_hotkeys.plist");
static const CFStringRef kDefaultApplicationKey = CFSTR("Default Application");
static const CFStringRef kVirtualKeyCodeKey = CFSTR("key_code");
static const CFStringRef kModifierKeysFlagsKey = CFSTR("modifier_flags");
static const CFStringRef kHoldTimeInSKey = CFSTR("hold_time_in_s");

static hot_keys_t *hot_keys_get(CFDictionaryRef hot_keys_dict) {

    CFNumberRef hk_virtual_key_code = CFDictionaryGetValue(hot_keys_dict, kVirtualKeyCodeKey);
    CFNumberRef hk_modifier_keys_flags = CFDictionaryGetValue(hot_keys_dict, kModifierKeysFlagsKey);
    CFNumberRef hk_hold_time_in_s = CFDictionaryGetValue(hot_keys_dict, kHoldTimeInSKey);

    int16_t virtual_key_code; CFNumberGetValue(hk_virtual_key_code, kCFNumberSInt16Type, &virtual_key_code);
    int64_t modifier_keys_flags; CFNumberGetValue(hk_modifier_keys_flags, kCFNumberSInt64Type, &modifier_keys_flags);
    int32_t hold_time_in_s; if(hk_hold_time_in_s != NULL) CFNumberGetValue(hk_hold_time_in_s, kCFNumberSInt32Type, &hold_time_in_s);

    hot_keys_t *hot_keys = malloc(sizeof(hot_keys_t));
    hot_keys->virtual_key_code = virtual_key_code;
    hot_keys->modifier_keys_flags = modifier_keys_flags;
    hot_keys->hold_time_in_s = hold_time_in_s;

    return hot_keys;
}

static hot_keys_t *system_hot_keys_get(const char *hot_keys_name) {

    // get property list of hot keys
    CFPropertyListRef plist = CFPropertyListCopyFromFileInMainBundle(kSystemHotKeysPlist);
    // make sure property list is a dictionary
    if( CFGetTypeID(plist) != CFDictionaryGetTypeID()) {
        fprintf(stderr, "%s: property list is not of the dictionary type.\n", __func__);
        return NULL;
    }

    CFStringRef hot_keys_name_key = CFStringCreateWithCString(kCFAllocatorDefault, hot_keys_name, kCFStringEncodingUTF8);
    CFDictionaryRef sys_hot_keys_dict = CFDictionaryGetValue(plist, hot_keys_name_key);
    CFRelease(hot_keys_name_key);
    if(sys_hot_keys_dict == NULL) {
        fprintf(stderr, "%s: Could not get system hot keys value for given hot keys name key from property list.\n", __func__);
        return NULL;
    }

    return hot_keys_get(sys_hot_keys_dict);
}

static hot_keys_t *app_hot_keys_get(const char *hot_keys_name, const char *application_name, bool consider_default) {

    // get property list of hot keys
    CFPropertyListRef plist = CFPropertyListCopyFromFileInMainBundle(kApplicationHotKeysPlist);
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

    return hot_keys_get(app_hot_keys_dict);
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

void scroll_hot_keys_event(scroll_direction_t scroll_direction) {

    switch (scroll_direction) {
        case kScrollUp:
            key_input(kVK_UpArrow);
            break;
        case kScrollDown:
            key_input(kVK_DownArrow);
            break;
        case kScrollLeft:
            key_input(kVK_LeftArrow);
            break;
        case kScrollRight:
            key_input(kVK_RightArrow);
            break;
        default:
            return;
    }
}

// macOS system hot keys
void system_hot_keys_event(const char *hot_keys_name) {

    hot_keys_t *hk = system_hot_keys_get(hot_keys_name);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name.\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

// application hot keys
void front_app_hot_keys_event(const char *hot_keys_name, bool consider_default) {

    char *application_name = front_window_owner();
    hot_keys_t *hk = app_hot_keys_get(hot_keys_name, application_name, consider_default);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name and front application (if considered, including default hot keys definition).\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

void app_hot_keys_event(const char *hot_keys_name, const char *application_name, bool consider_default) {

    hot_keys_t *hk = app_hot_keys_get(hot_keys_name, application_name, consider_default);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name and application name (if considered, including default hot keys definition).\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

// video & audio players common hot keys
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

// browser common hot keys
void browser_new_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserNewTabHotKeys, true);
}
void browser_next_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserNextTabHotKeys, true);
}
void browser_prev_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserPreviousTabHotKeys, true);
}
void browser_add_bookmark_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserAddBookmarkHotKeys, true);
}
void browser_new_private_window_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserNewPrivateWindowHotKeys, true);
}
void browser_reopen_closed_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserReopenClosedTabHotKeys, true);
}
void browser_open_file_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserOpenFileHotKeys, true);
}
void browser_open_location_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserOpenLocationHotKeys, true);
}
void browser_close_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserCloseTabHotKeys, true);
}
void browser_close_window_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserCloseWindowHotKeys, true);
}
void browser_emoji_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserEmojiHotKeys, true);
}
void browser_reload_page_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserReloadPageHotKeys, true);
}
void browser_show_downloads_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowDownloadsHotKeys, true);
}
void browser_show_history_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowHistoryHotKeys, true);
}
void browser_show_sidebar_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowSidebarHotKeys, true);
}
void browser_show_page_source_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowPageSourceHotKeys, true);
}
void browser_home_page_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserHomePageHotKeys, true);
}

// slide show common hot keys
void slide_show_start_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowStartHotKeys, true);
}
void slide_show_end_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowEndHotKeys, true);
}
void slide_show_next_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowNextHotKeys, true);
}
void slide_show_next_no_animation_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowNextNoAnimationHotKeys, true);
}
void slide_show_previous_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPreviousHotKeys, true);
}
void slide_show_previous_no_animation_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPreviousNoAnimationHotKeys, true);
}
void slide_show_blank_black_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowBlankBlackSlideHotKeys, true);
}
void slide_show_blank_white_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowBlankWhiteSlideHotKeys, true);
}
void slide_show_pause_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPauseHotKeys, true);
}
void slide_show_first_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowFirstSlideHotKeys, true);
}
void slide_show_last_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowLastSlideHotKeys, true);
}
void slide_show_hide_cursor_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowHideCursorHotKeys, true);
}
void slide_show_slide_number_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowSlideNumberHotKeys, true);
}
void slide_show_go_to_next_hidden_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowGoToNextHiddenSlideHotKeys, true);
}
void slide_show_pen_pointer_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPenPointerHotKeys, true);
}
void slide_show_arrow_pointer_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowArrowPointerHotKeys, true);
}


// other common hot keys
void zoom_actual_size_hot_keys_event(void) {
    front_app_hot_keys_event(kZoomActualSizeHotKeys, true);
}
void enter_full_screen_hot_keys_event(void) {
    front_app_hot_keys_event(kEnterFullScreenHotKeys, true);
}