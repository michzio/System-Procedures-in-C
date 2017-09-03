//
// Created by Michal Ziobro on 31.05.2017.
//

#ifndef KEYBOARD_EVENTS_IN_WINDOWS_HOT_KEYS_EVENTS_H
#define KEYBOARD_EVENTS_IN_WINDOWS_HOT_KEYS_EVENTS_H

#include <stdbool.h>

struct hot_keys {
    int16_t virtual_key_code; // virtual key code for the character
    int64_t modifier_keys_flags; // the sum of modifier key flags: Shift 17 bit, Ctrl 18 bit, Alt 19 bit, Windows key 20 bit, etc.
    int32_t hold_time_in_s; // hold down keys time [s]
};
typedef struct hot_keys hot_keys_t;

// typical mouse/touch pad gestures
enum zoom_direction {
    kZoomIn,
    kZoomOut,
};
typedef enum zoom_direction zoom_direction_t;

enum rotate_direction {
    kRotateClockWise,
    kRotateCounterClockWise,
};
typedef enum rotate_direction rotate_direction_t;

// swipe not supported in Windows?
enum swipe_direction {
    kSwipeLeft,
    kSwipeRight,
    kSwipeUp,
    kSwipeDown,
};
typedef enum swipe_direction swipe_direction_t;

// for scrolling use mouse events
enum scroll_direction {
    kScrollLeft,
    kScrollRight,
    kScrollUp,
    kScrollDown,
};
typedef enum scroll_direction scroll_direction_t;

// functions mimic common mouse/touch pad gestures using hot keys
void zoom_hot_keys_event(zoom_direction_t zoom_direction);
void rotate_hot_keys_event(rotate_direction_t rotate_direction);
void swipe_hot_keys_event(swipe_direction_t swipe_direction);
void scroll_hot_keys_event(scroll_direction_t scroll_direction);

// Windows system hot_keys
void system_hot_keys_event(const char *hot_keys_name);

// application hot keys
void front_app_hot_keys_event(const char *hot_keys_name, bool consider_default);
void app_hot_keys_event(const char *hot_keys_name, const char *application_name, bool consider_default);

// video & audio players common hot keys
void player_play_hot_keys_event(void);
void player_stop_hot_keys_event(void);
void player_next_hot_keys_event(void);
void player_previous_hot_keys_event(void);
void player_step_forward_hot_keys_event(void);
void player_step_backward_hot_keys_event(void);
void player_loop_hot_keys_event(void);
void player_shuffle_hot_keys_event(void);
void player_volume_up_hot_keys_event(void);
void player_volume_down_hot_keys_event(void);
void player_mute_hot_keys_event(void);
void player_full_screen_hot_keys_event(void);
void player_subtitles_hot_keys_event(void);

// browser common hot keys
void browser_new_tab_hot_keys_event(void);
void browser_next_tab_hot_keys_event(void);
void browser_prev_tab_hot_keys_event(void);
void browser_add_bookmark_hot_keys_event(void);
void browser_new_private_window_hot_keys_event(void);
void browser_reopen_closed_tab_hot_keys_event(void);
void browser_open_file_hot_keys_event(void);
void browser_close_tab_hot_keys_event(void);
void browser_close_window_hot_keys_event(void);
void browser_reload_page_hot_keys_event(void);
void browser_show_downloads_hot_keys_event(void);
void browser_show_history_hot_keys_event(void);
void browser_show_sidebar_hot_keys_event(void);
void browser_show_page_source_hot_keys_event(void);
void browser_home_page_hot_keys_event(void);

// slide show common hot keys
void slide_show_start_hot_keys_event(void);
void slide_show_end_hot_keys_event(void);
void slide_show_next_hot_keys_event(void);
void slide_show_next_no_animation_hot_keys_event(void);
void slide_show_previous_hot_keys_event(void);
void slide_show_previous_no_animation_hot_keys_event(void);
void slide_show_blank_slide_black_hot_keys_event(void);
void slide_show_blank_slide_white_hot_keys_event(void);
void slide_show_first_slide_hot_keys_event(void);
void slide_show_last_slide_hot_keys_event(void);
void slide_show_go_to_next_hidden_slide_hot_keys_event(void);
void slide_show_pen_pointer_hot_keys_event(void);
void slide_show_arrow_pointer_hot_keys_event(void);

// other common hot keys
void zoom_actual_size_hot_keys_event(void);
void enter_full_screen_hot_keys_event(void);

// constant hot keys names
// 1. application names
static const char *kDefaultApplication = "Default Application";

// 2. common hot keys names
static const char *kZoomOutHotKeys = "ZoomOutHotKeys";
static const char *kZoomInHotKeys = "ZoomInHotKeys";
static const char *kRotateCCWHotKeys = "RotateCCWHotKeys";
static const char *kRotateCWHotKeys = "RotateCWHotKeys";
static const char *kZoomActualSizeHotKeys = "ZoomActualSizeHotKeys";
static const char *kEnterFullScreenHotKeys = "EnterFullScreenHotKeys";
// 2.a players hot keys names
static const char *kPlayerPlayHotKeys = "PlayerPlayHotKeys";
static const char *kPlayerStopHotKeys = "PlayerStopHotKeys";
static const char *kPlayerNextHotKeys = "PlayerNextHotKeys";
static const char *kPlayerPreviousHotKeys = "PlayerPreviousHotKeys";
static const char *kPlayerStepForwardHotKeys = "PlayerStepForwardHotKeys";
static const char *kPlayerStepBackwardHotKeys = "PlayerStepBackwardHotKeys";
static const char *kPlayerLoopHotKeys = "PlayerLoopHotKeys";
static const char *kPlayerShuffleHotKeys = "PlayerShuffleHotKeys";
static const char *kPlayerVolumeUpHotKeys = "PlayerVolumeUpHotKeys";
static const char *kPlayerVolumeDownHotKeys = "PlayerVolumeDownHotKeys";
static const char *kPlayerMuteHotKeys = "PlayerMuteHotKeys";
// 2.b browsers hot keys names
static const char *kBrowserNewTabHotKeys = "BrowserNewTabHotKeys";
static const char *kBrowserNextTabHotKeys = "BrowserNextTabHotKeys";
static const char *kBrowserPreviousTabHotKeys = "BrowserPreviousTabHotKeys";
static const char *kBrowserAddBookmarkHotKeys = "BrowserAddBookmarkHotKeys";
static const char *kBrowserNewPrivateWindowHotKeys = "BrowserNewPrivateWindowHotKeys";
static const char *kBrowserReopenClosedTabHotKeys = "BrowserReopenClosedTabHotKeys";
static const char *kBrowserOpenFileHotKeys = "BrowserOpenFileHotKeys";
static const char *kBrowserCloseTabHotKeys = "BrowserCloseTabHotKeys";
static const char *kBrowserCloseWindowHotKeys = "BrowserCloseWindowHotKeys";
static const char *kBrowserReloadPageHotKeys = "BrowserReloadPageHotKeys";
static const char *kBrowserShowDownloadsHotKeys = "BrowserShowDownloadsHotKeys";
static const char *kBrowserShowHistoryHotKeys = "BrowserShowHistoryHotKeys";
static const char *kBrowserShowSidebarHotKeys = "BrowserShowSidebarHotKeys";
static const char *kBrowserShowPageSourceHotKeys = "BrowserShowPageSourceHotKeys";
static const char *kBrowserHomePageHotKeys = "BrowserHomePageHotKeys";
// 2.c slide show hot keys names
static const char *kSlideShowStartHotKeys = "SlideShowStartHotKeys";
static const char *kSlideShowEndHotKeys = "SlideShowEndHotKeys";
static const char *kSlideShowNextHotKeys = "SlideShowNextHotKeys";
static const char *kSlideShowNextNoAnimationHotKeys = "SlideShowNextNoAnimationHotKeys";
static const char *kSlideShowPreviousHotKeys = "SlideShowPreviousHotKeys";
static const char *kSlideShowPreviousNoAnimationHotKeys = "SlideShowPreviousNoAnimationHotKeys";
static const char *kSlideShowBlankSlideBlackHotKeys = "SlideShowBlankSlideBlackHotKeys";
static const char *kSlideShowBlankSlideWhiteHotKeys = "SlideShowBlankSlideWhiteHotKeys";
static const char *kSlideShowFirstSlideHotKeys = "SlideShowFirstSlideHotKeys";
static const char *kSlideShowLastSlideHotKeys = "SlideShowLastSlideHotKeys";
static const char *kSlideShowGoToNextHiddenSlideHotKeys = "SlideShowGoToNextHiddenSlideHotKeys";
static const char *kSlideShowPenPointerHotKeys = "SlideShowPenPointerHotKeys";
static const char *kSlideShowArrowPointerHotKeys = "SlideShowArrowPointerHotKeys";

// 3. system hot keys names
static const char *kCutHotKeys = "CutHotKeys";                                  // Ctrl, X
static const char *kCopyHotKeys = "CopyHotKeys";                                // Ctrl, C
static const char *kPasteHotKeys = "PasteHotKeys";                              // Ctrl, V
static const char *kUndoHotKeys = "UndoHotKeys";                                // Ctrl, Z
static const char *kRedoHotKeys = "RedoHotKeys";                                // Ctrl, Y
static const char *kSwitchAppsHotKeys = "SwitchAppsHotKeys";                    // Alt, Tab
static const char *kCloseFrontWindowHotKeys = "CloseFrontWindowHotKeys";        // Alt, F4
static const char *kLockPCHotKeys = "LockPCHotKeys";                            // Windows, L
static const char *kShowDesktopHotKeys = "ShowDesktopHotKeys";                  // Windows, D
static const char *kRenameSelectedHotKeys = "RenameSelectedHotKeys";            // F2
static const char *kFileExplorerSearchHotKeys = "FileExplorerSearchHotKeys";    // F3
static const char *kFileExplorerDisplayAddressBarListHotKeys = "FileExplorerDisplayAddressBarListHotKeys";  // F4
static const char *kRefreshActiveWindowHotKeys = "RefreshActiveWindowHotKeys";  // F5
static const char *kCycleElementsHotKeys = "CycleElementsHotKeys";              // F6
static const char *kActivateMenuBarHotKeys = "ActivateMenuBarHotKeys";          // F10
static const char *kShowPasswordHotKeys = "ShowPasswordHotKeys";                // Alt, F8
static const char *kCycleItemsOrderedHotKeys = "CycleItemsOrderedHotKeys";      // Alt, Esc
static const char *kDisplayItemPropertiesHotKeys = "DisplayItemPropertiesHotKeys"; // Alt, Enter
static const char *kOpenShortcutMenuHotKeys = "OpenShortcutMenuHotKeys";        // Alt, Spacebar
static const char *kGoBackHotKeys = "GoBackHotKeys";                            // Alt, LeftArrow
static const char *kGoForwardHotKeys = "GoForwardHotKeys";                      // Alt, RightArrow
static const char *kPageUpHotKeys = "PageUpHotKeys";                            // Alt, Page Up
static const char *kPageDownHotKeys = "PageDownHotKeys";                        // Alt, Page Down
static const char *kCloseTabHotKeys = "CloseTabHotKeys";                        // Ctrl, F4
static const char *kSelectAllHotKeys = "SelectAllHotKeys";                      // Ctrl, A
static const char *kMoveToTrashHotKeys = "MoveToTrashHotKeys";                  // Ctrl, D
static const char *kRefreshWindowHotKeys = "RefreshWindowHotKeys";              // Ctrl, R
static const char *kNextWordBeginningHotKeys = "NextWordBeginningHotKeys";      // Ctrl, RightArrow
static const char *kPrevWordBeginningHotKeys = "PrevWordBeginningHotKeys";      // Ctrl, LeftArrow
static const char *kNextParagraphBeginningHotKeys = "NextParagraphBeginningHotKeys"; // Ctrl, DownArrow
static const char *kPrevParagraphBeginningHotKeys = "PrevParagraphBeginningHotKeys"; // Ctrl, UpArrow
static const char *kAppsSwitcherHotKeys = "AppsSwitcherHotKeys";                // Ctrl, Alt, Tab
static const char *kExpandSelectionUpHotKeys = "ExpandSelectionUpHotKeys";      // Ctrl, Shift, UpArrow
static const char *kExpandSelectionDownHotKeys = "ExpandSelectionDownHotKeys";  // Ctrl, Shift, DownArrow
static const char *kExpandSelectionLeftHotKeys = "ExpandSelectionLeftHotKeys";  // Ctrl, Shift, LeftArrow
static const char *kExpandSelectionRightHotKeys = "ExpandSelectionRightHotKeys";// Ctrl, Shift, RightArrow
static const char *kOpenStartMenuHotKeys = "OpenStartMenuHotKeys";              // Ctrl, Esc
static const char *kOpenTaskManagerHotKeys = "OpenTaskManagerHotKeys";          // Ctrl, Shift, Esc
static const char *kSwitchKeyboardLayoutHotKeys = "SwitchKeyboardLayoutHotKeys";// Ctrl, Shift
static const char *kTurnChineseIMEHotKeys = "TurnChineseIMEHotKeys";            // Ctrl, Spacebar
static const char *kDisplayShortcutMenuHotKeys = "DisplayShortcutMenuHotKeys";  // Shift, F10
static const char *kSelectLeftHotKeys = "SelectLeftHotKeys";                    // Shift, LeftArrow
static const char *kSelectRightHotKeys = "SelectRightHotKeys";                  // Shift, RightArrow
static const char *kSelectUpHotKeys = "SelectUpHotKeys";                        // Shift, UpArrow
static const char *kSelectDownHotKeys = "SelectDownHotKeys";                    // Shift, DownArrow
static const char *kForceDeleteHotKeys = "ForceDeleteHotKeys";                  // Shift, Delete
static const char *kOpenActionCenterHotKeys = "OpenActionCenterHotKeys";        // Windows, A
static const char *kNotificationAreaFocusHotKeys = "NotificationAreaFocusHotKeys"; // Windows, B
static const char *kDisplayDateTimeHotKeys = "DisplayDateTimeHotKeys";          // Windows, Alt, D
static const char *kOpenFileExplorerHotKeys = "OpenFileExplorerHotKeys";        // Windows, E
static const char *kOpenFeedbackHubHotKeys = "OpenFeedbackHubHotKeys";          // Windows, F
static const char *kOpenGameBarHotKeys = "OpenGameBarHotKeys";                  // Windows, G
static const char *kOpenSettingsHotKeys = "OpenSettingsHotKeys";                // Windows, I
static const char *kOpenConnectHotKeys = "OpenConnectHotKeys";                  // Windows, K
static const char *kSwitchAccountsHotKeys = "SwitchAccountsHotKeys";            // Windows, L
static const char *kMinimizeAllWindowsHotKeys = "MinimizeAllWindowsHotKeys";    // Windows, M
static const char *kLockOrientationHotKeys = "LockOrientationHotKeys";          // Windows, O
static const char *kChoosePresentationDisplayModeHotKeys = "ChoosePresentationDisplayModeHotKeys"; // Windows, P
static const char *kOpenRunDialogBoxHotKeys = "OpenRunDialogBoxHotKeys";        // Windows, R
static const char *kOpenSearchHotKeys = "OpenSearchHotKeys";                    // Windows, S
static const char *kCycleTaskBarAppsHotKeys = "CycleTaskBarAppsHotKeys";        // Windows, T
static const char *kEaseOfAccessCenterHotKeys = "EaseOfAccessCenterHotKeys";    // Windows, U
static const char *kCycleNotificationsHotKeys = "CycleNotificationsHotKeys";    // Windows, V
static const char *kReverseCycleNotificationsHotKeys = "ReverseCycleNotificationsHotKeys"; // Windows, Shift, V
static const char *kOpenQuickLinkMenuHotKeys = "OpenQuickLinkMenuHotKeys";      // Windows, X
static const char *kAvailableCommandsHotKeys = "AvailableCommandsHotKeys";      // Windows, Z
static const char *kPeekDesktopHotKeys = "PeekDesktopHotKeys";                  // Windows, Comma (,)
static const char *kSystemPropertiesDialogBoxHotKeys = "SystemPropertiesDialogBoxHotKeys"; // Windows, Pause
static const char *kRestoreMinimizedWindowsHotKeys = "RestoreMinimizedWindowsHotKeys"; // Windows, Shift, M
static const char *kOpenTaskViewHotKeys = "OpenTaskViewHotKeys";                // Windows, Tab
static const char *kMaximizeWindowHotKeys = "MaximizeWindowHotKeys";            // Windows, UpArrow
static const char *kMinimizeWindowHotKeys = "MinimizeWindowHotKeys";            // Windows, DownArrow
static const char *kMaximizeWindowToLeftHotKeys = "MaximizeWindowToLeftHotKeys";// Windows, LeftArrow
static const char *kMaximizeWindowToRightHotKeys = "MaximizeWindowToRightHotKeys";// Windows, RightArrow
static const char *kMinimizeAllExceptCurrentWindowHotKeys = "MinimizeAllExceptCurrentWindowHotKeys"; // Windows, Home
static const char *kStretchWindowVerticallyHotKeys = "StretchWindowVerticallyHotKeys"; // Windows, Shift, UpArrow
static const char *kMinimizeWindowVerticallyHotKeys = "MinimizeWindowVerticallyHotKeys"; // Windows, Shift, DownArrow
static const char *kMoveWindowToLeftMonitorHotKeys = "MoveWindowToLeftMonitorHotKeys"; // Windows, Shift, LeftArrow
static const char *kMoveWindowToRightMonitorHotKeys = "MoveWindowToRightMonitorHotKeys"; // Windows, Shift, RightArrow
static const char *kInputLangAndKeyboardLayoutHotKeys = "InputLangAndKeyboardLayoutHotKeys"; // Windows, Spacebar
static const char *kOpenNarratorHotKeys = "OpenNarratorHotKeys";                // Windows, Ctrl, Enter
static const char *kMagnifierZoomInHotKeys = "MagnifierZoomInHotKeys";          // Windows, Plus sign (+)
static const char *kMagnifierZoomOutHotKeys = "MagnifierZoomOutHotKeys";        // Windows, Minus sign (-)
static const char *kMagnifierExitHotKeys = "MagnifierExitHotKeys";              // Windows, Esc
static const char *kFileExplorerSelectAddressBarHotKeys = "FileExplorerSelectAddressBarHotKeys"; // Alt, D
static const char *kFileExplorerSelectSearchBoxHotKeys = "FileExplorerSelectSearchBoxHotKeys"; // Ctrl, F
static const char *kFileExplorerNewWindowHotKeys = "FileExplorerNewWindowHotKeys";  // Ctrl, N
static const char *kFileExplorerCloseWindowHotKeys = "FileExplorerCloseWindowHotKeys"; // Ctrl, W
static const char *kFileExplorerAllAboveFoldersHotKeys = "FileExplorerAllAboveFoldersHotKeys"; // Ctrl, Shift, E
static const char *kFileExplorerNewFolderHotKeys = "FileExplorerNewFolderHotKeys"; // Ctrl, Shift, N
static const char *kFileExplorerDisplayPreviewPanelHotKeys = "FileExplorerDisplayPreviewPanelHotKeys"; // Alt, P
static const char *kFileExplorerPropertiesDialogBoxHotKeys = "FileExplorerPropertiesDialogBoxHotKeys"; // Alt, Enter
static const char *kFileExplorerNextFolderHotKeys = "FileExplorerNextFolderHotKeys"; // Alt, RightArrow
static const char *kFileExplorerPrevFolderHotKeys = "FileExplorerPrevFolderHotKeys"; // Alt, LeftArrow
static const char *kFileExplorerUpFolderHotKeys = "FileExplorerUpFolderHotKeys"; // Alt, UpArrow
static const char *kVirtualDesktopAddHotKeys = "VirtualDesktopAddHotKeys";      // Windows, Ctrl, D
static const char *kVirtualDesktopMoveLeftHotKeys = "VirtualDesktopMoveLeftHotKeys"; // Windows, Ctrl, LeftArrow
static const char *kVirtualDesktopMoveRightHotKeys = "VirtualDesktopMoveRightHotKeys"; // Windows, Ctrl, RightArrow
static const char *kVirtualDesktopCloseHotKeys = "VirtualDesktopCloseHotKeys";  // Windows, Ctrl, F4

#endif //KEYBOARD_EVENTS_IN_WINDOWS_HOT_KEYS_EVENTS_H
