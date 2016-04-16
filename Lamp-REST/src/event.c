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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include <kaa/kaa_error.h>
#include <kaa/platform/kaa_client.h>
#include <kaa/utilities/kaa_log.h>
#include <kaa/gen/kaa_lamp_event_family.h>
#include <kaa/kaa_event.h>
#include <kaa/platform/ext_event_listeners_callback.h>

#include "kaa.h"

static kaa_error_t event_listeners_callback(void *context,
		const kaa_endpoint_id listeners[], size_t listeners_count)
{
	printf("Event Listerners: %zd\n", listeners_count);

	kaa_error_t error_code;
	int i, j;

	for (i = 0; i < listeners_count; i++) {
		for (j = 0; j < sizeof(kaa_endpoint_id); j++) {
			printf("%c ", listeners[i][j]);
		}
	}

	/* Restore interval parameter */
	int64_t *interval_ptr = context;

	/* Create and send an event */

	kaa_lamp_event_family_oni_t *oni_request =
		kaa_lamp_event_family_oni_create();
	oni_request->interval = *interval_ptr;

	error_code = kaa_event_manager_send_kaa_lamp_event_family_oni(
			kaa_client_get_context(kaa_client)->event_manager
			, oni_request
			, NULL);
	//KAA_RETURN_IF_ERROR(error_code, "Failed to send LEDOnEvent");

	oni_request->destroy(oni_request);
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

	/* Create and send an event */
	
	kaa_lamp_event_family_oni_t *oni_request =
		kaa_lamp_event_family_oni_create();
	oni_request->interval = interval;

	error_code = kaa_event_manager_send_kaa_lamp_event_family_oni(
			kaa_client_get_context(kaa_client)->event_manager
			, oni_request
			, NULL);

	oni_request->destroy(oni_request);
}

void request_OnI_event_id(int64_t interval, kaa_endpoint_id id)
{
	kaa_error_t error_code;

	/* Create and send an event */
	
	kaa_lamp_event_family_oni_t *oni_request =
		kaa_lamp_event_family_oni_create();
	oni_request->interval = interval;

	error_code = kaa_event_manager_send_kaa_lamp_event_family_oni(
			kaa_client_get_context(kaa_client)->event_manager
			, oni_request
			, id);

	oni_request->destroy(oni_request);
}

void request_List_event(void) {
}
