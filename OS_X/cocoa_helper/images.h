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
unsigned char *CGImageCopyRGBAData(CGImageRef image, size_t *rgbaDataLength);

#endif //COCOA_HELPER_IN_OS_X_IMAGES_H
