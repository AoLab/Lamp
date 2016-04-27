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

struct kaa_endpoint_ids_context {
	kaa_endpoint_id **ids;
	size_t *ids_length;
};

static kaa_error_t event_listeners_callback(void *context,
		const kaa_endpoint_id listeners[], size_t listeners_count)
{
	kaa_error_t error_code;
	int i, j;

	struct kaa_endpoint_ids_context *c = context;
	kaa_endpoint_id **ids = c->ids;
	*ids = malloc(sizeof(kaa_endpoint_id) * sizeof(uint8_t) * listeners_count);
	*(c->ids_length) = listeners_count;

	/* Send data to REST side :) */
	for (i = 0; i < listeners_count; i++) {
		for (j = 0; j < sizeof(kaa_endpoint_id); j++) {
			(*ids)[i][j] = listeners[i][j];
		}
	}

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

void request_On_event(const char *id)
{
	kaa_error_t error_code;

	/* Create and send an event */

	kaa_lamp_event_family_trun_t *trun_request =
		kaa_lamp_event_family_turn_create();
	trun_request->id;
	turn_request->turn = 1;

	error_code = kaa_event_manager_send_kaa_lamp_event_family_turn(
			kaa_client_get_context(kaa_client)->event_manager
			, turn_request
			, NULL);

	turn_request->destroy(turn_request);
}

void request_Off_event(const char *id)
{
	kaa_error_t error_code;

	/* Create and send an event */

	kaa_lamp_event_family_oni_t *turn_request =
		kaa_lamp_event_family_turn_create();
	turn_request->id;
	turn_request->turn = 0;

	error_code = kaa_event_manager_send_kaa_lamp_event_family_turn(
			kaa_client_get_context(kaa_client)->event_manager
			, turn_request
			, NULL);

	turn_request->destroy(turn_request);
}


void request_List_event(kaa_endpoint_id **ids, size_t *ids_length) {
	kaa_error_t error_code;

	/* Try to find event sinks by FQDN :) */

	const char *fqns[] = {"ir.ac.aut.ceit.aolab.lamp.OnI"};

	struct kaa_endpoint_ids_context *c = malloc(sizeof(struct kaa_endpoint_ids_context));
	c->ids = ids;
	c->ids_length = ids_length;
	kaa_event_listeners_callback_t callback = {c, event_listeners_callback, event_listeners_request_failed};

	error_code = kaa_event_manager_find_event_listeners(kaa_client_get_context(kaa_client)->event_manager
			, fqns
			, 1
			, &callback);
}
