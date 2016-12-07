//
// Created by Michal Ziobro on 19/08/2016.
//

#ifndef MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H
#define MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H

// mouse moving
void mouse_position(float *x, float *y);
void mouse_move_to(float x, float y);
void _mouse_move_to(float x, float y);
void mouse_move_by(float dx, float dy);
void _mouse_move_by(float dx, float dy);

// mouse clicking
void mouse_left_click(void);
void mouse_left_click_at(float x, float y);
void mouse_right_click(void);
void mouse_right_click_at(float x, float y);
void mouse_middle_click(void);
void mouse_middle_click_at(float x, float y);
void mouse_left_double_click(void);
void mouse_left_double_click_at(float x, float y);
void mouse_right_double_click(void);
void mouse_right_double_click_at(float x, float y);
void mouse_middle_double_click(void);
void mouse_middle_double_click_at(float x, float y);
void mouse_left_triple_click(void);
void mouse_left_triple_click_at(float x, float y);
void mouse_right_triple_click(void);
void mouse_right_triple_click_at(float x, float y);
void mouse_middle_triple_click(void);
void mouse_middle_triple_click_at(float x, float y);

// mouse button pushing
void mouse_left_click_down(void);
void mouse_left_click_down_at(float x, float y);
void mouse_right_click_down(void);
void mouse_right_click_down_at(float x, float y);
void mouse_middle_click_down(void);
void mouse_middle_click_down_at(float x, float y);

// mouse button releasing
void mouse_left_click_up(void);
void mouse_left_click_up_at(float x, float y);
void mouse_right_click_up(void);
void mouse_right_click_up_at(float x, float y);
void mouse_middle_click_up(void);
void mouse_middle_click_up_at(float x, float y);

// mouse dragging
void mouse_left_drag(void);
void mouse_left_drag_by(float dx, float dy);
void mouse_left_drag_to(float x, float y);
void mouse_right_drag(void);
void mouse_right_drag_by(float dx, float dy);
void mouse_right_drag_to(float x, float y);
void mouse_middle_drag(void);
void mouse_middle_drag_by(float dx, float dy);
void mouse_middle_drag_to(float x, float y);

#endif //MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H
