//
// Created by Michal Ziobro on 15/09/2016.
//

#include <IOKit/IOTypes.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOGraphicsTypes.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include <CoreGraphics/CoreGraphics.h>
#include <NSSystemDirectories.h>
#include "system/display.h"
#include "cocoa_helper/strings.h"
#include "cocoa_helper/exec_cmd.h"
#include "cocoa_helper/images.h"
#include "cocoa_helper/file_system.h"
#include "strings.h"

void display_get_pixel_size(size_t *displayWidth, size_t *displayHeight) {

    CGDirectDisplayID displayID = display_current_displayID();

    if(displayWidth) *displayWidth =  CGDisplayPixelsWide(displayID);
    if(displayHeight) *displayHeight = CGDisplayPixelsHigh(displayID);
}

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

static const char *display_name_from_displayID(CGDirectDisplayID displayID, CFStringRef countryCode) {

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

CGDirectDisplayID display_current_displayID() {

    // displays[] Quartz display ID's
    CGDirectDisplayID *displays;
    CGDisplayCount displayCount;

    // get number of active displays
    if( CGGetActiveDisplayList(0, NULL, &displayCount) != CGDisplayNoErr ) {
        fprintf(stderr, "%s: Could not get the number of active displays.\n", __func__);
        return -1;
    }

    // allocate enough memory to hold all the display IDs we have
    displays = calloc((size_t) displayCount, sizeof(CGDirectDisplayID));

    // get the list of all active displays
    if( CGGetActiveDisplayList(displayCount, displays, &displayCount) != CGDisplayNoErr ) {
        fprintf(stderr, "%s: Could not get active display list.\n", __func__);
        return -1;
    }

    CGDirectDisplayID mainDisplay = CGMainDisplayID();
    const char *mainDisplayProductName = display_name_from_displayID(mainDisplay, NULL);
    printf("%s: Main Display ID: %d has product name: %s.\n", __func__, mainDisplay, mainDisplayProductName);

    for(int i=0; i<displayCount; i++) {

        const char *displayProductName = display_name_from_displayID(displays[i], NULL);
        printf("%s: Display ID: %d has product name: %s.\n", __func__,  displays[i], displayProductName);
    }

    return mainDisplay;
}

static CGImageRef display_screen_snapshot(void) {
    CGDirectDisplayID current_display = display_current_displayID();
    return CGDisplayCreateImage(current_display);
}

static CGImageRef display_screen_snapshot_rect(void) {

    CGFloat x, y, width, height;

    const char *output = exec_cmd("./tools/SelectionView.app/Contents/MacOS/SelectionView ");

    size_t num_tokens = 0;
    char **tokens = str_split(output, ",", &num_tokens);
    if(num_tokens<4) {
        fprintf(stderr, "%s: Could not get all four params of rectangular screen selection area.\n", __func__);
        return NULL;
    }
    sscanf(tokens[0]+2, "%lf", &x);
    sscanf(tokens[1]+2, "%lf", &y);
    sscanf(tokens[2]+2, "%lf", &width);
    sscanf(tokens[3]+2, "%lf", &height);
    printf("User selected rect: {x=%.2f, y=%.2f, w=%.2f, h=%.2f}\n", x, y, width, height);

    CGDirectDisplayID current_display = display_current_displayID();
    return CGDisplayCreateImageForRect(current_display, CGRectMake(x,y, width, height));
}

#define BUF_SIZE 64

static CFStringRef screen_snapshot_file_name(const char *file_extension) {

    // create file name for screen snapshot
    char c_file_name[BUF_SIZE];

    // with current date and time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(c_file_name, "Screen Shot %d-%02d-%02d at %02d.%02d.%02d.%s", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, file_extension);

    return CFStringCreateWithCString(kCFAllocatorDefault, c_file_name, kCFStringEncodingUTF8);

}

void display_screen_snapshot_to_desktop(void) {

    // take screen snapshot
    CGImageRef screen_snapshot = display_screen_snapshot();
    if(screen_snapshot == NULL) {
        fprintf(stderr, "%s: Could not take screen snapshot of the current display.\n", __func__);
        return;
    }

    // save screen snapshot to the desktop
    CFStringRef desktop_file_path = FSGetFilePath(NSDesktopDirectory, NSUserDomainMask);
    CFStringRef file_name = screen_snapshot_file_name("png");
    CGImageSaveToFile(screen_snapshot, desktop_file_path, file_name, kUTTypePNG );

    // releasing memory
    CGImageRelease(screen_snapshot);
    CFRelease(desktop_file_path);
    CFRelease(file_name);
}

void display_screen_snapshot_rect_to_desktop(void) {

    // take screen snapshot of selected rectangular area
    CGImageRef screen_snapshot = display_screen_snapshot_rect();
    if(screen_snapshot == NULL) {
        fprintf(stderr, "%s: Could not take screen snapshot of selected rectangular area of the current display.\n", __func__);
        return;
    }

    // save screen snapshot to the desktop
    CFStringRef desktop_file_path = FSGetFilePath(NSDesktopDirectory, NSUserDomainMask);
    CFStringRef file_name = screen_snapshot_file_name("png");
    CGImageSaveToFile(screen_snapshot, desktop_file_path, file_name, kUTTypePNG );

    // releasing memory
    CGImageRelease(screen_snapshot);
    CFRelease(desktop_file_path);
    CFRelease(file_name);
}

void display_screen_snapshot_to_clipboard(void) {

    // take screen snapshot
    CGImageRef screen_snapshot = display_screen_snapshot();
    if(screen_snapshot == NULL) {
        fprintf(stderr, "%s: Could not take screen snapshot of the current display.\n", __func__);
        return;
    }

    // copy screen snapshot to the clipboard
    CGImageCopyToClipboard(screen_snapshot);

    // releasing memory
    CGImageRelease(screen_snapshot);
}

void display_screen_snapshot_rect_to_clipboard(void) {

    // take screen snapshot of selected rectangular area
    CGImageRef screen_snapshot = display_screen_snapshot_rect();
    if(screen_snapshot == NULL) {
        fprintf(stderr, "%s: Could not take screen snapshot of selected rectangular area of the current display.\n", __func__);
        return;
    }

    // copy screen snapshot to the clipboard
    CGImageCopyToClipboard(screen_snapshot);

    // releasing memory
    CGImageRelease(screen_snapshot);
}

void display_screen_snapshot_to_buffer(unsigned char **rgbaData, size_t *rgbaDataLength, size_t *width, size_t *height) {

    // take screen snapshot
    CGImageRef screen_snapshot = display_screen_snapshot();
    if(screen_snapshot == NULL) {
        fprintf(stderr, "%s: Could not take screen snapshot of the current display.\n", __func__);
        return;
    }

    // convert image to raw RGBA bitmap
    *rgbaData = CGImageCopyRGBAData(screen_snapshot, rgbaDataLength);
    *width = CGImageGetWidth(screen_snapshot);
    *height = CGImageGetHeight(screen_snapshot);

    // releasing memory
    CGImageRelease(screen_snapshot);
}

void display_screen_snapshot_rect_to_buffer(unsigned char **rgbaData, size_t *rgbaDataLength, size_t *width, size_t *height) {

    // take screen snapshot of selected rectangular area
    CGImageRef screen_snapshot = display_screen_snapshot_rect();
    if(screen_snapshot == NULL) {
        fprintf(stderr, "%s: Could not take screen snapshot of selected rectangular area of the current display.\n", __func__);
        return;
    }

    // convert image to raw RGBA bitmap
    *rgbaData = CGImageCopyRGBAData(screen_snapshot, rgbaDataLength);
    *width = CGImageGetWidth(screen_snapshot);
    *height = CGImageGetHeight(screen_snapshot);

    // releasing memory
    CGImageRelease(screen_snapshot);
}