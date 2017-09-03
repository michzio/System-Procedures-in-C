//
// Created by Michal Ziobro on 24/08/2016.
//

#include <ApplicationServices/ApplicationServices.h>
#include "scroll_wheel_events.h"

void scroll_wheel_scroll(int speed) {

    /**
     * create a new Quartz scroll wheel event
     * params:
     * @source :  CGEventSourceRef
     * @unites :  CGScrollEventUnit (possible kCGScrollEventUnitPixel or kCGScrollEventUnitLine)
     * @wheelCount : uint32_t  (number of scrolling devices on the mouse, up to a maximum of 3)
     * @wheel1 : int32_t ( typically in a range from -10 to +10 to reflect movement )
     * @wheel2, @wheel3 are optional
     */
    CGEventRef scroll_event = CGEventCreateScrollWheelEvent(NULL, kCGScrollEventUnitPixel, 1, speed);

    /**
     * post a Quartz event into the event stream at a specified location.
     * params:
     * @tap : CGEventTapLocation
     * @event : CGEventRef
     */
    CGEventPost(kCGHIDEventTap, scroll_event);

    /**
     * release a Quartz event
     */
    CFRelease(scroll_event);
}

void scroll_wheel_scroll_up(unsigned int speed) {
    scroll_wheel_scroll(speed);
}

void scroll_wheel_scroll_down(unsigned int speed) {
    scroll_wheel_scroll(-speed);
}