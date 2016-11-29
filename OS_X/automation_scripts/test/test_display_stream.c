//
// Created by Michal Ziobro on 10/10/2016.
//

#include "test_display_stream.h"
#include "../system/display_stream.h"
#include "../../../../common/bitwise.h"
#include "../../../../common/bitmaps.h"
#include "../../../../common/libraries/png/png-encoding.h"
#include "../system/display.h"

static int count = 0;

static void test_create(void) {
    count = 0;
}

static void test_clean(void) {
    // nothing
}
static void display_stream_handler(const void *handlerArgs, const unsigned char *frameBuffer, const size_t frameBufferLength,
                            const size_t frameWidth, const size_t frameHeight, const size_t bytesPerPixel) {

    // printf("Display stream frame buffer:\n");
    // bytes_array_dump_segment(frameBuffer, 100, 200, 10);
    count++;
    char filePath[256];
    sprintf(filePath, "/Users/michzio/Desktop/display_stream/%d.png", count);

    writeRGBAasPNGFile( BGRABytesArray2RGBABytesArray(frameBuffer, frameBufferLength),
                        frameWidth, frameHeight, 8, filePath);
};

static void test_display_stream_new_frames(void) {

    test_create();

    size_t width = 0, height = 0;
    display_get_pixel_size(&width, &height);

    CGDisplayStreamRef displayStream = display_stream_init(width, height, display_stream_handler, NULL);
    display_stream_start(displayStream);
    sleep(5);
    display_stream_stop(displayStream);
    sleep(5);
    display_stream_start(displayStream);
    sleep(5);
    display_stream_stop(displayStream);

    display_stream_free(displayStream);

    test_clean();
}

static void display_stream_updates_handler(const void *handlerArgs, const unsigned char *updateBuffer, const size_t updateBufferLength,
                                           const size_t offsetX, const size_t offsetY, const size_t updateWidth,
                                           const size_t updateHeight, const size_t bytesPerPixel) {

    printf("Display stream update buffer: \n");
    printf("offset: {%zu, %zu}, size: {%zu, %zu}\n", offsetX, offsetY, updateWidth, updateHeight);
    // bytes_array_dump(updateBuffer, updateBufferLength, 20);
    count++;
    char filePath[256];
    sprintf(filePath, "/Users/michzio/Desktop/display_stream_updates/%d.png", count);

    writeRGBAasPNGFile( BGRABytesArray2RGBABytesArray(updateBuffer, updateBufferLength),
                        updateWidth, updateHeight, 8, filePath);
}

static void test_display_stream_update_frames(void) {

    test_create();

    size_t width = 0, height = 0;
    display_get_pixel_size(&width, &height);

    CGDisplayStreamRef displayStream = display_stream_updates_init(width, height, display_stream_updates_handler, NULL);
    display_stream_start(displayStream);
    sleep(5);
    display_stream_stop(displayStream);
    sleep(5);
    display_stream_start(displayStream);
    sleep(5);
    display_stream_stop(displayStream);

    display_stream_free(displayStream);

    test_clean();
}

static void run_tests(void) {
    // test_display_stream_new_frames();
    test_display_stream_update_frames();
}

test_display_stream_t test_display_stream = { .run_tests = run_tests };