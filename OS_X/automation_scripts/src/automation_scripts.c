//
// Created by Michal Ziobro on 06/09/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include "cocoa_helper/exec_cmd.h"

void display_notification(const char *message, const char *title, const char *subtitle) {

    char osascript[4096];
    sprintf(osascript, "osascript -e 'display notification \"%s\" with title \"%s\" subtitle \"%s\" sound name \"Frog\"' ", message, title, subtitle);
    //printf(osascript);
    system(osascript);
}