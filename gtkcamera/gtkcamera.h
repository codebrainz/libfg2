/*
 * gtkcamera.h
 *
 * Copyright 2017 Matthew Brush <mbrush@codebrainz.ca>
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


#ifndef GTK_CAMERA_H
#define GTK_CAMERA_H

#include <gtk/gtk.h>

G_BEGIN_DECLS


#define GTK_TYPE_CAMERA             (gtk_camera_get_type())
#define GTK_CAMERA(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_CAMERA, GtkCamera))
#define GTK_CAMERA_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_CAMERA, GtkCameraClass))
#define GTK_IS_CAMERA(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_CAMERA))
#define GTK_IS_CAMERA_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_TYPE_CAMERA))
#define GTK_CAMERA_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_CAMERA, GtkCameraClass))

typedef struct _GtkCamera           GtkCamera;
typedef struct _GtkCameraClass      GtkCameraClass;
typedef struct _GtkCameraPrivate    GtkCameraPrivate;

struct _GtkCamera
{
    GtkImage parent;
    /* add your public declarations here */

    GtkCameraPrivate *priv;
};

struct _GtkCameraClass
{
    GtkImageClass parent_class;
};


GType       gtk_camera_get_type   (void);
GtkWidget  *gtk_camera_new        (const gchar *device, 
                                   guint        input);
gchar      *gtk_camera_get_device (GtkCamera   *camera);
void        gtk_camera_set_device (GtkCamera   *camera,
                                   const gchar *device);
guint       gtk_camera_get_input  (GtkCamera   *camera);
void        gtk_camera_set_input  (GtkCamera   *camera,
                                   guint        input);


G_END_DECLS

#endif /* GTK_CAMERA_H */
