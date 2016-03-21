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

#include "server.h"
#include "config.h"

void server_init(SoupServer **server)
{
	GError *error = NULL;
	char server_name[256];

	sprinf(server_name, "Lamp-REST-%d.%d", Lamp_REST_MAJ_VER,
			Lamp_REST_MIN_VER);

	*server = soup_server_new(SOUP_SERVER_SERVER_HEADER,
		server_name, NULL);
	soup_server_listen_all(*server, 1373,
		SOUP_SERVER_LISTEN_IPV4_ONLY, &error);
	if (error) {
		g_critical("Unable to create soup server: %s\n",
				error->message);
		exit(1);
	}
}
