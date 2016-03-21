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

#include "server.h"
#include "route.h"

int main(int argc, char *argv[])
{
	SoupServer *server;

	g_printf("");

	server_init(&server);
	route_init(server);
}
