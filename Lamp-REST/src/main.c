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

int main(int argc, char *argv[])
{
	SoupServer *server;
	GMainLoop *loop;

	server_init(&server);
	route_init(server);

	/* Create main event loop */
	loop = g_main_loop_new(NULL, true);
	g_main_loop_run(loop);
	g_main_loop_unref(loop);

	return 0;
}
