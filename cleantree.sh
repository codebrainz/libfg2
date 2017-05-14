#!/bin/sh

rm -vrf \
    autom4te.cache/ \
    build-aux/ \
    examples/.deps/ \
    examples/.libs/ \
    gtkcamera/.deps/ \
    gtkcamera/.libs/ \
    libfg2/.deps/ \
    libfg2/.libs/

rm -vf \
    aclocal.m4 \
    config.* \
    configure \
    libtool \
    Makefile \
    Makefile.in \
    stamp-h1 \
    examples/*.o \
    examples/camsnap-vala \
    examples/camsnap-vala.c \
    examples/*.stamp \
    examples/camview-gtk \
    examples/camview-sdl \
    examples/Makefile \
    examples/Makefile.in \
    examples/test \
    gtkcamera/*.o \
    gtkcamera/*.lo \
    gtkcamera/*.la \
    gtkcamera/*.pc \
    gtkcamera/Makefile \
    gtkcamera/Makefile.in \
    libfg2/*.o \
    libfg2/*.lo \
    libfg2/*.la \
    libfg2/*.pc \
    libfg2/Makefile \
    libfg2/Makefile.in \
    m4/libtool.m4 \
    m4/lt*.m4 \
    vapi/Makefile \
    vapi/Makefile.in
    
