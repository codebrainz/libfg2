/**
 * \file    fg-udev.c
 * \brief   UDEV device namer for the frame grabber library.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#define DEV_DIR     "/dev"

/**
 * \brief   Checks if fn refers to a V4L2 capture device.
 * 
 * This function runs through a series of test; stat() first, then
 * checks if it's a character device, then checks that its major
 * number is 81 and minor number is between 0 and 255, and then checks
 * if the device can be open, then checks if the device supports
 * video capture.
 * 
 * \return  1 if the device is a frame grabber, 0 if not.
 */
int is_frame_grabber(const char *fn)
{
    int fd, maj, min;
    struct stat st;
    struct v4l2_capability cap;
    
    // file exists
    if (stat(fn, &st) == -1)
        return 0;
    
    // is character device
    if (!S_ISCHR(st.st_mode))
        return 0;
    
    // has major num 81 and minor num >= 0 and <=255
    maj = major(st.st_rdev);
    min = minor(st.st_rdev);
    //fprintf(stderr, "Maj: %d, Min: %d\n", maj, min);
    if (maj != 81 || min < 0 || min > 255)
        return 0;
    
    // can open
    fd = open(fn, O_RDWR | O_NONBLOCK, 0);
    if (fd == -1)
        return 0;
    
    // can query capabilities
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
    {
        close(fd);
        return 0;
    }
    
    // supports video capture
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        close(fd);
        return 0;
    }
    
    // it's a valid device
    return 1;
}

/**
 * \brief   Find the next available device index number.
 * 
 * This function looks in DEV_DIR for all devices starting with
 * '/dev/fg', then it finds the next available id of those devices.
 * For example, if there exists /dev/fg0 and /dev/fg1, then this
 * function will return 2.
 * 
 * \return  0 or higher depending on devices found.
 */
int next_dev_index(void)
{
    int i, n, id;
    int used_ids[256] = {0};
    char fn[NAME_MAX] = {0};
    char match_fn[NAME_MAX] = {0};
    char *id_str;
    struct dirent **namelist;
    
    // Flag each used id in used_ids array.
    snprintf(match_fn, NAME_MAX-1, "%s/%s", DEV_DIR, "fg");
    n = scandir(DEV_DIR, &namelist, 0, alphasort);
    if (n < 0)
    {
        perror("scandir");
    }   
    else
    {
        while (n--)
        {
            snprintf(fn, NAME_MAX-1, "%s/%s", DEV_DIR, 
                namelist[n]->d_name);
                
            if (is_frame_grabber(fn))
            {
                if (strstr(fn, match_fn) != NULL)
                {
                    id_str = strpbrk(fn, "0123456789");
                    if (id_str != NULL)
                    {
                        id = atoi(id_str);
                        used_ids[id] = 1;
                    }
                }
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    
    // Find the first available id.
    for (i=0; i < 256; i++)
    {
        if (!used_ids[i])
            return i;
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    int next_id = -1;
    char new_fn[NAME_MAX] = {0};
    
    if ( argc < 2 || !is_frame_grabber(argv[1]) )
        exit(EXIT_FAILURE);
    
    next_id = next_dev_index();
    
    if (next_id < 0 || next_id > 255)
        exit(EXIT_FAILURE);
    
    snprintf(new_fn, NAME_MAX-1, "%s/%s%d", DEV_DIR, "fg", next_id);
    printf("%s\n", new_fn);
    
    return 0;
}
