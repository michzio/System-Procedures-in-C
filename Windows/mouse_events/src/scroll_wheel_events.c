//
// Created by Michal Ziobro on 29.05.2017.
//

#include <stdio.h>
#include "scroll_wheel_events.h"
#include "mouse_events.h"

void create_scroll_wheel_input(INPUT *scrollWheelInput, int scroll_direction, int speed) {

    float x, y;

    mouse_position(&x, &y);

    // fill scroll wheel input structure
    scrollWheelInput->type = INPUT_MOUSE;
    scrollWheelInput->mi.dx = ((LONG)x) * 0xFFFF / (GetSystemMetrics(SM_CXSCREEN) - 1);;
    scrollWheelInput->mi.dy = ((LONG)y) * 0xFFFF / (GetSystemMetrics(SM_CYSCREEN) - 1);
    scrollWheelInput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
    if(scroll_direction == SCROLL_VERTICAL)
        scrollWheelInput->mi.dwFlags |= MOUSEEVENTF_WHEEL;
    else if(scroll_direction == SCROLL_HORIZONTAL)
        scrollWheelInput->mi.dwFlags |= MOUSEEVENTF_HWHEEL;
    /**
     * mouseData specifies the amount of wheel movement.
     * A positive value indicates that the wheel was rotated forward,
     * away from the user; a negative value indicates that
     * the wheel was rotated backward, toward the user.
     **/
    scrollWheelInput->mi.mouseData = speed;
    scrollWheelInput->mi.time = 0;
    scrollWheelInput->mi.dwExtraInfo = NULL;
}

/***
 * documentation of mouse inputs:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms646273(v=vs.85).aspx
 */
void scroll_wheel_scroll(int speed) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseScrollInput;
    create_scroll_wheel_input(&mouseScrollInput, SCROLL_VERTICAL, speed);

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseScrollInput, sizeof(mouseScrollInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void scroll_wheel_scroll_up(unsigned int speed) {
    scroll_wheel_scroll(speed);
}

void scroll_wheel_scroll_down(unsigned int speed) {
    scroll_wheel_scroll(-speed);
}

void scroll_wheel_scroll_vertical(int speed) {
    scroll_wheel_scroll(speed);
}

void scroll_wheel_scroll_vertical_up(unsigned int speed) {
    scroll_wheel_scroll_up(speed);
}

void scroll_wheel_scroll_vertical_down(unsigned int speed) {
    scroll_wheel_scroll_down(speed);
}

void scroll_wheel_scroll_horizontal(int speed) {

    /**
    * INPUT structure to store info about input event
    * type of input: mouse, keyboard, hardware
    * and corresponding structure containing info about
    * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
    */
    INPUT mouseHorizontalScrollInput;
    create_scroll_wheel_input(&mouseHorizontalScrollInput, SCROLL_HORIZONTAL, speed);

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseHorizontalScrollInput, sizeof(mouseHorizontalScrollInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void scroll_wheel_scroll_horizontal_right(unsigned int speed) {

    scroll_wheel_scroll_horizontal(speed);
}

void scroll_wheel_scroll_horizontal_left(unsigned int speed) {
    scroll_wheel_scroll_horizontal(-speed);
}