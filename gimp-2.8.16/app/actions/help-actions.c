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

#include "libgimpwidgets/gimpwidgets.h"

#include "actions-types.h"

#include "widgets/gimpactiongroup.h"
#include "widgets/gimphelp-ids.h"

#include "help-actions.h"
#include "help-commands.h"

#include "gimp-intl.h"


static const GimpActionEntry help_actions[] =
{
  { "help-menu", NULL, NC_("help-action", "_Help") },

  { "help-exemple02", NULL,
    NC_("help-action", "Exemple-Action"), "F2",
    NC_("help-action", "La description de l'entrée Exemple-Action"),
    G_CALLBACK (help_help_cmd_callback),
    GIMP_HELP_EXEMPLE02 },
    
  { "help-help", GTK_STOCK_HELP,
    NC_("help-action", "_Help"), "F1",
    NC_("help-action", "Open the GIMP user manual"),
    G_CALLBACK (help_help_cmd_callback),
    GIMP_HELP_HELP },

  /* Modification :: ajout d'un élément dans Help > Twitter
   * Nom de l'élément : Twitter
   * Appel de la fonction : help_twitter_cmd_callback
   * id : GIMP_HELP_TWITTER (à voir widgets/gimphelp-ids.h)
   */ 
  { "help-twitter", GTK_STOCK_HELP,
    NC_("help-action", "_Twitter"), "F1",
    NC_("help-action", "Open Twitter"),
    G_CALLBACK (help_help_cmd_callback),
    GIMP_HELP_TWITTER },


  { "help-context-help", GTK_STOCK_HELP,
    NC_("help-action", "_Context Help"), "<shift>F1",
    NC_("help-action", "Show the help for a specific user interface item"),
    G_CALLBACK (help_context_help_cmd_callback),
    GIMP_HELP_HELP_CONTEXT }
};


void
help_actions_setup (GimpActionGroup *group)
{
  gimp_action_group_add_actions (group, "help-action",
                                 help_actions,
                                 G_N_ELEMENTS (help_actions));
}

void
help_actions_update (GimpActionGroup *group,
                     gpointer         data)
{
}
