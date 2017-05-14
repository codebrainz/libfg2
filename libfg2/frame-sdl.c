#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libfg2/libfg2-sdl.h>

SDL_Surface *fg_frame_to_sdl_surface(fg_frame *fr)
{
    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_to_sdl_surface(): wrong frame format");
        return NULL;
    }

    SDL_Surface *frame;

    frame = SDL_CreateRGBSurfaceFrom(fr->data,
            fr->size.width,
            fr->size.height,
            24,
            fr->rowstride,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            0x0000ff, 0x00ff00, 0xff0000,
#else
            0xff0000, 0x00ff00, 0x0000ff,
#endif
            0);
    return frame;
}
