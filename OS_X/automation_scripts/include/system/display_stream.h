//
// Created by Michal Ziobro on 09/10/2016.
//

#include <CoreGraphics/CoreGraphics.h>

#ifndef AUTOMATION_SCRIPTS_DISPLAY_STREAM_H
#define AUTOMATION_SCRIPTS_DISPLAY_STREAM_H
/**
 * CGDisplayStream * introduced by the 'WWDC2012 506 video' API that is the solution for high performence
 * screen capture (color conversion, scaling, etc. done on GPU in VRAM) that can be used for example in remote desktop
 * apps. It can use CFRunLoopRef or dispatch queue (serial).
 */

// callback gets new frame buffer
typedef void (*display_stream_handler_t)(const void *handlerArgs, const unsigned char *frameBuffer, const size_t frameBufferLength,
                                         const size_t frameWidth, const size_t frameHeight, const size_t bytesPerPixel);
// callback gets only update of current frame buffer
// in current frame buffer should be replaced rectangle (offsetX, offsetY, updateWidth, updateHeight)
typedef void (*display_stream_updates_handler_t)(const void *handlerArgs, const unsigned char *updateBuffer, const size_t updateBufferLength,
                                                 const size_t offsetX, const size_t offsetY, const size_t updateWidth,
                                                 const size_t updateHeight, const size_t bytesPerPixel);

CGDisplayStreamRef display_stream_init(const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler, const void *handlerArgs);
CGDisplayStreamRef display_stream_rect_init(const double x, const double y, const double width, const double height,
                                            const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler, const void *handlerArgs);
CGDisplayStreamRef display_stream_updates_init(const size_t outWidth, const size_t outHeight, const display_stream_updates_handler_t customDisplayStreamUpdatesHandler, const void *handlerArgs);
CGDisplayStreamRef display_stream_rect_updates_init(const double x, const double y, const double width, const double height,
                                                    const size_t outWidth, const size_t outHeight, const display_stream_updates_handler_t customDisplayStreamUpdatesHandler, const void *handlerArgs);
int display_stream_start(CGDisplayStreamRef displayStream);
int display_stream_stop(CGDisplayStreamRef displayStream);
void display_stream_free(CGDisplayStreamRef displayStream);

#endif //AUTOMATION_SCRIPTS_DISPLAY_STREAM_H
