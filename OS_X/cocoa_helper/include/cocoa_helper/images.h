//
// Created by Michal Ziobro on 22/09/2016.
//
#include <CoreServices/CoreServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/ImageIO.h>

#ifndef COCOA_HELPER_IN_OS_X_IMAGES_H
#define COCOA_HELPER_IN_OS_X_IMAGES_H

#define kUTTypePNG CFSTR("public.png")
#define kUTTypeJPEG CFSTR("public.jpeg")
#define kUTTypeTIFF CFSTR("public.tiff")
#define kUTTypeGIF CFSTR("com.compuserve.gif")

bool CGImageSaveToFile(CGImageRef image, CFStringRef file_path, CFStringRef file_name, CFStringRef file_type);
bool CGImageCopyToClipboard(CGImageRef image);

unsigned char *CGImageCopyRawData(CGImageRef image, size_t *dataLength);
unsigned char *CGImageCopyRGBAData(CGImageRef image, size_t *rgbaDataLength);
unsigned char *CGImageCopyARGBData(CGImageRef image, size_t *argbDataLength);
unsigned char *CGImageCopyCMYKData(CGImageRef image, size_t *cmykDataLength);
CGImageRef CGImageCreateWithRawData(const unsigned char *rawData, const size_t rawDataLength, const size_t width, const size_t height, CGColorSpaceRef colorSpace);
CGImageRef CGImageCreateWithRGBAData(const unsigned char *rgbaData, const size_t rgbaDataLength, const size_t imageWidth, const size_t imageHeight);
CGImageRef CGImageCreateWithARGBData(const unsigned char *argbData, const size_t argbDataLength, const size_t width, const size_t height);
CGImageRef CGImageCreateWithCMYKData(const unsigned char *cmykData, const size_t cmykDataLength, const size_t width, const size_t height);
void CGImageDumpInfo(CGImageRef image, bool shouldPrintPixelData);

#endif //COCOA_HELPER_IN_OS_X_IMAGES_H
