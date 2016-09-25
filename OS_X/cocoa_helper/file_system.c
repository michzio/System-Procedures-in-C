//
// Created by Michal Ziobro on 23/09/2016.
//

#include <limits.h>
#include <stdio.h>
#include <NSSystemDirectories.h>
#include <sysdir.h>
#include "file_system.h"
#include "exec_cmd.h"

#define BUF_SIZE 64

CFStringRef FSGetAbsolutePath(int directory, int domainMask) {

    char path_cmd[BUF_SIZE];
    sprintf(path_cmd, "./tools/search_path_for_dir %d %d", directory, domainMask);
    char *path = exec_cmd(path_cmd);

    CFStringRef absolute_path = CFStringCreateWithCString(kCFAllocatorDefault, path, kCFStringEncodingUTF8);
    free(path);
    return absolute_path;
}

CFStringRef FSGetFilePath(int directory, int domainMask) {

    CFStringRef scheme = CFSTR("file://");
    CFStringRef absolutePath = FSGetAbsolutePath(directory, domainMask);

    CFMutableStringRef filePath = CFStringCreateMutable(NULL, 0);
    if (filePath) {

        CFStringAppend(filePath, scheme);
        CFStringAppend(filePath, absolutePath);

    }

    CFRelease(scheme);
    CFRelease(absolutePath);

    return filePath;
}