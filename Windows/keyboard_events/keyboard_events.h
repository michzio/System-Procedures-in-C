//
// Created by Michal Ziobro on 25.05.2017.
//

#ifndef KEYBOARD_EVENTS_KEYBOARD_EVENTS_H
#define KEYBOARD_EVENTS_KEYBOARD_EVENTS_H

#include <stdint.h>

// basic keyboard modifiers
enum {
    kMFShift        = 0x00020000,
    kMFLeftShift    = 0x00010000,
    kMFRightShift   = kMFShift,
    kMFControl      = 0x00040000,
    kMFOption       = 0x00080000,
    kMFRightOption  = kMFOption,
    kMFLeftOption   = 0x00200000,
    kMFAlt          = kMFOption,
    kMFCommand      = 0x00100000,
    kMFWindows      = kMFCommand,
    kMFFunction     = 0x00800000,
    kMFLeftAlt      = kMFLeftOption,
    kMFRightAlt     = kMFAlt,
};

// additional mouse modifiers
enum {
    kMFScrollUp = 0x10000000,
    kMFScrollDown = 0x20000000,
    kMFScrollRight = 0x40000000,
    kMFScrollLeft = 0x80000000,
};

void key_down(uint16_t key_code);
void key_up(uint16_t key_code);
void key_down_modified(uint16_t key_code, uint64_t modifiers_flags);
void key_up_modified(uint16_t key_code, uint64_t modifiers_flags);
void key_input(uint16_t key_code);
void key_input_modified(uint16_t key_code, uint64_t modifiers_flags);
void key_hold_down_modified(uint16_t key_code, uint64_t modifiers_flags, uint32_t hold_time_in_s);
void multi_key_down(int key_num, ...);
void multi_key_up(int key_num, ...);
void multi_key_input(int key_num, ...);

#endif //KEYBOARD_EVENTS_KEYBOARD_EVENTS_H
