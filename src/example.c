/* 
 * Simplest example for libfg2 to capture a JPEG image. Requires jpeglib.
 * 
 * I think this is as few lines as I can use to do something useful.
 */

#include <stdlib.h>
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
