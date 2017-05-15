/*! \file libfg2.h
    \mainpage libfg2
    \version  0.01
    \author   Matthew Brush <mbrush@leftclick.ca>
    \date     May 14, 2017
    \brief    Frame Grabber interface for Linux
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

#ifndef LIBFG2_H
#define LIBFG2_H

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
    int left;   ///< Left/x position in pixels
    int top;    ///< Top/y position in pixels
    int width;  ///< Width in pixels
    int height; ///< Height in pixels

} fg_rect;

///
/// Represents the size of things.
///
typedef struct
{
    unsigned int width;     ///< Width in pixels
    unsigned int height;    ///< Height in pixels

} fg_size;

///
/// Represents a single RGB pixel.
///
typedef struct
{
    char    red;    ///< Red pixel value
    char    green;  ///< Green pixel value
    char    blue;   ///< Blue pixel value

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
    fg_caps                 caps;           ///< Device capabilities
    fg_input                *inputs;        ///< Input sources (eg. TV, SVideo)
    int                     num_inputs;     ///< Number of input sources
    int                     input;          ///< Currently selected input
    fg_tuner                *tuners;        ///< TV or Radio tuner
    int                     num_tuners;     ///< Number of tuners on device
    int                     tuner;          ///< Currently selected tuner
    fg_crop                 cropcap;        ///< Capture window
    fg_format               format;         ///< Video format (size, etc)
    fg_control              *controls;      ///< Video controls (hue, etc)
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
/// \return One of FG_INPUT_TYPE_CAMERA or FG_INPUT_TYPE_TUNER on success,
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
int fg_set_capture_size(fg_grabber *fg, fg_size size);

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
fg_size fg_get_capture_size(fg_grabber *fg);

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
int fg_set_capture_window(fg_grabber *fg, fg_rect rect);

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
fg_rect fg_get_capture_window(fg_grabber *fg);

/** @} */ //end of grabber group

//==============================================================================

/** @defgroup control Control-related functions
 * These functions pertain to invidual controls
 * @{
 */

/* Return codes for control-related functions. */
#define FG_CONTROL_OK               0   ///< Control is read/write
#define FG_CONTROL_INVALID          -1  ///< Control is not supported
#define FG_CONTROL_READ_ONLY        -2  ///< Control is read-only
#define FG_CONTROL_OUT_OF_RANGE     -3  ///< Control value is out of range

///
/// Enumerations for control IDs.
///
typedef enum {
    /// Picture brightness, or more precisely, the black level.
    FG_CONTROL_ID_BRIGHTNESS             = V4L2_CID_BRIGHTNESS,
    /// Picture contrast or luma gain.
    FG_CONTROL_ID_CONTRAST               = V4L2_CID_CONTRAST,
    /// Picture color saturation or chroma gain.
    FG_CONTROL_ID_SATURATION             = V4L2_CID_SATURATION,
    /// Hue or color balance.
    FG_CONTROL_ID_HUE                    = V4L2_CID_HUE,
    /// Overall audio volume. Note some drivers also provide an OSS or ALSA mixer interface.
    FG_CONTROL_ID_AUDIO_VOLUME           = V4L2_CID_AUDIO_VOLUME,
    /// Audio stereo balance. Minimum corresponds to all the way left, maximum to right.
    FG_CONTROL_ID_AUDIO_BALANCE          = V4L2_CID_AUDIO_BALANCE,
    /// Audio bass adjustment.
    FG_CONTROL_ID_AUDIO_BASS             = V4L2_CID_AUDIO_BASS,
    /// Audio treble adjustment.
    FG_CONTROL_ID_AUDIO_TREBLE           = V4L2_CID_AUDIO_TREBLE,
    /// Mute audio, i. e. set the volume to zero, however without affecting #FG_CONTROL_ID_AUDIO_VOLUME. Like ALSA drivers, V4L2 drivers must mute at load time to avoid excessive noise. Actually the entire device should be reset to a low power consumption state.
    FG_CONTROL_ID_AUDIO_MUTE             = V4L2_CID_AUDIO_MUTE,
    /// Loudness mode (bass boost).
    FG_CONTROL_ID_AUDIO_LOUDNESS         = V4L2_CID_AUDIO_LOUDNESS,
    /// Automatic white balance (cameras).
    FG_CONTROL_ID_AUTO_WHITE_BALANCE     = V4L2_CID_AUTO_WHITE_BALANCE,
    /// This is an action control. When set (the value is ignored), the device will do a white balance and then hold the current setting. Contrast this with the boolean #FG_CONTROL_ID_AUTO_WHITE_BALANCE, which, when activated, keeps adjusting the white balance.
    FG_CONTROL_ID_DO_WHITE_BALANCE       = V4L2_CID_DO_WHITE_BALANCE,
    /// Red chroma balance.
    FG_CONTROL_ID_RED_BALANCE            = V4L2_CID_RED_BALANCE,
    /// Blue chroma balance.
    FG_CONTROL_ID_BLUE_BALANCE           = V4L2_CID_BLUE_BALANCE,
    /// Gamma adjust.
    FG_CONTROL_ID_GAMMA                  = V4L2_CID_GAMMA,
    /// Exposure (cameras).
    FG_CONTROL_ID_EXPOSURE               = V4L2_CID_EXPOSURE,
    /// Automatic gain/exposure control.
    FG_CONTROL_ID_AUTO_GAIN              = V4L2_CID_AUTOGAIN,
    /// Gain control.
    FG_CONTROL_ID_GAIN                   = V4L2_CID_GAIN,
    /// Mirror the picture horizontally.
    FG_CONTROL_ID_HFLIP                  = V4L2_CID_HFLIP,
    /// Mirror the picture vertically.
    FG_CONTROL_ID_VFLIP                  = V4L2_CID_VFLIP,
    /// Enables a power line frequency filter to avoid flicker. Possible values are: #FG_CONTROL_ID_POWER_LINE_FREQUENCY_DISABLED (0), #FG_CONTROL_ID_POWER_LINE_FREQUENCY_50HZ (1) and #FG_CONTROL_ID_POWER_LINE_FREQUENCY_60HZ (2).
    FG_CONTROL_ID_POWER_LINE_FREQUENCY   = V4L2_CID_POWER_LINE_FREQUENCY,
    /// Enables automatic hue control by the device. The effect of setting #FG_CONTROL_ID_HUE while automatic hue control is enabled is undefined, drivers should ignore such request.
    FG_CONTROL_ID_AUTO_HUE               = V4L2_CID_HUE_AUTO,
    /// This control specifies the white balance settings as a color temperature in Kelvin. A driver should have a minimum of 2800 (incandescent) to 6500 (daylight). For more information about color temperature see Wikipedia.
    FG_CONTROL_ID_WHITE_BALANCE_TEMP     = V4L2_CID_WHITE_BALANCE_TEMPERATURE,
    /// Adjusts the sharpness filters in a camera. The minimum value disables the filters, higher values give a sharper picture.
    FG_CONTROL_ID_SHARPNESS              = V4L2_CID_SHARPNESS,
    /// Adjusts the backlight compensation in a camera. The minimum value disables backlight compensation.
    FG_CONTROL_ID_BACKLIGHT_COMPENSATION = V4L2_CID_BACKLIGHT_COMPENSATION,
    FG_CONTROL_ID_CHROMA_AGC             = V4L2_CID_CHROMA_AGC,
    FG_CONTROL_ID_COLOR_KILLER           = V4L2_CID_COLOR_KILLER,
    FG_CONTROL_ID_COLOR_EFFECTS          = V4L2_CID_COLORFX,
    FG_CONTROL_ID_AUTO_BRIGHTNESS        = V4L2_CID_AUTOBRIGHTNESS,
    FG_CONTROL_ID_BAND_STOP_FILTER       = V4L2_CID_BAND_STOP_FILTER,
    FG_CONTROL_ID_ROTATE                 = V4L2_CID_ROTATE,
    FG_CONTROL_ID_BACKGROUND_COLOR       = V4L2_CID_BG_COLOR,
} fg_control_id;

typedef enum {
    FG_POWER_LINE_FREQUENCY_DISABLED    = 0,
    FG_POWER_LINE_FREQUENCY_50HZ        = 1,
    FG_POWER_LINE_FREQUENCY_60HZ        = 2,
} fg_power_line_freq;

typedef enum {
    FG_COLOR_EFFECTS_NONE               = 0,
    FG_COLOR_EFFECTS_BW                 = 1,
    FG_COLOR_EFFECTS_SEPIA              = 2,
    FG_COLOR_EFFECTS_NEGATIVE           = 3,
    FG_COLOR_EFFECTS_EMBOSS             = 4,
    FG_COLOR_EFFECTS_SKETCH             = 5,
    FG_COLOR_EFFECTS_SKY_BLUE           = 6,
    FG_COLOR_EFFECTS_GRASS_GREEN        = 7,
    FG_COLOR_EFFECTS_SKIN_WHITEN        = 8,
    FG_COLOR_EFFECTS_VIVID              = 9,
} fg_color_effects;

///
/// \brief  Check to see if control is valid for the frame grabber.
///
/// This function can be used to check whether or not a specific control can
/// be set or not on the frame grabber.
///
/// \param  fg          Frame grabber to check control on.
/// \param  control_id  The ID of the control to check.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read, and
///         FG_CONTROL_OK if the control can be read or set.
///
int fg_check_control(fg_grabber *fg, fg_control_id control_id);

///
/// \brief  Set control to value.
///
/// This function set the specified control to the specified value.  The value
/// should be between 0 and 65535, and will be scaled to value that the device
/// actually uses.
///
/// \param  fg          Frame grabber to set control value on.
/// \param  control_id  ID of control to set.
/// \param  value       Value to set control to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read, and
///         FG_CONTROL_OK if the control was set.
///
int fg_set_control(fg_grabber *fg, fg_control_id control_id, int value);

///
/// \brief  Get control value.
///
/// This function gets the value of the specified control.  The value will be
/// between 0 and 65535, and will be scaled to this range from the range that
/// the device actually uses.
///
/// \param  fg          Frame grabber to get control value on.
/// \param  control_id  ID of the control to get.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         or the value otherwise.
///
int fg_get_control(fg_grabber *fg, fg_control_id control_id);

///
/// \brief  Set controls to default values.
///
/// This function resets all supported controls to their default values.
///
/// \param  fg      Frame grabber to set control values to defaults on.
///
/// \return 0 on success, -1 on failure.
///
int fg_default_controls(fg_grabber *fg);

///
/// \brief Get value of audio balance.
///
/// Audio stereo balance. Minimum corresponds to all the way left: maximum to right.
///
/// \param fg     Frame grabber to set audio balance on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_audio_balance(fg_grabber *fg);

///
/// \brief Set value of audio balance.
///
/// Audio stereo balance. Minimum corresponds to all the way left: maximum to right.
///
/// \param  fg      Frame grabber to set audio balance on.
/// \param  value   Value to set audio balance to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_audio_balance(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of audio bass.
///
/// Audio bass adjustment.
///
/// \param fg     Frame grabber to set audio bass on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_audio_bass(fg_grabber *fg);

///
/// \brief Set value of audio bass.
///
/// Audio bass adjustment.
///
/// \param  fg      Frame grabber to set audio bass on.
/// \param  value   Value to set audio bass to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_audio_bass(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of audio loudness.
///
/// Loudness mode (bass boost).
///
/// \param fg     Frame grabber to set audio loudness on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_audio_loudness(fg_grabber *fg);

///
/// \brief Set value of audio loudness.
///
/// Loudness mode (bass boost).
///
/// \param  fg      Frame grabber to set audio loudness on.
/// \param  value   Value to set audio loudness to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_audio_loudness(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of audio mute.
///
/// Mute audio: i. e. set the volume to zero: however without affecting FG_AUDIO_VOLUME. Like ALSA drivers: V4L2 drivers must mute at load time to avoid excessive noise. Actually the entire device should be reset to a low power consumption state.
///
/// \param fg     Frame grabber to set audio mute on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_audio_mute(fg_grabber *fg);

///
/// \brief Set value of audio mute.
///
/// Mute audio: i. e. set the volume to zero: however without affecting FG_AUDIO_VOLUME. Like ALSA drivers: V4L2 drivers must mute at load time to avoid excessive noise. Actually the entire device should be reset to a low power consumption state.
///
/// \param  fg      Frame grabber to set audio mute on.
/// \param  value   Value to set audio mute to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_audio_mute(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of audio treble.
///
/// Audio treble adjustment.
///
/// \param fg     Frame grabber to set audio treble on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_audio_treble(fg_grabber *fg);

///
/// \brief Set value of audio treble.
///
/// Audio treble adjustment.
///
/// \param  fg      Frame grabber to set audio treble on.
/// \param  value   Value to set audio treble to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_audio_treble(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of audio volume.
///
/// Overall audio volume. Note some drivers also provide an OSS or ALSA mixer interface.
///
/// \param fg     Frame grabber to set audio volume on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_audio_volume(fg_grabber *fg);

///
/// \brief Set value of audio volume.
///
/// Overall audio volume. Note some drivers also provide an OSS or ALSA mixer interface.
///
/// \param  fg      Frame grabber to set audio volume on.
/// \param  value   Value to set audio volume to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_audio_volume(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of auto brightness.
///
///
///
/// \param fg     Frame grabber to set auto brightness on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_auto_brightness(fg_grabber *fg);

///
/// \brief Set value of auto brightness.
///
///
///
/// \param  fg      Frame grabber to set auto brightness on.
/// \param  value   Value to set auto brightness to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_auto_brightness(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of auto gain.
///
/// Automatic gain/exposure control.
///
/// \param fg     Frame grabber to set auto gain on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_auto_gain(fg_grabber *fg);

///
/// \brief Set value of auto gain.
///
/// Automatic gain/exposure control.
///
/// \param  fg      Frame grabber to set auto gain on.
/// \param  value   Value to set auto gain to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_auto_gain(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of auto hue.
///
/// Enables automatic hue control by the device. The effect of setting FG_HUE while automatic hue control is enabled is undefined: drivers should ignore such request.
///
/// \param fg     Frame grabber to set auto hue on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_auto_hue(fg_grabber *fg);

///
/// \brief Set value of auto hue.
///
/// Enables automatic hue control by the device. The effect of setting FG_HUE while automatic hue control is enabled is undefined: drivers should ignore such request.
///
/// \param  fg      Frame grabber to set auto hue on.
/// \param  value   Value to set auto hue to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_auto_hue(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of auto white balance.
///
/// Automatic white balance (cameras).
///
/// \param fg     Frame grabber to set auto white balance on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_auto_white_balance(fg_grabber *fg);

///
/// \brief Set value of auto white balance.
///
/// Automatic white balance (cameras).
///
/// \param  fg      Frame grabber to set auto white balance on.
/// \param  value   Value to set auto white balance to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_auto_white_balance(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of background color.
///
///
///
/// \param fg     Frame grabber to set background color on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_background_color(fg_grabber *fg);

///
/// \brief Set value of background color.
///
///
///
/// \param  fg      Frame grabber to set background color on.
/// \param  value   Value to set background color to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_background_color(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of backlight compensation.
///
/// Adjusts the backlight compensation in a camera. The minimum value disables backlight compensation.
///
/// \param fg     Frame grabber to set backlight compensation on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_backlight_compensation(fg_grabber *fg);

///
/// \brief Set value of backlight compensation.
///
/// Adjusts the backlight compensation in a camera. The minimum value disables backlight compensation.
///
/// \param  fg      Frame grabber to set backlight compensation on.
/// \param  value   Value to set backlight compensation to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_backlight_compensation(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of band stop filter.
///
///
///
/// \param fg     Frame grabber to set band stop filter on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_band_stop_filter(fg_grabber *fg);

///
/// \brief Set value of band stop filter.
///
///
///
/// \param  fg      Frame grabber to set band stop filter on.
/// \param  value   Value to set band stop filter to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_band_stop_filter(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of blue balance.
///
/// Blue chroma balance.
///
/// \param fg     Frame grabber to set blue balance on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_blue_balance(fg_grabber *fg);

///
/// \brief Set value of blue balance.
///
/// Blue chroma balance.
///
/// \param  fg      Frame grabber to set blue balance on.
/// \param  value   Value to set blue balance to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_blue_balance(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of brightness.
///
/// Picture brightness: or more precisely: the black level.
///
/// \param fg     Frame grabber to set brightness on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_brightness(fg_grabber *fg);

///
/// \brief Set value of brightness.
///
/// Picture brightness: or more precisely: the black level.
///
/// \param  fg      Frame grabber to set brightness on.
/// \param  value   Value to set brightness to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_brightness(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of chroma agc.
///
///
///
/// \param fg     Frame grabber to set chroma agc on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_chroma_agc(fg_grabber *fg);

///
/// \brief Set value of chroma agc.
///
///
///
/// \param  fg      Frame grabber to set chroma agc on.
/// \param  value   Value to set chroma agc to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_chroma_agc(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of color effects.
///
///
///
/// \param fg     Frame grabber to set color effects on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_color_effects(fg_grabber *fg);

///
/// \brief Set value of color effects.
///
///
///
/// \param  fg      Frame grabber to set color effects on.
/// \param  value   Value to set color effects to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_color_effects(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of color killer.
///
///
///
/// \param fg     Frame grabber to set color killer on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_color_killer(fg_grabber *fg);

///
/// \brief Set value of color killer.
///
///
///
/// \param  fg      Frame grabber to set color killer on.
/// \param  value   Value to set color killer to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_color_killer(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of contrast.
///
/// Picture contrast or luma gain.
///
/// \param fg     Frame grabber to set contrast on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_contrast(fg_grabber *fg);

///
/// \brief Set value of contrast.
///
/// Picture contrast or luma gain.
///
/// \param  fg      Frame grabber to set contrast on.
/// \param  value   Value to set contrast to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_contrast(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of do white balance.
///
/// This is an action control. When set (the value is ignored): the device will do a white balance and then hold the current setting. Contrast this with the boolean FG_AUTO_WHITE_BALANCE: which: when activated: keeps adjusting the white balance.
///
/// \param fg     Frame grabber to set do white balance on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_do_white_balance(fg_grabber *fg);

///
/// \brief Set value of do white balance.
///
/// This is an action control. When set (the value is ignored): the device will do a white balance and then hold the current setting. Contrast this with the boolean FG_AUTO_WHITE_BALANCE: which: when activated: keeps adjusting the white balance.
///
/// \param  fg      Frame grabber to set do white balance on.
/// \param  value   Value to set do white balance to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_do_white_balance(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of exposure.
///
/// Exposure (cameras).
///
/// \param fg     Frame grabber to set exposure on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_exposure(fg_grabber *fg);

///
/// \brief Set value of exposure.
///
/// Exposure (cameras).
///
/// \param  fg      Frame grabber to set exposure on.
/// \param  value   Value to set exposure to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_exposure(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of gain.
///
/// Gain control.
///
/// \param fg     Frame grabber to set gain on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_gain(fg_grabber *fg);

///
/// \brief Set value of gain.
///
/// Gain control.
///
/// \param  fg      Frame grabber to set gain on.
/// \param  value   Value to set gain to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_gain(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of gamma.
///
/// Gamma adjust.
///
/// \param fg     Frame grabber to set gamma on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_gamma(fg_grabber *fg);

///
/// \brief Set value of gamma.
///
/// Gamma adjust.
///
/// \param  fg      Frame grabber to set gamma on.
/// \param  value   Value to set gamma to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_gamma(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of hflip.
///
/// Mirror the picture horizontally.
///
/// \param fg     Frame grabber to set hflip on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_hflip(fg_grabber *fg);

///
/// \brief Set value of hflip.
///
/// Mirror the picture horizontally.
///
/// \param  fg      Frame grabber to set hflip on.
/// \param  value   Value to set hflip to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_hflip(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of hue.
///
/// Hue or color balance.
///
/// \param fg     Frame grabber to set hue on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_hue(fg_grabber *fg);

///
/// \brief Set value of hue.
///
/// Hue or color balance.
///
/// \param  fg      Frame grabber to set hue on.
/// \param  value   Value to set hue to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_hue(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of power line frequency.
///
/// nables a power line frequency filter to avoid flicker. Possible values are: FG_POWER_LINE_FREQUENCY_DISABLED (0): FG_POWER_LINE_FREQUENCY_50HZ (1) and FG_POWER_LINE_FREQUENCY_60HZ (2).
///
/// \param fg     Frame grabber to set power line frequency on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_power_line_frequency(fg_grabber *fg);

///
/// \brief Set value of power line frequency.
///
/// nables a power line frequency filter to avoid flicker. Possible values are: FG_POWER_LINE_FREQUENCY_DISABLED (0): FG_POWER_LINE_FREQUENCY_50HZ (1) and FG_POWER_LINE_FREQUENCY_60HZ (2).
///
/// \param  fg      Frame grabber to set power line frequency on.
/// \param  value   Value to set power line frequency to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_power_line_frequency(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of red balance.
///
/// 	Red chroma balance.
///
/// \param fg     Frame grabber to set red balance on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_red_balance(fg_grabber *fg);

///
/// \brief Set value of red balance.
///
/// 	Red chroma balance.
///
/// \param  fg      Frame grabber to set red balance on.
/// \param  value   Value to set red balance to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_red_balance(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of rotate.
///
///
///
/// \param fg     Frame grabber to set rotate on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_rotate(fg_grabber *fg);

///
/// \brief Set value of rotate.
///
///
///
/// \param  fg      Frame grabber to set rotate on.
/// \param  value   Value to set rotate to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_rotate(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of saturation.
///
/// Picture color saturation or chroma gain.
///
/// \param fg     Frame grabber to set saturation on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_saturation(fg_grabber *fg);

///
/// \brief Set value of saturation.
///
/// Picture color saturation or chroma gain.
///
/// \param  fg      Frame grabber to set saturation on.
/// \param  value   Value to set saturation to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_saturation(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of sharpness.
///
/// Adjusts the sharpness filters in a camera. The minimum value disables the filters: higher values give a sharper picture.
///
/// \param fg     Frame grabber to set sharpness on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_sharpness(fg_grabber *fg);

///
/// \brief Set value of sharpness.
///
/// Adjusts the sharpness filters in a camera. The minimum value disables the filters: higher values give a sharper picture.
///
/// \param  fg      Frame grabber to set sharpness on.
/// \param  value   Value to set sharpness to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_sharpness(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of vflip.
///
/// Mirror the picture vertically.
///
/// \param fg     Frame grabber to set vflip on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_vflip(fg_grabber *fg);

///
/// \brief Set value of vflip.
///
/// Mirror the picture vertically.
///
/// \param  fg      Frame grabber to set vflip on.
/// \param  value   Value to set vflip to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_vflip(fg_grabber *fg, int value);

//------------------------------------------------------------------------

///
/// \brief Get value of white balance temp.
///
/// This control specifies the white balance settings as a color temperature in Kelvin. A driver should have a minimum of 2800 (incandescent) to 6500 (daylight). For more information about color temperature see Wikipedia.
///
/// \param fg     Frame grabber to set white balance temp on.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_white_balance_temp(fg_grabber *fg);

///
/// \brief Set value of white balance temp.
///
/// This control specifies the white balance settings as a color temperature in Kelvin. A driver should have a minimum of 2800 (incandescent) to 6500 (daylight). For more information about color temperature see Wikipedia.
///
/// \param  fg      Frame grabber to set white balance temp on.
/// \param  value   Value to set white balance temp to.
///
/// \return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_white_balance_temp(fg_grabber *fg, int value);

//------------------------------------------------------------------------



/** @} */ // end of control group

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

//------------------------------------------------------------------------------

///
/// \brief Free memory used by an existing frame.
///
/// This function is a synonym for #fg_frame_release().
///
/// \param fr  The frame to release memory from.
///
void fg_frame_free(fg_frame *fr);

//------------------------------------------------------------------------------

///
/// \brief Gets a pointer to the frame's raw image data.
///
/// \param fr  The frame whos data to get a pointer to.
///
/// \return Pointer to the frame's data.
unsigned char *fg_frame_get_data(fg_frame *fr);

//------------------------------------------------------------------------------

///
/// \brief Get the size of the frame data in bytes.
///
/// \param fr  The frame whos data to get the length of.
///
/// \return The length of the frame's data in bytes or -1 on error.
///
int fg_frame_get_size(fg_frame *fr);

//------------------------------------------------------------------------------

///
/// \brief Get the horizontal resolution in pixels of the frame.
///
/// \param fr The frame whos width to get.
///
/// \return The width of the frame or -1 on error.
///
int fg_frame_get_width(fg_frame *fr);

//------------------------------------------------------------------------------

///
/// \brief Get the vertical resolution in pixels of the frame.
///
/// \param fr The frame whos height to get.
///
/// \return The height of the frame or -1 on error.
///
int fg_frame_get_height(fg_frame *fr);

//------------------------------------------------------------------------------

///
/// \brief Print debugging information for a frame.
///
/// \param fg   Frame to print debug info for.
/// \param fp   File stream to write debug info to.
///
void fg_debug_frame(fg_frame *fr, FILE *fp);

//------------------------------------------------------------------------------

///
/// \brief Copy frame from src to dst.
///
/// \param  src Frame to copy.
/// \param  dst Frame to copy to.
///
/// \return 0 on success, -1 on failure.
int fg_frame_copy(fg_frame *src, fg_frame *dst);

//------------------------------------------------------------------------------

///
/// \brief Duplicate frame.
///
/// \param fr   Frame to make a duplicate of.
///
/// \return A new #fg_frame or NULL on error.
///
fg_frame *fg_frame_clone(fg_frame *fr);

//------------------------------------------------------------------------------

#ifdef WITH_JPEG
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

/** @} */ // end of frame section

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* LIBFG2_H */
