libfg2 - Simple Linux Video Capture Library
===========================================

Introduction
------------

Libfg2 is a C library which provides access to video input devices such 
as frame grabber cards, webcams, and TV tuner devices under kernels 
which support Video4Linux2.  Using the excellent libv4l library, libfg2 
provides access to most devices, independent of which pixel formats 
they use.

The library began with me hacking on the libfg library to support the 
Video4Linux2 API.  I just started going through each function modifying 
each one to work with V4L2, renaming a few things along the way, and 
Libfg2 is the result.

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

Libfg2 has two dependencies, one required and one option.

### Required

* [LibV4L](http://people.atrpms.net/~hdegoede)

### Optional

Only required for saving frames to file.

* [JPEG Library](http://ijg.org)

See `./configure --help` for more information on configuring the library.

Using Ubuntu, both dependencies can be installed using the following 
command (only tested on Ubuntu 16.04):

    $ sudo apt-get install libv4l-dev libjpeg-dev

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
documentation generation will be integrated into the Autotools build 
system and available online.

License
-------

Libfg2 is licensed under the
[GNU Lesser General Public License](https://www.gnu.org/licenses/old-licenses/lgpl-2.1-standalone.html),
see the
[COPYING.md file](https://github.com/codebrainz/libfg2/blob/master/COPYING).
