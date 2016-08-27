#include <stdio.h>
#include <unistd.h>
#include <CoreGraphics/CoreGraphics.h>
#include "mouse_events.h"
#include "scroll_wheel_events.h"

int main() {

    float x, y;

    /*
    printf("Hello, world!\n");
    mouse_position(&x, &y);
    printf("Current mouse position: {%f,%f}\n", x, y);
    mouse_move_to(500,500);
    sleep(1);
    mouse_position(&x, &y);
    printf("Current mouse position: {%f,%f}\n", x, y);
    mouse_move_to(800,500);
    sleep(1);
    mouse_position(&x, &y);
    printf("Current mouse position: {%f,%f}\n", x, y);
    mouse_move_to(500,800);
    sleep(1);
    mouse_position(&x, &y);
    printf("Current mouse position: {%f,%f}\n", x, y);
    mouse_move_to(200,100);
    sleep(1);
    mouse_position(&x, &y);
    printf("Current mouse position: {%f,%f}\n", x, y);
    mouse_move_to_eventless(1000, 500);
    //sleep(1);
    mouse_position(&x, &y);
    printf("Current mouse position: {%f,%f}\n", x, y);
    */

    /*
    for(int i=0; i<1000; i++) {
        usleep(10000);
        mouse_move_by(5, 5);
    }
    */

    /*
    mouse_left_click_at(300, 150);
    sleep(1);
    mouse_left_double_click_at(300, 150);
    sleep(1);
    mouse_left_triple_click_at(300, 150);
     */

    //mouse_right_click_at(300, 150);
    //mouse_right_double_click_at(300, 150);
    //mouse_right_triple_click_at(300, 150);

    //mouse_middle_click_at(300, 150);
    //mouse_middle_double_click_at(300, 150);
    //mouse_middle_triple_click_at(300, 150);

    /*
    while(1) {
        sleep(2);
        mouse_left_click();
    }
    */

    /*
    while(1) {
        sleep(2);
        mouse_right_click();
    }
    */

    /*
   while(1) {
       sleep(2);
       mouse_middle_click();
   }
   */

    /*
    while(1) {
        sleep(2);
        mouse_left_double_click();
    }
    */

    /*
    while(1) {
        sleep(2);
        mouse_right_double_click();
    }
    */

    /*
    while(1) {
        sleep(2);
        mouse_middle_double_click();
    }
    */

    /*
    while(1) {
        sleep(2);
        mouse_left_triple_click();
    }
    */

    /*
    while(1) {
        sleep(2);
        mouse_right_triple_click();
    }
    */

    /*
    while(1) {
        sleep(2);
        mouse_middle_triple_click();
    }
    */

    /*
    mouse_left_click_at(400.0, 200.0);          // get focus
    usleep(10000);

    mouse_left_click_down_at(400.0, 200.0);     // start dragging
    usleep(10000);
    mouse_left_drag_to(500.0, 400.0);           // continue dragging
    usleep(10000);
    mouse_left_drag_to(600.0, 500.0);
    usleep(10000);
    mouse_left_drag_to(700.0, 600.0);
    usleep(10000);
    mouse_left_drag_to(800.0, 700.0);
    usleep(10000);
    mouse_left_click_up_at(800.0, 700.0);       // stop dragging
    */

    /*
    mouse_left_click_at(400, 200);
    usleep(10000);

    mouse_left_click_down_at(400,200);
    sleep(1);
    mouse_left_drag_by(100,100);
    sleep(1);
    mouse_left_drag_by(100,100);
    sleep(1);
    mouse_left_drag_by(100,100);
    sleep(1);
    mouse_left_click_up_at(700,500);
    */

    /*
    while(1) {
        sleep(3);
        mouse_left_click_down();
        sleep(3);
        mouse_left_drag();
        mouse_left_click_up();
    }
    */

    /*
    for(int i=0; i<100; i++) {
        sleep(1);
        scroll_wheel_scroll_down(10);
    }
    */

    return 0;
}