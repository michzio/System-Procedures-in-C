#include <stdio.h>
#include <NSSystemDirectories.h>
#include "strings.h"
#include "file_system.h"
#include "images.h"

int main() {
    printf("Cocoa Helper libraries.\n");

    char *test_c_str = CFStringCopyUTF8String(CFSTR("test cocoa string"));
    printf("converted string is: %s\n", test_c_str);

    /*
    CGDirectDisplayID displayID = CGMainDisplayID();
    CGImageRef image = CGDisplayCreateImage(displayID);
    //CFStringRef file_path = FSGetFilePath(NSDesktopDirectory, NSUserDomainMask);
    //CGImageSaveToFile(image, file_path, CFSTR("test.png"), kUTTypePNG);
    CGImageCopyToClipboard(image);
    */

    return 0;
}