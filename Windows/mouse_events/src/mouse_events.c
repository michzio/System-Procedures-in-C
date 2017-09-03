//
// Created by Michal Ziobro on 07.12.2016.
//

#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include "mouse_events.h"

// mouse moving
void mouse_position(float *x, float *y) {

    POINT position;

    // retrieve mouse cursor position in screen coordinates
    if(GetCursorPos(&position)) {
        *x = position.x;
        *y = position.y;
    } else {
        fprintf(stderr, "Error occurred while trying to retrieve cursor position in screen.\n");
        *x = -1;
        *y = -1;
    }
}

void mouse_move_to(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseMoveInput;
    mouseMoveInput.type = INPUT_MOUSE;
    mouseMoveInput.mi.dx = ((LONG)x) * 0xFFFF / (GetSystemMetrics(SM_CXSCREEN) - 1);
    mouseMoveInput.mi.dy = ((LONG)y) * 0xFFFF / (GetSystemMetrics(SM_CYSCREEN) - 1);
    mouseMoveInput.mi.mouseData = 0;
    mouseMoveInput.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    mouseMoveInput.mi.time = 0;
    mouseMoveInput.mi.dwExtraInfo = NULL;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseMoveInput, sizeof(mouseMoveInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

// function using deprecated Mouse Event Windows API
void _mouse_move_to(float x, float y) {

    /**
     * function synthesizes mouse motion and button clicks
     * params:
     * @dwFlags : _In_ DWORD
     * @dx : _In_ DWORD
     * @dy : _In_ DWORD
     * @dwData : _In_ DWORD
     * @dwExtraInfo : _In_ ULONG_PTR
     */
    mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
                ((LONG)x) * 0xFFFF / (GetSystemMetrics(SM_CXSCREEN) - 1),
                ((LONG)y) * 0xFFFF / (GetSystemMetrics(SM_CYSCREEN) - 1),
                0, NULL);

}

void mouse_move_by(float dx, float dy) {

   float x, y;

    mouse_position(&x, &y);
    mouse_move_to(x + dx, y + dy);
}

void _mouse_move_by(float dx, float dy) {

    float x, y;

    mouse_position(&x, &y);
    _mouse_move_to(x + dx, y + dy);
}

// mouse clicking
typedef enum MOUSE_BUTTON {
    LEFT, RIGHT, MIDDLE
} MouseButton;

static void mouse_button_input(INPUT *mouseButtonInput, float x, float y) {

    mouseButtonInput->type = INPUT_MOUSE;
    mouseButtonInput->mi.dx = ((LONG)x) * 0xFFFF / (GetSystemMetrics(SM_CXSCREEN) - 1);
    mouseButtonInput->mi.dy = ((LONG)y) * 0xFFFF / (GetSystemMetrics(SM_CYSCREEN) - 1);
    mouseButtonInput->mi.mouseData = 0;
    mouseButtonInput->mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    mouseButtonInput->mi.time = 0;
    mouseButtonInput->mi.dwExtraInfo = NULL;
}

static void mouse_click_at(float x, float y, MouseButton mouseButton, int noOfClicks) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseButtonDownInput, mouseButtonUpInput;

    // 1. mouse button click down at (x,y)
    mouse_button_input(&mouseButtonDownInput, x, y);

    // 2. mouse button click up at (x,y)
    mouse_button_input(&mouseButtonUpInput, x, y);

    // 3. select mouse button to be clicked
    switch(mouseButton) {
        case LEFT:
            mouseButtonDownInput.mi.dwFlags |= MOUSEEVENTF_LEFTDOWN;
            mouseButtonUpInput.mi.dwFlags |= MOUSEEVENTF_LEFTUP;
            break;
        case RIGHT:
            mouseButtonDownInput.mi.dwFlags |= MOUSEEVENTF_RIGHTDOWN;
            mouseButtonUpInput.mi.dwFlags |= MOUSEEVENTF_RIGHTUP;
            break;
        case MIDDLE:
            mouseButtonDownInput.mi.dwFlags |= MOUSEEVENTF_MIDDLEDOWN;
            mouseButtonUpInput.mi.dwFlags |= MOUSEEVENTF_MIDDLEUP;
            break;
        default:
            // default is mouse input of left button click
            mouseButtonDownInput.mi.dwFlags |= MOUSEEVENTF_LEFTDOWN;
            mouseButtonUpInput.mi.dwFlags |= MOUSEEVENTF_LEFTUP;
            break;
    }

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    INPUT mouseButtonClickInputs[2] = { mouseButtonDownInput, mouseButtonUpInput };

    for(int i=0; i<noOfClicks; i++) {
        if(SendInput(2, &mouseButtonClickInputs, sizeof(INPUT)) != 2) {
            fprintf(stderr, "Error while sending INPUT events into input stream.\n");
        }

        /*
         *   The alternative code sending mouse button down and mouse button up input events separately.
         *
         *   if(SendInput(1, &mouseButtonDownInput, sizeof(mouseButtonDownInput)) != 1) {
         *       fprintf(stderr, "Error while sending INPUT event into input stream.\n");
         *   }
         *
         *   if(SendInput(1, &mouseButtonUpInput, sizeof(mouseButtonUpInput)) != 1) {
         *       fprintf(stderr, "Error while sending INPUT event into input stream.\n");
         *   }
         *
         */
    }
}

void mouse_left_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_click_at(x, y);
}

void mouse_left_click_at(float x, float y) {
    mouse_click_at(x, y, LEFT, 1);
}

void mouse_right_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_right_click_at(x, y);
}

void mouse_right_click_at(float x, float y) {
    mouse_click_at(x, y, RIGHT, 1);
}

void mouse_middle_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_middle_click_at(x, y);
}

void mouse_middle_click_at(float x, float y) {
    mouse_click_at(x, y, MIDDLE, 1);
}

void mouse_left_double_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_double_click_at(x, y);
}

void mouse_left_double_click_at(float x, float y) {
    mouse_click_at(x, y, LEFT, 2);
}

void mouse_right_double_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_right_double_click_at(x, y);
}

void mouse_right_double_click_at(float x, float y) {
    mouse_click_at(x, y, RIGHT, 2);
}

void mouse_middle_double_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_middle_double_click_at(x, y);
}

void mouse_middle_double_click_at(float x, float y) {
    mouse_click_at(x, y, MIDDLE, 2);
}

void mouse_left_triple_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_triple_click_at(x, y);
}

void mouse_left_triple_click_at(float x, float y) {
    mouse_click_at(x, y, LEFT, 3);
}

void mouse_right_triple_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_right_triple_click_at(x, y);
}

void mouse_right_triple_click_at(float x, float y) {
    mouse_click_at(x, y, RIGHT, 3);
}

void mouse_middle_triple_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_middle_triple_click_at(x, y);
}

void mouse_middle_triple_click_at(float x, float y) {
    mouse_click_at(x, y, MIDDLE, 3);
}

// mouse button pushing
void mouse_left_click_down(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_click_down_at(x, y);
}

void mouse_left_click_down_at(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseLeftDownInput;

    // mouse left button click down at (x, y)
    mouse_button_input(&mouseLeftDownInput, x, y);
    mouseLeftDownInput.mi.dwFlags |= MOUSEEVENTF_LEFTDOWN;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseLeftDownInput, sizeof(mouseLeftDownInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void mouse_right_click_down(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_right_click_down_at(x, y);
}

void mouse_right_click_down_at(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseRightDownInput;

    // mouse right button click down at (x, y)
    mouse_button_input(&mouseRightDownInput, x, y);
    mouseRightDownInput.mi.dwFlags |= MOUSEEVENTF_RIGHTDOWN;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseRightDownInput, sizeof(mouseRightDownInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void mouse_middle_click_down(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_middle_click_down_at(x, y);
}

void mouse_middle_click_down_at(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseMiddleDownInput;

    // mouse middle button click down at (x, y)
    mouse_button_input(&mouseMiddleDownInput, x, y);
    mouseMiddleDownInput.mi.dwFlags |= MOUSEEVENTF_MIDDLEDOWN;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseMiddleDownInput, sizeof(mouseMiddleDownInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

// mouse button releasing
void mouse_left_click_up(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_click_up_at(x, y);
}

void mouse_left_click_up_at(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseLeftUpInput;

    // mouse left button click up at (x, y)
    mouse_button_input(&mouseLeftUpInput, x, y);
    mouseLeftUpInput.mi.dwFlags |= MOUSEEVENTF_LEFTUP;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseLeftUpInput, sizeof(mouseLeftUpInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void mouse_right_click_up(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_right_click_up_at(x, y);
}

void mouse_right_click_up_at(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseRightUpInput;

    // mouse right button click up at (x, y)
    mouse_button_input(&mouseRightUpInput, x, y);
    mouseRightUpInput.mi.dwFlags |= MOUSEEVENTF_RIGHTUP;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseRightUpInput, sizeof(mouseRightUpInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void mouse_middle_click_up(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_middle_click_up_at(x, y);
}

void mouse_middle_click_up_at(float x, float y) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT mouseMiddleUpInput;

    // mouse middle button click up at (x, y)
    mouse_button_input(&mouseMiddleUpInput, x, y);
    mouseMiddleUpInput.mi.dwFlags |= MOUSEEVENTF_MIDDLEUP;

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    if(SendInput(1, &mouseMiddleUpInput, sizeof(mouseMiddleUpInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

// mouse dragging
void mouse_left_drag(void) {

    // nowhere to drag
}

void mouse_left_drag_by(float dx, float dy) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_drag_to(x + dx, y + dy);
}

void mouse_left_drag_to(float x, float y) {

    mouse_left_click_down();
    mouse_move_to(x, y);
    mouse_left_click_up_at(x, y);
}

void mouse_right_drag(void) {

    // nowhere to drag
}

void mouse_right_drag_by(float dx, float dy) {

    float x, y;

    mouse_position(&x, &y);
    mouse_right_drag_to(x + dx, y + dy);
}

void mouse_right_drag_to(float x, float y) {

    mouse_right_click_down();
    mouse_move_to(x, y);
    mouse_right_click_up_at(x, y);
}

void mouse_middle_drag(void) {
    // nowhere to drag
}

void mouse_middle_drag_by(float dx, float dy) {

    float x, y;

    mouse_position(&x, &y);
    mouse_middle_drag_to(x + dx, y + dy);
}

void mouse_middle_drag_to(float x, float y) {

    mouse_middle_click_down();
    mouse_move_to(x, y);
    mouse_middle_click_up_at(x, y);
}