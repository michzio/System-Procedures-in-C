//
// Created by Michal Ziobro on 07/09/2016.
//

#include <IOSurface/IOSurface.h>
#include <CoreFoundation/CoreFoundation.h>

CFPropertyListRef CFPropertyListCopyFromFileInMainBundle(CFStringRef filePath) {

    CFDataRef plist_data;
    SInt32 error_code;
    CFErrorRef error;

    CFBundleRef bundle = CFBundleGetMainBundle();
    CFURLRef bundle_URL = CFBundleCopyBundleURL(bundle);
    CFURLRef plist_URL = CFURLCreateWithString(kCFAllocatorDefault, filePath, bundle_URL);

    CFURLCreateDataAndPropertiesFromResource(kCFAllocatorDefault, plist_URL, &plist_data, NULL, NULL, &error_code);
    CFPropertyListRef plist = CFPropertyListCreateWithData(kCFAllocatorDefault, plist_data, kCFPropertyListImmutable, NULL, &error);

    if(plist_data) {
        CFRelease(plist_data);
    } else {
        CFRelease(error);
    }

    return plist;
}