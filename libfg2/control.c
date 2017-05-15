#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <libfg2/libfg2.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <linux/videodev2.h>

//--------------------------------------------------------------------------

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
int fg_check_control(fg_grabber *fg, fg_control_id control_id)
{
    struct v4l2_queryctrl ctrl;
    FG_CLEAR(ctrl);
    for (ctrl.id = V4L2_CID_BASE; ctrl.id < V4L2_CID_LASTP1; ctrl.id++)
    {
        if (v4l2_ioctl(fg->fd, VIDIOC_QUERYCTRL, &ctrl) == 0)
        {
            if (ctrl.id == control_id)
            {
                if (ctrl.flags & V4L2_CTRL_FLAG_DISABLED)
                    return FG_CONTROL_INVALID;
                else if (ctrl.flags & V4L2_CTRL_FLAG_INACTIVE)
                    return FG_CONTROL_INVALID;
                else if (ctrl.flags & V4L2_CTRL_FLAG_GRABBED)
                    return FG_CONTROL_READ_ONLY;
                else if (ctrl.flags & V4L2_CTRL_FLAG_READ_ONLY)
                    return FG_CONTROL_READ_ONLY;
                else
                    return FG_CONTROL_OK;
            }
        }
        else
        {
            if(errno == EINVAL)
                continue;
            fg_debug_error("fg_check_control(): error enumerating controls");
            return FG_CONTROL_INVALID;
        }
    }
    return FG_CONTROL_INVALID;
}

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
int fg_set_control(fg_grabber *fg, fg_control_id control_id, int value)
{

    if (value < 0 || value > 65535)
    {
        fg_debug_error("fg_set_control(): value out of range");
        return FG_CONTROL_OUT_OF_RANGE;
    }

    switch (fg_check_control(fg, control_id))
    {
        case FG_CONTROL_INVALID:
            fg_debug_error("fg_set_control(): control not supported");
            return FG_CONTROL_INVALID;

        case FG_CONTROL_READ_ONLY:
            fg_debug_error("fg_set_control(): control is read-only");
            return FG_CONTROL_READ_ONLY;

        default:
            v4l2_set_control(fg->fd, control_id, value);
            return FG_CONTROL_OK;
    }
}

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
int fg_get_control(fg_grabber *fg, fg_control_id control_id)
{
    switch (fg_check_control(fg, control_id))
    {
        case FG_CONTROL_INVALID:
            fg_debug_error("fg_get_control(): control not supported");
            return FG_CONTROL_INVALID;
        default:
            return v4l2_get_control(fg->fd, control_id);
    }
}

///
/// \brief  Set controls to default values.
///
/// This function resets all supported controls to their default values.
///
/// \param  fg      Frame grabber to set control values to defaults on.
///
/// \return 0 on success, -1 on failure.
///
int fg_default_controls(fg_grabber *fg)
{
    int i;
    struct v4l2_control ctrl;
    struct v4l2_queryctrl ctrl_info;

    FG_CLEAR(ctrl);

    for (i=V4L2_CID_BASE; i < V4L2_CID_LASTP1; i++)
    {

        ctrl_info.id = i;
        if (v4l2_ioctl(fg->fd, VIDIOC_QUERYCTRL, &ctrl_info) == -1)
        {
            if (errno == EINVAL)
                continue;
            else
            {
                fg_debug_error("fg_default_controls(): error enumerating "
                    "controls");
                return -1;
            }
        }

        FG_CLEAR(ctrl);

        ctrl.id = ctrl_info.id;
        ctrl.value = ctrl_info.default_value;
        if (v4l2_ioctl(fg->fd, VIDIOC_S_CTRL, &ctrl) == -1)
            continue;

    }

    return 0;
}

//==============================================================================

///
/// \brief  Get the name of the specifed control.
///
/// The returned character array must be free()'d when it is no longer needed.
///
/// \param  fg  Frame grabber to get control name on.
/// \param  control_id  ID of the control to get name of.
///
/// \return Allocated character array containing the name of the control or
///         NULL on error.
///
char *fg_get_control_name(fg_grabber *fg, fg_control_id control_id)
{
    struct v4l2_queryctrl ctrl_info;

    FG_CLEAR(ctrl_info);

    ctrl_info.id = control_id;
    if (v4l2_ioctl(fg->fd, VIDIOC_QUERYCTRL, &ctrl_info) == -1)
    {
        fg_debug_error("fg_get_control_name(): unable to get control name");
        return NULL;
    }

    return strdup((const char*)ctrl_info.name);
}

//==============================================================================

/* the following functions were generated automatically */
/* see file python/controlgen.py file for details       */

///
/// \brief Get value of audio balance.
///
/// Audio stereo balance. Minimum corresponds to all the way left: maximum to right.
///
/// \param fg     Frame grabber to set audio balance on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_audio_balance(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUDIO_BALANCE);
}

///
/// \brief Set value of audio balance.
///
/// Audio stereo balance. Minimum corresponds to all the way left: maximum to right.
///
/// \param  fg      Frame grabber to set audio balance on.
/// \param  value   Value to set audio balance to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_audio_balance(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUDIO_BALANCE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of audio bass.
///
/// Audio bass adjustment.
///
/// \param fg     Frame grabber to set audio bass on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_audio_bass(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUDIO_BASS);
}

///
/// \brief Set value of audio bass.
///
/// Audio bass adjustment.
///
/// \param  fg      Frame grabber to set audio bass on.
/// \param  value   Value to set audio bass to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_audio_bass(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUDIO_BASS, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of audio loudness.
///
/// Loudness mode (bass boost).
///
/// \param fg     Frame grabber to set audio loudness on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_audio_loudness(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUDIO_LOUDNESS);
}

///
/// \brief Set value of audio loudness.
///
/// Loudness mode (bass boost).
///
/// \param  fg      Frame grabber to set audio loudness on.
/// \param  value   Value to set audio loudness to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_audio_loudness(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUDIO_LOUDNESS, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of audio mute.
///
/// Mute audio: i. e. set the volume to zero: however without affecting FG_AUDIO_VOLUME. Like ALSA drivers: V4L2 drivers must mute at load time to avoid excessive noise. Actually the entire device should be reset to a low power consumption state.
///
/// \param fg     Frame grabber to set audio mute on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_audio_mute(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUDIO_MUTE);
}

///
/// \brief Set value of audio mute.
///
/// Mute audio: i. e. set the volume to zero: however without affecting FG_AUDIO_VOLUME. Like ALSA drivers: V4L2 drivers must mute at load time to avoid excessive noise. Actually the entire device should be reset to a low power consumption state.
///
/// \param  fg      Frame grabber to set audio mute on.
/// \param  value   Value to set audio mute to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_audio_mute(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUDIO_MUTE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of audio treble.
///
/// Audio treble adjustment.
///
/// \param fg     Frame grabber to set audio treble on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_audio_treble(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUDIO_TREBLE);
}

///
/// \brief Set value of audio treble.
///
/// Audio treble adjustment.
///
/// \param  fg      Frame grabber to set audio treble on.
/// \param  value   Value to set audio treble to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_audio_treble(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUDIO_TREBLE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of audio volume.
///
/// Overall audio volume. Note some drivers also provide an OSS or ALSA mixer interface.
///
/// \param fg     Frame grabber to set audio volume on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_audio_volume(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUDIO_VOLUME);
}

///
/// \brief Set value of audio volume.
///
/// Overall audio volume. Note some drivers also provide an OSS or ALSA mixer interface.
///
/// \param  fg      Frame grabber to set audio volume on.
/// \param  value   Value to set audio volume to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_audio_volume(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUDIO_VOLUME, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of auto brightness.
///
///
///
/// \param fg     Frame grabber to set auto brightness on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_auto_brightness(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUTO_BRIGHTNESS);
}

///
/// \brief Set value of auto brightness.
///
///
///
/// \param  fg      Frame grabber to set auto brightness on.
/// \param  value   Value to set auto brightness to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_auto_brightness(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUTO_BRIGHTNESS, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of auto gain.
///
/// Automatic gain/exposure control.
///
/// \param fg     Frame grabber to set auto gain on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_auto_gain(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUTO_GAIN);
}

///
/// \brief Set value of auto gain.
///
/// Automatic gain/exposure control.
///
/// \param  fg      Frame grabber to set auto gain on.
/// \param  value   Value to set auto gain to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_auto_gain(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUTO_GAIN, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of auto hue.
///
/// Enables automatic hue control by the device. The effect of setting FG_HUE while automatic hue control is enabled is undefined: drivers should ignore such request.
///
/// \param fg     Frame grabber to set auto hue on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_auto_hue(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUTO_HUE);
}

///
/// \brief Set value of auto hue.
///
/// Enables automatic hue control by the device. The effect of setting FG_HUE while automatic hue control is enabled is undefined: drivers should ignore such request.
///
/// \param  fg      Frame grabber to set auto hue on.
/// \param  value   Value to set auto hue to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_auto_hue(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUTO_HUE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of auto white balance.
///
/// Automatic white balance (cameras).
///
/// \param fg     Frame grabber to set auto white balance on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_auto_white_balance(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_AUTO_WHITE_BALANCE);
}

///
/// \brief Set value of auto white balance.
///
/// Automatic white balance (cameras).
///
/// \param  fg      Frame grabber to set auto white balance on.
/// \param  value   Value to set auto white balance to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_auto_white_balance(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_AUTO_WHITE_BALANCE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of background color.
///
///
///
/// \param fg     Frame grabber to set background color on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_background_color(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_BACKGROUND_COLOR);
}

///
/// \brief Set value of background color.
///
///
///
/// \param  fg      Frame grabber to set background color on.
/// \param  value   Value to set background color to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_background_color(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_BACKGROUND_COLOR, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of backlight compensation.
///
/// Adjusts the backlight compensation in a camera. The minimum value disables backlight compensation.
///
/// \param fg     Frame grabber to set backlight compensation on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_backlight_compensation(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_BACKLIGHT_COMPENSATION);
}

///
/// \brief Set value of backlight compensation.
///
/// Adjusts the backlight compensation in a camera. The minimum value disables backlight compensation.
///
/// \param  fg      Frame grabber to set backlight compensation on.
/// \param  value   Value to set backlight compensation to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_backlight_compensation(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_BACKLIGHT_COMPENSATION, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of band stop filter.
///
///
///
/// \param fg     Frame grabber to set band stop filter on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_band_stop_filter(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_BAND_STOP_FILTER);
}

///
/// \brief Set value of band stop filter.
///
///
///
/// \param  fg      Frame grabber to set band stop filter on.
/// \param  value   Value to set band stop filter to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_band_stop_filter(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_BAND_STOP_FILTER, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of blue balance.
///
/// Blue chroma balance.
///
/// \param fg     Frame grabber to set blue balance on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_blue_balance(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_BLUE_BALANCE);
}

///
/// \brief Set value of blue balance.
///
/// Blue chroma balance.
///
/// \param  fg      Frame grabber to set blue balance on.
/// \param  value   Value to set blue balance to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_blue_balance(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_BLUE_BALANCE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of brightness.
///
/// Picture brightness: or more precisely: the black level.
///
/// \param fg     Frame grabber to set brightness on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_brightness(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_BRIGHTNESS);
}

///
/// \brief Set value of brightness.
///
/// Picture brightness: or more precisely: the black level.
///
/// \param  fg      Frame grabber to set brightness on.
/// \param  value   Value to set brightness to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_brightness(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_BRIGHTNESS, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of chroma agc.
///
///
///
/// \param fg     Frame grabber to set chroma agc on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_chroma_agc(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_CHROMA_AGC);
}

///
/// \brief Set value of chroma agc.
///
///
///
/// \param  fg      Frame grabber to set chroma agc on.
/// \param  value   Value to set chroma agc to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_chroma_agc(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_CHROMA_AGC, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of color effects.
///
///
///
/// \param fg     Frame grabber to set color effects on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_color_effects(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_COLOR_EFFECTS);
}

///
/// \brief Set value of color effects.
///
///
///
/// \param  fg      Frame grabber to set color effects on.
/// \param  value   Value to set color effects to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_color_effects(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_COLOR_EFFECTS, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of color killer.
///
///
///
/// \param fg     Frame grabber to set color killer on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_color_killer(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_COLOR_KILLER);
}

///
/// \brief Set value of color killer.
///
///
///
/// \param  fg      Frame grabber to set color killer on.
/// \param  value   Value to set color killer to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_color_killer(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_COLOR_KILLER, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of contrast.
///
/// Picture contrast or luma gain.
///
/// \param fg     Frame grabber to set contrast on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_contrast(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_CONTRAST);
}

///
/// \brief Set value of contrast.
///
/// Picture contrast or luma gain.
///
/// \param  fg      Frame grabber to set contrast on.
/// \param  value   Value to set contrast to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_contrast(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_CONTRAST, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of do white balance.
///
/// This is an action control. When set (the value is ignored): the device will do a white balance and then hold the current setting. Contrast this with the boolean FG_AUTO_WHITE_BALANCE: which: when activated: keeps adjusting the white balance.
///
/// \param fg     Frame grabber to set do white balance on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_do_white_balance(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_DO_WHITE_BALANCE);
}

///
/// \brief Set value of do white balance.
///
/// This is an action control. When set (the value is ignored): the device will do a white balance and then hold the current setting. Contrast this with the boolean FG_AUTO_WHITE_BALANCE: which: when activated: keeps adjusting the white balance.
///
/// \param  fg      Frame grabber to set do white balance on.
/// \param  value   Value to set do white balance to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_do_white_balance(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_DO_WHITE_BALANCE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of exposure.
///
/// Exposure (cameras).
///
/// \param fg     Frame grabber to set exposure on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_exposure(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_EXPOSURE);
}

///
/// \brief Set value of exposure.
///
/// Exposure (cameras).
///
/// \param  fg      Frame grabber to set exposure on.
/// \param  value   Value to set exposure to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_exposure(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_EXPOSURE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of gain.
///
/// Gain control.
///
/// \param fg     Frame grabber to set gain on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_gain(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_GAIN);
}

///
/// \brief Set value of gain.
///
/// Gain control.
///
/// \param  fg      Frame grabber to set gain on.
/// \param  value   Value to set gain to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_gain(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_GAIN, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of gamma.
///
/// Gamma adjust.
///
/// \param fg     Frame grabber to set gamma on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_gamma(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_GAMMA);
}

///
/// \brief Set value of gamma.
///
/// Gamma adjust.
///
/// \param  fg      Frame grabber to set gamma on.
/// \param  value   Value to set gamma to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_gamma(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_GAMMA, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of hflip.
///
/// Mirror the picture horizontally.
///
/// \param fg     Frame grabber to set hflip on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_hflip(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_HFLIP);
}

///
/// \brief Set value of hflip.
///
/// Mirror the picture horizontally.
///
/// \param  fg      Frame grabber to set hflip on.
/// \param  value   Value to set hflip to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_hflip(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_HFLIP, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of hue.
///
/// Hue or color balance.
///
/// \param fg     Frame grabber to set hue on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_hue(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_HUE);
}

///
/// \brief Set value of hue.
///
/// Hue or color balance.
///
/// \param  fg      Frame grabber to set hue on.
/// \param  value   Value to set hue to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_hue(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_HUE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of power line frequency.
///
/// nables a power line frequency filter to avoid flicker. Possible values are: FG_POWER_LINE_FREQUENCY_DISABLED (0): FG_POWER_LINE_FREQUENCY_50HZ (1) and FG_POWER_LINE_FREQUENCY_60HZ (2).
///
/// \param fg     Frame grabber to set power line frequency on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_power_line_frequency(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_POWER_LINE_FREQUENCY);
}

///
/// \brief Set value of power line frequency.
///
/// nables a power line frequency filter to avoid flicker. Possible values are: FG_POWER_LINE_FREQUENCY_DISABLED (0): FG_POWER_LINE_FREQUENCY_50HZ (1) and FG_POWER_LINE_FREQUENCY_60HZ (2).
///
/// \param  fg      Frame grabber to set power line frequency on.
/// \param  value   Value to set power line frequency to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_power_line_frequency(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_POWER_LINE_FREQUENCY, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of red balance.
///
/// 	Red chroma balance.
///
/// \param fg     Frame grabber to set red balance on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_red_balance(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_RED_BALANCE);
}

///
/// \brief Set value of red balance.
///
/// 	Red chroma balance.
///
/// \param  fg      Frame grabber to set red balance on.
/// \param  value   Value to set red balance to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_red_balance(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_RED_BALANCE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of rotate.
///
///
///
/// \param fg     Frame grabber to set rotate on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_rotate(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_ROTATE);
}

///
/// \brief Set value of rotate.
///
///
///
/// \param  fg      Frame grabber to set rotate on.
/// \param  value   Value to set rotate to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_rotate(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_ROTATE, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of saturation.
///
/// Picture color saturation or chroma gain.
///
/// \param fg     Frame grabber to set saturation on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_saturation(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_SATURATION);
}

///
/// \brief Set value of saturation.
///
/// Picture color saturation or chroma gain.
///
/// \param  fg      Frame grabber to set saturation on.
/// \param  value   Value to set saturation to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_saturation(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_SATURATION, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of sharpness.
///
/// Adjusts the sharpness filters in a camera. The minimum value disables the filters: higher values give a sharper picture.
///
/// \param fg     Frame grabber to set sharpness on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_sharpness(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_SHARPNESS);
}

///
/// \brief Set value of sharpness.
///
/// Adjusts the sharpness filters in a camera. The minimum value disables the filters: higher values give a sharper picture.
///
/// \param  fg      Frame grabber to set sharpness on.
/// \param  value   Value to set sharpness to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_sharpness(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_SHARPNESS, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of vflip.
///
/// Mirror the picture vertically.
///
/// \param fg     Frame grabber to set vflip on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_vflip(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_VFLIP);
}

///
/// \brief Set value of vflip.
///
/// Mirror the picture vertically.
///
/// \param  fg      Frame grabber to set vflip on.
/// \param  value   Value to set vflip to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_vflip(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_VFLIP, value);
}

//------------------------------------------------------------------------

///
/// \brief Get value of white balance temp.
///
/// This control specifies the white balance settings as a color temperature in Kelvin. A driver should have a minimum of 2800 (incandescent) to 6500 (daylight). For more information about color temperature see Wikipedia.
///
/// \param fg     Frame grabber to set white balance temp on.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_white_balance_temp(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_WHITE_BALANCE_TEMP);
}

///
/// \brief Set value of white balance temp.
///
/// This control specifies the white balance settings as a color temperature in Kelvin. A driver should have a minimum of 2800 (incandescent) to 6500 (daylight). For more information about color temperature see Wikipedia.
///
/// \param  fg      Frame grabber to set white balance temp on.
/// \param  value   Value to set white balance temp to.
///
/// \return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read,
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or
///         FG_CONTROL_OK if the control was set.
///
int fg_set_white_balance_temp(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_WHITE_BALANCE_TEMP, value);
}

//------------------------------------------------------------------------

