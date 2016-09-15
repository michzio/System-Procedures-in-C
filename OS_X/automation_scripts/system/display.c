//
// Created by Michal Ziobro on 15/09/2016.
//

#include <IOKit/IOTypes.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOGraphicsTypes.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include "display.h"

float display_get_brightness(void) {

    float level = 1.0f;

    /* deprecated:
    io_iterator_t iterator;
    kern_return_t result = IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("IODisplayConnect"), &iterator);

    if (result == kIOReturnSuccess) {
        io_object_t service;
        while ((service = IOIteratorNext(iterator))) {
            IODisplayGetFloatParameter(service, kNilOptions, CFSTR(kIODisplayBrightnessKey), &level);
            IOObjectRelease(service);
        }
    }
    */
    io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IODisplayConnect") );
    IODisplayGetFloatParameter(service, kNilOptions, CFSTR(kIODisplayBrightnessKey), &level);
    IOObjectRelease(service);

    return level;
}

void display_set_brightness(float level) {

    /* deprecated:
    io_iterator_t iterator;
    kern_return_t result = IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("IODisplayConnect"), &iterator);

    if(result == kIOReturnSuccess) {
        io_object_t service;
        while ((service = IOIteratorNext(iterator))) {
            IODisplaySetFloatParameter(service, kNilOptions, CFSTR(kIODisplayBrightnessKey), level);
            IOObjectRelease(service);
            return;
        }
    }
    */


    io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IODisplayConnect"));
    IODisplaySetFloatParameter(service, kNilOptions, CFSTR(kIODisplayBrightnessKey), level);
    IOObjectRelease(service);
}