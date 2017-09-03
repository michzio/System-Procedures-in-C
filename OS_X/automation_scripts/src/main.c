#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <NSSystemDirectories.h>
#include "../include/system/windows.h"
#include "../include/system/events.h"
#include "../include/system/display.h"
#include "../include/system/audio.h"
#include "cocoa_helper/file_system.h"
#include "cocoa_helper/strings.h"
#include "../test/test_display.h"
#include "../test/test_windows.h"
#include "../test/test_system_events.h"
#include "../test/test_audio.h"
#include "../test/test_display_stream.h"
#include "../test/test_automation_scripts.h"

int main(void) {

    printf("Automation scripts\n");

    //display_screen_snapshot_to_desktop();
    //display_screen_snapshot_rect_to_desktop();
    //display_screen_snapshot_to_clipboard();
    //display_screen_snapshot_rect_to_clipboard();

    //test_display.run_tests();
    //test_windows.run_tests();
    //test_audio.run_tests();
    //test_system_events.run_tests();
    //test_display_stream.run_tests();
    test_automation_scripts.run_tests();

    return 0;
}