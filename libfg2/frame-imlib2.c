#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libfg2/libfg2-imlib2.h>
#include <libfg2/convert.h>
#include <assert.h>
#include <stdlib.h>

Imlib_Image fg_frame_to_imlib2_image(fg_frame *fr)
{
    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_to_imlib2_image(): wrong frame format");
        return NULL;
    }

    int num_pixels;
    int dst_length;
    unsigned char *data;
    Imlib_Image image;

    num_pixels = fr->length / 3;
    dst_length = num_pixels * sizeof(DATA32) * 4;

    data = malloc(dst_length);
    assert(data != NULL);
    rgb24_to_rgb32(fr->data, fr->length, data);
    image = imlib_create_image_using_copied_data(fr->size.width, fr->size.height,
            (DATA32 *)data);
    free(data);

    assert(image);

    return image;
}
