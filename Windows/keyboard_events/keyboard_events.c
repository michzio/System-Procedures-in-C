//
// Created by Michal Ziobro on 25.05.2017.
//

#include "keyboard_events.h"
#include "virtual_key_codes.h"
#include <windows.h>
#include <stdio.h>
#include <unistd.h>

static void create_keyboard_input(INPUT *keyboardInput, uint16_t key_code) {

    keyboardInput->type = INPUT_KEYBOARD;
    keyboardInput->ki.wScan = 0;
    keyboardInput->ki.time = 0;
    keyboardInput->ki.dwExtraInfo = NULL;
    keyboardInput->ki.dwFlags = 0;
    keyboardInput->ki.wVk = key_code;
}

static void create_keyboard_down_input(INPUT *keyboardInput, uint16_t key_code) {
    create_keyboard_input(keyboardInput, key_code);
}

static void create_keyboard_up_input(INPUT *keyboardInput, uint16_t key_code) {
    create_keyboard_input(keyboardInput, key_code);
    // change default key (down) input to key up input
    keyboardInput->ki.dwFlags  |= KEYEVENTF_KEYUP;
}

void key_down(uint16_t key_code) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT keyDownInput;

    // use helper function to create down keyboard input
    create_keyboard_down_input(&keyDownInput, key_code);

    if(SendInput(1, &keyDownInput, sizeof(keyDownInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void key_up(uint16_t key_code) {

    /**
     * INPUT structure to store info about input event
     * type of input: mouse, keyboard, hardware
     * and corresponding structure containing info about
     * MOUSEINPUT, KEYBDINPUT or HARDWAREINPUT
     */
    INPUT keyUpInput;

    // use helper function to create up keyboard input
    create_keyboard_up_input(&keyUpInput, key_code);

    if(SendInput(1, &keyUpInput, sizeof(keyUpInput)) != 1) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

#define MAX_NUM_OF_INPUTS 5

void key_down_modified(uint16_t key_code, uint64_t modifiers_flags) {

    int numOfInputs = 0;
    INPUT keyDownInputs[MAX_NUM_OF_INPUTS];

    if(modifiers_flags & kMFShift) {
        create_keyboard_down_input(&(keyDownInputs[numOfInputs]), kVK_Shift);
        numOfInputs++;
    }
    if(modifiers_flags & kMFControl) {
        create_keyboard_down_input(&(keyDownInputs[numOfInputs]), kVK_Control);
        numOfInputs++;
    }
    if(modifiers_flags & kMFRightAlt) {
        create_keyboard_down_input(&(keyDownInputs[numOfInputs]), kVK_RightAlt);
        numOfInputs++;
    } else if (modifiers_flags & kMFLeftAlt) {
        create_keyboard_down_input(&(keyDownInputs[numOfInputs]), kVK_Alt);
        numOfInputs++;
    }

    if(modifiers_flags & kMFWindows) {
        create_keyboard_down_input(&(keyDownInputs[numOfInputs]), kVK_LeftWindowsKey);
        numOfInputs++;
    }

    create_keyboard_down_input(&(keyDownInputs[numOfInputs]), key_code);
    numOfInputs++;

    if(SendInput(numOfInputs, keyDownInputs, sizeof(INPUT)) != numOfInputs) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void key_up_modified(uint16_t key_code, uint64_t modifiers_flags) {

    int numOfInputs = 0;
    INPUT keyUpInputs[MAX_NUM_OF_INPUTS];

    create_keyboard_up_input(&(keyUpInputs[numOfInputs]), key_code);
    numOfInputs++;

    if(modifiers_flags & kMFShift) {
        create_keyboard_up_input(&(keyUpInputs[numOfInputs]), kVK_Shift);
        numOfInputs++;
    }
    if(modifiers_flags & kMFControl) {
        create_keyboard_up_input(&(keyUpInputs[numOfInputs]), kVK_Control);
        numOfInputs++;
    }
    if(modifiers_flags & kMFRightAlt) {
        create_keyboard_up_input(&(keyUpInputs[numOfInputs]), kVK_RightAlt);
        numOfInputs++;
    } else if(modifiers_flags & kMFLeftAlt) {
        create_keyboard_up_input(&(keyUpInputs[numOfInputs]), kVK_Alt);
        numOfInputs++;
    }
    if(modifiers_flags & kMFWindows) {
        create_keyboard_up_input(&(keyUpInputs[numOfInputs]), kVK_LeftWindowsKey);
        numOfInputs++;
    }

    if(SendInput(numOfInputs, keyUpInputs, sizeof(INPUT)) != numOfInputs) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

void key_input(uint16_t key_code) {

    INPUT keyDownInput, keyUpInput;

    // use helper function to create default keyboard input
    create_keyboard_down_input(&keyDownInput, key_code);
    create_keyboard_up_input(&keyUpInput, key_code);

    /**
     * send an INPUT event into the keyboard or mouse input stream.
     * function fails when blocked by UIPI.
     * params:
     * @nInputs : _In_ UINT
     * @pInputs : _In_ LPINPUT
     * @cbSize : _In_ int
     * @return : UINT (number of events sent)
     */
    INPUT keyInputs[2] = { keyDownInput, keyUpInput};

    if(SendInput(2, &keyInputs, sizeof(INPUT) ) != 2) {
        fprintf(stderr, "Error while sending INPUT events into input stream.\n");
    }

    /**
     * Alternative code sending key down and key up input events separately.
     *
     *   if(SendInput(1, &keyDownInput, sizeof(keyDownInput)) != 1) {
     *       fprintf(stderr, "Error while sending INPUT event into input stream.\n");
     *   }
     *   if(SendInput(1, &keyUpInput, sizeof(keyUpInput)) != 1) {
     *       fprintf(stderr, "Error while sending INPUT event into input stream.\n");
     *   }
     */
}

void key_input_modified(uint16_t key_code, uint64_t modifiers_flags) {

    int numOfInputs = 0;
    INPUT keyInputs[MAX_NUM_OF_INPUTS*2];

    // DOWN INPUTS

    if(modifiers_flags & kMFShift) {
        create_keyboard_down_input(&(keyInputs[numOfInputs]), kVK_Shift);
        numOfInputs++;
    }
    if(modifiers_flags & kMFControl) {
        create_keyboard_down_input(&(keyInputs[numOfInputs]), kVK_Control);
        numOfInputs++;
    }
    if(modifiers_flags & kMFRightAlt) {
        create_keyboard_down_input(&(keyInputs[numOfInputs]), kVK_RightAlt);
        numOfInputs++;
    } else if(modifiers_flags & kMFLeftAlt) {
        create_keyboard_down_input(&(keyInputs[numOfInputs]), kVK_Alt);
        numOfInputs++;
    }

    if(modifiers_flags & kMFWindows) {
        create_keyboard_down_input(&(keyInputs[numOfInputs]), kVK_LeftWindowsKey);
        numOfInputs++;
    }

    create_keyboard_down_input(&(keyInputs[numOfInputs]), key_code);
    numOfInputs++;

    // UP INPUTS
    create_keyboard_up_input(&(keyInputs[numOfInputs]), key_code);
    numOfInputs++;

    if(modifiers_flags & kMFShift) {
        create_keyboard_up_input(&(keyInputs[numOfInputs]), kVK_Shift);
        numOfInputs++;
    }
    if(modifiers_flags & kMFControl) {
        create_keyboard_up_input(&(keyInputs[numOfInputs]), kVK_Control);
        numOfInputs++;
    }
    if(modifiers_flags & kMFRightAlt) {
        create_keyboard_up_input(&(keyInputs[numOfInputs]), kVK_RightAlt);
        numOfInputs++;
    } else if(modifiers_flags & kMFLeftAlt) {
        create_keyboard_up_input(&(keyInputs[numOfInputs]), kVK_Alt);
        numOfInputs++;
    }
    if(modifiers_flags & kMFWindows) {
        create_keyboard_up_input(&(keyInputs[numOfInputs]), kVK_LeftWindowsKey);
        numOfInputs++;
    }

    // SEND INPUTS
    if(SendInput(numOfInputs, keyInputs, sizeof(INPUT)) != numOfInputs) {
        fprintf(stderr, "Error while sending INPUT event into input stream.\n");
    }
}

static uint64_t mod_key_code_to_mod_flag(uint16_t mod_key_code) {

    switch (mod_key_code) {
        case kVK_LeftShift:
            return kMFLeftShift;
        case kVK_RightShift:
            return kMFRightShift;
        case kVK_Shift:
            return kMFLeftShift;
        case kVK_Control:
            return kMFControl;
        case kVK_LeftControl:
            return kMFControl;
        case kVK_RightControl:
            return kMFControl;
        case kVK_Alt: // also kVK_Option
            return kMFAlt;
        case kVK_RightAlt: // also kVK_RightOption
            return kMFRightAlt;
        case kVK_LeftWindowsKey: // also kVK_Command
            return kMFWindows;
        case kVK_RightWindowsKey:
            return kMFWindows;
        default:
            return 0;
    }
}

void multi_key_down(int key_num, ...) {

    uint16_t key_code = -1;
    uint64_t modifier_flags = 0;

    // convert modifier key_codes into modifier flags
    va_list key_codes;
    va_start(key_codes, key_num);

    for(int i=0; i < key_num; i++) {
        uint16_t mod_key_code = (uint16_t) va_arg(key_codes, int);
        uint64_t mod_flag = mod_key_code_to_mod_flag(mod_key_code);
        if(mod_flag)
            modifier_flags |= mod_flag;
        else // flag not found it isn't modifier key
            key_code = mod_key_code;
    }

    va_end(key_codes);

    // lack of main key code despite of modifier keys
    if(key_code < 0) return;

    key_down_modified(key_code, modifier_flags);
}

void multi_key_up(int key_num, ...) {

    uint16_t key_code = -1;
    uint64_t modifier_flags = 0;

    // convert modifier key_codes into modifier flags
    va_list key_codes;
    va_start(key_codes, key_num);

    for(int i=0; i < key_num; i++) {
        uint16_t mod_key_code = (uint16_t) va_arg(key_codes, int);
        uint64_t mod_flag = mod_key_code_to_mod_flag(mod_key_code);
        if(mod_flag)
            modifier_flags |= mod_flag;
        else // flag not found it isn't modifier key
            key_code = mod_key_code;
    }

    va_end(key_codes);

    // lack of main key code despite of modifier keys
    if(key_code < 0) return;

    key_up_modified(key_code, modifier_flags);
}

void multi_key_input(int key_num, ...) {

    uint16_t key_code = -1;
    uint64_t modifier_flags = 0;

    // convert modifier key_codes into modifier flags
    va_list key_codes;
    va_start(key_codes, key_num);

    for(int i=0; i < key_num; i++) {
        uint16_t mod_key_code = (uint16_t) va_arg(key_codes, int);
        uint64_t mod_flag = mod_key_code_to_mod_flag(mod_key_code);
        if(mod_flag)
            modifier_flags |= mod_flag;
        else // flag not found it isn't modifier key
            key_code = mod_key_code;
    }

    va_end(key_codes);

    // lack of main key code despite of modifier keys
    if(key_code < 0) return;

    key_input_modified(key_code, modifier_flags);
}