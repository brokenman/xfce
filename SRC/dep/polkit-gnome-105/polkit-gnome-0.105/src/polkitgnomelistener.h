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

#ifndef __POLKIT_GNOME_LISTENER_H
#define __POLKIT_GNOME_LISTENER_H

#include <polkitagent/polkitagent.h>

G_BEGIN_DECLS

#define POLKIT_GNOME_TYPE_LISTENER          (polkit_gnome_listener_get_type())
#define POLKIT_GNOME_LISTENER(o)            (G_TYPE_CHECK_INSTANCE_CAST ((o), POLKIT_GNOME_TYPE_LISTENER, PolkitGnomeListener))
#define POLKIT_GNOME_LISTENER_CLASS(k)      (G_TYPE_CHECK_CLASS_CAST((k), POLKIT_GNOME_TYPE_LISTENER, PolkitGnomeListenerClass))
#define POLKIT_GNOME_LISTENER_GET_CLASS(o)  (G_TYPE_INSTANCE_GET_CLASS ((o), POLKIT_GNOME_TYPE_LISTENER, PolkitGnomeListenerClass))
#define POLKIT_GNOME_IS_LISTENER(o)         (G_TYPE_CHECK_INSTANCE_TYPE ((o), POLKIT_GNOME_TYPE_LISTENER))
#define POLKIT_GNOME_IS_LISTENER_CLASS(k)   (G_TYPE_CHECK_CLASS_TYPE ((k), POLKIT_GNOME_TYPE_LISTENER))

typedef struct _PolkitGnomeListener PolkitGnomeListener;
typedef struct _PolkitGnomeListenerClass PolkitGnomeListenerClass;

GType                 polkit_gnome_listener_get_type   (void) G_GNUC_CONST;
PolkitAgentListener  *polkit_gnome_listener_new        (void);

G_END_DECLS

#endif /* __POLKIT_GNOME_LISTENER_H */
