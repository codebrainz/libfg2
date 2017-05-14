#ifndef LIBFG2_IMLIB2_H
#define LIBFG2_IMLIB2_H

#include <libfg2/libfg2.h>
#include <Imlib2.h>
///
/// \brief  Convert #fg_frame to an Imlib_Image.
///
/// This function creates an Imlib_Image with newly allocated data.  The image
/// data pointed by the Imlib_Image must be freed before the Imlib_Image.
/// Freeing the Imlib_Image will not free the data and you will lose the
/// pointer to the data if it's not freed before hand.
///
/// \param fr Frame to convert.
///
/// \return An Imlib_Image on success or NULL on error.
///
Imlib_Image *fg_frame_to_imlib2_image(fg_frame *fr);

#endif /* LIBFG2_IMLIB2_H */
