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

#include "config.h"

#include <gtk/gtk.h>

#include "actions-types.h"

#include "core/gimp.h"

#include "actions.h"
#include "config-commands.h"


/*  public functions  */

void
config_use_gegl_cmd_callback (GtkAction *action,
                             gpointer   data)
{
  GtkToggleAction *toggle_action = GTK_TOGGLE_ACTION (action);
  Gimp            *gimp   = NULL;
  return_if_no_gimp (gimp, data);

  g_object_set (gimp->config,
                "use-gegl", gtk_toggle_action_get_active (toggle_action),
                NULL);
}
