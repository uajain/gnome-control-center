/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2020 Endless Mobile
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Umang Jain <umang@endlessm.com>
 */

#include "list-box-helper.h"
#include "cc-metrics-panel.h"
#include "cc-metrics-resources.h"
#include "cc-util.h"
#include "shell/cc-application.h"

#include <glib/gi18n.h>

struct _CcMetricsPanel
{
  CcPanel     parent_instance;

  GtkListBox *metrics_list_box;
  GtkSwitch  *enable_metrics_switch;
};

CC_PANEL_REGISTER (CcMetricsPanel, cc_metrics_panel)

static void
cc_metrics_panel_finalize (GObject *object)
{
  CcMetricsPanel *self = CC_METRICS_PANEL (object);

  G_OBJECT_CLASS (cc_metrics_panel_parent_class)->finalize (object);
}

static void
cc_metrics_panel_class_init (CcMetricsPanelClass *klass)
{
  GObjectClass *oclass = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  oclass->finalize = cc_metrics_panel_finalize;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/control-center/metrics/cc-metrics-panel.ui");

  gtk_widget_class_bind_template_child (widget_class, CcMetricsPanel, metrics_list_box);
  gtk_widget_class_bind_template_child (widget_class, CcMetricsPanel, enable_metrics_switch);
}

static void
cc_metrics_panel_init (CcMetricsPanel *self)
{
  g_resources_register (cc_metrics_get_resource ());

  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_list_box_set_header_func (self->metrics_list_box,
                                cc_list_box_update_header_func,
                                NULL, NULL);
}

static gboolean
on_reset_metrics_id_button_clicked (GtkButton     *button,
                                    CcMetricsPanel *self)
{
}

static gboolean
on_attribution_label_link (GtkLinkButton       *link_button,
                           CcMetricsPanel      *self)
{
  const gchar *uri = gtk_link_button_get_uri (link_button);

  if (g_strcmp0 (uri, "attribution-link") != 0)
    return FALSE;

  return cc_util_show_endless_terms_of_use (GTK_WIDGET (link_button));
}
