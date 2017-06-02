#include <stdio.h>
#include <unistd.h>
#include "windows.h"

int main() {
    printf("Windows Helpers library!\n");

    sleep(3);
    printf("%s\n", front_window_owner());

    return 0;
}