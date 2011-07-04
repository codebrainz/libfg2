#include <stdlib.h>
#include <gtk/gtk.h>

#include "gtkcamera.h"

static on_new_frame(GtkWidget *widget, gpointer data)
{

}

static GtkWidget *build_main_window(const gchar *device, guint input)
{
    gchar window_title[256];
    GtkWidget *window;
    GtkWidget *image;

    snprintf(window_title, 255, "CamView GTK+ - %s", device);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), window_title);

    g_signal_connect(window, "destroy", gtk_main_quit, NULL);

    image = gtk_camera_new(device, input);

    gtk_container_add(GTK_CONTAINER(window), image);

    return window;
}

int main(int argc, char *argv[])
{
    GtkWidget *win;

    gtk_init(&argc, &argv);

    win = build_main_window("/dev/video0", 0);
    gtk_widget_show_all(win);

    gtk_main();

    return 0;
}
