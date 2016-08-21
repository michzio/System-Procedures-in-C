//
// Created by Michal Ziobro on 19/08/2016.
//

#include <ApplicationServices/ApplicationServices.h>
#include "mouse_events.h"

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

    float curr_x, curr_y;

    mouse_position(&curr_x, &curr_y);
    mouse_move_to(curr_x + dx, curr_y + dy);
}

void mouse_move_by_eventless(float dx, float dy) {

    float curr_x, curr_y;

    mouse_position(&curr_x, &curr_y);
    mouse_move_to_eventless(curr_x + dx, curr_y + dy);
}