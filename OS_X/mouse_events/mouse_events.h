//
// Created by Michal Ziobro on 19/08/2016.
//

#ifndef MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H
#define MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H

void mouse_position(float *x, float *y);
void mouse_move_to(float x, float y);
void mouse_move_to_eventless(float x, float y);
void mouse_move_by(float dx, float dy);
void mouse_move_by_eventless(float dx, float dy);

#endif //MOUSE_EVENTS_IN_OS_X_MOUSE_EVENTS_H
