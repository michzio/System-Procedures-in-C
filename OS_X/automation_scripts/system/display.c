//
// Created by Michal Ziobro on 15/09/2016.
//

#include <dispatch/dispatch.h>
#include <IOKit/IOTypes.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOGraphicsTypes.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include <IOSurface/IOSurface.h>
#include <CoreGraphics/CoreGraphics.h>
#include <NSSystemDirectories.h>
#include "display.h"
#include "../../cocoa_helper/strings.h"
#include "../../cocoa_helper/exec_cmd.h"
#include "../../cocoa_helper/images.h"
#include "../../cocoa_helper/file_system.h"
#include "../../../../common/strings.h"
#include "../../../../common/bitwise.h"

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

static CGDirectDisplayID display_current_displayID() {

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

// serial dispatch queue used by CGDisplayStreamRef
dispatch_queue_t dispatch_queue;

// generic display stream initializer
CGDisplayStreamRef _display_stream_init(const CFDictionaryRef properties, const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler) {

    /**
     * CGDisplayStreamRef callback block that provides new display frames as IOSurfaceRef objects and display updates object.
     * IOSurfaceRef object contains frame (pixels) from the display. If there is need to keep it for a longer period then
     * the callback do it this way:
     *
     *      CFRetain(IOSourceRef ...)
     *      IOSurfaceIncrementUseCount(IOSurfaceRef ...)
     *      ...
     *      CFRelease(IOSourceRef ...)
     *      IOSurfaceDecrementUseCount(IOSourceRef ...)
     */
    CGDisplayStreamFrameAvailableHandler display_stream_handler = ^(CGDisplayStreamFrameStatus status,
                                                                    uint64_t displayTime, IOSurfaceRef __nullable frameSurface,
                                                                    CGDisplayStreamUpdateRef __nullable updateRef){

        switch(status) {
            case kCGDisplayStreamFrameStatusFrameComplete:
                // A new frame was generated.
                break;
            case kCGDisplayStreamFrameStatusFrameIdle:
                fprintf(stderr, "%s: A new frame was not generated because the display did not change.\n", __func__);
                return;
            case kCGDisplayStreamFrameStatusFrameBlank:
                fprintf(stderr, "%s: A new frame was not generated because the display has gone blank.\n", __func__);
                return;
            case kCGDisplayStreamFrameStatusStopped:
                fprintf(stderr, "%s: The display stream was stopped.\n", __func__);
                return;
            default:
                fprintf(stderr, "%s: Unhandled display stream frame status.\n", __func__);
                return;
        }

        /*
        size_t frameWidth = IOSurfaceGetWidth(frameSurface);
        size_t frameHeight = IOSurfaceGetHeight(frameSurface);
        size_t bytesPerElement = IOSurfaceGetBytesPerElement(frameSurface);
        size_t bytesPerRow = IOSurfaceGetBytesPerRow(frameSurface);
        size_t frameAllocSize = IOSurfaceGetAllocSize(frameSurface);
        size_t elementWidth = IOSurfaceGetElementWidth(frameSurface);
        size_t elementHeight = IOSurfaceGetElementHeight(frameSurface);
        OSType pixelFormat = IOSurfaceGetPixelFormat(frameSurface);
        size_t planeCount = IOSurfaceGetPlaneCount(frameSurface);
        uint32_t surfaceSeed = IOSurfaceGetSeed(frameSurface); // to check if content changed in the surface buffer

        printf("Display stream frame size: (%d, %d).\n", frameWidth, frameHeight);
        printf("Display stream frame alloc size: %d.\n", frameAllocSize);
        printf("Display stream frame bytes per element: %d.\n", bytesPerElement);
        printf("Display stream frame bytes per row: %d.\n", bytesPerRow);
        printf("Display stream frame element size: (%d, %d).\n", elementWidth, elementHeight);
        printf("Display stream frame pixel format: %ld.\n", pixelFormat);
        printf("Display stream frame is BGRA format: %d.\n", pixelFormat == 'BGRA' ? true : false);
        printf("Display stream frame plane count: %d.\n", planeCount);
        printf("Display stream frame surface seed: %d.\n", surfaceSeed);
        */

        // lock IOSurface to prevent frame buffer overwritting by the operating system.
        IOSurfaceLock(frameSurface, kIOSurfaceLockReadOnly, NULL);

        size_t frameAllocSize = IOSurfaceGetAllocSize(frameSurface);
        size_t frameWidth = IOSurfaceGetWidth(frameSurface);
        size_t frameHeight = IOSurfaceGetHeight(frameSurface);
        size_t bytesPerElement = IOSurfaceGetBytesPerElement(frameSurface);

        uint8_t *frameBuffer = (uint8_t *) IOSurfaceGetBaseAddress(frameSurface);
        if(frameBuffer == NULL) {
            fprintf(stderr, "%s: Could not get frame buffer from frame surface.\n", __func__);
            return;
        }

        // copy frameBuffer
        unsigned char *frameBufferCopy = malloc(sizeof(unsigned char)*frameAllocSize);
        memcpy(frameBufferCopy, frameBuffer, frameAllocSize);

        // printf("Display stream frame buffer:\n");
        // bytes_array_dump_segment(frameBuffer, 100, 200, 10);

        IOSurfaceUnlock(frameSurface, kIOSurfaceLockReadOnly, NULL);

        customDisplayStreamHandler(frameBufferCopy, frameAllocSize, frameWidth, frameHeight, bytesPerElement);
    };

    CGDirectDisplayID displayID = display_current_displayID();

    dispatch_queue = dispatch_queue_create("display stream queue", DISPATCH_QUEUE_SERIAL);

    // possible pixel formats are:
    // 'BGRA' - Packed Little Endian ARGB8888
    // 'l10r' - Packed Little Endian ARGB2101010
    // '420v' - 2-plane "video" range YCbCr 4:2:0
    // '420f' - 2-plane "full" range YCbCr 4:2:0
    CGDisplayStreamRef displayStream = CGDisplayStreamCreateWithDispatchQueue(displayID, outWidth, outHeight, 'BGRA', properties, dispatch_queue, display_stream_handler);
    if(displayStream == NULL) {
        fprintf(stderr, "%s: Error! Failed to create a display stream used to capture the screen.\n", __func__);
        return NULL;
    }

    return displayStream;
}

// display stream initializer of rectangle subarea of the screen
CGDisplayStreamRef display_stream_rect_init(const double x, const double y, const double width, const double height,
                                const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler) {

    // create properties dictionary
    CFMutableDictionaryRef properties = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);
    // set screen rect to be streamed
    CFDictionaryAddValue(properties,
                         kCGDisplayStreamSourceRect,
                         CGRectCreateDictionaryRepresentation(CGRectMake(x, y, width, height)));

    return _display_stream_init(properties, outWidth, outHeight, customDisplayStreamHandler);
}

// display stream initializer of the entire area of the screen
CGDisplayStreamRef display_stream_init(const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler) {

    // create properties dictionary
    CFMutableDictionaryRef properties = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);

    return _display_stream_init(properties, outWidth, outHeight, customDisplayStreamHandler);
}

// start display streaming
int display_stream_start(CGDisplayStreamRef displayStream) {

    if(CGDisplayStreamStart(displayStream) != kCGErrorSuccess) {
        fprintf(stderr, "%s: Error! Failed to start the display stream.\n", __func__);
        return -1;
    }
    return 0;
}

// stop display streaming
int display_stream_stop(CGDisplayStreamRef displayStream) {

    if(CGDisplayStreamStop(displayStream) != kCGErrorSuccess) {
        fprintf(stderr, "%s: Error! Failed to stop the display stream.\n", __func__);
        return -1;
    }
    return 0;
}