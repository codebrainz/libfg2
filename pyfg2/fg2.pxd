#cdef extern from "linux/videodev2.h":
#    pass
    #ctypedef enum fg_control_id:
        #BRIGHTNESS             = V4L2_CID_BRIGHTNESS
        #CONTRAST               = V4L2_CID_CONTRAST
        #SATURATION             = V4L2_CID_SATURATION
        #HUE                    = V4L2_CID_HUE
        #AUDIO_VOLUME           = V4L2_CID_AUDIO_VOLUME
        #AUDIO_BALANCE          = V4L2_CID_AUDIO_BALANCE
        #AUDIO_BASS             = V4L2_CID_AUDIO_BASS
        #AUDIO_TREBLE           = V4L2_CID_AUDIO_TREBLE
        #AUDIO_MUTE             = V4L2_CID_AUDIO_MUTE
        #AUDIO_LOUDNESS         = V4L2_CID_AUDIO_LOUDNESS
        #AUTO_WHITE_BALANCE     = V4L2_CID_AUTO_WHITE_BALANCE
        #DO_WHITE_BALANCE       = V4L2_CID_DO_WHITE_BALANCE
        #RED_BALANCE            = V4L2_CID_RED_BALANCE
        #BLUE_BALANCE           = V4L2_CID_BLUE_BALANCE
        #GAMMA                  = V4L2_CID_GAMMA
        #EXPOSURE               = V4L2_CID_EXPOSURE
        #AUTO_GAIN              = V4L2_CID_AUTOGAIN
        #GAIN                   = V4L2_CID_GAIN
        #HFLIP                  = V4L2_CID_HFLIP
        #VFLIP                  = V4L2_CID_VFLIP
        #POWER_LINE_FREQUENCY   = V4L2_CID_POWER_LINE_FREQUENCY
        #AUTO_HUE               = V4L2_CID_HUE_AUTO
        #WHITE_BALANCE_TEMP     = V4L2_CID_WHITE_BALANCE_TEMPERATURE
        #SHARPNESS              = V4L2_CID_SHARPNESS
        #BACKLIGHT_COMPENSATION = V4L2_CID_BACKLIGHT_COMPENSATION
        #CHROMA_AGC             = V4L2_CID_CHROMA_AGC
        #COLOR_KILLER           = V4L2_CID_COLOR_KILLER
        #COLOR_EFFECTS          = V4L2_CID_COLORFX
        #AUTO_BRIGHTNESS        = V4L2_CID_AUTOBRIGHTNESS
        #BAND_STOP_FILTER       = V4L2_CID_BAND_STOP_FILTER
        #ROTATE                 = V4L2_CID_ROTATE
        #BACKGROUND_COLOR       = V4L2_CID_BG_COLOR

cdef extern from "libfg2.h":

    ctypedef enum fg_control_id:
        pass

    ctypedef enum fg_power_line_freq:
        FG_POWER_LINE_FREQUENCY_DISABLED    = 0
        FG_POWER_LINE_FREQUENCY_50HZ        = 1
        FG_POWER_LINE_FREQUENCY_60HZ        = 2
    
    ctypedef enum fg_color_effects:
        FG_COLOR_EFFECTS_NONE               = 0
        FG_COLOR_EFFECTS_BW                 = 1
        FG_COLOR_EFFECTS_SEPIA              = 2
        FG_COLOR_EFFECTS_NEGATIVE           = 3
        FG_COLOR_EFFECTS_EMBOSS             = 4
        FG_COLOR_EFFECTS_SKETCH             = 5
        FG_COLOR_EFFECTS_SKY_BLUE           = 6
        FG_COLOR_EFFECTS_GRASS_GREEN        = 7
        FG_COLOR_EFFECTS_SKIN_WHITEN        = 8
        FG_COLOR_EFFECTS_VIVID              = 9

    ctypedef struct fg_rect:
        int left  
        int top  
        int width
        int height
        
    ctypedef struct fg_size:
        unsigned int width    
        unsigned int height 
        
    ctypedef struct fg_rgb:
        char    red   
        char    green
        char    blue
        
    ctypedef struct fg_caps: 
        pass
    ctypedef struct fg_input: 
        pass
    ctypedef struct fg_tuner: 
        pass
    ctypedef struct fg_crop: 
        pass
    ctypedef struct fg_format: 
        pass
    ctypedef struct fg_control: 
        pass
    
    ctypedef struct fg_frame:
        fg_size         size
        int             rowstride
        int             format
        int             length       
        unsigned char   *data        
        #struct timeval timestamp
    
    ctypedef struct fg_grabber:
        char                    *device
        int                     fd
        fg_caps                 caps
        fg_input                *inputs
        int                     num_inputs
        int                     input
        fg_tuner                *tuners
        int                     num_tuners
        int                     tuner
        fg_crop                 cropcap
        fg_format               format
        fg_control              *controls
        int                     num_controls
    
    #void fg_debug(char* fmt, ...)
    #void fg_debug_error(char* fmt, ...)
    void fg_dump_info(fg_grabber* fg)
    fg_grabber* fg_open(char* dev)
    void fg_close(fg_grabber* fg)
    fg_frame* fg_grab(fg_grabber* fg)
    int fg_grab_frame(fg_grabber* fg, fg_frame* fr)
    int fg_get_input_count(fg_grabber* fg)
    int fg_get_input(fg_grabber* fg)
    int fg_set_input(fg_grabber* fg, int index)
    char* fg_get_input_name(fg_grabber* fg, int index)
    int fg_get_input_type(fg_grabber* fg, int index)
    int fg_set_channel(fg_grabber* fg, float freq)
    float fg_get_channel(fg_grabber* fg)
    int fg_set_format(fg_grabber* fg, int fmt)
    int fg_get_format(fg_grabber* fg)
    int fg_set_capture_size(fg_grabber* fg, fg_size* size)
    int fg_get_capture_size(fg_grabber* fg, fg_size* size)
    int fg_set_capture_window(fg_grabber* fg, fg_rect* rect)
    int fg_get_capture_window(fg_grabber* fg, fg_rect* rect)

    int fg_check_control(fg_grabber* fg, fg_control_id control_id)
    int fg_set_control(fg_grabber* fg, fg_control_id control_id, int value)
    int fg_get_control(fg_grabber* fg, fg_control_id control_id)
    int fg_default_controls(fg_grabber* fg)
    int fg_get_audio_balance(fg_grabber* fg)
    int fg_set_audio_balance(fg_grabber* fg, int value)
    int fg_get_audio_bass(fg_grabber* fg)
    int fg_set_audio_bass(fg_grabber* fg, int value)
    int fg_get_audio_loudness(fg_grabber* fg)
    int fg_set_audio_loudness(fg_grabber* fg, int value)
    int fg_get_audio_mute(fg_grabber* fg)
    int fg_set_audio_mute(fg_grabber* fg, int value)
    int fg_get_audio_treble(fg_grabber* fg)
    int fg_set_audio_treble(fg_grabber* fg, int value)
    int fg_get_audio_volume(fg_grabber* fg)
    int fg_set_audio_volume(fg_grabber* fg, int value)
    int fg_get_auto_brightness(fg_grabber* fg)
    int fg_set_auto_brightness(fg_grabber* fg, int value)
    int fg_get_auto_gain(fg_grabber* fg)
    int fg_set_auto_gain(fg_grabber* fg, int value)
    int fg_get_auto_hue(fg_grabber* fg)
    int fg_set_auto_hue(fg_grabber* fg, int value)
    int fg_get_auto_white_balance(fg_grabber* fg)
    int fg_set_auto_white_balance(fg_grabber* fg, int value)
    int fg_get_background_color(fg_grabber* fg)
    int fg_set_background_color(fg_grabber* fg, int value)
    int fg_get_backlight_compensation(fg_grabber* fg)
    int fg_set_backlight_compensation(fg_grabber* fg, int value)
    int fg_get_band_stop_filter(fg_grabber* fg)
    int fg_set_band_stop_filter(fg_grabber* fg, int value)
    int fg_get_blue_balance(fg_grabber* fg)
    int fg_set_blue_balance(fg_grabber* fg, int value)
    int fg_get_brightness(fg_grabber* fg)
    int fg_set_brightness(fg_grabber* fg, int value)
    int fg_get_chroma_agc(fg_grabber* fg)
    int fg_set_chroma_agc(fg_grabber* fg, int value)
    int fg_get_color_effects(fg_grabber* fg)
    int fg_set_color_effects(fg_grabber* fg, int value)
    int fg_get_color_killer(fg_grabber* fg)
    int fg_set_color_killer(fg_grabber* fg, int value)
    int fg_get_contrast(fg_grabber* fg)
    int fg_set_contrast(fg_grabber* fg, int value)
    int fg_get_do_white_balance(fg_grabber* fg)
    int fg_set_do_white_balance(fg_grabber* fg, int value)
    int fg_get_exposure(fg_grabber* fg)
    int fg_set_exposure(fg_grabber* fg, int value)
    int fg_get_gain(fg_grabber* fg)
    int fg_set_gain(fg_grabber* fg, int value)
    int fg_get_gamma(fg_grabber* fg)
    int fg_set_gamma(fg_grabber* fg, int value)
    int fg_get_hflip(fg_grabber* fg)
    int fg_set_hflip(fg_grabber* fg, int value)
    int fg_get_hue(fg_grabber* fg)
    int fg_set_hue(fg_grabber* fg, int value)
    int fg_get_power_line_frequency(fg_grabber* fg)
    int fg_set_power_line_frequency(fg_grabber* fg, int value)
    int fg_get_red_balance(fg_grabber* fg)
    int fg_set_red_balance(fg_grabber* fg, int value)
    int fg_get_rotate(fg_grabber* fg)
    int fg_set_rotate(fg_grabber* fg, int value)
    int fg_get_saturation(fg_grabber* fg)
    int fg_set_saturation(fg_grabber* fg, int value)
    int fg_get_sharpness(fg_grabber* fg)
    int fg_set_sharpness(fg_grabber* fg, int value)
    int fg_get_vflip(fg_grabber* fg)
    int fg_set_vflip(fg_grabber* fg, int value)
    int fg_get_white_balance_temp(fg_grabber* fg)
    int fg_set_white_balance_temp(fg_grabber* fg, int value)

    fg_frame* fg_frame_new(fg_grabber* fg)
    void fg_frame_release(fg_frame* fr)
    void fg_frame_free(fg_frame* fr)
    unsigned char* fg_frame_get_data(fg_frame* fr)
    int fg_frame_get_size(fg_frame* fr)
    int fg_frame_get_width(fg_frame* fr)
    int fg_frame_get_height(fg_frame* fr)
    #void fg_debug_frame(fg_frame* fr, FILE* fp)
    int fg_frame_copy(fg_frame* src, fg_frame* dst)
    fg_frame* fg_frame_clone(fg_frame* fr)
