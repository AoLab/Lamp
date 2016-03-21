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

static void on_OnI_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/OnI/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/OnI")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		return;
	}

	/*
	 * We have OnI function with GET method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_GET) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		return;
	}
}

void route_init(SoupServer *server)
{
	soup_server_add_handler(server, "/Lamp/OnI",
			on_OnI_event_callback, NULL, NULL);
}
