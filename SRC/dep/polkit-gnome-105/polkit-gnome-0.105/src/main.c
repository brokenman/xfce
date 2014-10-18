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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <string.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <polkitagent/polkitagent.h>

#include "polkitgnomelistener.h"

/* the Authority */
static PolkitAuthority *authority = NULL;

/* the session we are servicing */
static PolkitSubject *session = NULL;

static GDBusConnection *session_bus_connection = NULL;

int
main (int argc, char **argv)
{
  gint ret;
  GMainLoop *loop;
  PolkitAgentListener *listener;
  GError *error;

  g_type_init ();
  gtk_init (&argc, &argv);

  loop = NULL;
  authority = NULL;
  listener = NULL;
  session = NULL;
  ret = 1;

  bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);
#if HAVE_BIND_TEXTDOMAIN_CODESET
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif
  textdomain (GETTEXT_PACKAGE);

  loop = g_main_loop_new (NULL, FALSE);

  error = NULL;
  authority = polkit_authority_get_sync (NULL /* GCancellable* */, &error);
  if (authority == NULL)
    {
      g_warning ("Error getting authority: %s", error->message);
      g_error_free (error);
      goto out;
    }

  listener = polkit_gnome_listener_new ();

  error = NULL;
  session = polkit_unix_session_new_for_process_sync (getpid (), NULL, &error);
  if (error != NULL)
    {
      g_warning ("Unable to determine the session we are in: %s", error->message);
      g_error_free (error);
      goto out;
    }

  error = NULL;
  if (!polkit_agent_listener_register (listener,
                                       POLKIT_AGENT_REGISTER_FLAGS_NONE,
                                       session,
                                       "/org/gnome/PolicyKit1/AuthenticationAgent",
                                       NULL, /* GCancellable */
                                       &error))
    {
      g_printerr ("Cannot register authentication agent: %s\n", error->message);
      g_error_free (error);
      goto out;
    }

  /* Poor mans session management - connect to the session bus
   * so we get killed when it goes away
   */
  session_bus_connection = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, NULL);

  g_main_loop_run (loop);

  ret = 0;

 out:
  if (authority != NULL)
    g_object_unref (authority);
  if (session != NULL)
    g_object_unref (session);
  if (listener != NULL)
    g_object_unref (listener);
  if (loop != NULL)
    g_main_loop_unref (loop);

  return ret;
}
