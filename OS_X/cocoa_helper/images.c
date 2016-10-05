//
// Created by Michal Ziobro on 22/09/2016.
//

#include <NSSystemDirectories.h>
#include <sys/stat.h>
#include "images.h"
#include "strings.h"
#include "file_system.h"
#include "exec_cmd.h"
#include "../../../common/bitmaps.h"

#define BYTES_PER_COMPONENT 1
#define BITS_PER_COMPONENT 8
#define COMPONENTS_PER_PIXEL 4

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
    if (curr_app_caches_file_path) {
        CFStringAppend(curr_app_caches_file_path, caches_file_path);
        CFStringAppend(curr_app_caches_file_path, CFSTR("/com.remote-controller.server"));
    }
    CFStringRef file_name = image_file_name("png");

    if (!CGImageSaveToFile(image, curr_app_caches_file_path, file_name, kUTTypePNG)) {
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

    if (status_code != 0) {
        fprintf(stderr, "%s: Could not copy image to clipboard, cocoa tool failed!\n", __func__);
        return false;
    }
    return true;
}

static unsigned char *CGImageCopyPixelData(CGImageRef image, CGColorSpaceRef colorSpace, uint32_t bitmap_info, size_t *pixelDataLength) {

    unsigned char *pixelData = 0;

    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);

    // allocate image pixel components array, where each component takes one byte (unsigned char)
    size_t dataLength = width*height*COMPONENTS_PER_PIXEL*BYTES_PER_COMPONENT;
    pixelData = (unsigned char*) malloc(sizeof(unsigned char) * (dataLength));
    if(pixelData == 0) {
        *pixelDataLength = 0;
        return 0;
    }

    // draw image using core graphics context in frame buffer
    CGContextRef context = CGBitmapContextCreate(pixelData, width, height, BITS_PER_COMPONENT,
                                                 COMPONENTS_PER_PIXEL * width, colorSpace, bitmap_info);
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, width, height), image);
    CGContextRelease(context);

    if(pixelDataLength) *pixelDataLength = dataLength;
    return pixelData;
}

static CGImageRef CGImageCreateWithPixelData(const unsigned char *pixelData, const size_t pixelDataLength,
                                             const size_t width, const size_t height, CGColorSpaceRef colorSpace, uint32_t bitmap_info) {

    if(width*height*COMPONENTS_PER_PIXEL*BYTES_PER_COMPONENT != pixelDataLength) {
        fprintf(stderr, "%s: Length of pixelData bytes array is not in accordance with the specified size of the image (width x height) you want to create.\n", __func__);
        return NULL;
    }

    CGContextRef context = CGBitmapContextCreate(pixelData, width, height, BITS_PER_COMPONENT,
                                                 COMPONENTS_PER_PIXEL * width, colorSpace, bitmap_info);
    CGImageRef image = CGBitmapContextCreateImage(context);
    CFRelease(context);

    return image;
}

unsigned char *CGImageCopyRawData(CGImageRef image, size_t *rawDataLength) {

    CGDataProviderRef dataProvider = CGImageGetDataProvider(image);
    CFDataRef data = CGDataProviderCopyData(dataProvider);
    if(rawDataLength) *rawDataLength = (size_t) CFDataGetLength(data);
    CFRelease(dataProvider);
    CFRelease(data);
    return CFDataGetBytePtr(data);
}

unsigned char *CGImageCopyRGBAData(CGImageRef image, size_t *rgbaDataLength) {

    CGColorSpaceRef colorSpaceRGB = CGColorSpaceCreateDeviceRGB();
    unsigned char *rgbaData = CGImageCopyPixelData(image, colorSpaceRGB, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big, rgbaDataLength);
    CGColorSpaceRelease(colorSpaceRGB);
    return rgbaData;
}

unsigned char *CGImageCopyARGBData(CGImageRef image, size_t *argbDataLength) {

    CGColorSpaceRef colorSpaceRGB = CGColorSpaceCreateDeviceRGB();
    unsigned char *argbData = CGImageCopyPixelData(image, colorSpaceRGB, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Big, argbDataLength);
    CGColorSpaceRelease(colorSpaceRGB);
    return argbData;
}

unsigned char *CGImageCopyCMYKData(CGImageRef image, size_t *cmykDataLength) {

    CGColorSpaceRef colorSpaceCMYK = CGColorSpaceCreateDeviceCMYK();
    unsigned char *cmykData = CGImageCopyPixelData(image, colorSpaceCMYK, kCGImageAlphaNone, cmykDataLength);
    CGColorSpaceRelease(colorSpaceCMYK);
    return cmykData;
}

CGImageRef CGImageCreateWithRawData(const unsigned char *rawData, const size_t rawDataLength, const size_t width, const size_t height, CGColorSpaceRef colorSpace) {

    CFDataRef data = CFDataCreate(kCFAllocatorDefault, rawData, (long) rawDataLength);
    CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData(data);
    CGImageRef image = CGImageCreate(width, height, BITS_PER_COMPONENT, BITS_PER_COMPONENT*COMPONENTS_PER_PIXEL, BYTES_PER_COMPONENT*COMPONENTS_PER_PIXEL*width,
                                   colorSpace, kCGBitmapByteOrderDefault, dataProvider, NULL, false, kCGRenderingIntentDefault);
    CFRelease(dataProvider);
    CFRelease(data);
    return image;
}

CGImageRef CGImageCreateWithRGBAData(const unsigned char *rgbaData, const size_t rgbaDataLength, const size_t width, const size_t height) {

    CGColorSpaceRef colorSpaceRGB = CGColorSpaceCreateDeviceRGB();
    CGImageRef image = CGImageCreateWithPixelData(rgbaData, rgbaDataLength, width, height, colorSpaceRGB, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpaceRGB);
    return image;
}

CGImageRef CGImageCreateWithARGBData(const unsigned char *argbData, const size_t argbDataLength, const size_t width, const size_t height) {

    CGColorSpaceRef colorSpaceRGB = CGColorSpaceCreateDeviceRGB();
    CGImageRef image = CGImageCreateWithPixelData(argbData, argbDataLength, width, height, colorSpaceRGB, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpaceRGB);
    return image;
}

CGImageRef CGImageCreateWithCMYKData(const unsigned char *cmykData, const size_t cmykDataLength, const size_t width, const size_t height) {

    CGColorSpaceRef colorSpaceCMYK = CGColorSpaceCreateDeviceCMYK();
    CGImageRef image = CGImageCreateWithPixelData(cmykData, cmykDataLength, width, height, colorSpaceCMYK,
                                                  kCGImageAlphaNone);
    CGColorSpaceRelease(colorSpaceCMYK);
    return image;
}

void CGImageDumpInfo(CGImageRef image, bool shouldPrintPixelData) {

    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image);
    size_t bytesPerRow = CGImageGetBytesPerRow(image);
    size_t bitsPerPixel = CGImageGetBitsPerPixel(image);
    size_t bitsPerComponent = CGImageGetBitsPerComponent(image);
    size_t componentsPerPixel = bitsPerPixel / bitsPerComponent;
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(image);

    printf("\n");
    printf("CGImageGetWidth: %d\n", width);
    printf("CGImageGetHeight: %d\n", height);
    printf("CGColorSpaceModel: %d\n", CGColorSpaceGetModel(colorSpace));
    printf("CGImageGetBytesPerRow: %d\n", bytesPerRow);
    printf("CGImageGetBitsPerPixel: %d\n", bitsPerPixel);
    printf("CGImageGetBitsPerComponent: %d\n", bitsPerComponent);
    printf("components per pixel: %d\n", componentsPerPixel);
    printf("CGImageGetBitmapInfo: 0x%.8X\n", (unsigned) bitmapInfo);
    printf("->kCGBitmapAlphaInfoMask = %s\n", (bitmapInfo & kCGBitmapAlphaInfoMask) ? "YES" : "NO");
    printf("->kCGBitmapFloatComponents = %s\n", (bitmapInfo & kCGBitmapFloatComponents) ? "YES" : "NO");
    printf("->kCGBitmapByteOrderMask = 0x%.8X\n", (bitmapInfo & kCGBitmapByteOrderMask));
    printf("->->kCGBitmapByteOrderDefault = %s\n",
           ((bitmapInfo & kCGBitmapByteOrderMask) == kCGBitmapByteOrderDefault) ? "YES" : "NO");
    printf("->->kCGBitmapByteOrder16Little = %s\n",
           ((bitmapInfo & kCGBitmapByteOrderMask) == kCGBitmapByteOrder16Little) ? "YES" : "NO");
    printf("->->kCGBitmapByteOrder32Little = %s\n",
           ((bitmapInfo & kCGBitmapByteOrderMask) == kCGBitmapByteOrder32Little) ? "YES" : "NO");
    printf("->->kCGBitmapByteOrder16Big = %s\n",
           ((bitmapInfo & kCGBitmapByteOrderMask) == kCGBitmapByteOrder16Big) ? "YES" : "NO");
    printf("->->kCGBitmapByteOrder32Big = %s\n",
           ((bitmapInfo & kCGBitmapByteOrderMask) == kCGBitmapByteOrder32Big) ? "YES" : "NO");

    if(!shouldPrintPixelData) return;

    PixelBytesArrayDump( CGImageCopyRawData(image, 0), width, height, bytesPerRow, componentsPerPixel);

    printf("\n");
}