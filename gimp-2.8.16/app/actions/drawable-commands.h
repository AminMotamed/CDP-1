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

#ifndef __DRAWABLE_COMMANDS_H__
#define __DRAWABLE_COMMANDS_H__


void   drawable_equalize_cmd_callback       (GtkAction *action,
                                             gpointer   data);
void   drawable_invert_cmd_callback         (GtkAction *action,
                                             gpointer   data);
void   drawable_levels_stretch_cmd_callback (GtkAction *action,
                                             gpointer   data);
void   drawable_offset_cmd_callback         (GtkAction *action,
                                             gpointer   data);

void   drawable_linked_cmd_callback         (GtkAction *action,
                                             gpointer   data);
void   drawable_visible_cmd_callback        (GtkAction *action,
                                             gpointer   data);
void   drawable_lock_content_cmd_callback   (GtkAction *action,
                                             gpointer   data);

void   drawable_flip_cmd_callback           (GtkAction *action,
                                             gint       value,
                                             gpointer   data);
void   drawable_rotate_cmd_callback         (GtkAction *action,
                                             gint       value,
                                             gpointer   data);


#endif /* __DRAWABLE_COMMANDS_H__ */
