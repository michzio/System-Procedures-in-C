#include <stdio.h>
#include <unistd.h>
#include "system/windows.h"
#include "system/events.h"
#include "system/display.h"

int main(void) {

    printf("Automation scripts\n");

    /*
    sleep(5);
    char *window_owner = front_window_owner();
    printf("front window owner: %s\n", window_owner);
    */

    //system_sleep();
    //system_shutdown();

    //display_set_brightness(1.0);
    printf("Brightness level: %.2f\n", display_get_brightness());
    return 0;
}