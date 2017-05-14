#ifndef LIBFG2_OPENCV_H
#define LIBFG2_OPENCV_H

#include <libfg2/libfg2.h>
#include <cv.h>

///
/// \brief Convert #fg_frame to an IplImage.
///
/// This function creates an IplImage whos data points to the data for the
/// #fg_frame.  If the frame is freed, the IplImage's data is also freed,
/// but not the IplImage.  If the IplImage is freed, the #fg_frame's data is
/// not freed.
///
/// \param fr Frame to convert.
///
/// \return An IplImage on success or NULL on error.
///
IplImage *fg_frame_to_ipl_image(fg_frame *fr);

#endif /* LIBFG2_OPENCV_H */
