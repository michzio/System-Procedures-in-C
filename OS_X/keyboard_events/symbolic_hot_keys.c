//
// Created by Michal Ziobro on 28/08/2016.
//

#include "symbolic_hot_keys.h"

static const CFStringRef kApplicationName = CFSTR("com.apple.symbolichotkeys");
static const CFStringRef kAppleSymbolicHotKeysKey = CFSTR("AppleSymbolicHotKeys");
static const CFStringRef kEnabledKey = CFSTR("enabled");
static const CFStringRef kValueKey = CFSTR("value");
static const CFStringRef kParametersKey = CFSTR("parameters");
static const CFStringRef kTypeKey = CFSTR("type");

static char * CFStringCopyUTF8String(CFStringRef aString) {
    if (aString == NULL) {
        return NULL;
    }
    CFIndex length = CFStringGetLength(aString);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
    char *buffer = (char *)malloc(maxSize);
    if (CFStringGetCString(aString, buffer, maxSize, kCFStringEncodingUTF8)) {
        return buffer;
    }
    return NULL;
}

static symbolic_hot_keys_t *apple_symbolic_hot_keys_get(int shk_id) {

    CFPropertyListRef app_plist = CFPreferencesCopyAppValue(kAppleSymbolicHotKeysKey, kApplicationName);
    if(app_plist == NULL) {
        fprintf(stderr, "%s: Could not copy app value for AppleSymbolicHotKeys key from com.apple.symbolichotkeys.\n", __func__);
        return NULL;
    }

    // make sure application property list is a dictionary
    if( CFGetTypeID(app_plist) != CFDictionaryGetTypeID() ) {
        fprintf(stderr, "%s: application property list is not of the dictionary type.\n", __func__);
        return NULL;
    }

    // get symbolic hot keys dictionary for given shk_id key from application property list dictionary
    CFPropertyListRef shk_plist = CFDictionaryGetValue(app_plist, CFStringCreateWithFormat(NULL, NULL, CFSTR("%d"), shk_id) );
    if(shk_plist == NULL) {
        fprintf(stderr, "%s: Could not get symbolic hot keys value for given shk_id key from application property list dictionary.\n", __func__);
        return NULL;
    }

    // make sure symbolic hot keys property list is a dictionary
    if( CFGetTypeID(shk_plist) != CFDictionaryGetTypeID() ) {
        fprintf(stderr, "%s: symbolic hot keys property list is not of the dictionary type.\n", __func__);
        return NULL;
    }

    // to test use: CFShow(shk_plist);

    bool shk_enabled = CFBooleanGetValue(CFDictionaryGetValue(shk_plist, kEnabledKey));
    CFPropertyListRef shk_params = CFDictionaryGetValue(CFDictionaryGetValue(shk_plist, kValueKey), kParametersKey);
    CFStringRef shk_type = (CFStringRef) CFDictionaryGetValue(CFDictionaryGetValue(shk_plist, kValueKey), kTypeKey);

    CFNumberRef shk_ascii_code = CFArrayGetValueAtIndex(shk_params, 0);
    CFNumberRef shk_virtual_key_code = CFArrayGetValueAtIndex(shk_params, 1);
    CFNumberRef shk_modifier_keys_flags = CFArrayGetValueAtIndex(shk_params, 2);

    int64_t ascii_code; CFNumberGetValue(shk_ascii_code, kCFNumberSInt64Type, &ascii_code);
    int64_t virtual_key_code; CFNumberGetValue(shk_virtual_key_code, kCFNumberSInt64Type, &virtual_key_code);
    int64_t modifier_keys_flags; CFNumberGetValue(shk_modifier_keys_flags, kCFNumberSInt64Type, &modifier_keys_flags);

    symbolic_hot_keys_t *shk = malloc(sizeof(symbolic_hot_keys_t));
    shk->shk_id = shk_id;
    shk->enabled = (int) shk_enabled;
    shk->type = CFStringCopyUTF8String(shk_type);
    shk->ASCII_code = ascii_code;
    shk->virtual_key_code = virtual_key_code;
    shk->modifier_keys_flags = modifier_keys_flags;

    return shk;
}

static void apple_symbolic_hot_keys_set(int shk_id, const symbolic_hot_keys_t *shk) {

}

void test_shk(void) {

    symbolic_hot_keys_t *shk = apple_symbolic_hot_keys_get(kSHKCopyPictureOfScreenToTheClipboard);

    printf("symbolic hot keys id => %d\n", shk->shk_id);
    printf("%s => %d\n", CFStringCopyUTF8String(kEnabledKey), shk->enabled);
    printf("%s => %s\n", CFStringCopyUTF8String(kTypeKey), shk->type);
    printf("ascii code => %lld\n", shk->ASCII_code);
    printf("virtual key code => %lld\n", shk->virtual_key_code);
    printf("modifier keys flags => %lld\n", shk->modifier_keys_flags);

    free(shk);
}