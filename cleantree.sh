#!/bin/sh

rm -vrf \
    autom4te.cache/ \
    build-aux/ \
    doc/reference/ \
    examples/.deps/ \
    examples/.libs/ \
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
    examples/Makefile \
    examples/Makefile.in \
    examples/test \
    libfg2/*.o \
    libfg2/*.lo \
    libfg2/*.la \
    libfg2/*.pc \
    libfg2/Makefile \
    libfg2/Makefile.in \
    m4/libtool.m4 \
    m4/lt*.m4
