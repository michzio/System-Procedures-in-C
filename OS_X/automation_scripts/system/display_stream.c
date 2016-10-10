//
// Created by Michal Ziobro on 09/10/2016.
//

#include <dispatch/dispatch.h>
#include <IOKit/IOTypes.h>
#include <IOKit/IOKitLib.h>
#include <IOSurface/IOSurface.h>
#include <CoreGraphics/CoreGraphics.h>
#include "display_stream.h"
#include "display.h"

// serial dispatch queue used by CGDisplayStreamRef
static dispatch_queue_t dispatch_queue;

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
                                                                    uint64_t displayTime, // mach absolute time when event occurred
                                                                    IOSurfaceRef __nullable frameSurface,
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
                fprintf(stderr, "%s: The display stream has been stopped.\n", __func__);
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

// generic display stream updates initializer
CGDisplayStreamRef _display_stream_updates_init(const CFDictionaryRef properties, const size_t outWidth, const size_t outHeight, const display_stream_updates_handler_t customDisplayStreamUpdatesHandler) {

    /**
     * CGDisplayStreamRef callback block that provides new display frames as IOSurfaceRef objects and display updates object.
     * IOSurfaceRef object contains frame (pixels) from the display. CGDisplayStreamUpdateRef object contains information
     * about changes in display and provides list of CGRect rectangles where this changes occured. There is no need to update
     * entire frame buffer, as we can update frame buffer only in this well defined subregions.
     */
    CGDisplayStreamFrameAvailableHandler display_stream_updates_handler = ^(CGDisplayStreamFrameStatus status,
                                                                            uint64_t displayTime, // mach absolute time when event occurred
                                                                            IOSurfaceRef __nullable frameSurface,
                                                                            CGDisplayStreamUpdateRef __nullable updateRef) {
        switch(status) {
            case kCGDisplayStreamFrameStatusFrameComplete:
                // A new frame was generated.
                break;
            case kCGDisplayStreamFrameStatusFrameIdle:
                fprintf(stderr, "%s: A new frame was not generated because the display did not change.\n", __func__);
                return;
            case kCGDisplayStreamFrameStatusFrameBlank:
                fprintf(stderr, "$s: A new frame was not generated because the display has gone blank.\n", __func__);
                return;
            case kCGDisplayStreamFrameStatusStopped:
                fprintf(stderr, "%s: The display stream has been stopped.\n", __func__);
                return;
            default:
                fprintf(stderr, "%s: Unhandled display stream frame status.\n", __func__);
                return;
        }

        // lock IOSurface to prevent frame buffer overwritting by operating system
        IOSurfaceLock(frameSurface, kIOSurfaceLockReadOnly, NULL);

        size_t bytesPerElement = IOSurfaceGetBytesPerElement(frameSurface);
        size_t frameBufferBytesPerRow = IOSurfaceGetBytesPerRow(frameSurface);
        uint8_t *frameBuffer = (uint8_t *) IOSurfaceGetBaseAddress(frameSurface);

        size_t rectCount = 0;
        CGRect *rects = 0;
        unsigned char **updateBuffers = 0;
        size_t *updateBuffersLengths = 0;
        size_t updateBufferBytesPerRow = 0;
        size_t frameBufferOffset = 0;

        // helper variables:
        size_t rectX = 0, rectY = 0, rectWidth = 0, rectHeight = 0;

        rects = CGDisplayStreamUpdateGetRects(updateRef, kCGDisplayStreamUpdateDirtyRects, &rectCount);

        updateBuffers = (unsigned char **) malloc(sizeof(unsigned char *)*rectCount);
        updateBuffersLengths = (size_t *) malloc(sizeof(size_t) * rectCount);
        for(int i=0; i<rectCount; i++) {
            rectX = (size_t) rects[i].origin.x;
            rectY = (size_t) rects[i].origin.y;
            rectWidth = (size_t) (rects[i].size.width + 0.5);
            rectHeight = (size_t) (rects[i].size.height + 0.5);

            updateBufferBytesPerRow = rectWidth * bytesPerElement;
            updateBuffersLengths[i] = updateBufferBytesPerRow * rectHeight;
            updateBuffers[i] = (unsigned char *) malloc(sizeof(unsigned char) * updateBuffersLengths[i]);


            // copy sub-frame of surface frame buffer given by ith rectangle (need to be copied row by row)
            for(int dy = 0; dy<rectHeight; dy++) {

                // offset in frame buffer of dy-th row of sub-frame to be copied
                frameBufferOffset = (frameBufferBytesPerRow * (rectY + dy)) + (rectX*bytesPerElement);
                memcpy(updateBuffers[i] + updateBufferBytesPerRow*dy, frameBuffer + frameBufferOffset, updateBufferBytesPerRow);
            }
        }

        IOSurfaceUnlock(frameSurface, kIOSurfaceLockReadOnly, NULL);

        for(int i=0; i<rectCount; i++) {
            customDisplayStreamUpdatesHandler(updateBuffers[i], updateBuffersLengths[i], (size_t) rects[i].origin.x, (size_t) rects[i].origin.y,
                                              (size_t)(rects[i].size.width + 0.5), (size_t)(rects[i].size.height + 0.5), bytesPerElement);
        }

        free(updateBuffersLengths);
        free(updateBuffers);
    };

    CGDirectDisplayID  displayID = display_current_displayID();

    dispatch_queue_create("display stream update queue", DISPATCH_QUEUE_SERIAL);

    // possible pixel formats are:
    // 'BGRA' - Packed Little Endian ARGB8888
    // 'l10r' - Packed Little Endian ARGB2101010
    // '420v' - 2-plane "video" range YCbCr 4:2:0
    // '420f' - 2-plane "full" range YCbCr 4:2:0
    CGDisplayStreamRef displayStream = CGDisplayStreamCreateWithDispatchQueue(displayID, outWidth, outHeight, 'BGRA', properties, dispatch_queue, display_stream_updates_handler);
    if(displayStream == NULL) {
        fprintf(stderr, "%s: Error! Failed to create a display stream used to capture the screen updates.\n", __func__);
        return NULL;
    }

    return displayStream;
}


CGDisplayStreamRef display_stream_rect_updates_init(const double x, const double y, const double width, const double height,
                                                    const size_t outWidth, const size_t outHeight, const display_stream_updates_handler_t customDisplayStreamUpdatesHandler) {

    // create properties dictionary
    CFMutableDictionaryRef properties = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);
    // set screen rect to be streamed
    CFDictionaryAddValue(properties,
                         kCGDisplayStreamSourceRect,
                         CGRectCreateDictionaryRepresentation(CGRectMake(x, y, width, height)));

    return _display_stream_updates_init(properties, outWidth, outHeight, customDisplayStreamUpdatesHandler);
}
CGDisplayStreamRef display_stream_updates_init(const size_t outWidth, const size_t outHeight, const display_stream_updates_handler_t customDisplayStreamUpdatesHandler) {

    // create properties dictionary
    CFMutableDictionaryRef properties = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);

    return _display_stream_updates_init(properties, outWidth, outHeight, customDisplayStreamUpdatesHandler);
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

void display_stream_free(CGDisplayStreamRef displayStream) {

    // deallocate display stream
    if(displayStream) {
        CFRelease(displayStream);
        displayStream == NULL;
    }
}