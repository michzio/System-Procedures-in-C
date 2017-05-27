//
// Created by Michal Ziobro on 26.05.2017.
//

#ifndef KEYBOARD_EVENTS_VIRTUAL_KEY_CODES_H
#define KEYBOARD_EVENTS_VIRTUAL_KEY_CODES_H

#include <windows.h>

/**
 * Summary:
 *      Virtual key codes
 *
 * Discussion:
 *      These constants are the virtual key codes defined
 *      originally in MSDN documentation on the website
 *      https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
 *      They are symbolic constant names, hexadecimal values. They represent
 *      mouse or keyboard equivalents for the virtual key codes used by the Windows system.
 *      Virtual Key Codes are listed in numeric order on MSDN website.
 *
 *      Here we map Windows-specific symbolic constant names/hexadecimal values
 *      into macOS virtual key constant names used in this library.
 *
 */

// other virtual key codes - Windows-specific
enum {
    kVK_LeftMouseButton             = VK_LBUTTON,
    kVK_RightMouseButton            = VK_RBUTTON,
    kVK_ControlBreakProcessing      = VK_CANCEL,
    kVK_MiddleMouseButton           = VK_MBUTTON,
    kVK_X1MouseButton               = VK_XBUTTON1,
    kVK_X2MouseButton               = VK_XBUTTON2,
    //kVK_Undefined                 = 0x07,
    //kVK_Reserved                  = 0x0A-0B
    //kVK_Undefined                 = 0x0E-0F
            kVK_PauseKey                    = VK_PAUSE, // Windows-specific? PAUSE/BREAK key (0x13)
    kVK_KanaModeKey                 = VK_KANA, // IME KANA mode key (0x15)
    kVK_HangulModeKey               = VK_HANGUL, // IME HANGUL mode key (0x15)
    //kVK_Undefined                 = 0x16,
            kVK_JunjaModeKey                = VK_JUNJA, // IME JUNJA mode key (0x17)
    kVK_FinalModeKey                = VK_FINAL, // IME FINAL mode key (0x18)
    kVK_HanjaModeKey                = VK_HANJA, // IME HANJA mode key (0x19)
    kVK_KanjiModeKey                = VK_KANJI, // IME KANJI mode key (0x19)
    //kVK_Undefined                 = 0x1A,
            kVK_ConvertKey                  = VK_CONVERT, // IME CONVERT key (0x1c)
    kVK_NonConvertKey               = VK_NONCONVERT, // IME NONCONVERT key (0x1d)
    kVK_AcceptKey                   = VK_ACCEPT, // IME ACCEPT key (0x1e)
    kVK_ModeChangeKey               = VK_MODECHANGE, // IME MODE CHANGE REQUEST key (0x1f)
    kVK_SelectKey                   = VK_SELECT, // SELECT key (0x29)
    kVK_PrintKey                    = VK_PRINT, // PRINT key (0x2a)
    kVK_ExecuteKey                  = VK_EXECUTE, // EXECUTE key (0x2b)
    kVK_SnapshotKey                 = VK_SNAPSHOT, // SNAPSHOT key (0x2c)
    kVK_InsertKey                   = VK_INSERT, // INSERT key (0x2d)
    // kVK_Undefined                = 0x3a-40,
            kVK_LeftWindowsKey              = VK_LWIN, // LEFT WINDOWS key (0x5b)
    kVK_RightWindowsKey             = VK_RWIN, // RIGHT WINDOWS key (0x5c)
    kVK_ApplicationsKey             = VK_APPS, // APPLICATIONS key (0x5d)
    // kVK_Reserved                 = 0x5E,
            kVK_SleepKey                    = VK_SLEEP, // SLEEP key (0x5f)
    kVK_KeypadSeparator             = VK_SEPARATOR, // keypad SEPARATOR key (0x6c)
    kVK_F21                         = VK_F21, // F21 key (0x84)
    kVK_F22                         = VK_F22, // F22 key (0x85)
    kVK_F23                         = VK_F23, // F23 key (0x86)
    kVK_F24                         = VK_F24, // F24 key (0x87)
    //kVK_Unassigned                = 0x88-8F,
            kVK_NumLockKey                  = VK_NUMLOCK, // NUMLOCK key (0x90)
    kVK_ScrollLockKey               = VK_SCROLL, // SCROLL LOCK key (0x91)
    kVK_LeftShift                   = VK_LSHIFT, // LEFT SHIFT key (0xA0)
    kVK_LeftControl                 = VK_LCONTROL, // LEFT CONTROL key (0xA2)
    kVK_Menu                        = VK_MENU, // MENU key (0x12)
    kVK_LeftMenu                    = VK_LMENU, // LEFT MENU key (0xA4)
    kVK_RightMenu                   = VK_RMENU, // RIGHT MENU key (0xA5)
    kVK_BrowserBackKey              = VK_BROWSER_BACK, // BROWSER BACK key (0xA6)
    kVK_BrowserForwardKey           = VK_BROWSER_FORWARD, // BROWSER FORWARD key (0xA7)
    kVK_BrowserRefreshKey           = VK_BROWSER_REFRESH, // BROWSER REFRESH key (0xA8)
    kVK_BrowserStopKey              = VK_BROWSER_STOP, // BROWSER STOP key (0xA9)
    kVK_BrowserSearchKey            = VK_BROWSER_SEARCH, // BROWSER SEARCH key (0xAA)
    kVK_BrowserFavoritesKey         = VK_BROWSER_FAVORITES, // BROWSER FAVORITES key (0xAB)
    kVK_BrowserHomeKey              = VK_BROWSER_HOME, // BROWSER HOME key (0xAC)
    kVK_MediaNextTrackKey           = VK_MEDIA_NEXT_TRACK, // MEDIA NEXT TRACK key (0xB0)
    kVK_MediaPrevTrackKey           = VK_MEDIA_PREV_TRACK, // MEDIA PREV TRACK key (0xB1)
    kVK_MediaStopKey                = VK_MEDIA_STOP, // MEDIA STOP key (0xB2)
    kVK_MediaPlayPauseKey           = VK_MEDIA_PLAY_PAUSE, // MEDIA PLAY/PAUSE key (0xB3)
    kVK_LaunchMailKey               = VK_LAUNCH_MAIL, // LAUNCH MAIL key (0xB4)
    kVK_LaunchMediaSelectKey        = VK_LAUNCH_MEDIA_SELECT, // LAUNCH MEDIA SELECT key (0xB5)
    kVK_LaunchApp1Key               = VK_LAUNCH_APP1, // LAUNCH APP1 key (0xB6)
    kVK_LaunchApp2Key               = VK_LAUNCH_APP2, // LAUNCH APP2 key (0xB7)
    //kVK_Reserved                  = 0xB8-B9
    kVK_ProcessKey                  = VK_PROCESSKEY, // PROCESS key (0xE5)
    kVK_AttnKey                     = VK_ATTN, // ATTN key (0xF6)
    kVK_CrSelKey                    = VK_CRSEL, // CRSEL key (0xF7)
    kVK_ExSelKey                    = VK_EXSEL, // EKSEL key (0xF8)
    kVK_EraseEOFKey                 = VK_EREOF, // Erase EOF key (0xF9)
    kVK_PlayKey                     = VK_PLAY, // Play key (0xFA)
    kVK_ZoomKey                     = VK_ZOOM, // Zoom key (0xFB)
};

// common virtual key codes
enum {
    kVK_ANSI_A                    = 0x41, // A key
    kVK_ANSI_S                    = 0x53, // S key
    kVK_ANSI_D                    = 0x44, // D key
    kVK_ANSI_F                    = 0x46, // F key
    kVK_ANSI_H                    = 0x48, // H key
    kVK_ANSI_G                    = 0x47, // G key
    kVK_ANSI_Z                    = 0x5A, // Z key
    kVK_ANSI_X                    = 0x58, // X key
    kVK_ANSI_C                    = 0x43, // C key
    kVK_ANSI_V                    = 0x56, // V key
    kVK_ANSI_B                    = 0x42, // B key
    kVK_ANSI_Q                    = 0x51, // Q key
    kVK_ANSI_W                    = 0x57, // W key
    kVK_ANSI_E                    = 0x45, // E key
    kVK_ANSI_R                    = 0x52, // R key
    kVK_ANSI_Y                    = 0x59, // Y key
    kVK_ANSI_T                    = 0x54, // T key
    kVK_ANSI_1                    = 0x31, // 1 key
    kVK_ANSI_2                    = 0x32, // 2 key
    kVK_ANSI_3                    = 0x33, // 3 key
    kVK_ANSI_4                    = 0x34, // 4 key
    kVK_ANSI_6                    = 0x36, // 6 key
    kVK_ANSI_5                    = 0x35, // 5 key
    kVK_ANSI_Equal                = VK_OEM_PLUS, // EQUAL/PLUS SIGN key (0xBB)
    kVK_ANSI_9                    = 0x39, // 9 key
    kVK_ANSI_7                    = 0x37, // 7 key
    kVK_ANSI_Minus                = VK_OEM_MINUS, // MINUS SIGN key (0xBD)
    kVK_ANSI_8                    = 0x38, // 8 key
    kVK_ANSI_0                    = 0x30, // 0 key
    kVK_ANSI_RightBracket         = VK_OEM_6, // US keyboard ']}' key (0xDD)
    kVK_ANSI_O                    = 0x4F, // 0 key
    kVK_ANSI_U                    = 0x55, // U key
    kVK_ANSI_LeftBracket          = VK_OEM_4, // US keyboard '[{' key (0xDB)
    kVK_ANSI_I                    = 0x49, // I key
    kVK_ANSI_P                    = 0x50, // P key
    kVK_ANSI_L                    = 0x4C, // L key
    kVK_ANSI_J                    = 0x4A, // J key
    kVK_ANSI_Quote                = VK_OEM_7, // US keyboard single/double quote key (0xDE)
    kVK_ANSI_K                    = 0x4B, // K key
    kVK_ANSI_Semicolon            = VK_OEM_1, // US keyboard ';:' key (0xBA)
    kVK_ANSI_Backslash            = VK_OEM_5, // US keyboard '\|' key (0xDC)
    kVK_ANSI_Comma                = VK_OEM_PLUS, // COMMA/LEFT TRIANGLE QUOTE key (0xBC)
    kVK_ANSI_Slash                = VK_OEM_2, // US keyboard '/?' key (0xBF)
    kVK_ANSI_N                    = 0x4E, // N key
    kVK_ANSI_M                    = 0x4D, // M key
    kVK_ANSI_Period               = VK_OEM_PERIOD, // PERIOD/RIGHT TRAINGLE QUOTE key (0xBE)
    kVK_ANSI_Grave                = VK_OEM_3, // US keyboard '`~' key (0xC0)
    kVK_ANSI_KeypadDecimal        = VK_DECIMAL, // keypad DECIMAL key (0x6e)
    kVK_ANSI_KeypadMultiply       = VK_MULTIPLY, // keypad MULTIPLY key (0x6a)
    kVK_ANSI_KeypadPlus           = VK_ADD, // keypad ADD/PLUS key (0x6b)
    kVK_ANSI_KeypadClear          = VK_CLEAR, // CLEAR key (0x0c)
    kVK_ANSI_KeypadDivide         = VK_DIVIDE, // DIVIDE key (0x6f)
    kVK_ANSI_KeypadEnter          = -1, // not supported in Windows
    kVK_ANSI_KeypadMinus          = VK_SUBTRACT, // keypad SUBTRACT/MINUS key (0x6d)
    kVK_ANSI_KeypadEquals         = -1, // not supported in Windows
    kVK_ANSI_Keypad0              = VK_NUMPAD0, // keypad 0 key (0x60)
    kVK_ANSI_Keypad1              = VK_NUMPAD1, // keypad 1 key (0x61)
    kVK_ANSI_Keypad2              = VK_NUMPAD2, // keypad 2 key (0x62)
    kVK_ANSI_Keypad3              = VK_NUMPAD3, // keypad 3 key (0x63)
    kVK_ANSI_Keypad4              = VK_NUMPAD4, // keypad 4 key (0x64)
    kVK_ANSI_Keypad5              = VK_NUMPAD5, // keypad 5 key (0x65)
    kVK_ANSI_Keypad6              = VK_NUMPAD6, // keypad 6 key (0x66)
    kVK_ANSI_Keypad7              = VK_NUMPAD7, // keypad 7 key (0x67)
    kVK_ANSI_Keypad8              = VK_NUMPAD8, // keypad 8 key (0x68)
    kVK_ANSI_Keypad9              = VK_NUMPAD9  // keypad 9 key (0x69)
};

enum {
    kVK_Return                    = VK_RETURN, // ENTER/RETURN key (0x0D)
    kVK_Tab                       = VK_TAB, // TAB key (0x09)
    kVK_Space                     = VK_SPACE, // SPACEBAR key (0x20)
    kVK_Delete                    = VK_BACK, // BACKSPACE key (0x08)
    //kVK_Delete                    = VK_DELETE, // DEL key (0x2d)
    kVK_Escape                    = VK_ESCAPE, // ESC key (0x1B)
    kVK_Command                   = VK_LWIN, // WIN key (0x5B)
    kVK_Shift                     = VK_SHIFT, // SHIFT key (0x10)
    kVK_CapsLock                  = VK_CAPITAL, // CAPS LOCK key (0x14)
    kVK_Option                    = VK_MENU, // ALT key (0x12), equivalent of macOS OPTION key
    kVK_Alt                       = kVK_Option,
    kVK_Control                   = VK_CONTROL, // CONTROL key (0x11)
    kVK_RightShift                = VK_RSHIFT, // RIGHT SHIFT key (0xA1)
    kVK_RightOption               = kVK_RightMenu, // RIGHT ALT key (0xA5)
    kVK_RightAlt                  = kVK_RightOption,
    kVK_RightControl              = VK_RCONTROL, // RIGHT CONTROL key (0xA3)
    kVK_Function                  = -1, // not supported in Windows
    kVK_F17                       = VK_F17, // F17 key (0x80)
    kVK_VolumeUp                  = VK_VOLUME_UP, // VOLUME UP key (0xAF)
    kVK_VolumeDown                = VK_VOLUME_DOWN, // VOLUME DOWN key (0xAE)
    kVK_Mute                      = VK_VOLUME_MUTE, // VOLUME MUTE key (0xAD)
    kVK_F18                       = VK_F18, // F18 key (0x81)
    kVK_F19                       = VK_F19, // F19 key (0x82)
    kVK_F20                       = VK_F20, // F20 key (0x83)
    kVK_F5                        = VK_F5, // F5 key (0x74)
    kVK_F6                        = VK_F6, // F6 key (0x75)
    kVK_F7                        = VK_F7, // F7 key (0x76)
    kVK_F3                        = VK_F3, // F3 key (0x72)
    kVK_F8                        = VK_F8, // F8 key (0x77)
    kVK_F9                        = VK_F9, // F9 key (0x78)
    kVK_F11                       = VK_F11, // F11 key (0x7a)
    kVK_F13                       = VK_F13, // F13 key (0x7c)
    kVK_F16                       = VK_F16, // F16 key (0x7f)
    kVK_F14                       = VK_F14, // F14 key (0x7d)
    kVK_F10                       = VK_F10, // F10 key (0x79)
    kVK_F12                       = VK_F12, // F12 key (0x7b)
    kVK_F15                       = VK_F15, // F15 key (0x7e)
    kVK_Help                      = VK_HELP, // HELP key
    kVK_Home                      = VK_HOME, // HOME key
    kVK_PageUp                    = VK_PRIOR, // PAGE UP key (0x21)
    kVK_ForwardDelete             = -1, // not supported in Windows
    kVK_F4                        = VK_F4, // F4 key (0x73)
    kVK_End                       = VK_END, // END key (0x23)
    kVK_F2                        = VK_F2, // F2 key (0x71)
    kVK_PageDown                  = VK_NEXT, // PAGE DOWN key (0x22)
    kVK_F1                        = VK_F1, // F1 key (0x70)
    kVK_LeftArrow                 = VK_LEFT, // LEFT ARROW key (0x25)
    kVK_RightArrow                = VK_RIGHT, // RIGHT ARROW key (0x27)
    kVK_DownArrow                 = VK_DOWN, // DOWN ARROW key (0x28)
    kVK_UpArrow                   = VK_UP // UP ARROW key (0x26)
};

#endif //KEYBOARD_EVENTS_VIRTUAL_KEY_CODES_H
