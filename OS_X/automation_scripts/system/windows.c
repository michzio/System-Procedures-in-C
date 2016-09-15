//
// Created by Michal Ziobro on 06/09/2016.
//
#include "../../cocoa_helper/strings.h"

char *front_window_owner(void) {

    CFArrayRef windows = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);

    for(CFIndex idx = 0; idx < CFArrayGetCount(windows); idx++) {

        CFDictionaryRef window = CFArrayGetValueAtIndex(windows, idx);

        int64_t window_layer;
        CFNumberRef window_layer_ref = CFDictionaryGetValue(window, kCGWindowLayer);
        CFNumberGetValue(window_layer_ref, kCFNumberSInt64Type, &window_layer);
        CFRelease(window_layer_ref);
        if(window_layer == 0) {
            char *window_owner;
            CFStringRef window_owner_ref = CFDictionaryGetValue(window, kCGWindowOwnerName);
            window_owner = CFStringCopyUTF8String(window_owner_ref);
            CFRelease(window_owner_ref);
            return window_owner;
        }
    }
    CFRelease(windows);
    return NULL;
}