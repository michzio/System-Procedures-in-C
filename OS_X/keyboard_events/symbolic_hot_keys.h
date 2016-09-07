//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef KEYBOARD_EVENTS_IN_OS_X_SYMBOLIC_HOTKYES_H
#define KEYBOARD_EVENTS_IN_OS_X_SYMBOLIC_HOTKYES_H

#include <CoreGraphics/CoreGraphics.h>

/**
 * Apple Symbolic HotKeys Ids
 * To find this symbolic hot keys indices do:
 * 1. open Terminal
 * 2. restore defaults in System Preferences > Keyboard > Shortcuts
 * 3. defaults read com.apple.symbolichotkeys > current.txt
 * 4. enable/disable given symbolic hot key in System Preferences > Keyboard > Shortcuts
 * 5. defaults read com.apple.symbolichotkeys | diff -C 5 current.txt -
 * 6. restore defaults in System Preferences > Keyboard > Shortcuts
 */
enum {
    kSHKMoveFocusToTheMenuBar                   = 7,    // Ctrl, F2
    kSHKMoveFocusToTheDock                      = 8,    // Ctrl, F3
    kSHKMoveFocusToActiveOrNextWindow           = 9,    // Ctrl, F4
    kSHKMoveFocusToTheWindowToolbar             = 10,   // Ctrl, F5
    kSHKMoveFocusToTheFloatingWindow            = 11,   // Ctrl, F6
    kSHKTurnKeyboardAccessOnOrOff               = 12,   // Ctrl, F1
    kSHKChangeTheWayTabMovesFocus               = 13,   // Ctrl, F7
    kSHKTurnZoomOnOrOff                         = 15,   // Opt, Cmd, 8
    kSHKZoomIn                                  = 17,   // Opt, Cmd, =
    kSHKZoomOut                                 = 19,   // Opt, Cmd, -
    kSHKInvertColors                            = 21,   // Ctrl, Opt, Cmd, 8
    kSHKTurnImageSmoothingOnOrOff               = 23,   // Opt, Cmd, Backslash "\"
    kSHKIncreaseContrast                        = 25,   // Ctrl, Opt, Cmd, .
    kSHKDecreaseContrast                        = 26,   // Ctrl, Opt, Cmd, ,
    kSHKMoveFocusToNextWindow                   = 27,   // Cmd, `
    kSHKSavePictureOfScreenAsAFile              = 28,   // Shift, Cmd, 3
    kSHKCopyPictureOfScreenToTheClipboard       = 29,   // Ctrl, Shift, Cmd, 3
    kSHKSavePictureOfSelectedAreaAsAFile        = 30,   // Shift, Cmd, 4
    kSHKCopyPictureOfSelectedAreaToTheClipboard = 31,   // Ctrl, Shift, Cmd, 4
    kSHKMissionControl                          = 32,   // Ctrl, Arrow Up
    kSHKApplicationWindows                      = 33,   // Ctrl, Arrow Down
    kSHKShowDesktop                             = 36,   // F11
    kSHKMoveFocusToTheWindowDrawer              = 51,   // Opt, Cmd, `
    kSHKTurnDockHidingOnOrOff                   = 52,   // Opt, Cmd, D
    kSHKMoveFocusToStatusMenus                  = 57,   // Ctrl, F8
    kSHKTurnVoiceOverOnOrOff                    = 59,   // Cmd, F5
    kSHKSelectThePreviousInputSource            = 60,   // Ctrl, Space bar
    kSHKSelectNextSourceInInputMenu             = 61,   // Ctrl, Opt, Space bar
    kSHKShowDashboard                           = 62,   // F12
    kSHKShowSpotlightSearch                     = 64,   // Cmd, Space bar
    kSHKShowFinderSearchWindow                  = 65,   // Opt, Cmd, Space bar
    kSHKLookUpInDictionary                      = 70,   // Shift, Cmd, E
    kSHKHideAndShowFrontRow                     = 73,   // Cmd, Esc
    kSHKActivateSpaces                          = 75,   // F8
    kSHKMoveLeftASpace                          = 79,   // Ctrl, Arrow Left
    kSHKMoveRightASpace                         = 81,   // Ctrl, Arrow Right
    kSHKShowHelpMenu                            = 98,   // Shift, Cmd, /
    kSHKSwitchToDesktop1                        = 118,  // Ctrl, 1
    kSHKSwitchToDesktop2                        = 119,  // Ctrl, 2
    kSHKSwitchToDesktop3                        = 120,  // Ctrl, 3
    kSHKSwitchToDesktop4                        = 121,  // Ctrl, 4
    kSHKShowLaunchpad                           = 160,  //
    kSHKShowAccessibilityControls               = 162,  // Opt, Cmd, F5
    kSHKShowNotificationCenter                  = 163,  //
    kSHKTurnDoNotDisturbOnOrOff                 = 175,  //
    kSHKTurnFocusFollowingOnOrOff               = 179,  //
};


struct symbolic_hot_keys {
    int shk_id;                     // symbolic hot keys identifier
    int enabled;
    char *type;                     // usually "standard"
    int64_t ASCII_code;             // ASCII code of the character or 65535 (0xFFFF) for non-ASCII characters
    int64_t virtual_key_code;       // virtual key code for the character
    int64_t modifier_keys_flags;    // the sum of modifier key flags: Shift 17 bit, Ctrl 18 bit, Opt 19 bit, Cmd 20 bit
};
typedef struct symbolic_hot_keys symbolic_hot_keys_t;

// simple mapping of modifier flags
enum {
    kMFShift    = kCGEventFlagMaskShift,
    kMFControl  = kCGEventFlagMaskControl,
    kMFOption   = kCGEventFlagMaskAlternate,
    kMFCommand  = kCGEventFlagMaskCommand,
};

void symbolic_hot_keys_event(int shk_id);

#endif //KEYBOARD_EVENTS_IN_OS_X_SYMBOLIC_HOTKYES_H
