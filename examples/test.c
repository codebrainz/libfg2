#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <libfg2/libfg2.h>

/* this device MUST be a valid V4L2 capture device */
#ifndef VALID_DEVICE
#define VALID_DEVICE "/dev/video0"
#endif

/* this width and height MUST be exactly supported by the device */
#ifndef VALID_WIDTH
#define VALID_WIDTH 640
#endif
#ifndef VALID_HEIGHT
#define VALID_HEIGHT 480
#endif

static char *passed_string = "passed";
static char *failed_string = "failed";

static char *res_string(int res)
{
    if (res == 0)
        return passed_string;
    else
        return failed_string;
}

static void print_result(const char *func, int result)
{
    printf("** Test '%s' %s.\n", func, res_string(result));
}

int test_fg_open(void)
{
    fg_grabber *fg = fg_open(VALID_DEVICE);

    assert(fg->device != NULL);
    assert(fg->fd >= 0);

    assert(fg->caps.capabilities & V4L2_CAP_VIDEO_CAPTURE);

    assert(fg->num_inputs > 0);
    assert(fg->inputs != NULL);
    assert(fg->input == 0);

    assert(fg->num_tuners >= 0);
    assert(fg->tuner == 0);

    assert(fg->format.fmt.pix.width > 0);
    assert(fg->format.fmt.pix.height > 0);
    assert(fg->format.fmt.pix.pixelformat == FG_FORMAT_RGB24);

    fg_close(fg);

    return 0;
}

int test_fg_close(void)
{
    fg_grabber *fg = fg_open(VALID_DEVICE);
    fg_close(fg);
    // how to test?
    return 0;
}

int test_fg_set_capture_size(void)
{
    fg_grabber *fg = fg_open(VALID_DEVICE);

    fg_size sz;

    sz.width = VALID_WIDTH;
    sz.height = VALID_HEIGHT;

    fg_set_capture_size(fg, sz);

    sz = fg_get_capture_size(fg);

    assert(sz.width == VALID_WIDTH);
    assert(sz.height == VALID_HEIGHT);

    fg_close(fg);

    return 0;
}

int test_fg_get_capture_size(void)
{
    fg_grabber *fg = fg_open(VALID_DEVICE);

    fg_size sz = {VALID_WIDTH, VALID_HEIGHT};

    fg_set_capture_size(fg, sz);

    sz = fg_get_capture_size(fg);

    assert(sz.width == VALID_WIDTH);
    assert(sz.height == VALID_HEIGHT);

    fg_close(fg);

    return 0;
}

int test_fg_set_format(void)
{
    fg_grabber *fg = fg_open(VALID_DEVICE);

    int i;
    int formats[4] = {
        FG_FORMAT_BGR24,
        FG_FORMAT_RGB24,
        FG_FORMAT_YUV420,
        FG_FORMAT_YVU420
        };

    for (i=0; i < 4; i++)
    {
        int result = fg_set_format(fg, formats[i]);

        assert(result == 0);
        assert(fg->format.fmt.pix.pixelformat == formats[i]);
    }

    fg_close(fg);

    return 0;
}

int test_fg_get_format(void)
{
    fg_grabber *fg = fg_open(VALID_DEVICE);

    int i;
    int formats[4] = {
        FG_FORMAT_BGR24,
        FG_FORMAT_RGB24,
        FG_FORMAT_YUV420,
        FG_FORMAT_YVU420
        };

    for (i=0; i < 4; i++)
    {
        fg_set_format(fg, formats[i]);
        int result = fg_get_format(fg);
        assert(result == formats[i]);
        assert(fg->format.fmt.pix.pixelformat == formats[i]);
    }

    fg_close(fg);

    return 0;
}

int test_fg_get_input_count(void)
{
    int test_num, real_num;
    fg_grabber *fg = fg_open(VALID_DEVICE);
    struct v4l2_input inp;

    test_num = fg_get_input_count(fg);
    assert(test_num > 0);

    real_num = 0;
    inp.index = 0;
    while (ioctl(fg->fd, VIDIOC_ENUMINPUT, &inp) != -1)
    {
        real_num++;
        inp.index++;
    }

    assert(test_num == real_num);

    fg_close(fg);

    return 0;
}

int main(int argc, char *argv[])
{
    print_result("fg_open()", test_fg_open());
    print_result("fg_close()", test_fg_close());
    print_result("fg_set_capture_size()", test_fg_set_capture_size());
    print_result("fg_get_capture_size()", test_fg_get_capture_size());
    print_result("fg_set_format()", test_fg_set_format());
    print_result("fg_get_format()", test_fg_get_format());
    print_result("fg_get_input_count()", test_fg_get_input_count());
    return 0;
}


















