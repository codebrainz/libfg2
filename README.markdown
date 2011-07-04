libfg2 - Simple Linux Video Capture Library
===========================================

Introduction
------------

Libfg2 is a C library which provides access to video input devices such as
frame grabber cards, webcams, and TV tuner devices under kernels which support
Video4Linux2.  Using the excellent libv4l library, libfg2 provides access to
most devices, independent of which pixel formats they use.  Libfg2 also
provides functions to convert video frames to popular in-memory formats such
as those used by Gtk+, SDL, Imlib2, and OpenCV.

The library began with me hacking on the libfg library to support the
Video4Linux2 API.  I just started going through each function modifying each
one to work with V4L2, renaming a few things along the way, and Libfg2 is the
result.

Example
-------

Here's a minimal example of use:

```c
#include <libfg2.h>

int main(int argc, char *argv[])
{

    /* get name of video device or default */
    char *device = (argc>1) ? argv[1] : "/dev/video0";

    /* get name of snapshot file or default */
    char *snap_file = (argc>2) ? argv[2] : "snapshot.jpg";

    /* open and initialize the fg_grabber */
    fg_grabber *fg = fg_open(device);

    /* allocate a new fg_frame and fill it with data */
    fg_frame *fr = fg_grab(fg);

    /* save the fg_frame as a JPEG */
    fg_frame_save(fr, snap_file);

    /* free memory for fg_frame */
    fg_frame_release(fr);

    /* free memory for fg_grabber and close device */
    fg_close(fg);

    return 0;
}
```

You can compile the example using:

    gcc `pkg-config --cflags --libs libfg2` -o example example.c

Building and Installing
-----------------------

To checkout, build and install libfg2 you'll need to do the following:

    $ git clone git://github.com/codebrainz/libfg2.git
    $ cd libfg2
    $ ./autogen.sh
    $ ./configure [options] # use --help to see options
    $ make
    $ make install # possibly as root

Dependencies
------------

Libfg2 supports compiling with different dependencies, the defaults and
recommended ones being:

* [LibV4L](http://people.atrpms.net/~hdegoede) - For better device support
* [JPEG Library](http://ijg.org) - For saving frames to file

Non-default dependencies used for converting to other formats include:

* [GdkPixbuf](http://developer.gnome.org/gdk-pixbuf/unstable/rn01.html)
* [Imlib2](http://docs.enlightenment.org/api/imlib2/html)
* [OpenCV](http://opencv.willowgarage.com/wiki)
* [LibSDL](http://www.libsdl.org)

For generating language bindings in Python and Vala, respectively:

* [Python 2.6+](http://www.python.org)
* [Vala 0.10+](http://live.gnome.org/Vala)

Additionally, the GTK+ widget named GtkCamera, depends on:

* [GTK+ 2.16+](http://www.gtk.org)

None of the above dependencies above are required, the only absolute
requirement is support for the Video4Linux 2 API.  See ./configure --help
for more information on compiling the library.

Using Ubuntu, all of the dependencies can be installed using the following
command (only tested on Ubuntu 10.10):

    $ sudo apt-get install \
        libv4l-dev \
        libjpeg-dev \
        libgdk-pixbuf2.0-dev \
        libimlib2-dev \
        libcv-dev \
        libhighgui-dev \
        libsdl1.2-dev \
        python-dev \
        libvala-0.10-dev \
        libgtk2.0-dev

Other distributions should have equivalent packages available.

Documentation
-------------

To generate API documentation in HTML, LaTeX, and Manpage formats:

    $ cd doc
    $ make

To generate API documentation in PDF format, use above commands then:

    $ cd reference/latex
    $ make pdf

To generate the documentation, you will need
[Doxygen](http://www.stack.nl/~dimitri/doxygen).  Eventually the
documentation generation will be integrated into the Autotools build system
and available online.

License
-------

Libfg2 is licensed under the
[GNU Lesser General Public License](http://www.gnu.org/copyleft/lesser.html),
see the
[COPYING file](https://github.com/codebrainz/libfg2/blob/master/COPYING).
