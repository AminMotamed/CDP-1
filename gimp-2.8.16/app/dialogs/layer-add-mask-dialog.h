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

#ifndef __LAYER_ADD_MASK_DIALOG_H__
#define __LAYER_ADD_MASK_DIALOG_H__


typedef struct _LayerAddMaskDialog LayerAddMaskDialog;

struct _LayerAddMaskDialog
{
  GtkWidget       *dialog;

  GimpLayer       *layer;
  GimpAddMaskType  add_mask_type;
  GimpChannel     *channel;
  gboolean         invert;
};


LayerAddMaskDialog * layer_add_mask_dialog_new (GimpLayer       *layer,
                                                GimpContext     *context,
                                                GtkWidget       *parent,
                                                GimpAddMaskType  add_mask_type,
                                                gboolean         invert);


#endif /* __LAYER_ADD_MASK_DIALOG_H__ */
