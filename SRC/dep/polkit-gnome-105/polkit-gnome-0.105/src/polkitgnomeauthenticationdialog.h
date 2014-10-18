/*
 * Copyright (C) 2009 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Author: David Zeuthen <davidz@redhat.com>
 */

#ifndef __POLKIT_GNOME_AUTHENTICATION_DIALOG_H
#define __POLKIT_GNOME_AUTHENTICATION_DIALOG_H

#include <gtk/gtk.h>
#include <polkit/polkit.h>

G_BEGIN_DECLS

#define POLKIT_GNOME_TYPE_AUTHENTICATION_DIALOG            (polkit_gnome_authentication_dialog_get_type ())
#define POLKIT_GNOME_AUTHENTICATION_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), POLKIT_GNOME_TYPE_AUTHENTICATION_DIALOG, PolkitGnomeAuthenticationDialog))
#define POLKIT_GNOME_AUTHENTICATION_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), POLKIT_GNOME_TYPE_AUTHENTICATION_DIALOG, PolkitGnomeAuthenticationDialogClass))
#define POLKIT_GNOME_IS_AUTHENTICATION_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), POLKIT_GNOME_TYPE_AUTHENTICATION_DIALOG))
#define POLKIT_GNOME_IS_AUTHENTICATION_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), POLKIT_GNOME_TYPE_AUTHENTICATION_DIALOG))

typedef struct _PolkitGnomeAuthenticationDialog        PolkitGnomeAuthenticationDialog;
typedef struct _PolkitGnomeAuthenticationDialogClass   PolkitGnomeAuthenticationDialogClass;
typedef struct _PolkitGnomeAuthenticationDialogPrivate PolkitGnomeAuthenticationDialogPrivate;

struct _PolkitGnomeAuthenticationDialog
{
  GtkDialog parent_instance;
  PolkitGnomeAuthenticationDialogPrivate *priv;
};

struct _PolkitGnomeAuthenticationDialogClass
{
  GtkDialogClass parent_class;
};

GType      polkit_gnome_authentication_dialog_get_type                      (void);
GtkWidget *polkit_gnome_authentication_dialog_new                           (const gchar    *action_id,
                                                                             const gchar    *vendor,
                                                                             const gchar    *vendor_url,
                                                                             const gchar    *icon_name,
                                                                             const gchar    *message_markup,
                                                                             PolkitDetails  *details,
                                                                             gchar         **users);
gchar     *polkit_gnome_authentication_dialog_get_selected_user             (PolkitGnomeAuthenticationDialog *dialog);
gboolean   polkit_gnome_authentication_dialog_run_until_user_is_selected    (PolkitGnomeAuthenticationDialog *dialog);
gchar     *polkit_gnome_authentication_dialog_run_until_response_for_prompt (PolkitGnomeAuthenticationDialog *dialog,
                                                                             const gchar                     *prompt,
                                                                             gboolean                         echo_chars,
                                                                             gboolean                        *was_cancelled,
                                                                             gboolean                        *new_user_selected);
gboolean   polkit_gnome_authentication_dialog_cancel                        (PolkitGnomeAuthenticationDialog *dialog);
void       polkit_gnome_authentication_dialog_indicate_error                (PolkitGnomeAuthenticationDialog *dialog);
void       polkit_gnome_authentication_dialog_set_info_message              (PolkitGnomeAuthenticationDialog *dialog,
                                                                             const gchar                     *info_markup);

G_END_DECLS

#endif /* __POLKIT_GNOME_AUTHENTICATION_DIALOG_H */
