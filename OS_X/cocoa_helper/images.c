//
// Created by Michal Ziobro on 22/09/2016.
//

#include <NSSystemDirectories.h>
#include <sys/stat.h>
#include "images.h"
#include "strings.h"
#include "file_system.h"
#include "exec_cmd.h"

bool CGImageSaveToFile(CGImageRef image, CFStringRef file_path, CFStringRef file_name, CFStringRef file_type) {

    // create file URL
    CFURLRef filePathURL = CFURLCreateWithString(kCFAllocatorDefault, file_path, NULL);
    CFURLRef fileURL = CFURLCreateCopyAppendingPathComponent(kCFAllocatorDefault, filePathURL, file_name, false);

    // ensure file path directories already exists or create them if not
    char *c_file_path = CFStringCopyUTF8String(file_path) + 8;
    mkdir(c_file_path, 0777);

    // create image destination
    CGImageDestinationRef imageDestination = CGImageDestinationCreateWithURL(fileURL, file_type, 1, NULL);
    if(!imageDestination) {
        fprintf(stderr, "%s: Failed to create CGImageDestination for %s/%s.\n", __func__, CFStringCopyUTF8String(file_path), CFStringCopyUTF8String(file_name));
        CFRelease(filePathURL);
        CFRelease(fileURL);
        CFRelease(imageDestination);
        return false;
    }

    CGImageDestinationAddImage(imageDestination, image, NULL);

    if(!CGImageDestinationFinalize(imageDestination)) {
        fprintf(stderr, "%s: Failed to write image to %s/%s.\n", __func__, CFStringCopyUTF8String(file_path), CFStringCopyUTF8String(file_name));
        CFRelease(filePathURL);
        CFRelease(fileURL);
        CFRelease(imageDestination);
        return false;
    }

    CFRelease(imageDestination);
    return true;
}

#define BUF_SIZE 128

static CFStringRef image_file_name(const char *file_extension) {

    // create file name for image
    char c_file_name[BUF_SIZE];

    // with current date and time
    time_t t = time(NULL);
    struct tm tm  = *localtime(&t);
    sprintf(c_file_name, "Image_%d-%02d-%02d_%02d.%02d.%02d.%s", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, file_extension);

    return CFStringCreateWithCString(kCFAllocatorDefault, c_file_name, kCFStringEncodingUTF8);
}

bool CGImageCopyToClipboard(CGImageRef image) {


    CFStringRef caches_file_path = FSGetFilePath(NSCachesDirectory, NSUserDomainMask);
    CFMutableStringRef curr_app_caches_file_path = CFStringCreateMutable(NULL, 0);
    if(curr_app_caches_file_path) {
            CFStringAppend(curr_app_caches_file_path, caches_file_path);
            CFStringAppend(curr_app_caches_file_path, CFSTR("/com.remote-controller.server"));
    }
    CFStringRef file_name = image_file_name("png");

    if(!CGImageSaveToFile(image, curr_app_caches_file_path, file_name, kUTTypePNG)) {
        fprintf(stderr, "%s: Failed to save image %s in current app caches directory %s.\n",
                __func__, CFStringCopyUTF8String(file_name), CFStringCopyUTF8String(curr_app_caches_file_path));
        CFRelease(curr_app_caches_file_path);
        CFRelease(caches_file_path);
        CFRelease(file_name);
        return false;
    }

    char clipboard_cmd[BUF_SIZE];
    sprintf(clipboard_cmd, "./tools/image_to_clipboard %s", CFStringCopyUTF8String(file_name));
    char *status = exec_cmd(clipboard_cmd);
    int status_code = atoi(status);

    // releasing memory
    CFRelease(curr_app_caches_file_path);
    CFRelease(caches_file_path);
    CFRelease(file_name);
    free(status);

    if(status_code != 0) {
        fprintf(stderr, "%s: Could not copy image to clipboard, cocoa tool failed!\n", __func__);
        return false;
    }
    return true;
}

#define COMPONENTS_PER_PIXEL 4
#define BYTES_PER_COMPONENT 1
#define BITS_PER_COMPONENT 8

unsigned char *CGImageCopyRGBAData(CGImageRef image, size_t *rgbaDataLength) {

    unsigned char *rgbaData = 0;

    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

    // allocate RGBA image components array, where each component takes one byte (unsigned char)
    *rgbaDataLength = width*height*COMPONENTS_PER_PIXEL*BYTES_PER_COMPONENT;
     rgbaData = (unsigned char*) malloc(sizeof(unsigned char) * (*rgbaDataLength));
    if(rgbaData == 0) return 0;

    // draw image using core graphics context in RGBA frame buffer
    CGContextRef context = CGBitmapContextCreate(rgbaData, width, height, BITS_PER_COMPONENT,
                                                 COMPONENTS_PER_PIXEL * width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, width, height), image);
    CGContextRelease(context);

    return rgbaData;
}