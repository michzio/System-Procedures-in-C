//
// Created by Michal Ziobro on 15/09/2016.
//

#ifndef AUTOMATION_SCRIPTS_DISPLAY_H
#define AUTOMATION_SCRIPTS_DISPLAY_H

unsigned int display_current_displayID();


float display_get_brightness(void);
void display_set_brightness(float level);
void display_get_pixel_size(size_t *displayWidth, size_t *displayHeight);

void display_screen_snapshot_to_desktop(void);
void display_screen_snapshot_rect_to_desktop(void);
void display_screen_snapshot_to_clipboard(void);
void display_screen_snapshot_rect_to_clipboard(void);
void display_screen_snapshot_to_buffer(unsigned char **rgbaData, size_t *rgbaDataLength, size_t *width, size_t *height);
void display_screen_snapshot_rect_to_buffer(unsigned char **rgbaData, size_t *rgbaDataLength, size_t *width, size_t *height);

#endif //AUTOMATION_SCRIPTS_DISPLAY_H
