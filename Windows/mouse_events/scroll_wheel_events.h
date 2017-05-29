//
// Created by Michal Ziobro on 29.05.2017.
//
#include <windows.h>

#ifndef MOUSE_EVENTS_IN_WINDOWS_SCROLL_WHEEL_EVENTS_H
#define MOUSE_EVENTS_IN_WINDOWS_SCROLL_WHEEL_EVENTS_H

// available in Windows Vista or newer
#define MOUSEEVENTF_HWHEEL 0x01000

#define SCROLL_UNIT WHEEL_DELTA

// possible scroll wheel input scroll direction
enum {
    SCROLL_VERTICAL,
    SCROLL_HORIZONTAL
};
void create_scroll_wheel_input(INPUT *scrollWheelInput, int scroll_direction, int speed);

void scroll_wheel_scroll(int speed);
void scroll_wheel_scroll_up(unsigned int speed);
void scroll_wheel_scroll_down(unsigned int speed);

void scroll_wheel_scroll_vertical(int speed);
void scroll_wheel_scroll_vertical_up(unsigned int speed);
void scroll_wheel_scroll_vertical_down(unsigned int speed);

void scroll_wheel_scroll_horizontal(int speed);
void scroll_wheel_scroll_horizontal_right(unsigned int speed);
void scroll_wheel_scroll_horizontal_left(unsigned int speed);

#endif //MOUSE_EVENTS_IN_WINDOWS_SCROLL_WHEEL_EVENTS_H
