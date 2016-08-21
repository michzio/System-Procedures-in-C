//
// Created by Michal Ziobro on 19/08/2016.
//

#ifndef MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H
#define MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H

// mouse moving
void mouse_position(float *x, float *y);
void mouse_move_to(float x, float y);
void mouse_move_to_eventless(float x, float y);
void mouse_move_by(float dx, float dy);
void mouse_move_by_eventless(float dx, float dy);

// mouse clicking
void mouse_left_click(void);
void mouse_left_click_at(float x, float y);
void mouse_right_click(void);
void mouse_right_click_at(float x, float y);
void mouse_left_double_click(void);
void mouse_left_double_click_at(float x, float y);
void mouse_right_double_click(void);
void mouse_right_double_click_at(float x, float y);
void mouse_left_triple_click(void);
void mouse_left_triple_click_at(float x, float y);
void mouse_right_triple_click(void);
void mouse_right_triple_click_at(float x, float y);


#endif //MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H
