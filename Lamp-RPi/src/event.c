/*
 * In The Name Of God
 * ========================================
 * [] File Name : event.c
 *
 * [] Creation Date : 28-02-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/
#include <stdint.h>
#include <stdio.h>

#include <kaa/kaa_event.h>
#include <kaa/gen/kaa_lamp_event_family.h>

#include "event.h"
#include "util.h"
#include "lamp.h"

static void on_OnI_event(void *context,
		kaa_lamp_event_family_oni_t *event, kaa_endpoint_id_p source)
{
	int interval;

	interval = event->interval;

	lamp(interval);

	event->destroy(event);
}

kaa_error_t kaa_event_register(kaa_event_manager_t *manager)
{
	kaa_error_t error_code;

	error_code = kaa_event_manager_set_kaa_lamp_event_family_oni_listener(
			manager,
			on_OnI_event, NULL);
	KAA_RETURN_IF_ERROR(error_code, "Failed add event listener");

	return error_code;
}
