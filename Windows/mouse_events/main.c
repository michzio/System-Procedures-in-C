#include <stdio.h>
#include "mouse_events.h"

int main() {

    printf("Mouse Events in Windows\n");

    float x, y;

    mouse_position(&x, &y);
    printf("Current mouse position: {%f, %f}\n", x, y);

    // mouse_move_to(1350, 350);
    //_mouse_move_to(1350, 350);
    //mouse_move_to(0,0);
    //mouse_move_by(1400,700);
    _mouse_move_to(0,0);
    _mouse_move_by(1400, 700);

    return 0;
}