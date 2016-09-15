#include "keyboard_events.h"
#include "virtual_key_codes.h"
#include "symbolic_hot_keys.h"
#include "hot_keys_events.h"
#include "../automation_scripts/system/windows.h"

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
        zoom_hot_keys_event(kZoomOut);
        //zoom_hot_keys_event(kZoomIn);
    }
    */

    /*
    while(1) {
        sleep(3);
        rotate_hot_keys_event(kRotateClockWise);
        //rotate_hot_keys_event(kRotateCounterClockWise);
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

    //sleep(5);
    //zoom_actual_size_hot_keys_event();

    //sleep(5);
    //enter_full_screen_hot_keys_event();

    /*
    while(1) {
        sleep(5);
        player_play_hot_keys_event();
    }
    */

    //sleep(5);
    //player_stop_hot_keys_event();

    //sleep(5);
    //player_next_hot_keys_event();

    //sleep(5);
    //player_previous_hot_keys_event();

    /*
    sleep(3);
    while(1) {
        sleep(1);
        //player_step_forward_hot_keys_event();
        player_step_backward_hot_keys_event();
    }
    */

    /*
    while(1) {
        sleep(3);
        //player_volume_up_hot_keys_event();
        //player_volume_down_hot_keys_event();
        player_mute_hot_keys_event();
    }
    */

    //sleep(10);
    //browser_new_tab_hot_keys_event();
    //browser_next_tab_hot_keys_event();
    //browser_prev_tab_hot_keys_event();
    //browser_add_bookmark_hot_keys_event();
    //browser_new_private_window_hot_keys_event();
    //browser_reopen_closed_tab_hot_keys_event();
    //browser_open_file_hot_keys_event();
    //browser_open_location_hot_keys_event();
    //browser_close_tab_hot_keys_event();
    //browser_close_window_hot_keys_event();
    //browser_emoji_hot_keys_event();
    //browser_reload_page_hot_keys_event();
    //browser_show_downloads_hot_keys_event();
    //browser_show_history_hot_keys_event();
    //browser_show_sidebar_hot_keys_event();
    //browser_show_page_source_hot_keys_event();
    //browser_home_page_hot_keys_event();
    //slide_show_start_hot_keys_event();
    //slide_show_end_hot_keys_event();
    //slide_show_next_hot_keys_event();
    //slide_show_next_no_animation_hot_keys_event();
    //slide_show_previous_hot_keys_event();
    //slide_show_previous_no_animation_hot_keys_event();
    //slide_show_blank_black_slide_hot_keys_event();
    //slide_show_blank_white_slide_hot_keys_event();
    //slide_show_first_slide_hot_keys_event();
    //slide_show_last_slide_hot_keys_event();
    //slide_show_hide_cursor_hot_keys_event();
    //slide_show_slide_number_hot_keys_event();
    //slide_show_go_to_next_hidden_slide_hot_keys_event();
    //slide_show_pen_pointer_hot_keys_event();
    //slide_show_arrow_pointer_hot_keys_event();

    //printf("%s\n", front_window_owner());
    printf("%d\n", kVK_ANSI_A);
    printf("Cmd: %d\n", kMFCommand);
    printf("Cmd + Opt: %d\n", kMFCommand + kMFOption);
    printf("Cmd + Shift: %d\n", kMFCommand + kMFShift);
    printf("Cmd + Shift + Opt: %d\n", kMFCommand + kMFShift + kMFOption);
    printf("Ctrl + Opt + Cmd: %d\n", kMFControl + kMFOption + kMFCommand);
    printf("Ctrl + Cmd: %d\n", kMFControl + kMFCommand);
    printf("Ctrl + Cmd + Shift: %d\n", kMFControl + kMFCommand + kMFShift);
    printf("Opt: %d\n", kMFOption);
    printf("Ctrl: %d\n", kMFControl);
    printf("Fn: %d\n", kMFFunction);
    printf("Shift: %d\n", kMFShift);
    printf("Cmd + Fn: %d\n", kMFCommand + kMFFunction);
    printf("Ctrl + Shift: %d\n", kMFControl + kMFShift);

    return 0;
}