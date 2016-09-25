//
// Created by Michal Ziobro on 15/09/2016.
//

#ifndef AUTOMATION_SCRIPTS_DISPLAY_H
#define AUTOMATION_SCRIPTS_DISPLAY_H

float display_get_brightness(void);
void display_set_brightness(float level);
void display_screen_snapshot_to_desktop(void);
void display_screen_snapshot_rect_to_desktop(void);
void display_screen_snapshot_to_clipboard(void);
void display_screen_snapshot_rect_to_clipboard(void);

#endif //AUTOMATION_SCRIPTS_DISPLAY_H
