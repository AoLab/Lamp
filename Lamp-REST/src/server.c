/*
 * In The Name Of God
 * ========================================
 * [] File Name : server.c
 *
 * [] Creation Date : 21-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#include <libsoup/soup.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>

#include "server.h"
#include "config.h"

void rest_server_init(SoupServer **server)
{
	GError *error = NULL;
	char server_name[256];

	g_sprintf(server_name, "Lamp-REST-%d.%d", Lamp_REST_MAJ_VER,
			Lamp_REST_MIN_VER);

#if SOUP_CHECK_VERSION(2, 48, 0)
	*server = soup_server_new(SOUP_SERVER_SERVER_HEADER,
		server_name, NULL);
	soup_server_listen_all(*server, 1373,
		SOUP_SERVER_LISTEN_IPV4_ONLY, &error);
#else
	*server = soup_server_new(SOUP_SERVER_SERVER_HEADER,
		server_name, SOUP_SERVER_PORT, 1373, NULL);
	soup_server_run_async(*server);
#endif
	if (error) {
		g_critical("Unable to create soup server: %s\n",
				error->message);
		exit(1);
	}
	g_message("Server created successfully");
}
