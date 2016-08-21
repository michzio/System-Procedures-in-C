//
// Created by Michal Ziobro on 19/08/2016.
//

#include <ApplicationServices/ApplicationServices.h>
#include "mouse_events.h"

// mouse moving
static CGPoint osx_mouse_position(void) {

    CGPoint position;

    CGEventRef event = CGEventCreate(NULL);
    position = CGEventGetLocation(event);
    CFRelease(event);

    return position;
}

void mouse_position(float *x, float *y) {

    CGPoint position = osx_mouse_position();
    *x = position.x;
    *y = position.y;
}

void mouse_move_to(float x, float y) {

    /**
     * create a new Quartz mouse event.
     * params:
     * @source : CGEventSourceRef
     * @mouseType : CGEventType
     * @mouseCursorPosition : CGPoint
     * @mouseButton : CGMouseButton
     */
    CGEventRef move_event = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, CGPointMake(x, y), 0);


    /**
     * post a Quartz event into the event stream at a specified location.
     * params:
     * @tap : CGEventTapLocation
     * @event : CGEventRef
     */
    CGEventPost(kCGHIDEventTap, move_event);

    /**
     * release a Quartz event
     */
    CFRelease(move_event);
}

void mouse_move_to_eventless(float x, float y) {

    /**
     * moves the mouse cursor without generating events
     * often used to move the cursor position back to the center of the screen
     * by games that don't want the cursor pinned by display edges.
     * @newCursorPosition : CGPoint (in the global display coordinate space)
     */
    CGWarpMouseCursorPosition(CGPointMake(x, y));

    /** ALTERNATIVE -- not blocking other mouse
     * moves the mouse cursor to a specified point relative to the display origin
     * (the upper-left corner of the display). No events are generated as a result of this move.
     * Points that lie outside the desktop are clipped to the desktop.
     */
    //CGDisplayMoveCursorToPoint(CGMainDisplayID(), CGPointMake(x, y));

    CGAssociateMouseAndMouseCursorPosition(true); // smooth relocation of the mouse ?
}

void mouse_move_by(float dx, float dy) {

    float x, y;

    mouse_position(&x, &y);
    mouse_move_to(x + dx, y + dy);
}

void mouse_move_by_eventless(float dx, float dy) {

    float x, y;

    mouse_position(&x, &y);
    mouse_move_to_eventless(x + dx, y + dy);
}

// mouse clicking
void mouse_left_click(void) {

    float x, y;

    mouse_position(&x, &y);
    mouse_left_click_at(x, y);
}

void mouse_left_click_at(float x, float y) {

    // 1. mouse left click down at (x,y)
    /**
    * create a new Quartz mouse event.
    * params:
    * @source : CGEventSourceRef
    * @mouseType : CGEventType
    * @mouseCursorPosition : CGPoint
    * @mouseButton : CGMouseButton
    */
    CGEventRef left_click_down_event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x,y), 0);

    // 2. mouse left click up at (x,y)
    /**
    * create a new Quartz mouse event.
    * params:
    * @source : CGEventSourceRef
    * @mouseType : CGEventType
    * @mouseCursorPosition : CGPoint
    * @mouseButton : CGMouseButton
    */
    CGEventRef left_click_up_event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, CGPointMake(x,y), 0);

    // 3. set mouse event click state to 1 (single click)
    CGEventSetIntegerValueField(left_click_down_event, kCGMouseEventClickState, 1);
    CGEventSetIntegerValueField(left_click_up_event, kCGMouseEventClickState, 1);

    /**
     * post a Quartz event into the event stream at a specified location.
     * params:
     * @tap : CGEventTapLocation
     * @event : CGEventRef
     */
    CGEventPost(kCGHIDEventTap, left_click_down_event);
    CGEventPost(kCGHIDEventTap, left_click_up_event);

    /**
     * release a Quartz event
     */
    CFRelease(left_click_up_event);
    CFRelease(left_click_down_event);
}

void mouse_right_click(void) {

}

void mouse_right_click_at(float x, float y) {

}

void mouse_left_double_click(void) {


}

void mouse_left_double_click_at(float x, float y) {

    // 1. mouse left click down at (x,y)
    /**
    * create a new Quartz mouse event.
    * params:
    * @source : CGEventSourceRef
    * @mouseType : CGEventType
    * @mouseCursorPosition : CGPoint
    * @mouseButton : CGMouseButton
    */
    CGEventRef left_click_down_event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x,y), 0);

    // 2. mouse left click up at (x,y)
    /**
    * create a new Quartz mouse event.
    * params:
    * @source : CGEventSourceRef
    * @mouseType : CGEventType
    * @mouseCursorPosition : CGPoint
    * @mouseButton : CGMouseButton
    */
    CGEventRef left_click_up_event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, CGPointMake(x,y), 0);

    // 3. set mouse event click state to 2 (double click)
    CGEventSetIntegerValueField(left_click_down_event, kCGMouseEventClickState, 2);
    CGEventSetIntegerValueField(left_click_up_event, kCGMouseEventClickState, 2);

    /**
     * post a Quartz event into the event stream at a specified location.
     * params:
     * @tap : CGEventTapLocation
     * @event : CGEventRef
     */
    CGEventPost(kCGHIDEventTap, left_click_down_event);
    CGEventPost(kCGHIDEventTap, left_click_up_event);

    CGEventPost(kCGHIDEventTap, left_click_down_event);
    CGEventPost(kCGHIDEventTap, left_click_up_event);

    /**
     * release a Quartz event
     */
    CFRelease(left_click_up_event);
    CFRelease(left_click_down_event);

}

void mouse_right_double_click(void) {

}

void mouse_right_double_click_at(float x, float y) {

}

void mouse_left_triple_click(void) {

}

void mouse_left_triple_click_at(float x, float y) {

    // 1. mouse left click down at (x,y)
    /**
    * create a new Quartz mouse event.
    * params:
    * @source : CGEventSourceRef
    * @mouseType : CGEventType
    * @mouseCursorPosition : CGPoint
    * @mouseButton : CGMouseButton
    */
    CGEventRef left_click_down_event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x,y), 0);

    // 2. mouse left click up at (x,y)
    /**
    * create a new Quartz mouse event.
    * params:
    * @source : CGEventSourceRef
    * @mouseType : CGEventType
    * @mouseCursorPosition : CGPoint
    * @mouseButton : CGMouseButton
    */
    CGEventRef left_click_up_event = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, CGPointMake(x,y), 0);

    // 3. set mouse event click state to 3 (triple click)
    CGEventSetIntegerValueField(left_click_down_event, kCGMouseEventClickState, 3);
    CGEventSetIntegerValueField(left_click_up_event, kCGMouseEventClickState, 3);

    /**
     * post a Quartz event into the event stream at a specified location.
     * params:
     * @tap : CGEventTapLocation
     * @event : CGEventRef
     */
    CGEventPost(kCGHIDEventTap, left_click_down_event);
    CGEventPost(kCGHIDEventTap, left_click_up_event);

    CGEventPost(kCGHIDEventTap, left_click_down_event);
    CGEventPost(kCGHIDEventTap, left_click_up_event);

    CGEventPost(kCGHIDEventTap, left_click_down_event);
    CGEventPost(kCGHIDEventTap, left_click_up_event);

    /**
     * release a Quartz event
     */
    CFRelease(left_click_up_event);
    CFRelease(left_click_down_event);
}

void mouse_right_triple_click(void) {

}

void mouse_right_triple_click_at(float x, float y) {

}