/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 12-03-2016
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
#include <kaa/kaa_status.h>
#include <kaa/platform/kaa_client.h>
#include <kaa/utilities/kaa_log.h>

#include "util.h"
#include "event.h"
#include "serial.h"
#include "notification.h"
#include "user.h"
#include "profile.h"
#include "config.h"
#include "log.h"

static kaa_client_t *kaa_client;

int main(int argc, char *argv[])
{
	log_global_create(1024, stderr);

	LOG_INFO(LOGGER, "Lamp-RPi started\n");
	kaa_error_t error_code;

	open_serial(LAMP_SERIAL_PATH);

	/* Build Kaa client */

	error_code = kaa_client_create(&kaa_client, NULL);
	KAA_RETURN_IF_ERROR(error_code, "Failed create Kaa client");

	/* Build notification related things */

	error_code = kaa_notification_register(
			kaa_client_get_context(
				kaa_client)->notification_manager);
	KAA_RETURN_IF_ERROR(error_code, "Failed to register notification");

	/* Build event related things */

	error_code = kaa_event_register(
			kaa_client_get_context(kaa_client)->event_manager);
	KAA_RETURN_IF_ERROR(error_code, "Failed to register event");

	/* Attach to user :) */

	attach_endpoint_to_user(
			kaa_client_get_context(kaa_client)->user_manager,
			"Parham",
			"");

	/* Register our location */
	/*
	kaa_profile_register(
			kaa_client_get_context(kaa_client)->profile_manager);
	*/
	int i;
	kaa_digest_p hash = ((kaa_status_t *)(kaa_client_get_context(kaa_client)->status))->endpoint_public_key_hash;
	for (i = 0; i < sizeof(kaa_digest); i++)
		printf("%u ", hash[i]);
	printf("\n");

	error_code = kaa_client_start(kaa_client, NULL, NULL, 0);
	KAA_RETURN_IF_ERROR(error_code, "Failed to start Kaa main loop");

	kaa_client_destroy(kaa_client);
	return error_code;
}
