#include <stdio.h>
#include "mouse_events.h"

int main() {

    printf("Mouse Events in Windows\n");

    float x, y;

    mouse_position(&x, &y);
    printf("Current mouse position: {%f, %f}\n", x, y);

    // mouse_move_to(1350, 350);
    _mouse_move_to(1350, 350);

    return 0;
}