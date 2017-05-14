#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string.h>
#include <SDL/SDL.h>
#include <libfg2/libfg2.h>

int main(int argc, char *argv[])
{
    char wind_title[256] = {0};
    int quit = 0;

    SDL_Surface *frame;
    SDL_Surface *screen;
    SDL_Event event;

    fg_grabber *fg;
    fg_frame *fr;

    if (argc == 1)
        fg = fg_open(FG_DEFAULT_DEVICE);
    else
        fg = fg_open(argv[1]);

    fr = fg_frame_new(fg);

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(fr->size.width, fr->size.height, 32,
        SDL_SWSURFACE|SDL_SRCALPHA);

    snprintf(wind_title, 255, "CamView SDL - %s", fg->device);
    SDL_WM_SetCaption(wind_title, "CamView");

    while (quit == 0)
    {

        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = 1;
                continue;
            }
        }

        fg_grab_frame(fg, fr);
        frame = fg_frame_to_sdl_surface(fr);

        SDL_BlitSurface(frame, NULL, screen, NULL);
        SDL_Flip(screen);

        SDL_FreeSurface(frame);

    }

    fg_frame_release(fr);
    SDL_FreeSurface(screen);
    SDL_Quit();
    fg_close(fg);

    return 0;
}
















