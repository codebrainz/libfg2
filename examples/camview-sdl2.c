#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libfg2/libfg2-sdl.h>
#include <string.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
    char wind_title[256] = {0};
    int quit = 0;

    SDL_Surface *frame;
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;

    fg_grabber *fg;
    fg_frame *fr;

    if (argc == 1)
        fg = fg_open(FG_DEFAULT_DEVICE);
    else
        fg = fg_open(argv[1]);

    fr = fg_frame_new(fg);

    SDL_Init(SDL_INIT_VIDEO);

    snprintf(wind_title, 255, "CamView SDL2 - %s", fg->device);
    
    win = SDL_CreateWindow(wind_title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        fr->size.width, fr->size.height, 
        SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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

        texture = SDL_CreateTextureFromSurface(renderer, frame);
        SDL_FreeSurface(frame);
    
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(texture);
    }

    fg_frame_release(fr);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    fg_close(fg);

    return 0;
}
