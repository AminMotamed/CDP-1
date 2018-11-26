/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis
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

#include "config.h"

#include <gegl.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpconfig/gimpconfig.h"

#include "core-types.h"

#include "base/tile-manager.h"

#include "config/gimpcoreconfig.h"

#include "gimp.h"
#include "gimpbuffer.h"
#include "gimpchannel.h"
#include "gimpcontext.h"
#include "gimpimage.h"
#include "gimpimage-colormap.h"
#include "gimpimage-new.h"
#include "gimpimage-undo.h"
#include "gimplayer.h"
#include "gimptemplate.h"

#include "gimp-intl.h"


GimpTemplate *
gimp_image_new_get_last_template (Gimp      *gimp,
                                  GimpImage *image)
{
  GimpTemplate *template;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (image == NULL || GIMP_IS_IMAGE (image), NULL);

  template = gimp_template_new ("image new values");

  if (image)
    {
      gimp_config_sync (G_OBJECT (gimp->config->default_image),
                        G_OBJECT (template), 0);
      gimp_template_set_from_image (template, image);
    }
  else
    {
      gimp_config_sync (G_OBJECT (gimp->image_new_last_template),
                        G_OBJECT (template), 0);
    }

  return template;
}

void
gimp_image_new_set_last_template (Gimp         *gimp,
                                  GimpTemplate *template)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));
  g_return_if_fail (GIMP_IS_TEMPLATE (template));

  gimp_config_sync (G_OBJECT (template),
                    G_OBJECT (gimp->image_new_last_template), 0);
}

GimpImage *
gimp_image_new_from_template (Gimp         *gimp,
                              GimpTemplate *template,
                              GimpContext  *context)
{
  GimpImage     *image;
  GimpLayer     *layer;
  GimpImageType  type;
  gint           width, height;
  const gchar   *comment;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (GIMP_IS_TEMPLATE (template), NULL);
  g_return_val_if_fail (GIMP_IS_CONTEXT (context), NULL);

  image = gimp_create_image (gimp,
                             gimp_template_get_width (template),
                             gimp_template_get_height (template),
                             gimp_template_get_image_type (template),
                             FALSE);

  gimp_image_undo_disable (image);

  comment = gimp_template_get_comment (template);

  if (comment)
    {
      GimpParasite *parasite;

      parasite = gimp_parasite_new ("gimp-comment",
                                    GIMP_PARASITE_PERSISTENT,
                                    strlen (comment) + 1,
                                    comment);
      gimp_image_parasite_attach (image, parasite);
      gimp_parasite_free (parasite);
    }

  gimp_image_set_resolution (image,
                             gimp_template_get_resolution_x (template),
                             gimp_template_get_resolution_y (template));
  gimp_image_set_unit (image, gimp_template_get_resolution_unit (template));

  width  = gimp_image_get_width (image);
  height = gimp_image_get_height (image);

  switch (gimp_template_get_fill_type (template))
    {
    case GIMP_TRANSPARENT_FILL:
      type = ((gimp_template_get_image_type (template) == GIMP_RGB) ?
              GIMP_RGBA_IMAGE : GIMP_GRAYA_IMAGE);
      break;
    default:
      type = ((gimp_template_get_image_type (template) == GIMP_RGB) ?
              GIMP_RGB_IMAGE : GIMP_GRAY_IMAGE);
      break;
    }

  layer = gimp_layer_new (image, width, height, type,
                          _("Background"),
                          GIMP_OPACITY_OPAQUE, GIMP_NORMAL_MODE);

  gimp_drawable_fill_by_type (GIMP_DRAWABLE (layer),
                              context, gimp_template_get_fill_type (template));

  gimp_image_add_layer (image, layer, NULL, 0, FALSE);

  gimp_image_undo_enable (image);
  gimp_image_clean_all (image);

  gimp_create_display (gimp, image, gimp_template_get_unit (template), 1.0);

  g_object_unref (image);

  return image;
}

GimpImage *
gimp_image_new_from_drawable (Gimp         *gimp,
                              GimpDrawable *drawable)
{
  GimpItem          *item;
  GimpImage         *image;
  GimpImage         *new_image;
  GimpLayer         *new_layer;
  GType              new_type;
  gint               off_x, off_y;
  GimpImageBaseType  type;
  gdouble            xres;
  gdouble            yres;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (GIMP_IS_DRAWABLE (drawable), NULL);

  item  = GIMP_ITEM (drawable);
  image = gimp_item_get_image (item);

  type = GIMP_IMAGE_TYPE_BASE_TYPE (gimp_drawable_type (drawable));

  new_image = gimp_create_image (gimp,
                                 gimp_item_get_width  (item),
                                 gimp_item_get_height (item),
                                 type, TRUE);
  gimp_image_undo_disable (new_image);

  if (type == GIMP_INDEXED)
    gimp_image_set_colormap (new_image,
                             gimp_image_get_colormap (image),
                             gimp_image_get_colormap_size (image),
                             FALSE);

  gimp_image_get_resolution (image, &xres, &yres);
  gimp_image_set_resolution (new_image, xres, yres);
  gimp_image_set_unit (new_image, gimp_image_get_unit (image));

  if (GIMP_IS_LAYER (drawable))
    new_type = G_TYPE_FROM_INSTANCE (drawable);
  else
    new_type = GIMP_TYPE_LAYER;

  new_layer = GIMP_LAYER (gimp_item_convert (GIMP_ITEM (drawable),
                                             new_image, new_type));

  gimp_object_set_name (GIMP_OBJECT (new_layer),
                        gimp_object_get_name (drawable));

  gimp_item_get_offset (GIMP_ITEM (new_layer), &off_x, &off_y);
  gimp_item_translate (GIMP_ITEM (new_layer), -off_x, -off_y, FALSE);
  gimp_item_set_visible (GIMP_ITEM (new_layer), TRUE, FALSE);
  gimp_item_set_linked (GIMP_ITEM (new_layer), FALSE, FALSE);
  gimp_layer_set_mode (new_layer, GIMP_NORMAL_MODE, FALSE);
  gimp_layer_set_opacity (new_layer, GIMP_OPACITY_OPAQUE, FALSE);
  gimp_layer_set_lock_alpha (new_layer, FALSE, FALSE);

  gimp_image_add_layer (new_image, new_layer, NULL, 0, TRUE);

  gimp_image_undo_enable (new_image);

  return new_image;
}

GimpImage *
gimp_image_new_from_component (Gimp            *gimp,
                               GimpImage       *image,
                               GimpChannelType  component)
{
  GimpImage   *new_image;
  GimpChannel *channel;
  GimpLayer   *layer;
  const gchar *desc;
  gdouble      xres;
  gdouble      yres;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (GIMP_IS_IMAGE (image), NULL);

  new_image = gimp_create_image (gimp,
                                 gimp_image_get_width  (image),
                                 gimp_image_get_height (image),
                                 GIMP_GRAY, TRUE);

  gimp_image_undo_disable (new_image);

  gimp_image_get_resolution (image, &xres, &yres);
  gimp_image_set_resolution (new_image, xres, yres);
  gimp_image_set_unit (new_image, gimp_image_get_unit (image));

  channel = gimp_channel_new_from_component (image, component, NULL, NULL);

  layer = GIMP_LAYER (gimp_item_convert (GIMP_ITEM (channel),
                                         new_image, GIMP_TYPE_LAYER));
  g_object_unref (channel);

  gimp_enum_get_value (GIMP_TYPE_CHANNEL_TYPE, component,
                       NULL, NULL, &desc, NULL);
  gimp_object_take_name (GIMP_OBJECT (layer),
                         g_strdup_printf (_("%s Channel Copy"), desc));

  gimp_image_add_layer (new_image, layer, NULL, 0, TRUE);

  gimp_image_undo_enable (new_image);

  return new_image;
}

GimpImage *
gimp_image_new_from_buffer (Gimp       *gimp,
                            GimpImage  *invoke,
                            GimpBuffer *paste)
{
  GimpImage     *image;
  GimpLayer     *layer;
  GimpImageType  type;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (invoke == NULL || GIMP_IS_IMAGE (invoke), NULL);
  g_return_val_if_fail (GIMP_IS_BUFFER (paste), NULL);

  switch (tile_manager_bpp (paste->tiles))
    {
    case 1: type = GIMP_GRAY_IMAGE;  break;
    case 2: type = GIMP_GRAYA_IMAGE; break;
    case 3: type = GIMP_RGB_IMAGE;   break;
    case 4: type = GIMP_RGBA_IMAGE;  break;
    default:
      g_return_val_if_reached (NULL);
      break;
    }

  /*  create a new image  (always of type GIMP_RGB)  */
  image = gimp_create_image (gimp,
                             gimp_buffer_get_width  (paste),
                             gimp_buffer_get_height (paste),
                             GIMP_IMAGE_TYPE_BASE_TYPE (type),
                             TRUE);
  gimp_image_undo_disable (image);

  if (invoke)
    {
      gdouble xres;
      gdouble yres;

      gimp_image_get_resolution (invoke, &xres, &yres);
      gimp_image_set_resolution (image, xres, yres);
      gimp_image_set_unit (image, gimp_image_get_unit (invoke));
    }

  layer = gimp_layer_new_from_tiles (paste->tiles, image, type,
                                     _("Pasted Layer"),
                                     GIMP_OPACITY_OPAQUE, GIMP_NORMAL_MODE);

  gimp_image_add_layer (image, layer, NULL, 0, TRUE);

  gimp_image_undo_enable (image);

  return image;
}

GimpImage *
gimp_image_new_from_pixbuf (Gimp        *gimp,
                            GdkPixbuf   *pixbuf,
                            const gchar *layer_name)
{
  GimpImageType  image_type;
  GimpImage     *new_image;
  GimpLayer     *layer;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (GDK_IS_PIXBUF (pixbuf), NULL);

  switch (gdk_pixbuf_get_n_channels (pixbuf))
    {
    case 1: image_type = GIMP_GRAY_IMAGE;  break;
    case 2: image_type = GIMP_GRAYA_IMAGE; break;
    case 3: image_type = GIMP_RGB_IMAGE;   break;
    case 4: image_type = GIMP_RGBA_IMAGE;  break;
      break;

    default:
      g_return_val_if_reached (NULL);
      break;
    }

  new_image = gimp_create_image (gimp,
                                 gdk_pixbuf_get_width  (pixbuf),
                                 gdk_pixbuf_get_height (pixbuf),
                                 GIMP_IMAGE_TYPE_BASE_TYPE (image_type),
                                 FALSE);

  gimp_image_undo_disable (new_image);

  layer = gimp_layer_new_from_pixbuf (pixbuf, new_image, image_type,
                                      layer_name,
                                      GIMP_OPACITY_OPAQUE, GIMP_NORMAL_MODE);

  gimp_image_add_layer (new_image, layer, NULL, 0, TRUE);

  gimp_image_undo_enable (new_image);

  return new_image;
}
