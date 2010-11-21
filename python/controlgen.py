#!/usr/bin/env python2

FG_CONTROLS = {
    "BRIGHTNESS": "Picture brightness: or more precisely: the black level.",
    "CONTRAST": "Picture contrast or luma gain.",
    "SATURATION": "Picture color saturation or chroma gain.",
    "HUE": "Hue or color balance.",
    "AUDIO_VOLUME": "Overall audio volume. Note some drivers also provide an OSS or ALSA mixer interface.",
    "AUDIO_BALANCE": "Audio stereo balance. Minimum corresponds to all the way left: maximum to right.",
    "AUDIO_BASS": "Audio bass adjustment.",
    "AUDIO_TREBLE": "Audio treble adjustment.",
    "AUDIO_MUTE": "Mute audio: i. e. set the volume to zero: however without affecting FG_AUDIO_VOLUME. Like ALSA drivers: V4L2 drivers must mute at load time to avoid excessive noise. Actually the entire device should be reset to a low power consumption state.",
    "AUDIO_LOUDNESS": "Loudness mode (bass boost).",
    "AUTO_WHITE_BALANCE": "Automatic white balance (cameras).",
    "DO_WHITE_BALANCE": "This is an action control. When set (the value is ignored): the device will do a white balance and then hold the current setting. Contrast this with the boolean FG_AUTO_WHITE_BALANCE: which: when activated: keeps adjusting the white balance.",
    "RED_BALANCE": "	Red chroma balance.",
    "BLUE_BALANCE": "Blue chroma balance.",
    "GAMMA": "Gamma adjust.",
    "EXPOSURE": "Exposure (cameras).",
    "AUTO_GAIN": "Automatic gain/exposure control.",
    "GAIN": "Gain control.",
    "HFLIP": "Mirror the picture horizontally.",
    "VFLIP": "Mirror the picture vertically.",
    "POWER_LINE_FREQUENCY": "nables a power line frequency filter to avoid flicker. Possible values are: FG_POWER_LINE_FREQUENCY_DISABLED (0): FG_POWER_LINE_FREQUENCY_50HZ (1) and FG_POWER_LINE_FREQUENCY_60HZ (2).",
    "AUTO_HUE": "Enables automatic hue control by the device. The effect of setting FG_HUE while automatic hue control is enabled is undefined: drivers should ignore such request.",
    "WHITE_BALANCE_TEMP": "This control specifies the white balance settings as a color temperature in Kelvin. A driver should have a minimum of 2800 (incandescent) to 6500 (daylight). For more information about color temperature see Wikipedia.",
    "SHARPNESS": "Adjusts the sharpness filters in a camera. The minimum value disables the filters: higher values give a sharper picture.",
    "BACKLIGHT_COMPENSATION": "Adjusts the backlight compensation in a camera. The minimum value disables backlight compensation.",
    "CHROMA_AGC": "",
    "COLOR_KILLER": "",
    "COLOR_EFFECTS": "",
    "AUTO_BRIGHTNESS": "",
    "BAND_STOP_FILTER": "",
    "ROTATE": "",
    "BACKGROUND_COLOR": ""
}

def get_getter_proto(name, desc):
    " Generates a C accessor definition for getting control value. "
    const_name = name.upper()
    var_name = name.lower()
    text_name = name.lower().replace("_", " ")
    code = """///
/// \\brief Get value of %s.
///
/// %s
///
/// \\param fg     Frame grabber to set %s on.
///
/// \\return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         or value of control otherwise.
///
int fg_get_%s(fg_grabber *fg);
""" % (text_name, desc, text_name, var_name)
    return code

def get_setter_proto(name, desc):
    " Generates a C accessor for getting control value. "
    const_name = name.upper()
    var_name = name.lower()
    text_name = name.lower().replace("_", " ")
    code = """///
/// \\brief Set value of %s.
///
/// %s
///
/// \\param  fg      Frame grabber to set %s on.
/// \\param  value   Value to set %s to.
///
/// \\return #FG_CONTROL_INVALID if the control is disabled or not supported,
///         #FG_CONTROL_READ_ONLY if the control can only be read or 
///         #FG_CONTROL_OK if the value could be set.
///
int fg_set_%s(fg_grabber *fg, int value);
""" % (text_name, desc, text_name, text_name, var_name)
    return code

def get_getter(name, desc):
    " Generates a C accessor for getting control value. "
    const_name = name.upper()
    var_name = name.lower()
    text_name = name.lower().replace("_", " ")
    code = """///
/// \\brief Get value of %s.
///
/// %s
///
/// \\param fg     Frame grabber to set %s on.
///
/// \\return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read or value of
///         control otherwise.
///
int fg_get_%s(fg_grabber *fg)
{
    return fg_get_control(fg, FG_CONTROL_ID_%s);
}
""" % (text_name, desc, text_name, var_name, const_name)
    return code


def get_setter(name, desc):
    " Generates a C accessor for setting control value. "
    const_name = name.upper()
    var_name = name.lower()
    text_name = name.lower().replace("_", " ")
    code = """///
/// \\brief Set value of %s.
///
/// %s
///
/// \\param  fg      Frame grabber to set %s on.
/// \\param  value   Value to set %s to.
///
/// \\return FG_CONTROL_INVALID if the control is disabled or not supported,
///         FG_CONTROL_READ_ONLY if the control can only be read, 
///         FG_CONTROL_OUT_OF_RANGE if the value is out of range or 
///         FG_CONTROL_OK if the control was set.
///
int fg_set_%s(fg_grabber *fg, int value)
{
    return fg_set_control(fg, FG_CONTROL_ID_%s, value);
}
""" % (text_name, desc, text_name, text_name, var_name, const_name)
    return code


if __name__ == "__main__":
    
    for name, desc in sorted(FG_CONTROLS.items()):
        
        print get_getter_proto(name, desc)
        print get_setter_proto(name, desc)
        print "//%s\n" % str("-"*72)
