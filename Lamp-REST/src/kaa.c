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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include <kaa/kaa_error.h>
#include <kaa/platform/kaa_client.h>
#include <kaa/utilities/kaa_log.h>
#include <kaa/gen/kaa_led_event_class_family.h>
#include <kaa/kaa_event.h>
#include <kaa/platform/ext_event_listeners_callback.h>

#include "user.h"

static kaa_client_t *kaa_client;


void kaa_init(void)
{
	kaa_error_t error_code;
	
	/* Build Kaa client */

	error_code = kaa_client_create(&kaa_client, NULL);
	KAA_RETURN_IF_ERROR(error_code, "Failed create Kaa client");

	/* Attach to user :) */
	
	attach_endpoint_to_user(
			kaa_client_get_context(kaa_client)->user_manager,
			"Parham",
			"");

	error_code = kaa_client_start(kaa_client, NULL, NULL, 0);
	KAA_RETURN_IF_ERROR(error_code, "Failed to start Kaa main loop");

	kaa_client_destroy(kaa_client);
	return error_code;
}
