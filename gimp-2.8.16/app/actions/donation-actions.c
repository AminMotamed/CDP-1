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

#include "donation-actions.h"

#include "gimp-intl.h"


static const GimpActionEntry donation_actions[] =
{
  { "donation-menu", NULL, NC_("donation-action", "Donation") },

};


void
donation_actions_setup (GimpActionGroup *group)
{
  gimp_action_group_add_actions (group, "donation-action",
                                 donation_actions,
                                 G_N_ELEMENTS (donation_actions));
}

void
donation_actions_update (GimpActionGroup *group,
                     gpointer         data)
{
}
