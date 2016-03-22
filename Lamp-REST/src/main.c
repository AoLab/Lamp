/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
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
#include <stdbool.h>

#include "server.h"
#include "route.h"

static gpointer kaa_thread(gpointer data) {
	return NULL;
}

int main(int argc, char *argv[])
{
	/* Kaa */

	GThread *kaa;
	
	kaa = g_thread_new("Kaa", kaa_thread, NULL);

	/* REST */
	
	SoupServer *server;
	GMainLoop *rest_loop;

	rest_server_init(&server);
	rest_route_init(server);

	/* Create main event loop */
	rest_loop = g_main_loop_new(NULL, true);
	g_main_loop_run(rest_loop);
	g_main_loop_unref(rest_loop);

	return 0;
}
