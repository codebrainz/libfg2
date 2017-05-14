#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libfg2/libfg2-gdkpixbuf.h>

GdkPixbuf *fg_frame_to_gdk_pixbuf(fg_frame *fr)
{
    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_to_gdk_pixbuf(): wrong frame format");
        return NULL;
    }

    GdkPixbuf *pb = gdk_pixbuf_new_from_data(
        fr->data,
        GDK_COLORSPACE_RGB, 0, 8,
        fr->size.width,
        fr->size.height,
        fr->rowstride,
        NULL, NULL);
    return pb;
}
