//
// Created by Michal Ziobro on 23/09/2016.
//

#include <CoreServices/CoreServices.h>

#ifndef COCOA_HELPER_IN_OS_X_FILE_SYSTEM_H
#define COCOA_HELPER_IN_OS_X_FILE_SYSTEM_H

CFStringRef FSGetAbsolutePath(int directory, int domainMask);
CFStringRef FSGetFilePath(int directory, int domainMask);

#endif //COCOA_HELPER_IN_OS_X_FILE_SYSTEM_H
