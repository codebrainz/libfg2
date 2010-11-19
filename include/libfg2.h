/*! \file libfg2.h
    \mainpage 	libfg2
    \version	0.01
    \author	    Matthew Brush <mbrush@leftclick.ca>
    \date	    Oct 28, 2010
    \brief      Frame Grabber interface for Linux
*/
//==========================================================================
//
//  libfg2 - Frame Grabber interface for Linux
//  
//--------------------------------------------------------------------------
//  This library is based heavily on libfg, but with many (all?) parts 
//  re-written to support Video4Linux2 and some different functionality.
//
//  libfg - Frame Grabber interface for Linux
//    http://antonym.org/libfg/
//    Copyright (c) 2002 Gavin Baker
//
//--------------------------------------------------------------------------
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

#ifndef H_INCLUDED_LIBFG
#define H_INCLUDED_LIBFG

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#include <sys/time.h>
#include <linux/videodev2.h>
#include <libv4l2.h>

///
/// Standard/default device for fg_open().
///
#define FG_DEFAULT_DEVICE       "/dev/video0"

///
/// Normal/default capture size.
///
#define FG_DEFAULT_WIDTH        640
#define FG_DEFAULT_HEIGHT       480

///
/// Default input sources.
///
#define FG_SOURCE_TV            0
#define FG_SOURCE_COMPOSITE     1
#define FG_SOURCE_SVIDEO        2

///
/// Arbitrary maximum number of inputs/tuners.
///
#define FG_MAX_INPUTS           256
#define FG_MAX_TUNERS           256

///
/// Type of video inputs on a frame grabber device.
///
#define FG_INPUT_TYPE_TUNER     V4L2_INPUT_TYPE_TUNER
#define FG_INPUT_TYPE_CAMERA    V4L2_INPUT_TYPE_CAMERA

///
/// Supported pixel formats, as supported by libv4l for destination buffers.
///
#define FG_FORMAT_RGB24         V4L2_PIX_FMT_RGB24
#define FG_FORMAT_BGR24         V4L2_PIX_FMT_BGR24
#define FG_FORMAT_YUV420        V4L2_PIX_FMT_YUV420
#define FG_FORMAT_YVU420        V4L2_PIX_FMT_YVU420
#define FG_FORMAT_DEFAULT       FG_FORMAT_RGB24

///
/// Number of seconds to wait for a frame to become ready to ready.
///
#define FG_READ_TIMEOUT         2

///
/// Control ID's for use with fg_set_control()/fg_get_control() functions.
///
#define FG_CONTROL_BRIGHTNESS               V4L2_CID_BRIGHTNESS
#define FG_CONTROL_CONTRAST                 V4L2_CID_CONTRAST
#define FG_CONTROL_SATURATION               V4L2_CID_SATURATION
#define FG_CONTROL_HUE                      V4L2_CID_HUE
#define FG_CONTROL_AUTO_WHITE_BALANCE       V4L2_CID_AUTO_WHITE_BALANCE
#define FG_CONTROL_DO_WHITE_BALANCE         V4L2_CID_DO_WHITE_BALANCE
#define FG_CONTROL_RED_BALANCE              V4L2_CID_RED_BALANCE
#define FG_CONTROL_BLUE_BALANCE             V4L2_CID_BLUE_BALANCE
#define FG_CONTROL_GAMMA                    V4L2_CID_GAMMA
#define FG_CONTROL_EXPOSURE                 V4L2_CID_EXPOSURE
#define FG_CONTROL_AUTOGAIN                 V4L2_CID_AUTOGAIN
#define FG_CONTROL_GAIN                     V4L2_CID_GAIN
#define FG_CONTROL_HFLIP                    V4L2_CID_HFLIP
#define FG_CONTROL_VFLIP                    V4L2_CID_VFLIP
#define FG_CONTROL_HUE_AUTO                 V4L2_CID_HUE_AUTO
#define FG_CONTROL_WHITE_BALANCE            V4L2_CID_WHITE_BALANCE_TEMPERATURE
#define FG_CONTROL_SHARPNESS                V4L2_CID_SHARPNESS
#define FG_CONTROL_BACKLIGHT_COMPENSATION   V4L2_CID_BACKLIGHT_COMPENSATION
#define FG_CONTROL_CHROMA_AGC               V4L2_CID_CHROMA_AGC
#define FG_CONTROL_COLOR_KILLER             V4L2_CID_COLOR_KILLER
#define FG_CONTROL_AUTOBRIGHTNESS           V4L2_CID_AUTOBRIGHTNESS
#define FG_CONTROL_BAND_STOP_FILTER         V4L2_CID_BAND_STOP_FILTER

///
/// Set the memory used by x to 0, as in a quick way to zero out x.
///
#define FG_CLEAR(x) memset (&(x), 0, sizeof (x))

///
/// Convert a frame interval fraction to a double.
///
#define FG_FRAME_INTERVAL(i) ((double)(r).numerator / (double)(r).denominator)

///
/// Convert a frame interval to a frame rate.
///
#define FG_FRAME_RATE(i) (1.0 / FG_FRAME_INTERVAL(i))

///
/// Get a control value based on a percentage.
///
#define FG_CONTROL_VALUE(percent) ( (int)( (percent * 65536) / 100.0 ) )

///
/// Get a percentage based on a control value.
///
#define FG_CONTROL_PERCENT(value) ( (int)( (100.0 * value) / 65536 ) )

///
/// Represents rectangular dimension.
///
typedef struct 
{
    int left;
    int top;
    int width;
    int height;
    
} fg_rect;

///
/// Represents the size of things.
///
typedef struct
{
    unsigned int width;
    unsigned int height;
    
} fg_size;

///
/// Represents a single RGB pixel.
///
typedef struct
{
    char    red;
    char    green;
    char    blue;
    
} fg_rgb;

typedef struct v4l2_capability  fg_caps;
typedef struct v4l2_input       fg_input;
typedef struct v4l2_tuner       fg_tuner;
typedef struct v4l2_cropcap     fg_crop;
typedef struct v4l2_format      fg_format;
typedef struct v4l2_queryctrl   fg_control;

///
/// This stores the raw frames read from the frame grabber.
///
typedef struct
{
    fg_size         size;           ///< Size in pixels
    int             rowstride;      ///< Number of bytes per line
    int             format;         ///< FG_FORMAT_* pixel format
    int             length;         ///< Size of data in bytes
    unsigned char   *data;          ///< Pointer to the image data
    struct timeval timestamp;       ///< Timestamp when frame was grabbed

} fg_frame;

///
/// This stores information associated with a frame grabber device.
///
typedef struct
{
    char                    *device;        ///< Device name, eg. "/dev/video0"
    int                     fd;             ///< File handle for open device
    struct v4l2_capability  caps;           ///< Device capabilities
    struct v4l2_input       *inputs;        ///< Input sources (eg. TV, SVideo)
    int                     num_inputs;     ///< Number of input sources
    int                     input;          ///< Currently selected input
    struct v4l2_tuner       *tuners;        ///< TV or Radio tuner
    int                     num_tuners;     ///< Number of tuners on device
    int                     tuner;          ///< Currently selected tuner
    struct v4l2_cropcap     cropcap;        ///< Capture window
    struct v4l2_format      format;         ///< Video format (size, etc)
    struct v4l2_queryctrl   *controls;      ///< Video controls (hue, etc)
    int                     num_controls;   ///< Number of controls

} fg_grabber;

/** @defgroup grabber Frame grabber-related functions
 * These pertain to the frame grabber.
 * @{
 */

//------------------------------------------------------------------------------
///
/// \fn void fg_debug(const char *fmt, ...)
/// \brief	Write debugging information
///
/// This function behaves like printf if DEBUG is defined, otherwise it 
/// writes to syslog with LOG_DEBUG mode.
///
/// \param  fmt     Format string to format varargs with.
/// \param  ...     The varargs to format with fmt.
///
void fg_debug(const char *fmt, ...);

//------------------------------------------------------------------------------
///
/// \brief  Write debugging errors
///
/// This function behaves like perror sort of, if DEBUG is defined, otherwise
/// it writes to syslog with LOG_ERR mode.
///
/// \param  fmt     Format string to format varargs with.
/// \param  ...     The varargs to format with fmt.
///
/// @todo   Fix this so it behaves more like perror, by appending the error
///         number and strerror() description.
///
void fg_debug_error(const char *fmt, ...);

//------------------------------------------------------------------------------
///
/// \brief  Write all kinds of debugging output to standard output.
///
/// This function just prints a bunch of relevant and useful debugging 
/// messages to standard output.
///
/// \param  fg      Framegrabber to dump info for.
///
void fg_dump_info( fg_grabber* fg );

//------------------------------------------------------------------------------
///
/// \brief  Open a new frame grabber device.
///
/// This function opens the device specified, initializes it, and sets some
/// defaults to allow capture from the device without any further settings.
/// The pointer returned must be closed with fg_close() to free any memory
/// which gets allocated in this function and to close the file descriptor.
///
/// \param  dev     Path to the Video4Linux2 character device (ex. /dev/video0)
///                 or the default device (FG_DEFAULT_DEVICE).
///
/// \return If the device can be successfully opened and initialized then a 
///         fg_grabber is returned fully configured.  In case of any errors
///         NULL is returned.
///
fg_grabber *fg_open(const char *dev);

//------------------------------------------------------------------------------
///
/// \brief  Close a previously opened frame grabber device.
///
/// This function closes the frame grabber device and frees any allocated
/// memory associated with it.  Use this function when you're done with the
/// frame grabber opened with fg_open().
///
/// \param  fg  Frame grabber device to close.
///
void fg_close(fg_grabber *fg);

///
/// \brief  Set the video input (source).
///
/// This function sets the input number on the frame grabber device to the
/// specified index.  The index specified must be between 0 and fg->num_inputs.
/// 
/// \param  fg      Frame grabber device to set input on.
/// \param  index   Input number to switch to.
///
/// \return If the input is switched successfully, 0 is returned.  If an error
///         occurred then -1 is returned.
///
int fg_set_input(fg_grabber* fg, int index);

//------------------------------------------------------------------------------
///
/// \brief  Get the current video input (source).
///
/// This function returns the currently selected input number on the frame
/// grabber device.
///
/// \param  fg  Frame grabber device to get selected input on.
///
/// \return If the currently selected input can be determined, it is returned,
///         otherwise -1 is returned.
///
int fg_get_input(fg_grabber *fg);

//------------------------------------------------------------------------------
///
/// \brief  Grab a new frame from the frame grabber.
///
/// This function allocates a new fg_frame and loads it with the image 
/// captured from the frame grabber device.  The frame returned must be
/// destroyed with the fg_frame_release() function afterwards.
///
/// \param  fg  Frame grabber device to capture image from.
///
/// \return If a new frame could be successfully allocated, initialized and
///         read from the frame grabber, a pointer to the frame is returned.
///         If an error occurred, NULL is returned.
///
fg_frame *fg_grab(fg_grabber* fg);

//------------------------------------------------------------------------------
///
/// \brief  Grab a frame from the frame grabber into an existing frame.
///
/// This function is similar to fg_grab() except that it does not automatically
/// allocate a new frame, a pointer to an existing frame must be provided.
///
/// \param  fg  Frame grabber device to capture image from.
/// \param  fr  Frame to store image data into.
///
/// \return If a frame could be read successfully, 0 is returned.  If an error
///         occurred, -1 is returned.
///
int fg_grab_frame(fg_grabber *fg, fg_frame *fr);

//------------------------------------------------------------------------------
/* todo */
/*int fg_set_source_norm( fg_grabber* fg, int norm );*/

//------------------------------------------------------------------------------
///
/// \brief  Get the number of inputs.
///
/// This function enumerates through all the available video inputs on a
/// frame grabber device and returns the total count.
///
/// \param  fg  Frame grabber device to count inputs on.
///
/// \return The number of inputs on the frame grabber are returned (>=0).
///
int fg_get_input_count(fg_grabber *fg);

//------------------------------------------------------------------------------
///
/// \brief  Get the index of the current input.
///
/// This function gets the index of the currently selected input on the frame
/// grabber device.
///
/// \param  fg  Frame grabber device to get input index on.
///
/// \return The currently selected/active input on the frame grabber or -1 in
///         case of an error.
///
int fg_get_input(fg_grabber *fg);

//------------------------------------------------------------------------------
///
/// \brief  Set the active/selected input.
///
/// This function sets the currently selected input to the index specifed.
///
/// \param  fg  Frame grabber device to set input index on.
///
/// \return The index specified is returned if the input was switched or -1 if
///         an error occurred.
///
int fg_set_input(fg_grabber* fg, int index);

//------------------------------------------------------------------------------
///
/// \brief  Get the name of an input.
///
/// This function gets the name of the video input.  This information is 
/// intended for the user, preferably the connector label on the device itself.
///
/// \param  fg      Frame grabber to get the input name on.
/// \param  index   The index number of the input to get the name of.
///
/// \return A pointer to a null-terminated ASCII character array or NULL if
///         an error occurred.
///
char *fg_get_input_name(fg_grabber *fg, int index);

//------------------------------------------------------------------------------
///
/// \brief  Get the type of the input.
///
/// This function gets the type of the input specified by index.  The input
/// types are one of FG_INPUT_TYPE_TUNER or FG_INPUT_TYPE_CAMERA.
///
/// \param  fg      The frame grabber to get the input type on.
/// \param  index   The input number to get the type of.
///
/// \return One of FG_INPUT_TYPE_TUNER or FG_INPUT_TYPE_TUNER on success, 
/// or -1 if an error occurred.
///
int fg_get_input_type( fg_grabber* fg, int index );

//------------------------------------------------------------------------------
///
/// \brief  Tune a tuner to a specific frequency.
///
/// This function sets the frequency of the default tuner on the current video
/// input to a specific frequency in MHz.
///
/// \param  fg      The frame grabber to get the tuner frequency on.
/// \param  freq    The frequency in MHz to set the tuner to.
///
/// \return On success, 0 is returned or if an error occurred -1 is returned.
///
/// @todo   Test this function and check scaling and such (copied from libfg).
///
int fg_set_channel(fg_grabber* fg, float freq);

//------------------------------------------------------------------------------
///
/// \brief  Get the frequency of a tuner.
/// 
/// This function gets the currently tuned frequency on a tuner on the current
/// video input in MHz.
/// 
/// \param  fg  The frame grabber with the tuner to get the frequency of.
///
/// \return On success, the current frequency is returned or -1 if an error 
///         occurred.
///
/// @todo   Test this function and check scaling and such (copied from libfg).
///
float fg_get_channel( fg_grabber* fg );

//------------------------------------------------------------------------------
///
/// \brief  Set the selected video format.
///
/// This function sets the video format of the currently active input.  The
/// formats are of a select few; FG_FORMAT_RGB24, FG_FORMAT_BGR24,
/// FG_FORMAT_YUV420, or FG_FORMAT_YVU240.  The libv4l library is used to
/// provide transparent conversion from the actual video formats supported by
/// the frame grabber to one of these.  Many source formats are supported.  If
/// you intend to use the fg_frame_save() function, then choose FG_FORMAT_RGB24.
///
/// \param  fg      The frame grabber to set the format on.
/// \param  fmt     The video format to set.
/// 
/// \return On success, 0 is returned or -1 is returned if an error occurred.
///
int fg_set_format(fg_grabber *fg, int fmt);

//------------------------------------------------------------------------------
///
/// \brief  Get the selected video format.
///
/// This function gets the currently selected video input format.  The format
/// is one of FG_FORMAT_RGB24, FG_FORMAT_BGR24, FG_FORMAT_YUV420, or 
/// FG_FORMAT_YVU420.
///
/// \param  fg  The frame grabber to set the format on.
///
/// \return On success one of FG_FORMAT_* is returned or -1 if an error 
///         occurred.
///
int fg_get_format(fg_grabber *fg);

//------------------------------------------------------------------------------
///
///\brief   Set the size of the video frames.
///
/// This function sets the size of the video frames captured from the frame
/// grabber.  By default the size will be FG_DEFAULT_WIDTH and 
/// FG_DEFAULT_HEIGHT.
///
/// \param  fg      The frame grabber to set the capture size on.
/// \param  size    The size of the frames grabbed.
///
/// \return On success, 0 is returned or -1 is returned if an error occurred.
///
int fg_set_capture_size(fg_grabber *fg, fg_size *size);

//------------------------------------------------------------------------------
///
/// \brief  Get the size of the video frames.
///
/// This function returns the size that the grabbed frames will be.
///
/// \param  fg      The frame grabber to get the size on.
/// \param  size    Pointer to an fg_size where the current width and height
///                 will be stored.
///
/// \return On success 0, on error -1.
///
int fg_get_capture_size(fg_grabber *fg, fg_size *size);

//------------------------------------------------------------------------------
///
/// \brief  Set the cropping window for the video frames.
///
/// This function sets the cropping fg_rect which will crop out a region of the
/// full capture frames.  This may not be supported at all on some devices.
///
/// \param  fg      The frame grabber to set capture window on.
/// \param  rect    The dimensions of the capture window.
///
/// \return On success 0, on error -1.
///
int fg_set_capture_window(fg_grabber *fg, fg_rect *rect);

//------------------------------------------------------------------------------
///
/// \brief  Get the current capture window for the video frames.
///
/// This function gets the cropping fg_rect which is currently cropped out of
/// a region of the full capture frames.  This may not be supported on some 
/// devices.
///
/// \param  fg      The frame grabber to get the capture window on.
/// \param  rect    The cropping rectangle to crop out of full frame.
///
/// \return On success 0, on error -1.
///
int fg_get_capture_window(fg_grabber *fg, fg_rect *rect);


int fg_default_controls(fg_grabber *fg);
int fg_set_control(fg_grabber *fg, int cid, int value);
int fg_get_control(fg_grabber *fg, int control_id);
char *fg_get_control_name(fg_grabber *fg, int control_id);

int fg_set_brightness( fg_grabber* fg, int br );
int fg_set_hue( fg_grabber* fg, int hu );
int fg_set_contrast( fg_grabber* fg, int ct );
int fg_set_saturation(fg_grabber *fg, int sat);

/*
int fg_set_colour( fg_grabber* fg, int co );
int fg_set_whiteness( fg_grabber* fg, int wh );
*/
/** @} */ //end of grabber group
//------------------------------------------------------------------------------
/** @defgroup frame Frame-related functions
 * These functions pertain to individual frames.
 * @{
 */

///
/// \brief  Allocate memory for a new frame.
///
/// This function allocates memory for a new frame based on the frame grabber's
/// current settings (width, height, number of bytes, etc.).  A frame created
/// with this function can be passed to any of the fg_frame_* functions and 
/// fg_grab_frame().  To free the memory used by the fg_frame, you must call
/// fg_frame_release() with a pointer to it.  Unless you're using some sort of
/// buffer array of frames, it's probably best to use a single fg_frame for
/// all operations so that malloc() and free() don't get called as often.
///
/// \param  fg  The frame grabber who's settings to use to initialize the frame.
///
/// \return A pointer to a new fg_frame with properties set and memory allocated
///         for the frame's buffer.
///
fg_frame *fg_frame_new(fg_grabber *fg);

//------------------------------------------------------------------------------
/// 
/// \brief  Free memory used by an existing frame.
///
/// This function frees/releases memory used by a frame allocated with
/// fg_frame_new().
///
/// \param  fr  The frame to release memory from.
///
void fg_frame_release(fg_frame* fr);
void fg_frame_free(fg_frame *fr);
void *fg_frame_get_data(fg_frame* fr);
int fg_frame_get_size(fg_frame* fr);
int fg_frame_get_width(fg_frame* fr);
int fg_frame_get_height(fg_frame* fr);
void fg_debug_frame(fg_frame *fr, FILE *fp);
int fg_frame_copy(fg_frame *src, fg_frame *dst);
fg_frame *fg_frame_clone(fg_frame *fr);

#ifdef WITH_JPEGLIB
/// \brief  Save a frame as a JPEG file.
///
/// This function uses jpeglib to save the image in an fg_frame to a JPEG
/// encoded/compressed file.  This is convenient if for example for taking
/// snapshots or time-lapse.  This function is only available when the
/// WITH_JPEGLIB is defined.
///
/// \param  The fg_frame whos image data to save as a JPEG.
/// \param  The filename to save the JPEG file as.
/// 
/// \return 0 on success, -1 on failure.
///
/// \see    The functions in convert.c named fg_frame_to_*() can also be used
///         to get data into other libraries and be used for various purposes,
///         include writing to other types of files or drawing on the screen.
///
int fg_frame_save(fg_frame* fr, const char* filename);
#endif
/** @} */ //end of frame group
//------------------------------------------------------------------------------
/** @defgroup frame Frame-related functions
 * These functions pertain to individual frames.
 * @{
 */
 
#ifdef WITH_SDL
#include <SDL/SDL.h>
SDL_Surface *fg_frame_to_sdl_surface(fg_frame *fr);
#endif

#ifdef WITH_GDKPIXBUF
#include <gdk-pixbuf/gdk-pixbuf.h>
GdkPixbuf *fg_frame_to_gdk_pixbuf(fg_frame *fr);
#endif

#ifdef WITH_IMLIB2
#include <Imlib2.h>
static inline int rgb24_to_rgb32(unsigned char *src, int src_len, 
                                    unsigned char *dst);
#endif

#ifdef WITH_OPENCV
#include <cv.h>
#include <highgui.h>
IplImage *fg_frame_to_ipl_image(fg_frame *fr);
#endif

 /** @} */ // end of convert section
 
 
#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* H_INCLUDED_LIBFG */




























