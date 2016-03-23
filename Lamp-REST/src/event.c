/*
 * In The Name Of God
 * ========================================
 * [] File Name : event.c
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

#include "util.h"

static kaa_error_t event_listeners_callback(void *context,
		const kaa_endpoint_id listeners[], size_t listeners_count)
{
	printf("Event Listerners: %zd\n", listeners_count);

	kaa_error_t error_code;

	/* Restore interval parameter */
	int64_t *interval_ptr = context;

	/* Create and send an event */

	/* TODO: replace with lamp event */
	kaa_led_event_class_family_led_on_event_t *led_on_request =
		kaa_led_event_class_family_led_on_event_create();

	error_code = kaa_event_manager_send_kaa_led_event_class_family_led_on_event(
			kaa_client_get_context(kaa_client)->event_manager
			, led_on_request
			, NULL);
	KAA_RETURN_IF_ERROR(error_code, "Failed to send LEDOnEvent");

	led_on_request->destroy(led_on_request);
	free(context);

	return KAA_ERR_NONE;
}

static kaa_error_t event_listeners_request_failed(void *context)
{
	printf("Event Listeners founding faild :(\n");

	return KAA_ERR_NONE;
}

void request_OnI_event(int64_t interval)
{
	kaa_error_t error_code;

	/* Store interval on heap for future processing */

	int64_t *interval_ptr = malloc(sizeof(int64_t));

	/* Find endpoint by event FQDN */

	/* TODO: replace with lamp FQDN */
	const char *fqns[] = {"ir.ac.aut.aolab.lamp"};

	kaa_event_listeners_callback_t callback = {interval_ptr, event_listeners_callback, event_listeners_request_failed};

	error_code = kaa_event_manager_find_event_listeners(kaa_client_get_context(kaa_client)->event_manager
			, fqns
			, 1
			, &callback);
	KAA_EXIT_IF_ERROR(error_code, "Failed to attach event listener");
}
