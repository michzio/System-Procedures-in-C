#include <stdio.h>
#include <NSSystemDirectories.h>
#include "strings.h"
#include "file_system.h"
#include "images.h"
#include "../../../common/bitwise.h"
#include "../../../common/libraries/md5/md5.h"
#include "../../../common/libraries/png/png-decoding.h"
#include "../../../common/bitmaps.h"

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

    /*
    CGDirectDisplayID displayID = CGMainDisplayID();
    CGImageRef image = CGDisplayCreateImage(displayID);

    size_t rgbaDataLength = 0;
    unsigned char * rgbaData = CGImageCopyRGBAData(image, &rgbaDataLength);
    size_t imgWidth = CGImageGetWidth(image);
    size_t imgHeight = CGImageGetHeight(image);
    CGImageRef newImage = CGImageCreateWithRGBAData(rgbaData, rgbaDataLength,  imgWidth, imgHeight);

    CGImageCopyToClipboard(newImage);
    */

    CGDirectDisplayID displayID = CGMainDisplayID();

    printf("taking first screen shot...\n");
    sleep(2);
    CGImageRef A_image = CGDisplayCreateImage(displayID);

    size_t A_rgbaDataLength = 0;
    unsigned char *A_rgbaData = CGImageCopyRGBAData(A_image, &A_rgbaDataLength);

    size_t screen_width = CGImageGetWidth(A_image);
    size_t screen_height = CGImageGetHeight(A_image);

    printf("taking next screen shot...\n");
    sleep(2);
    CGImageRef B_image = CGDisplayCreateImage(displayID);

    size_t B_rgbaDataLength = 0;
    unsigned char *B_rgbaData = CGImageCopyRGBAData(B_image, &B_rgbaDataLength);

    if( A_rgbaDataLength != B_rgbaDataLength )
        printf("Lengths of bytes arrays A and B are different.\n");

    if( screen_width != CGImageGetWidth(B_image) || screen_height != CGImageGetHeight(B_image))
        printf("Screen sizes of images A and B are different.\n");

    unsigned char *xorRgbaData = bitwise_xor(A_rgbaData, B_rgbaData, A_rgbaDataLength);
    size_t xorRgbaDataLength = A_rgbaDataLength;

    // create image based on xor-ed bytes arrays A and B of rgba data
    //CGImageRef xorImage = CGImageCreateWithRGBAData(xorRgbaData, A_rgbaDataLength, screen_width, screen_height);
    //CGImageCopyToClipboard(xorImage);

    //CGImageDumpInfo(A_image, true);
    printf("RGBA "); PixelBytesArrayDump(A_rgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);
    //CGImageDumpInfo(B_image, true);
    printf("RGBA "); PixelBytesArrayDump(B_rgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);
    //CGImageDumpInfo(xorImage, false);
    printf("RGBA "); PixelBytesArrayDump(xorRgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);

    size_t A_rgbDataLength = 0;
    unsigned char *A_rgbData = RGBABytesArraySkipAlpha(A_rgbaData, A_rgbaDataLength, &A_rgbDataLength);
    printf("RGB "); PixelBytesArrayDump(A_rgbData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGB_COMPONENTS_PER_PIXEL);

    size_t A_argbDataLength = 0;
    unsigned char *A_argbData = RGBBytesArrayPrependAlpha(A_rgbData, A_rgbDataLength, 0xFF, &A_argbDataLength);
    printf("ARGB "); PixelBytesArrayDump(A_argbData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), ARGB_COMPONENTS_PER_PIXEL);

    printf("xor RGBA "); PixelBytesArrayDump(xorRgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);
    RGBABytesArraySetAlpha(xorRgbaData, xorRgbaDataLength, 0xFF);
    printf("xor RGBA "); PixelBytesArrayDump(xorRgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);

    // create image based on xor-ed bytes arrays A and B of rgba data
    CGImageRef xorImage = CGImageCreateWithRGBAData(xorRgbaData, xorRgbaDataLength, screen_width, screen_height);
    CGImageCopyToClipboard(xorImage);
    RGBABytesArraySetAlpha(xorRgbaData, xorRgbaDataLength, 0x00);

    // A_image - 1st image
    // B_image - 2nd image
    // xorImage - difference between 1st and 2nd
    // so A_image XOR xorImage -> B_image ?

    unsigned char *new_B_rgbaData = bitwise_xor(A_rgbaData, xorRgbaData, A_rgbaDataLength);
    size_t new_B_rgbaDataLength = A_rgbaDataLength;
    printf("RGBA "); PixelBytesArrayDump(B_rgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);
    printf("RGBA "); PixelBytesArrayDump(new_B_rgbaData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), RGBA_COMPONENTS_PER_PIXEL);
    CGImageRef new_B_image = CGImageCreateWithRGBAData(new_B_rgbaData, new_B_rgbaDataLength, screen_width, screen_height);
 //   CGImageCopyToClipboard(new_B_image);

    char *md5_A_image = md5_hash(A_rgbaData, A_rgbaDataLength);
    char *md5_B_image = md5_hash(B_rgbaData, B_rgbaDataLength);

    printf("MD5 A image: %s\n", md5_A_image);
    printf("MD5 B image: %s\n", md5_B_image);

    /*
    CGImageRef img = CGImageCreateWithRGBAData(A_rgbaData, A_rgbaDataLength, screen_width, screen_height);
    CGImageCopyToClipboard(img);

    size_t A_argbDataLength;
    unsigned char *A_argbData = CGImageCopyARGBData(A_image, &A_argbDataLength);
    PixelBytesArrayDump(A_argbData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), 4);
    CGImageRef img2 = CGImageCreateWithARGBData(A_argbData, A_argbDataLength, screen_width, screen_height);
    CGImageCopyToClipboard(img2);

    size_t rawDataLength = 0;
    unsigned char *rawData = CGImageCopyRawData(A_image, &rawDataLength);
    PixelBytesArrayDump(rawData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), 4);
    CGImageRef rawImage = CGImageCreateWithRawData(rawData, rawDataLength, screen_width, screen_height, CGColorSpaceCreateDeviceRGB());
    CGImageCopyToClipboard(rawImage);
    */

    /*
    size_t A_cmykDataLength = 0;
    unsigned char *A_cmykData = CGImageCopyCMYKData(A_image, &A_cmykDataLength);
    printf("CMYK "); PixelBytesArrayDump(A_cmykData, screen_width, screen_height, CGImageGetBytesPerRow(A_image), 4);
    CGImageRef *A_cmykImage = CGImageCreateWithCMYKData(A_cmykData, A_cmykDataLength, screen_width, screen_height);
    CGImageCopyToClipboard(A_cmykImage);
    */

    unsigned char *rgbaData = 0;
    size_t rgbaDataLength = 0;
    size_t width = 0;
    size_t height = 0;
    int result = readRGBAfromPNGFile("/Users/michzio/Desktop/River.png", &rgbaData, &rgbaDataLength, &width, &height, NULL);
    printf("Reading RGBA from PNG file: %d\n", result);

    CGImageRef image = CGImageCreateWithRGBAData(rgbaData, rgbaDataLength, width, height);
    CGImageCopyToClipboard(image);

    return 0;
}