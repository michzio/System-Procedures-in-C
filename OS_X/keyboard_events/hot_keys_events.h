//
// Created by Michal Ziobro on 28/08/2016.
//

#ifndef KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H
#define KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H

#include <stdint.h>
#include <stdbool.h>

struct hot_keys {
    int16_t virtual_key_code;       // virtual key code for the character
    int64_t modifier_keys_flags;    // the sum of modifier key flags: Shift 17 bit, Ctrl 18 bit, Opt 19 bit, Cmd 20 bit
    int32_t hold_time_in_s;         // hold down keys time [s]
};
typedef struct hot_keys hot_keys_t;

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

enum swipe_direction {
    kSwipeLeft,
    kSwipeRight,
    kSwipeUp,
    kSwipeDown,
};
typedef enum swipe_direction swipe_direction_t;

enum scroll_direction {
    kScrollLeft,
    kScrollRight,
    kScrollUp,
    kScrollDown,
};
typedef enum scroll_direction scroll_direction_t;

// functions mimic common mouse gestures using hot keys
void zoom_hot_keys_event(zoom_direction_t zoom_direction);
void rotate_hot_keys_event(rotate_direction_t rotate_direction);
void swipe_hot_keys_event(swipe_direction_t swipe_direction);
void scroll_hot_keys_event(scroll_direction_t scroll_direction);

// macOS system hot keys
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
void player_volume_up_hot_keys_event(void);
void player_volume_down_hot_keys_event(void);
void player_mute_hot_keys_event(void);

// browser common hot keys
void browser_new_tab_hot_keys_event(void);
void browser_next_tab_hot_keys_event(void);
void browser_prev_tab_hot_keys_event(void);
void browser_add_bookmark_hot_keys_event(void);
void browser_new_private_window_hot_keys_event(void);
void browser_reopen_closed_tab_hot_keys_event(void);
void browser_open_file_hot_keys_event(void);
void browser_open_location_hot_keys_event(void);
void browser_close_tab_hot_keys_event(void);
void browser_close_window_hot_keys_event(void);
void browser_emoji_hot_keys_event(void);
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
void slide_show_blank_black_slide_hot_keys_event(void);
void slide_show_blank_white_slide_hot_keys_event(void);
void slide_show_pause_hot_keys_event(void);
void slide_show_first_slide_hot_keys_event(void);
void slide_show_last_slide_hot_keys_event(void);
void slide_show_hide_cursor_hot_keys_event(void);
void slide_show_slide_number_hot_keys_event(void);
void slide_show_go_to_next_hidden_slide_hot_keys_event(void);
void slide_show_pen_pointer_hot_keys_event(void);
void slide_show_arrow_pointer_hot_keys_event(void);

// other common hot keys
void zoom_actual_size_hot_keys_event(void);
void enter_full_screen_hot_keys_event(void);

// constant names
// 1. application names
static const char *kDefaultApplication = "Default Application";

// 2. common hot keys names
static const char *kZoomOutHotKeys = "ZoomOutHotKeys";
static const char *kZoomInHotKeys = "ZoomInHotKeys";
static const char *kRotateCCWHotKeys = "RotateCCWHotKeys";
static const char *kRotateCWHotKeys = "RotateCWHotKeys";
static const char *kZoomActualSizeHotKeys = "ZoomActualSizeHotKeys";
static const char *kEnterFullScreenHotKeys = "EnterFullScreenHotKeys";
static const char *kPlayerPlayHotKeys = "PlayerPlayHotKeys";
static const char *kPlayerStopHotKeys = "PlayerStopHotKeys";
static const char *kPlayerNextHotKeys = "PlayerNextHotKeys";
static const char *kPlayerPreviousHotKeys = "PlayerPreviousHotKeys";
static const char *kPlayerStepForwardHotKeys = "PlayerStepForwardHotKeys";
static const char *kPlayerStepBackwardHotKeys = "PlayerStepBackwardHotKeys";
static const char *kPlayerLoopHotKeys = "PlayerLoopHotKeys";
static const char *kPlayerVolumeUpHotKeys = "PlayerVolumeUpHotKeys";
static const char *kPlayerVolumeDownHotKeys = "PlayerVolumeDownHotKeys";
static const char *kPlayerMuteHotKeys = "PlayerMuteHotKeys";
static const char *kBrowserNewTabHotKeys = "BrowserNewTabHotKeys";
static const char *kBrowserNextTabHotKeys = "BrowserNextTabHotKeys";
static const char *kBrowserPreviousTabHotKeys = "BrowserPreviousTabHotKeys";
static const char *kBrowserAddBookmarkHotKeys = "BrowserAddBookmarkHotKeys";
static const char *kBrowserNewPrivateWindowHotKeys = "BrowserNewPrivateWindowHotKeys";
static const char *kBrowserReopenClosedTabHotKeys = "BrowserReopenClosedTabHotKeys";
static const char *kBrowserOpenFileHotKeys = "BrowserOpenFileHotKeys";
static const char *kBrowserOpenLocationHotKeys = "BrowserOpenLocationHotKeys";
static const char *kBrowserCloseTabHotKeys = "BrowserCloseTabHotKeys";
static const char *kBrowserCloseWindowHotKeys = "BrowserCloseWindowHotKeys";
static const char *kBrowserEmojiHotKeys = "BrowserEmojiHotKeys";
static const char *kBrowserReloadPageHotKeys = "BrowserReloadPageHotKeys";
static const char *kBrowserShowDownloadsHotKeys = "BrowserShowDownloadsHotKeys";
static const char *kBrowserShowHistoryHotKeys = "BrowserShowHistoryHotKeys";
static const char *kBrowserShowSidebarHotKeys = "BrowserShowSidebarHotKeys";
static const char *kBrowserShowPageSourceHotKeys = "BrowserShowPageSourceHotKeys";
static const char *kBrowserHomePageHotKeys = "BrowserHomePageHotKeys";
static const char *kSlideShowStartHotKeys = "SlideShowStartHotKeys";
static const char *kSlideShowEndHotKeys = "SlideShowEndHotKeys";
static const char *kSlideShowNextHotKeys = "SlideShowNextHotKeys";
static const char *kSlideShowNextNoAnimationHotKeys = "SlideShowNextNoAnimationHotKeys";
static const char *kSlideShowPreviousHotKeys = "SlideShowPreviousHotKeys";
static const char *kSlideShowPreviousNoAnimationHotKeys = "SlideShowPreviousNoAnimationHotKeys";
static const char *kSlideShowBlankBlackSlideHotKeys = "SlideShowBlankBlackSlideHotKeys";
static const char *kSlideShowBlankWhiteSlideHotKeys = "SlideShowBlankWhiteSlideHotKeys";
static const char *kSlideShowPauseHotKeys = "SlideShowPauseHotKeys";
static const char *kSlideShowFirstSlideHotKeys = "SlideShowFirstSlideHotKeys";
static const char *kSlideShowLastSlideHotKeys = "SlideShowLastSlideHotKeys";
static const char *kSlideShowHideCursorHotKeys= "SlideShowHideCursorHotKeys";
static const char *kSlideShowSlideNumberHotKeys = "SlideShowSlideNumberHotKeys";
static const char *kSlideShowGoToNextHiddenSlideHotKeys = "SlideShowGoToNextHiddenSlideHotKeys";
static const char *kSlideShowPenPointerHotKeys = "SlideShowPenPointerHotKeys";
static const char *kSlideShowArrowPointerHotKeys = "SlideShowArrowPointerHotKeys";

// 3. system hot keys names
// a) cut, copy, paste, and other common shortcuts
static const char *kCutHotKeys = "CutHotKeys";                                  // Cmd, X
static const char *kCopyHotKeys = "CopyHotKeys";                                // Cmd, C
static const char *kPasteHotKeys = "PasteHotKeys";                              // Cmd, V
static const char *kUndoHotKeys = "UndoHotKeys";                                // Cmd, Z
static const char *kRedoHotKeys = "RedoHotKeys";                                // Cmd, Shift, Z
static const char *kSelectAllHotKeys = "SelectAllHotKeys";                      // Cmd, A
static const char *kFindHotKeys = "FindHotKeys";                                // Cmd, F
static const char *kFindNextHotKeys = "FindNextHotKeys";                        // Cmd, G
static const char *kFindPreviousHotKeys = "FindPreviousHotKeys";                // Cmd, Shift, G
static const char *kHideFrontWindowHotKeys = "HideFrontWindowHotKeys";          // Cmd, H
static const char *kHideOtherWindowsHotKeys = "HideOtherWindowsHotKeys";        // Cmd, Opt, H
static const char *kMinimizeFrontWindowHotKeys = "MinimizeFrontWindowHotKeys";  // Cmd, M
static const char *kOpenNewHotKeys = "OpenNewHotKeys";                          // Cmd, N
static const char *kOpenItemHotKeys = "OpenItemHotKeys";                        // Cmd, 0
static const char *kPrintHotKeys = "PrintHotKeys";                              // Cmd, P
static const char *kSaveHotKeys = "SaveHotKeys";                                // Cmd, S
static const char *kCloseFrontWindowHotKeys = "CloseFrontWindowHotKeys";        // Cmd, W
static const char *kCloseAllWindowsHotKeys = "CloseAllWindowsHotKeys";          // Cmd, Opt, W
static const char *kQuitTheAppHotKeys = "QuitTheAppHotKeys";                    // Cmd, Q
static const char *kForceQuitHotKeys = "ForceQuitHotKeys";                      // Cmd, Opt, Esc
static const char *kForceQuitFrontAppHotKeys = "ForceQuitFrontAppHotKeys";      // Cmd, Shift, Opt, Esc, 3 sec hold time
static const char *kSpotlightHotKeys = "SpotlightHotKeys";                      // Cmd, Space bar
static const char *kFinderSpotlightHotKeys = "FinderSpotlightHotKeys";          // Cmd, Opt, Space bar
static const char *kQuickLookHotKeys = "QuickLookHotKeys";                      // Space bar
static const char *kSwitchAppsHotKeys = "SwitchAppsHotKeys";                    // Cmd, Tab
static const char *kSwitchAppWindowsHotKeys = "SwitchAppWindowsHotKeys";        // Cmd, ~ (Shift, `)
static const char *kScreenshotHotKeys = "ScreenshotHotKeys";                    // Cmd, Shift, 3
static const char *kAppPreferencesHotKeys = "AppPreferencesHotKeys";            // Cmd, comma (,)
//  log out shortcut
static const char *kLogOutHotKeys = "LogOutHotKeys";                            // Cmd, Shift, Opt, Q
// document shortcuts
static const char *kBoldTextHotKeys = "BoldTextHotKeys";                        // Cmd, B
static const char *kItalicizeTextHotKeys = "ItalicizeTextHotKeys";              // Cmd, I
static const char *kUnderlineTextHotKeys = "UnderlineTextHotKeys";              // Cmd, U
static const char *kFontsWindowHotKeys = "FontsWindowHotKeys";                  // Cmd, T
static const char *kWordDefinitionHotKeys = "WordDefinitionHotKeys";            // Ctrl, Cmd, D
static const char *kSpellingWindowHotKeys = "SpellingWindowHotKeys";            // Cmd, Shift, : (colon)
static const char *kDeletePreviousWordHotKeys = "DeletePreviousWordHotKeys";    // Opt, Del
static const char *kForwardDeleteHotKeys = "ForwardDeleteHotKeys";              // Ctrl, D
static const char *kPageUpHotKeys = "PageUpHotKeys";                            // Fn, Up arrow
static const char *kPageDownHotKeys = "PageDownHotKeys";                        // Fn, Down arrow
static const char *kDocumentHomeHotKeys = "DocumentHomeHotKeys";                // Fn, Left arrow
static const char *kDocumentEndHotKeys = "DocumentEndHotKeys";                  // Fn, Right arrow
static const char *kMoveToDocumentBeginHotKeys = "MoveToDocumentBeginHotKeys";  // Cmd, Up arrow
static const char *kMoveToDocumentEndHotKeys = "MoveToDocumentEndHotKeys";      // Cmd, Down arrow
static const char *kMoveToLineBeginHotKeys = "MoveToLineBeginHotKeys";          // Cmd, Left arrow
static const char *kMoveToLineEndHotKeys = "MoveToLineEndHotKeys";              // Cmd, Right arrow
static const char *kMoveToWordBeginHotKeys = "MoveToWordBeginHotKeys";          // Opt, Left arrow
static const char *kMoveToWordEndHotKeys = "MoveToWordEndHotKeys";              // Opt, Right arrow
static const char *kExpandSelectionUpHotKeys = "ExpandSelectionUpHotKeys";      // Shift, Up arrow
static const char *kExpandSelectionDownHotKeys = "ExpandSelectionDownHotKeys";  // Shift, Down arrow
static const char *kExpandSelectionLeftHotKeys = "ExpandSelectionLeftHotKeys";  // Shift, Left arrow
static const char *kExpandSelectionRightHotKeys = "ExpandSelectionRightHotKeys";// Shift, Right arrow
static const char *kLeftAlignHotKeys = "LeftAlignHotKeys";                      // Cmd, { (Shift, [)
static const char *kRightAlignHotKeys = "RightAlignHotKeys";                    // Cmd, } (Shift, ])
static const char *kCenterAlignHotKeys = "CenterAlignHotKeys";                  // Cmd, | (Shift, \)
static const char *kSearchFieldHotKeys = "SearchFieldHotKeys";                  // Cmd, Opt, F
static const char *kShowToolbarHotKeys = "ShowToolbarHotKeys";                  // Cmd, Opt, T
static const char *kShowInspectorWindowHotKeys = "ShowInspectorWindowHotKeys";  // Cmd, Opt, I
static const char *kIncreaseTextSizeHotKeys = "IncreaseTextSizeHotKeys";        // Cmd, Shift, = (+)
static const char *kDecreaseTextSizeHotKeys = "DecreaseTextSizeHotKeys";        // Cmd, Shift, -
// finder shortcuts
static const char *kDuplicateFileHotKeys = "DuplicateFileHotKeys";              // Cmd, D
static const char *kEjectDiskHotKeys = "EjectDiskHotKeys";                      // Cmd, E
static const char *kFinderSpotlightSearchHotKeys = "FinderSpotlightSearchHotKeys";// Cmd, F
static const char *kFileInfoHotKeys = "FileInfoHotKeys";                        // Cmd, I
static const char *kOpenComputerHotKeys = "OpenComputerHotKeys";                // Cmd, Shift, C
static const char *kOpenDesktopHotKeys = "OpenDesktopHotKeys";                  // Cmd, Shift, D
static const char *kOpenAllMyFilesHotKeys = "OpenAllMyFilesHotKeys";            // Cmd, Shift, F
static const char *kOpenGoToHotKeys = "OpenGoToHotKeys";                        // Cmd, Shift, G
static const char *kOpenHomeHotKeys = "OpenHomeHotKeys";                        // Cmd, Shift, H
static const char *kOpeniCloudHotKeys = "OpeniCloudHotKeys";                    // Cmd, Shift, I
static const char *kOpenNetworkHotKeys = "OpenNetworkHotKeys";                  // Cmd, Shift, K
static const char *kOpenDownloadsHotKeys = "OpenDownloadsHotKeys";              // Cmd, Opt, L
static const char *kOpenDocumentsHotKeys = "OpenDocumentsHotKeys";              // Cmd, Shift, O
static const char *kOpenLibraryHotKeys = "OpenLibraryHotKeys";                  // Cmd, Shift, L
static const char *kOpenAirDropHotKeys = "OpenAirDropHotKeys";                  // Cmd, Shift, R
static const char *kAddItemToDockHotKeys = "AddItemToDockHotKeys";              // Ctrl, Cmd, Shift, T
static const char *kOpenUtilitiesHotKeys = "OpenUtilitiesHotKeys";              // Cmd, Shift, U
static const char *kShowDockHotKeys = "ShowDockHotKeys";                        // Cmd, Opt, D
static const char *kAddItemToSidebarHotKeys = "AddItemToSidebarHotKeys";        // Ctrl, Cmd, T
static const char *kShowPathBarHotKeys = "ShowPathBarHotKeys";                  // Cmd, Opt, P
static const char *kShowSidebarHotKeys = "ShowSidebarHotKeys";                  // Cmd, Opt, S
static const char *kShowStatusBarHotKeys = "ShowStatusBarHotKeys";              // Cmd, /
static const char *kShowViewOptionsHotKeys = "ShowViewOptionsHotKeys";          // Cmd, J
static const char *kOpenConnectToServerHotKeys = "OpenConnectToServerHotKeys";  // Cmd, K
static const char *kMakeItemAliasHotKeys = "MakeItemAliasHotKeys";              // Cmd, L
static const char *kOpenNewWindowHotKeys = "OpenNewWindowHotKeys";              // Cmd, N
static const char *kCreateNewFolderHotKeys = "CreateNewFolderHotKeys";          // Cmd, Shift, N
static const char *kCreateNewSmartFolderHotKeys = "CreateNewSmartFolderHotKeys";// Cmd, Opt, N
static const char *kShowFileForAliasHotKeys = "ShowFileForAliasHotKeys";        // Cmd, R
static const char *kShowTabBarHotKeys = "ShowTabBarHotKeys";                    // Cmd, Shift, T
static const char *kIconsViewHotKeys = "IconsViewHotKeys";                      // Cmd, 1
static const char *kListViewHotKeys = "ListViewHotKeys";                        // Cmd, 2
static const char *kColumnsViewHotKeys = "ColumnsViewHotKeys";                  // Cmd, 3
static const char *kCoverFlowViewHotKeys = "CoverFlowViewHotKeys";              // Cmd, 4
static const char *kPreviousFolderHotKeys = "PreviousFolderHotKeys";            // Cmd, [
static const char *kNextFolderHotKeys = "NextFolderHotKeys";                    // Cmd, ]
static const char *kUpFolderHotKeys = "UpFolderHotKeys";                        // Cmd, Up arrow
static const char *kDownFolderHotKeys = "DownFolderHotKeys";                    // Cmd, Down arrow
static const char *kShowDesktopHotKeys = "ShowDesktopHotKeys";                  // F11
static const char *kMoveToTrashHotKeys = "MoveToTrashHotKeys";                  // Cmd, Delete
static const char *kEmptyTrashHotKeys = "EmptyTrashHotKeys";                    // Cmd, Shift, Delete
static const char *kForceEmptyTrashHotKeys = "ForceEmptyTrashHotKeys";          // Cmd, Shift, Opt, Delete
// other shortcuts
static const char *kScrollFullScreenDown = "ScrollFullScreenDownHotKeys";       // Space bar
static const char *kScrollFullScreenUp = "ScrollFullScreenUpHotKeys";           // Shift + Space bar

#endif //KEYBOARD_EVENTS_IN_OS_X_HOTKEYS_EVENTS_H