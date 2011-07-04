
[CCode (cheader_filename="libfg2.h")]
namespace Libfg2
{
    [Compact]
    [CCode (cname="fg_grabber", cprefix="fg_", lower_case_prefix="fg_", free_function="fg_close")]
    public class FrameGrabber
    {
        [CCode (cname="fg_open")]
        public FrameGrabber(string device);
        public int check_control(Control control_id);

        public uint input
        {
            [CCode (cname="fg_get_input")] get;
            [CCode (cname="fg_set_input")] set;
        }

        public Frame grab();
        public int grab_frame(out Frame frame);

        public uint input_count
        {
            [CCode (cname="fg_get_input_count")] get;
        }

        public string get_input_name(uint input);
        public InputType get_input_type(uint index);

        public float channel
        {
            [CCode (cname="fg_get_channel")] get;
            [CCode (cname="fg_set_channel")] set;
        }

        public Format format
        {
            [CCode (cname="fg_get_format")] get;
            [CCode (cname="fg_set_format")] set;
        }

        public Size capture_size
        {
            [CCode (cname="fg_get_capture_size")]   get;
            [CCode (cname="fg_set_capture_size")]   set;
        }

        public Rectangle capture_window
        {
            [CCode (cname="fg_get_capture_window")] get;
            [CCode (cname="fg_set_capture_window")] set;
        }
    }

    [Compact]
    [CCode (cname="fg_frame", cprefix="fg_frame_", lower_case_prefix="fg_frame_", free_function="fg_frame_free")]
    public class Frame
    {
        [CCode (cname="fg_frame_new")]
        public Frame(FrameGrabber fg);

        public int save(string filename);
    }

    [CCode (cname="fg_control_id", common_prefix="FG_CONTROL_ID_")]
    public enum Control
    {
        BRIGHTNESS,
        CONTRAST,
        SATURATION,
        HUE,
        AUDIO_VOLUME,
        AUDIO_BALANCE,
        AUDIO_BASS,
        AUDIO_TREBLE,
        AUDIO_MUTE,
        AUDIO_LOUDNESS,
        AUTO_WHITE_BALANCE,
        DO_WHITE_BALANCE,
        RED_BALANCE,
        BLUE_BALANCE,
        GAMMA,
        EXPOSURE,
        AUTO_GAIN,
        GAIN,
        HFLIP,
        VFLIP,
        POWER_LINE_FREQUENCY,
        AUTO_HUE,
        WHITE_BALANCE_TEMP,
        SHARPNESS,
        BACKLIGHT_COMPENSATION,
        CHROMA_AGC,
        COLOR_KILLER,
        COLOR_EFFECTS,
        AUTO_BRIGHTNESS,
        BAND_STOP_FILTER,
        ROTATE,
        BACKGROUND_COLOR
    }

    public enum InputType
    {
        [CCode (cname="FG_INPUT_TYPE_TUNER")]   TUNER,
        [CCode (cname="FG_INPUT_TYPE_CAMERA")]  CAMERA
    }

    public enum Format
    {
        [CCode (cname="FG_FORMAT_RGB24")]   RGB24,
        [CCode (cname="FG_FORMAT_BGR24")]   BGR24,
        [CCode (cname="FG_FORMAT_YUV420")]  YUV420,
        [CCode (cname="FG_FORMAT_YVU420")]  YVU420,
        [CCode (cname="FG_FORMAT_DEFAULT")] DEFAULT
    }

    [Compact]
    [CCode (cname="fg_rect")]
    public struct Rectangle
    {
        public uint left;
        public uint top;
        public uint width;
        public uint height;
    }

    [Compact]
    [CCode (cname="fg_size")]
    public struct Size
    {
        public uint width;
        public uint height;
    }

}
