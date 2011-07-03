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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <jpeglib.h>

#ifdef HAVE_CONFIG_H
#include "libfg2-config.h"
#endif

#include "libfg2.h"

//--------------------------------------------------------------------------

fg_frame *fg_frame_new(fg_grabber *fg)
{
    fg_frame* fr = malloc( sizeof( fg_frame ) );
    fg_get_capture_size(fg, &(fr->size));
    fr->format = fg->format.fmt.pix.pixelformat;
    fr->rowstride = fg->format.fmt.pix.bytesperline;
    fr->length = fg->format.fmt.pix.sizeimage;
    fr->data = malloc( fr->length );

    if (fr->data == NULL)
    {
        fg_debug_error("frame_new(): ran out of memory allocating new frame");
        free(fr);
        return NULL;
    }

    return fr;
}

//--------------------------------------------------------------------------

void fg_frame_release(fg_frame *fr)
{
    fg_frame_free(fr);
}

//--------------------------------------------------------------------------

void fg_frame_free(fg_frame *fr)
{
    free(fr->data);
    free(fr);
}

//--------------------------------------------------------------------------

int fg_frame_copy(fg_frame *src, fg_frame *dst)
{
    free(dst->data);
    dst->size = src->size;
    dst->rowstride = src->rowstride;
    dst->format = src->format;
    dst->timestamp = src->timestamp;
    dst->length = src->length;
    dst->data = malloc(dst->length);
    assert(dst->data != NULL);
    memcpy(dst->data, src->data, dst->length);
    return 0;
}

//--------------------------------------------------------------------------

fg_frame *fg_frame_clone(fg_frame *fr)
{
    fg_frame *clone = malloc(sizeof(fg_frame));
    clone->data = NULL;
    fg_frame_copy(fr, clone);
    return clone;
}

//--------------------------------------------------------------------------

void fg_debug_frame(fg_frame *fr, FILE *fp)
{
    time_t when;
    struct tm *tm;
    char time_string[256];

    if (fp == NULL)
        fp = stdout;

    fprintf(fp, "fg_debug_frame():\n");
    fprintf(fp, "  size:        %d x %d pixels\n",
                fr->size.width, fr->size.height);
    fprintf(fp, "  rowstride:   %d bytes\n", fr->rowstride);
    fprintf(fp, "  data length: %d bytes\n", fr->length);

    switch (fr->format)
    {
        case FG_FORMAT_RGB24:
            fprintf(fp, "  format:      RGB24\n");
            break;
        case FG_FORMAT_BGR24:
            fprintf(fp, "  format:      BGR24\n");
            break;
        case FG_FORMAT_YUV420:
            fprintf(fp, "  format:      YUV420\n");
            break;
        case FG_FORMAT_YVU420:
            fprintf(fp, "  format:      YVU420\n");
            break;
    }

    when = fr->timestamp.tv_sec;
    tm = localtime(&when);
    strftime(time_string, 255, "%c", tm);
    fprintf(fp, "  timestamp:   %s [%06ld]\n",
        time_string, fr->timestamp.tv_usec);
}

//--------------------------------------------------------------------------

int fg_frame_get_size( fg_frame* fr )
{
    return fr->length;
}

//--------------------------------------------------------------------------
#if defined(WITH_JPEGLIB) && WITH_JPEGLIB == 1
int fg_frame_save( fg_frame* fr, const char* filename )
{

    if (fr->format != FG_FORMAT_RGB24)
    {
        fg_debug_error("fg_frame_save(): failed because format is not RGB24");
        return -1;
    }

    FILE *outfile;

    if ( (outfile = fopen(filename, "wb")) == NULL)
    {
        fg_debug_error("fg_frame_save(): unable to open output file");
        return -1;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    cinfo.image_width = fr->size.width;
    cinfo.image_height = fr->size.height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, 80, FALSE);

    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &(fr->data[cinfo.next_scanline*fr->rowstride]);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return 0;
}
#endif
//==========================================================================
