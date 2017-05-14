/*
 * gtkcamera.c
 *
 * Copyright 2011 Matthew Brush <mbrush@codebrainz.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libfg2/libfg2-gdkpixbuf.h>
#include <gtkcamera/gtkcamera.h>


enum
{
  PROP_0,
  PROP_DEVICE,
  PROP_INPUT,
  PROP_LAST
};


enum
{
  SIGNAL_NEW_FRAME,
  SIGNAL_LAST
};


static guint gtk_camera_signals[SIGNAL_LAST] = { 0 };


struct _GtkCameraPrivate
{
  fg_grabber *fg;
  fg_frame *frame;
};


static void gtk_camera_finalize     (GObject      *object);
static void gtk_camera_get_property (GObject      *object,
                                     guint         property_id,
                                     GValue       *value,
                                     GParamSpec   *pspec);
static void gtk_camera_set_property (GObject      *object,
                                     guint         property_id,
                                     const GValue *value,
                                     GParamSpec   *pspec);



G_DEFINE_TYPE(GtkCamera, gtk_camera, GTK_TYPE_IMAGE)


static void
gtk_camera_class_init (GtkCameraClass *klass)
{
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS (klass);
  g_object_class->finalize = gtk_camera_finalize;
  g_object_class->get_property = gtk_camera_get_property;
  g_object_class->set_property = gtk_camera_set_property;

  g_type_class_add_private ((gpointer) klass, sizeof(GtkCameraPrivate));

  g_object_class_install_property (
    g_object_class,
    PROP_DEVICE,
    g_param_spec_string ("device",
                         "Device",
                         "Video capture device",
                         "/dev/video0",
                         G_PARAM_CONSTRUCT | G_PARAM_READWRITE));

  g_object_class_install_property (
    g_object_class,
    PROP_INPUT,
    g_param_spec_uint ("input",
                       "Input",
                       "Input number",
                       0, 64, 0,
                       G_PARAM_CONSTRUCT | G_PARAM_READWRITE));
  
  gtk_camera_signals[SIGNAL_NEW_FRAME] =
    g_signal_new ("new-frame",
                  G_TYPE_FROM_CLASS (g_object_class),
                  G_SIGNAL_RUN_LAST,
                  0,
                  NULL,
                  NULL,
                  g_cclosure_marshal_VOID__OBJECT,
                  G_TYPE_NONE,
                  1,
                  GDK_TYPE_PIXBUF);
}


static void
gtk_camera_finalize (GObject *object)
{
  GtkCamera *self;

  g_return_if_fail (object != NULL);
  g_return_if_fail (GTK_IS_CAMERA (object));

  self = GTK_CAMERA (object);

  if (self->priv->frame != NULL)
    fg_frame_free (self->priv->frame);

  if (self->priv->fg != NULL)
    fg_close (self->priv->fg);

  G_OBJECT_CLASS (gtk_camera_parent_class)->finalize (object);
}


static void
gtk_camera_init (GtkCamera *self)
{
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_TYPE_CAMERA, GtkCameraPrivate);
  self->priv->fg = NULL;
  self->priv->frame = NULL;
}


static gboolean
on_idle (GtkCamera *self)
{
  GdkPixbuf *pixbuf;

  g_return_val_if_fail (GTK_IS_CAMERA (self), TRUE);
  g_return_val_if_fail (self->priv->fg != NULL, FALSE);

  fg_grab_frame (self->priv->fg, self->priv->frame);
  pixbuf = fg_frame_to_gdk_pixbuf (self->priv->frame);

  if (pixbuf)
    {
      gtk_image_set_from_pixbuf (GTK_IMAGE (self), pixbuf);
      g_object_unref (pixbuf);
      g_signal_emit_by_name (self, 
                             "new-frame", 
                             gtk_image_get_pixbuf (GTK_IMAGE (self)), 
                             NULL);
    }

  return TRUE;
}


gchar *
gtk_camera_get_device (GtkCamera *self)
{
  gchar *device = NULL;
  g_object_get (G_OBJECT (self), "device", &device, NULL);
  return device;
}


void
gtk_camera_set_device (GtkCamera   *self,
                       const gchar *device)
{
  g_object_set (G_OBJECT (self), "device", device, NULL);
}


guint 
gtk_camera_get_input (GtkCamera *self)
{
  guint input = 0;
  g_object_get (G_OBJECT (self), "input", &input, NULL);
  return input;
}


void
gtk_camera_set_input (GtkCamera *self,
                      guint      input)
{
  g_object_set (G_OBJECT (self), "input", input, NULL);
}


GtkWidget *
gtk_camera_new (const gchar *device,
                guint input)
{
  GtkCamera *self;

  g_return_val_if_fail (device != NULL, NULL);

  self = g_object_new (GTK_TYPE_CAMERA, "device", device, "input", input, NULL);

  if (self->priv->fg)
    self->priv->frame = fg_frame_new (self->priv->fg);

  g_idle_add ((GSourceFunc) on_idle, self);

  return GTK_WIDGET (self);
}


static void
gtk_camera_get_property (GObject    *object,
                         guint       property_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
  GtkCamera *self = GTK_CAMERA (object);

  switch (property_id)
    {
    case PROP_DEVICE:
      g_value_set_string (value, self->priv->fg->device);
      break;
    case PROP_INPUT:
      g_value_set_uint (value, (guint) fg_get_input (self->priv->fg));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}


static void
gtk_camera_set_property (GObject      *object,
                         guint         property_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
  GtkCamera *self = GTK_CAMERA (object);

  switch (property_id)
    {
    case PROP_DEVICE:
      if (self->priv->fg)
        fg_close (self->priv->fg);
      self->priv->fg = fg_open (g_value_get_string (value));
      g_return_if_fail (self->priv->fg != NULL);
      g_object_notify (object, "device");
      break;
    case PROP_INPUT:
      if (self->priv->fg)
        fg_set_input (self->priv->fg, (gint) g_value_get_uint (value));
      g_object_notify (object, "input");
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}
