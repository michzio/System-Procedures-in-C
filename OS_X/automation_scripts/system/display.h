//
// Created by Michal Ziobro on 15/09/2016.
//

#include <CoreGraphics/CoreGraphics.h>

#ifndef AUTOMATION_SCRIPTS_DISPLAY_H
#define AUTOMATION_SCRIPTS_DISPLAY_H

typedef void (*display_stream_handler_t)(const unsigned char *frameBuffer, const size_t frameBufferLength,
                                         const size_t frameWidth, const size_t frameHeight, const size_t bytesPerPixel);

float display_get_brightness(void);
void display_set_brightness(float level);
void display_screen_snapshot_to_desktop(void);
void display_screen_snapshot_rect_to_desktop(void);
void display_screen_snapshot_to_clipboard(void);
void display_screen_snapshot_rect_to_clipboard(void);

// TODO
/**
 * CGDisplayStream * introduced by the 'WWDC2012 506 video' API that is the solution for high performence
 * screen capture (color conversion, scaling, etc. done on GPU in VRAM) that can be used for example in remote desktop
 * apps. It can use CFRunLoopRef or dispatch queue (serial).
 */
CGDisplayStreamRef display_stream_init(const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler);
CGDisplayStreamRef display_stream_rect_init(const double x, const double y, const double width, const double height,
                                                               const size_t outWidth, const size_t outHeight, const display_stream_handler_t customDisplayStreamHandler);
int display_stream_start(CGDisplayStreamRef displayStream);
int display_stream_stop(CGDisplayStreamRef displayStream);

#endif //AUTOMATION_SCRIPTS_DISPLAY_H
