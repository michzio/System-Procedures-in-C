//
// Created by Michal Ziobro on 28/08/2016.
//
#include "../cocoa_helper/strings.h"
#include "../cocoa_helper/property_list.h"
#include "symbolic_hot_keys.h"
#include "keyboard_events.h"

static const CFStringRef kApplicationName = CFSTR("com.apple.symbolichotkeys");
static const CFStringRef kAppleSymbolicHotKeysKey = CFSTR("AppleSymbolicHotKeys");
static const CFStringRef kEnabledKey = CFSTR("enabled");
static const CFStringRef kValueKey = CFSTR("value");
static const CFStringRef kParametersKey = CFSTR("parameters");
static const CFStringRef kTypeKey = CFSTR("type");

static const CFStringRef kDefaultSymbolicHotKeysPlist = CFSTR("resources/default_symbolichotkeys.plist");

static symbolic_hot_keys_t *symbolic_hot_keys_get(CFPropertyListRef app_plist, int shk_id) {

    // make sure application property list is a dictionary
    if( CFGetTypeID(app_plist) != CFDictionaryGetTypeID() ) {
        fprintf(stderr, "%s: application property list is not of the dictionary type.\n", __func__);
        return NULL;
    }

    // get symbolic hot keys dictionary for given shk_id key from application property list dictionary
    CFStringRef shk_id_string = CFStringCreateWithFormat(NULL, NULL, CFSTR("%d"), shk_id);
    CFPropertyListRef shk_plist = CFDictionaryGetValue(app_plist, shk_id_string );
    CFRelease(shk_id_string);
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

static symbolic_hot_keys_t *apple_symbolic_hot_keys_get(int shk_id) {

    CFPropertyListRef app_plist = CFPreferencesCopyAppValue(kAppleSymbolicHotKeysKey, kApplicationName);
    if(app_plist == NULL) {
        fprintf(stderr, "%s: Could not copy app value for AppleSymbolicHotKeys key from com.apple.symbolichotkeys.\n", __func__);
        return NULL;
    }

    return symbolic_hot_keys_get(app_plist, shk_id);
}

static symbolic_hot_keys_t *default_symbolic_hot_keys_get(int shk_id) {

    CFPropertyListRef default_plist = CFPropertyListCopyFromFileInMainBundle(kDefaultSymbolicHotKeysPlist);
    CFPropertyListRef app_plist = CFDictionaryGetValue(default_plist, kAppleSymbolicHotKeysKey);

    return symbolic_hot_keys_get(app_plist, shk_id);
}

static void apple_symbolic_hot_keys_enable(int shk_id, bool enabled) {

    // copy application property list
    CFPropertyListRef app_plist = CFPreferencesCopyAppValue(kAppleSymbolicHotKeysKey, kApplicationName);
    // make sure application property list is a dictionary
    if( CFGetTypeID(app_plist) != CFDictionaryGetTypeID() ) {
        fprintf(stderr, "%s: application property list is not of the dictionary type.\n", __func__);
        return;
    }
    // get current symbolic hot keys dictionary
    CFStringRef shk_id_string = CFStringCreateWithFormat(NULL, NULL, CFSTR("%d"), shk_id);
    CFPropertyListRef shk_plist = CFDictionaryGetValue(app_plist, shk_id_string);
    // create a mutable copy of symbolic hot keys dictionary
    CFMutableDictionaryRef shk_dict = CFDictionaryCreateMutableCopy(kCFAllocatorDefault, 0, shk_plist);
    CFRelease(shk_plist);

    // to test use: CFShow(shk_dict);

    // update enabled item in shk dictionary
    CFDictionarySetValue(shk_dict, kEnabledKey, enabled == 1 ? kCFBooleanTrue : kCFBooleanFalse);

    // create a mutable copy of application property list dictionary
    CFMutableDictionaryRef app_plist_dict = CFDictionaryCreateMutableCopy(kCFAllocatorDefault, 0, app_plist);

    // update symbolic hot keys in application property list dictionary
    CFDictionarySetValue(app_plist_dict, shk_id_string, shk_dict);

    // save changes in application property list
    CFPreferencesSetAppValue(kAppleSymbolicHotKeysKey, app_plist_dict, kApplicationName);
    if(!CFPreferencesAppSynchronize(kApplicationName)) {
        fprintf(stderr, "%s: could not synchronize changes in application property list.\n", __func__);
        return;
    }

    CFRelease(shk_id_string);
    CFRelease(shk_dict);
    CFRelease(app_plist_dict);
    CFRelease(app_plist);
}

static void apple_symbolic_hot_keys_set(int shk_id, const symbolic_hot_keys_t *shk) {

    // create symbolic hot keys dictionary
    CFMutableDictionaryRef shk_dict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    // put enabled item into shk dictionary
    CFDictionarySetValue(shk_dict, kEnabledKey, shk->enabled == 1 ? kCFBooleanTrue : kCFBooleanFalse);

    // create symbolic hot keys value dictionary
    CFMutableDictionaryRef shk_value_dict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    // put type item into value dictionary
    CFStringRef shk_type = CFStringCreateWithCString(NULL, shk->type, kCFStringEncodingUTF8);
    CFDictionarySetValue(shk_value_dict, kTypeKey, shk_type);
    CFRelease(shk_type);

    // create params array with ASCII code, virtual key code, and modifier keys flags
    CFNumberRef shk_ascii_code = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt64Type, &shk->ASCII_code);
    CFNumberRef shk_virtual_key_code = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt64Type, &shk->virtual_key_code);
    CFNumberRef shk_modifier_keys_flags = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt64Type, &shk->modifier_keys_flags);

    CFMutableArrayRef shk_params_array = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
    CFArrayInsertValueAtIndex(shk_params_array, 0, shk_ascii_code);
    CFArrayInsertValueAtIndex(shk_params_array, 1, shk_virtual_key_code);
    CFArrayInsertValueAtIndex(shk_params_array, 2, shk_modifier_keys_flags);

    // put params item into value dictionary
    CFArrayRef shk_params_array_immutable =CFArrayCreateCopy(kCFAllocatorDefault, shk_params_array);
    CFDictionarySetValue(shk_value_dict, kParametersKey, shk_params_array_immutable);
    CFRelease(shk_params_array_immutable);
    CFRelease(shk_ascii_code);
    CFRelease(shk_virtual_key_code);
    CFRelease(shk_modifier_keys_flags);
    CFRelease(shk_params_array);

    // put value item into shk dictionary
    CFDictionaryRef shk_value_dict_immutable = CFDictionaryCreateCopy(kCFAllocatorDefault, shk_value_dict);
    CFDictionarySetValue(shk_dict, kValueKey, shk_value_dict_immutable);
    CFRelease(shk_value_dict_immutable);
    CFRelease(shk_value_dict);

    // copy application property list that has to be modified
    CFPropertyListRef app_plist = CFPreferencesCopyAppValue(kAppleSymbolicHotKeysKey, kApplicationName);
    // make sure application property list is a dictionary
    if( CFGetTypeID(app_plist) != CFDictionaryGetTypeID() ) {
        fprintf(stderr, "%s: application property list is not of the dictionary type.\n", __func__);
        return;
    }
    // create a mutable copy of application property list dictionary
    CFMutableDictionaryRef app_plist_dict = CFDictionaryCreateMutableCopy(kCFAllocatorDefault, 0, app_plist);

    // put new shk dictionary for shk_id key in application property list dictionary
    CFStringRef shk_id_string = CFStringCreateWithFormat(NULL, NULL, CFSTR("%d"), shk_id);
    CFDictionaryRef shk_dict_immutable = CFDictionaryCreateCopy(kCFAllocatorDefault, shk_dict);
    CFDictionarySetValue(app_plist_dict, shk_id_string, shk_dict_immutable);

    // save changes in application property list
    CFPreferencesSetAppValue(kAppleSymbolicHotKeysKey, app_plist_dict, kApplicationName);
    if(!CFPreferencesAppSynchronize(kApplicationName)) {
        fprintf(stderr, "%s: could not synchronize changes in application property list.\n", __func__);
        return;
    }

    CFRelease(shk_id_string);
    CFRelease(shk_dict_immutable);
    CFRelease(shk_dict);
}

void symbolic_hot_keys_event(int shk_id) {

    // get symbolic hot keys for given identifier
    symbolic_hot_keys_t *shk = apple_symbolic_hot_keys_get(shk_id);
    if(shk == NULL) {
        fprintf(stderr, "%s: Given symbolic hot keys are not found in System Preferences.\n", __func__);
        return;
    }
    if(!shk->enabled) {
        fprintf(stderr, "%s: Given symbolic hot keys are not enabled in System Preferences.\n", __func__);
        return;
    }

    // post keyboard event using symbolic hot keys information
    key_input_modified(shk->virtual_key_code, shk->modifier_keys_flags);
}