		
cdef extern from "sys/time.h":
	ctypedef long time_t
	ctypedef long int suseconds_t
	struct timeval:
		time_t tv_sec
		suseconds_t tv_usec

cdef extern from "stdio.h":
	ctypedef struct FILE:
		pass

cdef extern from "libfg2.h":
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------
	ctypedef struct fg_frame:
		fg_size         size
		int             rowstride
		int             format
		int             length
		unsigned char   *data
		timeval         timestamp
#===============================================================================
	fg_grabber *fg_open(char *dev)
	void fg_close(fg_grabber *fg)
	int fg_set_input(fg_grabber* fg, int index)
	int fg_get_input(fg_grabber *fg)
	fg_frame *fg_grab(fg_grabber* fg)
	int fg_grab_frame(fg_grabber *fg, fg_frame *fr)
	int fg_get_input_count(fg_grabber *fg)
	int fg_get_input(fg_grabber *fg)
	int fg_set_input(fg_grabber* fg, int index)
	char *fg_get_input_name(fg_grabber *fg, int index)
	int fg_get_input_type(fg_grabber* fg, int index)
	int fg_set_channel(fg_grabber* fg, float freq)
	float fg_get_channel(fg_grabber* fg)
	int fg_set_format(fg_grabber *fg, int fmt)
	int fg_get_format(fg_grabber *fg)
	int fg_set_capture_size(fg_grabber *fg, fg_size *size)
	int fg_get_capture_size(fg_grabber *fg, fg_size *size)
	int fg_set_capture_window(fg_grabber *fg, fg_rect *rect)
	int fg_get_capture_window(fg_grabber *fg, fg_rect *rect)
	#int fg_check_control(fg_grabber *fg, fg_control_id control_id)
	#int fg_set_control(fg_grabber *fg, fg_control_id control_id, int value)
	#int fg_get_control(fg_grabber *fg, fg_control_id control_id)
	#int fg_default_controls(fg_grabber *fg)
	
	#fg_frame *fg_frame_new(fg_grabber *fg)
	#void fg_frame_release(fg_frame* fr)
	#void fg_frame_free(fg_frame *fr)
	#unsigned char *fg_frame_get_data(fg_frame *fr)
	#int fg_frame_get_size(fg_frame *fr)
	#int fg_frame_get_width(fg_frame *fr)
	#int fg_frame_get_height(fg_frame *fr)
	#void fg_debug_frame(fg_frame *fr, FILE *fp)
	#int fg_frame_copy(fg_frame *src, fg_frame *dst)
	#fg_frame *fg_frame_clone(fg_frame *fr)

	
	
	
	
	
	
