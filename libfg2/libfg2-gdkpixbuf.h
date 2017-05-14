#ifndef LIBFG2_GDKPIXBUF_H
#define LIBFG2_GDKPIXBUF_H

#include <libfg2/libfg2.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
///
/// \brief Convert #fg_frame to a GdkPixbuf.
///
/// This function creates a GdkPixbuf whos data points to the data for the
/// #fg_frame.  If the frame is freed, the GdkPixbuf's data is also freed,
/// but not the GdkPixbuf.  If the GdkPixbuf is freed, the #fg_frame's data
/// is not freed.
///
/// \param  fr Frame to convert.
///
/// \return A GdkPixbuf on success or NULL on error.
///
GdkPixbuf *fg_frame_to_gdk_pixbuf(fg_frame *fr);

#endif /* LIBFG2_GDKPIXBUF_H */
