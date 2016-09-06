#include <stdio.h>
#include <unistd.h>
#include "system/windows.h"

int main(void) {

    printf("Automation scripts\n");

    sleep(5);
    char *window_owner = front_window_owner();
    printf("front window owner: %s\n", window_owner);

    printf("\a\n");
    return 0;
}