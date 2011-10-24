#include <stdlib.h>
#include <gtk/gtk.h>

#include "gtkcamera.h"


static gchar *device = NULL;
static gint   input = 0;


static GOptionEntry entries[] = {
  { "device", 'd', 0, G_OPTION_ARG_STRING, &device, "Video device", "DEV" },
  { "input", 'i', 0, G_OPTION_ARG_INT, &input, "Input number", "INP" },
  { NULL }
};


static on_new_frame(GtkWidget *widget, gpointer data)
{

}

static GtkWidget *build_main_window(const gchar *device, guint input)
{
  gchar   window_title[256];
  GtkWidget *window;
  GtkWidget *image;

  snprintf (window_title, 255, "CamView GTK+ - %s", device);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW (window), window_title);

  g_signal_connect (window, "destroy", gtk_main_quit, NULL);

  image = gtk_camera_new (device, input);

  gtk_container_add (GTK_CONTAINER (window), image);

  return window;
}

int main(int argc, char *argv[])
{
  GtkWidget      *win;
  GOptionContext *context;
  GError         *error = NULL;

  gtk_init(&argc, &argv);

  context = g_option_context_new ("- View V4L2 video");
  g_option_context_add_main_entries (context, entries, NULL);
  g_option_context_add_group (context, gtk_get_option_group (TRUE));

  if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_print ("unable to parse options: %s\n", error->message);
      g_error_free (error);
      exit (EXIT_FAILURE);
    }

  if (!device)
    device = g_strdup ("/dev/video0");

  win = build_main_window (device, input);
  gtk_widget_show_all (win);

  gtk_main();

  g_free (device);

  return 0;
}
