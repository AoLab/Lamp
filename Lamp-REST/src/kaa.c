/*
 * In The Name Of God
 * ========================================
 * [] File Name : kaa.c
 *
 * [] Creation Date : 23-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/
#include <glib.h>
#include <stdint.h>
#include <stdlib.h>

#include <kaa/kaa_error.h>
#include <kaa/platform/kaa_client.h>
#include <kaa/utilities/kaa_log.h>

#include "user.h"
#include "kaa.h"

kaa_client_t *kaa_client = NULL;

void kaa_start(void)
{
	g_message("Kaa client initiation started.");
	kaa_error_t error_code;
	
	/* Build Kaa client */

	error_code = kaa_client_create(&kaa_client, NULL);
	if (error_code) {
		g_critical("Failed to create Kaa client");
		abort();
	}
	g_message("Kaa client created susuccessfully");

	/* Attach to user :) */	
	
	attach_endpoint_to_user(
			kaa_client_get_context(kaa_client)->user_manager,
			"Parham",
			"");

	/* Start Kaa client */

	error_code = kaa_client_start(kaa_client, NULL, NULL, 0);
	if (error_code) {
		g_critical("Failed to start Kaa main loop");
		abort();
	}
	g_message("Kaa client started susuccessfully");

	kaa_client_destroy(kaa_client);
}
