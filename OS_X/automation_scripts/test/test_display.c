//
// Created by Michal Ziobro on 08/10/2016.
//

#include <unistd.h>
#include <printf.h>
#include <stdlib.h>
#include "test_display.h"
#include "system/display.h"
#include "test/assertion.h"
#include "png/png-encoding.h"
#include "png/png-helper.h"


static void test_display_brightness(void) {

    float init_brightness = 0.0f;
    float brightness = 0.0f;

    // get current brightness
    brightness = init_brightness = display_get_brightness();
    printf("Brightness level - initial: %.2f\n", brightness);

    // set half of current brightness
    display_set_brightness(init_brightness*0.5);
    brightness = display_get_brightness();

    assert_not_equal_int( (int) (brightness*100), (int) (init_brightness*100), "Brightness changed!");
    assert_equal_int( (int) (brightness*100), (int) (init_brightness*0.5*100), "Brightness reduced by half");
    printf("Brightness level - after setting: %.2f\n", brightness);
    sleep(1);

    // reset brightness to previous value
    display_set_brightness(init_brightness);
    brightness = display_get_brightness();

    assert_equal_int( (int) (brightness*100), (int) (init_brightness*100), "Brightness reset to init value!");
    printf("Brightness level - after resetting: %.2f\n", brightness);
}

static void test_display_get_pixel_size(void) {

    size_t width = 0, height = 0;
    display_get_pixel_size(&width, &height);

    printf("Display size: [%zu, %zu]\n", width, height);
}

static void test_display_screen_snapshot_to_buffer() {

    unsigned char *rgbaData = 0;
    size_t rgbaDataLength = 0;
    size_t width = 0;
    size_t height = 0;

    display_screen_snapshot_to_buffer(&rgbaData, &rgbaDataLength, &width, &height);

    assert_not_null(rgbaData, __func__);
    writeRGBAasPNGFile(rgbaData, width, height, PNG_BIT_DEPTH_8, "/Users/michzio/Desktop/test_screen_snapshot.png");
    free(rgbaData);
}

static void run_tests(void) {
    test_display_brightness();
    test_display_get_pixel_size();
    test_display_screen_snapshot_to_buffer();
}

test_display_t test_display = { .run_tests = run_tests };