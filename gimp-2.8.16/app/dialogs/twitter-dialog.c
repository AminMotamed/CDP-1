/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Modification :: Ajout d'un nouveau twitter-dialog.c qui est une boîte de 
 * dialogue contenant une description de Twitter
 */

#include "config.h"

#include <string.h>

#include <gtk/gtk.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpmath/gimpmath.h"
#include "libgimpwidgets/gimpwidgets.h"

#include "dialogs-types.h"

#include "core/gimp.h"
#include "core/gimpcontext.h"

#include "pdb/gimppdb.h"

#include "twitter.h"
#include "twitter-dialog.h"

#include "gimp-intl.h"

typedef struct
{
  GtkWidget   *dialog;
  int 				state;
} GimpTwitterDialog;

static GdkPixbuf * twitter_dialog_load_logo     (void);

GtkWidget *
twitter_dialog_create (GimpContext *context)
{
  static GimpTwitterDialog dialog;
  dialog.state = 0;

  g_return_val_if_fail (GIMP_IS_CONTEXT (context), NULL);

  if (! dialog.dialog)
    {
      GtkWidget *widget;
      GdkPixbuf *pixbuf;

      pixbuf = twitter_dialog_load_logo ();

      widget = g_object_new (GTK_TYPE_ABOUT_DIALOG,
                             "role",               "gimp-twitter",
                             "window-position",    GTK_WIN_POS_CENTER,
                             "title",              _("Social Network"),
                             "program-name",       TWITTER_ACRONYM,
                             "comments",           TWITTER_DESCRIPTION,
                             "logo",               pixbuf,
                             "website",            TWITTER_WEBSITE,
                             "website-label",      TWITTER_WEBSITE_LABEL,
                             NULL);

      if (pixbuf)
        g_object_unref (pixbuf);

      dialog.dialog = widget;

      g_object_add_weak_pointer (G_OBJECT (widget), (gpointer) &dialog.dialog);

      g_signal_connect (widget, "response",
                        G_CALLBACK (gtk_widget_destroy),
                        NULL);
	    dialog.state = 1;
    }

	if(dialog.state)
    printf("La boîte de dialogue Twitter s'est bien déroulée.\n");
  else
    printf("Erreur avec la boîte de dialogue Twitter (cf twitter-dialog.c).\n");
  gtk_window_present (GTK_WINDOW (dialog.dialog));

  return dialog.dialog;
}

static GdkPixbuf *
twitter_dialog_load_logo (void)
{
  GdkPixbuf *pixbuf;
  gchar     *filename;

  filename = g_build_filename (gimp_data_directory (), "images",
                               "twitter-logo.png",
                               NULL);

  pixbuf = gdk_pixbuf_new_from_file (filename, NULL);
  g_free (filename);

  return pixbuf;
}
