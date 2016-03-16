/*
 * In The Name Of God
 * ========================================
 * [] File Name : route.c
 *
 * [] Creation Date : 15-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#include <libsoup/soup.h>

#include "route.h"

static void on_on_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
}

void route_init(SoupServer *server)
{
	soup_server_add_handler(server, "/Lamp/on", on_on_event_callback, NULL, NULL);
}
