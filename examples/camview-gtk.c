#include <stdlib.h>
#include <gtk/gtk.h>

#include "libfg.h"

#define DEFAULT_WIDTH   320
#define DEFAULT_HEIGHT  240

static on_new_frame(GtkWidget *widget, gpointer data)
{
    
}

static GtkWidget *build_main_window(const gchar *device)
{
    gchar window_title[256];
    GtkWidget *window;
    
    snprintf(window_title, 255, "CamView - %s", device);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), title);
    
    gtk_window_set_default_size(
        GTK_WINDOW(window), 
        DEFAULT_WIDTH, 
        DEFAULT_HEIGHT);
    
    gtk_bin_add(GTK_BIN(window), image);
    
    
    
    
}

int main(int argc, char *argv[])
{
    
    
    
    return 0;
}
