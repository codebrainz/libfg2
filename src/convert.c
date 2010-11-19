//==========================================================================
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
//  or obtain a copy from the GNU website at http://www.gnu.org/
//
//==========================================================================

/* 
 * none of this was really tested at all yet!
 * need colorspace conversion functions from testoverlay.c and/or elsewhere
 */

#include <stdlib.h>
#include <assert.h>

#include "libfg2.h"

//------------------------------------------------------------------------------
#ifdef WITH_IMLIB2 || WITH_OPENCV
#include <Imlib2.h>
static inline int rgb24_to_rgb32(unsigned char *src, int src_len, 
                                    unsigned char *dst)
{
    int num_pixels = src_len / 3;
    register int i;
    register DATA32 a,r,g,b;
    
    for (i=0; i < num_pixels; i++)
    {
        a = 0;
        r = *src++;
        g = *src++;
        b = *src++;
        // reverse for some reason
        *dst++ = b;
        *dst++ = g;
        *dst++ = r;
        *dst++ = a;
    }
    
    return 0;
}
#endif
//------------------------------------------------------------------------------
#ifdef WITH_SDL
#include <SDL/SDL.h>
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
#endif
//------------------------------------------------------------------------------
#ifdef WITH_GDKPIXBUF
#include <gdk-pixbuf/gdk-pixbuf.h>
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
#endif
//------------------------------------------------------------------------------
#ifdef WITH_IMLIB2
Imlib_Image *fg_frame_to_imlib2_image(fg_frame *fr)
{
    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_to_imlib2_image(): wrong frame format");
        return NULL;
    }
    
    int num_pixels;
    int dst_length;
    unsigned char *data;
    Imlib_Image *image;
    
    num_pixels = fr->length / 3;
    dst_length = num_pixels * sizeof(DATA32) * 4;
    
    data = malloc(dst_length);
    assert(data != NULL);

    rgb24_to_rgb32(fr->data, fr->length, data);
        
    *image = imlib_create_image_using_data(fr->size.width, fr->size.height, 
            (DATA32 *)data);

    assert(*image);
    
    return image;    
}
#endif
//------------------------------------------------------------------------------
#ifdef WITH_OPENCV
#include <cv.h>
#include <highgui.h>
IplImage *fg_frame_to_ipl_image(fg_frame *fr)
{

    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_to_ipl_image(): wrong frame format");
        return NULL;
    }

    unsigned char *img32;
    IplImage *image;
    
    img32 = iplMalloc(fr->width * fr->height * 4);
    
    rgb24_to_rgb32(fr->data, fr->length, img32);
    
    image = cvCreateImage(cvSize(fr->size.width, fr->size.height), 
                IPL_DEPTH32S, 4);
    
    cvSetImageData(img32, fr->data, fr->rowstride);
    
    return image;
}
#endif





































