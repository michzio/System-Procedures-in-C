//
// Created by Michal Ziobro on 15/09/2016.
//

#include <IOKit/IOTypes.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOGraphicsTypes.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include <CoreGraphics/CoreGraphics.h>
#include "display.h"
#include "../../cocoa_helper/strings.h"

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

static const char *displayNameFromDisplayID(CGDirectDisplayID displayID, CFStringRef countryCode) {

    char *displayProductName = 0;

    // get a CFDictionary with a key for the preferred name of the display
    CFDictionaryRef displayInfo = IODisplayCreateInfoDictionary(CGDisplayIOServicePort(displayID), kIODisplayOnlyPreferredName);
    // retrieve the display product name
    CFStringRef displayProductNameKey = CFStringCreateWithCString(kCFAllocatorDefault, kDisplayProductName, kCFStringEncodingUTF8);
    CFDictionaryRef localizedNames = CFDictionaryGetValue(displayInfo, displayProductNameKey);
    CFRelease(displayProductNameKey);
    // use the first name
    if(CFDictionaryGetCount(localizedNames) > 0) {
        if(!countryCode) countryCode = CFSTR("en_US");
        CFStringRef displayProductNameValue = (CFStringRef) CFDictionaryGetValue(localizedNames, countryCode);
        displayProductName = CFStringCopyUTF8String(displayProductNameValue);
        CFRelease(displayProductNameValue);
    }

    CFRelease(localizedNames);

    return displayProductName;
}

void display_capture(void) {

    // displays[] Quartz display ID's
    CGDirectDisplayID *displays;
    CGDisplayCount displayCount;

    // get number of active displays
    if( CGGetActiveDisplayList(0, NULL, &displayCount) != CGDisplayNoErr ) {
        fprintf(stderr, "%s: Could not get the number of active displays.\n", __func__);
        return;
    }

    // allocate enough memory to hold all the display IDs we have
    displays = calloc((size_t) displayCount, sizeof(CGDirectDisplayID));

    // get the list of all active displays
    if( CGGetActiveDisplayList(displayCount, displays, &displayCount) != CGDisplayNoErr ) {
        fprintf(stderr, "%s: Could not get active display list.\n", __func__);
        return;
    }

    for(int i=0; i<displayCount; i++) {

        const char *displayProductName = displayNameFromDisplayID(displays[i], NULL);
        printf("%s: Display ID: %d has product name: %s.\n", __func__,  displays[i], displayProductName);
    }

}

void display_capture_rect(void) {

}