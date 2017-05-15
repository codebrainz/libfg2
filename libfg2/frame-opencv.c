#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libfg2/libfg2-opencv.h>
#include <libfg2/convert.h>

// FIXME: where is this function defined now? opencv2 seems to have moved it
extern void *iplMalloc(int);

IplImage *fg_frame_to_ipl_image(fg_frame *fr)
{

    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_to_ipl_image(): wrong frame format");
        return NULL;
    }

    unsigned char *img32;
    IplImage *image;

    img32 = iplMalloc(fr->size.width * fr->size.height * 4);

    rgb24_to_rgb32(fr->data, fr->length, img32);

    image = cvCreateImage(cvSize(fr->size.width, fr->size.height),
                IPL_DEPTH_32S, 4);

    cvSetImageData(img32, fr->data, fr->rowstride);

    return image;
}
