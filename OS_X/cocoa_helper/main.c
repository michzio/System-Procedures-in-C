#include <stdio.h>
#include "strings.h"

int main() {
    printf("Cocoa Helper libraries.\n");

    char *test_c_str = CFStringCopyUTF8String(CFSTR("test cocoa string"));
    printf("converted string is: %s\n", test_c_str);
    return 0;
}