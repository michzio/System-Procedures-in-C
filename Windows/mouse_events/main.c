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
    //_mouse_move_to(0,0);
    //_mouse_move_by(1000, 700);
    //mouse_left_click();
    //mouse_left_click_at(100,700);
    //mouse_right_click();
    //mouse_right_click_at(1050, 875);
    //mouse_middle_click();
    //mouse_middle_click_at(300, 230);
    //mouse_left_double_click();
    //mouse_left_double_click_at(900, 160);
    //mouse_right_double_click();
    //mouse_right_double_click_at(900, 160);
    //mouse_middle_double_click();
    //mouse_middle_double_click_at(900, 160);
    //mouse_left_triple_click();
    //mouse_left_triple_click_at(900, 160);
    //mouse_right_triple_click();
    //mouse_right_triple_click_at(900, 160);
    //mouse_middle_triple_click();
    //mouse_middle_triple_click_at(900, 160);
    //mouse_left_click_down();
    //mouse_left_click_down_at(50, 250);
    //mouse_right_click_down();
    //mouse_right_click_down_at(50, 250);
    //mouse_middle_click_down();
    //mouse_middle_click_down_at(1090, 500);
    //mouse_left_click_up();
    //mouse_left_click_up_at(50,250);
    //mouse_right_click_up();
    //mouse_right_click_up_at(50,250);
    //mouse_middle_click_up();
    //mouse_middle_click_up_at(1090, 500);
    mouse_left_drag_by(50,100);
    //mouse_left_drag_to(100,600);
    //mouse_right_drag_by(150,150);
    //mouse_middle_drag_by(150, 150);

    return 0;
}