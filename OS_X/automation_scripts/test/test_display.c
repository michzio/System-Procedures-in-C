//
// Created by Michal Ziobro on 08/10/2016.
//

#include <unistd.h>
#include <math.h>
#include <printf.h>
#include <Carbon/Carbon.h>
#include "test_display.h"
#include "../system/display.h"
#include "../../../../unit_tests/test/assertion.h"
#include "../../../../unit_tests/common/comparer.h"
#include "../../../../common/bitwise.h"
#include "../../../../common/bitmaps.h"
#include "../../../../common/libraries/png/png-encoding.h"

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

static int count = 0;

void display_stream_handler(const unsigned char *frameBuffer, const size_t frameBufferLength,
             const size_t frameWidth, const size_t frameHeight, const size_t bytesPerPixel) {

    // printf("Display stream frame buffer:\n");
    // bytes_array_dump_segment(frameBuffer, 100, 200, 10);
    count++;
    char filePath[256];
    sprintf(filePath, "/Users/michzio/Desktop/display_stream/%d.png", count);

    writeRGBAasPNGFile( BGRABytesArray2RGBABytesArray(frameBuffer, frameBufferLength),
                        frameWidth, frameHeight, 8, filePath);
};

static void test_display_stream(void) {

    CGDisplayStreamRef  displayStream = display_stream_init(1440, 900, display_stream_handler);
    display_stream_start(displayStream);
    sleep(5);
    display_stream_stop(displayStream);
    sleep(5);
    display_stream_start(displayStream);
    sleep(5);
    display_stream_stop(displayStream);
}

static void run_tests(void) {
    //test_display_brightness();
    test_display_stream();
}

test_display_t test_display = { .run_tests = run_tests };