//
// Created by Michal Ziobro on 31.05.2017.
//

#include <stdio.h>
#include "../include/hot_keys_events.h"
#include "../include/keyboard_events.h"
#include "../mouse_events/scroll_wheel_events.h"
#include "../../windows_helpers/windows.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <unistd.h>

static const char *kSystemHotKeysXML = "./resources/system_hotkeys.xml";
static const char *kApplicationHotKeysXML = "./resources/application_hotkeys.xml";

static xmlNodePtr hot_keys_find_node_by_name(xmlNodePtr node, const char *hot_keys_name) {

    // go through <hotkeys> nodes and find one with hot_keys_name
    for(node = node->xmlChildrenNode;  node != NULL; node = node->next) {
        if(xmlStrcmp(node->name, (const xmlChar *) "hotkeys") == 0) {
            xmlChar *name = xmlGetProp(node, "name");
            if(xmlStrcmp(name, (const xmlChar *) hot_keys_name) == 0) {
                xmlFree(name);
               return node;
            }
            xmlFree(name);
        }
    }
}

static xmlNodePtr hot_keys_find_node_by_app_name(xmlNodePtr node,
                                                 const char *application_name,
                                                 bool consider_default) {

    xmlNodePtr default_app_node = NULL;

    // go throught <app> nodes and find one with application name
    for(node = node->xmlChildrenNode; node != NULL; node = node->next) {
        if(xmlStrcmp(node->name, (const xmlChar *) "app") == 0) {
            xmlChar *name = xmlGetProp(node, "name");
            if(strstr(application_name, name) != NULL) {
                return node;
            } else if(consider_default && strstr(kDefaultApplication, name) != NULL) {
                default_app_node = node;
            }
        }
    }

    return default_app_node;
}

static hot_keys_t *hot_keys_from_node(xmlNodePtr node) {

    hot_keys_t *hot_keys = malloc(sizeof(hot_keys_t));

    for(node = node->xmlChildrenNode;  node != NULL; node = node->next) {
        if(xmlStrcmp(node->name, (const xmlChar *) "key_code") == 0) {
            xmlChar *key_code = xmlNodeListGetString(node->doc, node->xmlChildrenNode, 1);
            printf("key_code: %s\n", key_code);
            hot_keys->virtual_key_code = atoi(key_code);
            xmlFree(key_code);
        } else if(xmlStrcmp(node->name, (const xmlChar *) "modifier_flags") == 0) {
            xmlChar *modifier_flags = xmlNodeListGetString(node->doc, node->xmlChildrenNode, 1);
            printf("modifier_flags: %s\n", modifier_flags);
            hot_keys->modifier_keys_flags = atol(modifier_flags);
            xmlFree(modifier_flags);
        } else if(xmlStrcmp(node->name, (const xmlChar *) "hold_time_in_s") == 0) {
            xmlChar *hold_time_in_s = xmlNodeListGetString(node->doc, node->xmlChildrenNode, 1);
            printf("hold_time_in_s: %s\n", hold_time_in_s);
            hot_keys->hold_time_in_s = atoi(hold_time_in_s);
            xmlFree(hold_time_in_s);
        }
    }

    return hot_keys;
}

static hot_keys_t *system_hot_keys_get(const char *hot_keys_name) {

    xmlDocPtr doc;
    xmlNodePtr node;
    hot_keys_t *hot_keys = 0;

    /**
        // make absolute path to XML file
        char path[1024];
        if( getcwd(path, sizeof(path)) == NULL) {
            fprintf(stderr, "%s: Could not get current directory path.\n", __func__);
            return NULL;
        }
        strcat(path, kSystemHotKeysXML);
     **/

    if( (doc = xmlReadFile(kSystemHotKeysXML, NULL, 0)) == NULL )  {  // or xmlReadFile(docname)
        fprintf(stderr, "%s: Document not parsed successfully.\n", __func__);
        return NULL;
    }

    if( (node = xmlDocGetRootElement(doc)) == NULL) {
        fprintf(stderr, "%s: Empty document.\n", __func__);
        xmlFreeDoc(doc);
        return NULL;
    }

    if(xmlStrcmp(node->name, (const xmlChar *) "system-hotkeys") != 0) {
        fprintf(stderr, "%s: Document of the wrong type, root node != system-hotkeys.\n", __func__);
        xmlFreeDoc(doc);
        return NULL;
    }

    if( (node = hot_keys_find_node_by_name(node, hot_keys_name)) == NULL) {
        fprintf(stderr, "%s: Could not find node with given hot_keys_name.\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    hot_keys = hot_keys_from_node(node);

    xmlFreeDoc(doc);
    return hot_keys;
}

static hot_keys_t *app_hot_keys_get(const char *hot_keys_name, const char *application_name, bool consider_default) {

    xmlDocPtr doc;
    xmlNodePtr node;
    hot_keys_t *hot_keys = 0;

    if( (doc = xmlReadFile(kApplicationHotKeysXML, NULL, 0)) == NULL ) {
        fprintf(stderr, "%s: Document not parsed successfully.\n", __func__);
        return NULL;
    }

    if( (node = xmlDocGetRootElement(doc)) == NULL ) {
        fprintf(stderr, "%s: Empty document.\n", __func__);
        xmlFreeDoc(doc);
        return NULL;
    }

    if(xmlStrcmp(node->name, (const xmlChar *) "application-hotkeys") != 0) {
        fprintf(stderr, "%s: Document of the wrong type, root element != application-hotkeys.\n", __func__);
        xmlFreeDoc(doc);
        return NULL;
    }

    if( (node = hot_keys_find_node_by_name(node, hot_keys_name)) == NULL) {
        fprintf(stderr, "%s: Could not find node with given hot_keys_name.\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    if( (node = hot_keys_find_node_by_app_name(node, application_name, consider_default)) == NULL) {
        fprintf(stderr, "%s: Could not find node for given application_name (or if considered for default application).\n", __func__);
        xmlFreeDoc(doc);
        return NULL;
    }

    hot_keys = hot_keys_from_node(node);

    xmlFreeDoc(doc);
    return hot_keys;
}

// functions mimic common mouse/
// touch pad gestures using hot keys
void zoom_hot_keys_event(zoom_direction_t zoom_direction) {

    switch(zoom_direction) {
        case kZoomIn:
            front_app_hot_keys_event(kZoomInHotKeys, true);
            break;
        case kZoomOut:
            front_app_hot_keys_event(kZoomOutHotKeys, true);
            break;
        default:
            return;
    }
}

void rotate_hot_keys_event(rotate_direction_t rotate_direction) {

    switch(rotate_direction) {
        case kRotateClockWise:
            front_app_hot_keys_event(kRotateCWHotKeys, false);
            break;
        case kRotateCounterClockWise:
            front_app_hot_keys_event(kRotateCCWHotKeys, false);
            break;
        default:
            return;
    }
}

void swipe_hot_keys_event(swipe_direction_t swipe_direction) {
    printf("Not supported on Windows\n");
}

void scroll_hot_keys_event(scroll_direction_t scroll_direction) {
    // use mouse events
    switch(scroll_direction) {
        case kScrollUp:
            scroll_wheel_scroll_vertical_up(SCROLL_UNIT);
            break;
        case kScrollDown:
            scroll_wheel_scroll_vertical_down(SCROLL_UNIT);
            break;
        case kScrollLeft:
            scroll_wheel_scroll_horizontal_left(SCROLL_UNIT);
            break;
        case kScrollRight:
            scroll_wheel_scroll_horizontal_right(SCROLL_UNIT);
            break;
        default:
            return;
    }
}

// Windows system hot keys
void system_hot_keys_event(const char *hot_keys_name) {

    hot_keys_t *hk = system_hot_keys_get(hot_keys_name);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name.\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

// application hot keys
void front_app_hot_keys_event(const char *hot_keys_name, bool consider_default) {

    char *application_name = front_window_owner();
    app_hot_keys_event(hot_keys_name, application_name, consider_default);
}

void app_hot_keys_event(const char *hot_keys_name, const char *application_name, bool consider_default) {

    hot_keys_t *hk = app_hot_keys_get(hot_keys_name, application_name, consider_default);
    if(hk == NULL) {
        fprintf(stderr, "%s: Could not find hot keys definition for given hot keys name and application name (if considered, including default hot keys definition).\n", __func__);
        return;
    }
    key_input_modified(hk->virtual_key_code, hk->modifier_keys_flags);
}

// video & audio players common hot keys
void player_play_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerPlayHotKeys, true);
}
void player_stop_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerStopHotKeys, true);
}
void player_next_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerNextHotKeys, true);
}
void player_previous_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerPreviousHotKeys, true);
}
void player_step_forward_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerStepForwardHotKeys, true);
}
void player_step_backward_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerStepBackwardHotKeys, true);
}
void player_loop_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerLoopHotKeys, true);
}
void player_shuffle_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerShuffleHotKeys, true);
}
void player_volume_up_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerVolumeUpHotKeys, true);
}
void player_volume_down_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerVolumeDownHotKeys, true);
}
void player_mute_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerMuteHotKeys, true);
}

void player_full_screen_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerFullScreenHotKeys, true);
}

void player_subtitles_hot_keys_event(void) {
    front_app_hot_keys_event(kPlayerSubtitlesHotKeys, true);
}

// browser common hot keys
void browser_new_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserNewTabHotKeys, true);
}
void browser_next_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserNextTabHotKeys, true);
}
void browser_prev_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserPreviousTabHotKeys, true);
}
void browser_add_bookmark_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserAddBookmarkHotKeys, true);
}
void browser_new_private_window_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserNewPrivateWindowHotKeys, true);
}
void browser_reopen_closed_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserReopenClosedTabHotKeys, true);
}
void browser_open_file_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserOpenFileHotKeys, true);
}
void browser_close_tab_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserCloseTabHotKeys, true);
}
void browser_close_window_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserCloseWindowHotKeys, true);
}
void browser_reload_page_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserReloadPageHotKeys, true);
}
void browser_show_downloads_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowDownloadsHotKeys, true);
}
void browser_show_history_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowHistoryHotKeys, true);
}
void browser_show_sidebar_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowSidebarHotKeys, true);
}
void browser_show_page_source_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserShowPageSourceHotKeys, true);
}
void browser_home_page_hot_keys_event(void) {
    front_app_hot_keys_event(kBrowserHomePageHotKeys, true);
}

// slide show common hot keys
void slide_show_start_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowStartHotKeys, true);
}
void slide_show_end_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowEndHotKeys, true);
}
void slide_show_next_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowNextHotKeys, true);
}
void slide_show_next_no_animation_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowNextNoAnimationHotKeys, true);
}
void slide_show_previous_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPreviousHotKeys, true);
}
void slide_show_previous_no_animation_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPreviousNoAnimationHotKeys, true);
}
void slide_show_blank_slide_black_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowBlankSlideBlackHotKeys, true);
}
void slide_show_blank_slide_white_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowBlankSlidekWhiteHotKeys, true);
}
void slide_show_first_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowFirstSlideHotKeys, true);
}
void slide_show_last_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowLastSlideHotKeys, true);
}
void slide_show_go_to_next_hidden_slide_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowGoToNextHiddenSlideHotKeys, true);
}
void slide_show_pen_pointer_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowPenPointerHotKeys, true);
}
void slide_show_arrow_pointer_hot_keys_event(void) {
    front_app_hot_keys_event(kSlideShowArrowPointerHotKeys, true);
}

// other common hot keys
void zoom_actual_size_hot_keys_event(void) {
    front_app_hot_keys_event(kZoomActualSizeHotKeys, true);
}
void enter_full_screen_hot_keys_event(void) {
    front_app_hot_keys_event(kEnterFullScreenHotKeys, true);
}