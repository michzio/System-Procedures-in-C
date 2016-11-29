//
// Created by Michal Ziobro on 22/10/2016.
//

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "../automation_scripts.h"
#include "test_automation_scripts.h"
#include "../../../../../cocoa/AppleScriptSystemAutomation/AppleScriptSystemAutomation/AppleScriptSystemAutomation.h"

static void test_cocoa_apple_script_system_automation_lib(void) {

    requestAccessibilityFeaturesAccess();
    const char *params[1] = {"10"};
    executeAppleScriptFromFile("/Users/michzio/Developer/MyProjects/BachelorDegree/apple_scripts/volume.scpt",
                               "volume_output", params, 1);
}

static void test_display_notification(void) {
    display_notification("My notification body", "My Title ", "My Subtitle");
}

static void run_tests(void) {

    test_cocoa_apple_script_system_automation_lib();
    //test_display_notification();
}

test_automation_scripts_t test_automation_scripts = { .run_tests = run_tests };

