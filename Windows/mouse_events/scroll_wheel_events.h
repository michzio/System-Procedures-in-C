//
// Created by Michal Ziobro on 29.05.2017.
//
#include <windows.h>

#ifndef MOUSE_EVENTS_IN_WINDOWS_SCROLL_WHEEL_EVENTS_H
#define MOUSE_EVENTS_IN_WINDOWS_SCROLL_WHEEL_EVENTS_H

#define SCROLL_UNIT WHEEL_DELTA

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
