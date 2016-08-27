//
// Created by Michal Ziobro on 27/08/2016.
//

#ifndef KEYBOARD_EVENTS_IN_OS_X_KEYBOARD_EVENTS_H
#define KEYBOARD_EVENTS_IN_OS_X_KEYBOARD_EVENTS_H

#include <CoreGraphics/CoreGraphics.h>

void key_down(uint16_t key_code);
void key_up(uint16_t key_code);
void key_down_modified(uint16_t key_code, uint64_t modifiers_flags);
void key_up_modified(uint16_t key_code, uint64_t modifiers_flags);
void key_input(uint16_t key_code);
void key_input_modified(uint16_t key_code, uint64_t modifiers_flags);
void multi_key_down(uint16_t key_code, uint16_t mod_key_code, ...);
void multi_key_up(uint16_t key_code, uint16_t mod_key_code, ...);
void multi_key_input(int key_num, ...);


#endif //KEYBOARD_EVENTS_IN_OS_X_KEYBOARD_EVENTS_H
