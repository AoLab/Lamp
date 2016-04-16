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
#include <stdint.h>

#include <kaa/kaa_common.h>

#include "route.h"
#include "event.h"

static void on_OnI_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("Start handling request for %s", path);

	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/OnI/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/OnI")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		g_message("Invalid path: %s instead of /Lamp/OnI", path);
		return;
	}

	/*
	 * We have OnI function with GET method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_GET) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		g_message("Invalid method: %s instead of GET", msg->method);
		return;
	}

	if (query == NULL) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("Interval not found");
		return;
	}

	const char *interval_str = g_hash_table_lookup(query, "interval");

	if (interval_str == NULL) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("Interval not found");
		return;
	}

	int64_t interval = g_ascii_strtoll(interval_str, NULL, 10);

	request_OnI_event(interval);

	soup_message_set_status(msg, SOUP_STATUS_OK);
}

static void on_List_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("Start handling request for %s", path);

	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/List/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/List")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		g_message("Invalid path: %s instead of /Lamp/List", path);
		return;
	}

	/*
	 * We have List function with GET method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_GET) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		g_message("Invalid method: %s instead of GET", msg->method);
		return;
	}

	request_List_event();

	soup_message_set_status(msg, SOUP_STATUS_OK);
}

static void default_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("404 NotFound: %s", path);
	soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
}


void rest_route_init(SoupServer *server)
{
	soup_server_add_handler(server, "/Lamp/OnI",
			on_OnI_event_callback, NULL, NULL);
	
	soup_server_add_handler(server, "/Lamp/List",
			on_List_event_callback, NULL, NULL);

	soup_server_add_handler(server, NULL,
			default_event_callback, NULL, NULL);
}
