#ifndef LIBFG2_CONVERT_H
#define LIBFG2_CONVERT_H

#include <stdint.h>

static inline int rgb24_to_rgb32(unsigned char *src, int src_len,
                                    unsigned char *dst)
{
    int num_pixels = src_len / 3;
    register int i;
    register uint32_t a,r,g,b;

    for (i=0; i < num_pixels; i++)
    {
        a = 0;
        r = *src++;
        g = *src++;
        b = *src++;
        // reversed
        *dst++ = b;
        *dst++ = g;
        *dst++ = r;
        *dst++ = a;
    }

    return 0;
}

#endif /* LIBFG2_CONVERT_H */
