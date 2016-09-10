//
// Created by Michal Ziobro on 27/08/2016.
//

#include <ApplicationServices/ApplicationServices.h>
#include "keyboard_events.h"
#include "virtual_key_codes.h"

static void key_event(uint16_t virtual_key, bool key_down, uint64_t modifiers_flags) {

    /**
     * create a Quartz event source with HID System State
     * params: CGEventFlags
     * @stateId : CGEventSourceStateID
     */
    CGEventSourceRef event_source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    /**
     * create a new Quartz keyboard event
     * params:
     * @source : CGEventSourceRef
     * @virtualKey : CGKeyCode
     * @keyDown : bool
     */
    CGEventRef key_event = CGEventCreateKeyboardEvent(event_source, (CGKeyCode) virtual_key, key_down);

    /**
     * set modifiers flags on Quartz event
     * params:
     * @event :  CGEventRef
     * @flags :
     */
    CGEventSetFlags(key_event, CGEventGetFlags(key_event) | modifiers_flags);

    /**
     * post a Quartz event into the event stream at a specified location.
     * params:
     * @tap : CGEventTapLocation
     * @event : CGEventRef
     */
    CGEventPost(kCGHIDEventTap, key_event);

    /**
     * release a Quartz event and event source
     */
    CFRelease(key_event);
    CFRelease(event_source);
}

void key_down(uint16_t key_code) {
    key_down_modified(key_code, 0);
}

void key_up(uint16_t key_code) {
    key_up_modified(key_code, 0);
}

void key_down_modified(uint16_t key_code, uint64_t modifiers_flags) {

    key_event(key_code, true, modifiers_flags);
    printf("Key down: %d\n", key_code);
}

void key_up_modified(uint16_t key_code, uint64_t modifiers_flags) {

    key_event(key_code, false, modifiers_flags);
    printf("Key up: %d\n", key_code);
}

void key_input(uint16_t key_code) {
    key_down(key_code);
    key_up(key_code);
}

void key_input_modified(uint16_t key_code, uint64_t modifiers_flags) {
    key_down_modified(key_code, modifiers_flags);
    key_up_modified(key_code, modifiers_flags);
}

void key_hold_down_modified(uint16_t key_code, uint64_t modifiers_flags, uint32_t hold_time_in_s) {
    key_down_modified(key_code, modifiers_flags);
    sleep(hold_time_in_s);
    key_up_modified(key_code, modifiers_flags);
}

static uint64_t mod_key_code_to_mod_flag(uint16_t mod_key_code) {

    switch(mod_key_code) {
        case kVK_Shift:
            return kCGEventFlagMaskAlphaShift;
        case kVK_RightShift:
            return kCGEventFlagMaskShift;
        case kVK_Control:
            return kCGEventFlagMaskControl;
        case kVK_Option:
        case kVK_RightOption:
            return kCGEventFlagMaskAlternate;
        case kVK_Command:
            return kCGEventFlagMaskCommand;
        case kVK_Help:
            return kCGEventFlagMaskHelp;
        case kVK_Function:
            return kCGEventFlagMaskSecondaryFn;
        default:
            return 0;
    }
}

void multi_key_input(int key_num, ...) {

    uint16_t key_code = -1;
    uint64_t modifiers_flags = 0;

    // convert modifiers key_codes into modifiers flags
    va_list key_codes;
    va_start(key_codes, key_num);

    for(int i = 0; i < key_num; i++) {
       uint16_t mod_key_code = (uint16_t) va_arg(key_codes, int);
       uint64_t mod_flag = mod_key_code_to_mod_flag(mod_key_code);
       if(mod_flag)
            modifiers_flags |= mod_flag;
        else // flag not found it isn't modifier key
           key_code = mod_key_code;
    }

    va_end(key_codes);

    // lack of main key code despite of modifier keys
    if(key_code < 0) return;

    key_input_modified(key_code, modifiers_flags);
}

