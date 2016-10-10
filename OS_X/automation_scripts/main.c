#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <NSSystemDirectories.h>
#include "system/windows.h"
#include "system/events.h"
#include "system/display.h"
#include "system/audio.h"
#include "../cocoa_helper/file_system.h"
#include "../cocoa_helper/strings.h"
#include "test/test_display.h"
#include "test/test_windows.h"
#include "test/test_system_events.h"
#include "test/test_audio.h"
#include "test/test_display_stream.h"

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
    test_display_stream.run_tests();

    return 0;
}