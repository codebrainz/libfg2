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

#include "libfg2.h"
#include "gtkcamera.h"

struct _GtkCameraPrivate
{
    fg_grabber *fg;
    fg_frame *frame;
};

static void gtk_camera_finalize            (GObject *object);

G_DEFINE_TYPE(GtkCamera, gtk_camera, GTK_TYPE_IMAGE)


static void gtk_camera_class_init(GtkCameraClass *klass)
{
    GObjectClass *g_object_class;

    g_object_class = G_OBJECT_CLASS(klass);

    g_object_class->finalize = gtk_camera_finalize;

    g_type_class_add_private((gpointer)klass, sizeof(GtkCameraPrivate));
}


static void gtk_camera_finalize(GObject *object)
{
    GtkCamera *self;

    g_return_if_fail(object != NULL);
    g_return_if_fail(GTK_IS_CAMERA(object));

    self = GTK_CAMERA(object);

    if (self->priv->frame != NULL)
        fg_frame_free(self->priv->frame);

    if (self->priv->fg != NULL)
        fg_close(self->priv->fg);

    G_OBJECT_CLASS(gtk_camera_parent_class)->finalize(object);
}


static void gtk_camera_init(GtkCamera *self)
{
    self->priv = G_TYPE_INSTANCE_GET_PRIVATE(self,
        GTK_TYPE_CAMERA, GtkCameraPrivate);
    self->priv->fg = NULL;
    self->priv->frame = NULL;
}


static gboolean on_idle(GtkCamera *self)
{
    GdkPixbuf *pixbuf;

    g_return_val_if_fail(GTK_IS_CAMERA(self), TRUE);

    fg_grab_frame(self->priv->fg, self->priv->frame);

    pixbuf = fg_frame_to_gdk_pixbuf(self->priv->frame);

    gtk_image_set_from_pixbuf(GTK_IMAGE(self), pixbuf);

    gdk_pixbuf_unref(pixbuf);

    return TRUE;
}


GtkWidget *gtk_camera_new(const gchar *device, guint input)
{
    GtkCamera *self;

    g_return_val_if_fail(device != NULL, NULL);

    self = g_object_new(GTK_TYPE_CAMERA, NULL);

    self->priv->fg = fg_open(device);
    self->priv->frame = fg_frame_new(self->priv->fg);

    g_idle_add((GSourceFunc) on_idle, self);

    return GTK_WIDGET(self);
}

