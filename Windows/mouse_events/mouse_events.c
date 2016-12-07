//
// Created by Michal Ziobro on 07.12.2016.
//

#include <windows.h>
#include <stdio.h>

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
    INPUT mouseInput;
    mouseInput.type = INPUT_MOUSE;
    mouseInput.mi.dx = x * 0xFFFF / GetSystemMetrics(SM_CXSCREEN) + 1;
    mouseInput.mi.dy = y * 0xFFFF / GetSystemMetrics(SM_CYSCREEN) + 1;
    mouseInput.mi.mouseData = 0;
    mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    mouseInput.mi.time = 0;
    mouseInput.mi.dwExtraInfo = NULL;

    /**
     * send a INPUT events into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    SendInput(1, &mouseInput, sizeof(mouseInput));
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
                x * 0xFFFF / GetSystemMetrics(SM_CXSCREEN) + 1,
                y * 0xFFFF / GetSystemMetrics(SM_CYSCREEN) + 1,
                0, NULL);

}

void mouse_move_by(float dx, float dy) {

}

void _mouse_move_by(float dx, float dy) {

}