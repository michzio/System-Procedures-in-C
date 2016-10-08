//
// Created by Michal Ziobro on 15/09/2016.
//

#include <CoreGraphics/CoreGraphics.h>

#ifndef AUTOMATION_SCRIPTS_DISPLAY_H
#define AUTOMATION_SCRIPTS_DISPLAY_H

typedef void (*screen_stream_handler_t)(unsigned char *screenData, size_t screenDataLength);

float display_get_brightness(void);
void display_set_brightness(float level);
void display_screen_snapshot_to_desktop(void);
void display_screen_snapshot_rect_to_desktop(void);
void display_screen_snapshot_to_clipboard(void);
void display_screen_snapshot_rect_to_clipboard(void);

// TODO
CGDisplayStreamRef display_stream(const size_t outWidth, const size_t outHeight, const screen_stream_handler_t stream_handler);
int display_stream_start(CGDisplayStreamRef displayStream);
int display_stream_stop(CGDisplayStreamRef displayStream);

#endif //AUTOMATION_SCRIPTS_DISPLAY_H
