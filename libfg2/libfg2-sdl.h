#ifndef LIBFG2_SDL_H
#define LIBFG2_SDL_H

#include <libfg2/libfg2.h>
#include <SDL/SDL.h>

///
/// \brief Convert #fg_frame to an SDL_Surface.
///
/// This function creates an SDL_Surface whos data (pixels) points to the
/// data for the #fg_frame.  If the frame is freed, the SDL_Surface's data is
/// also freed, but not the SDL_Surface.  If the SDL_Surface is freed, the
/// #fg_frame's data is not freed.
///
/// \param fr Frame to convert.
///
/// \return An SDL_Surface on success or NULL on error.
///
SDL_Surface *fg_frame_to_sdl_surface(fg_frame *fr);

#endif /* LIBFG2_SDL_H */
