/*
 * In The Name Of God
 * ========================================
 * [] File Name : user.c
 *
 * [] Creation Date : 23-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
 */
/*
 * Copyright (c) 2016 Parham Alvani.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <glib.h>

#include <kaa/kaa_error.h>
#include <kaa/kaa_user.h>
#include <kaa/platform/ext_user_callback.h>

#include "user.h"

static kaa_error_t on_attached(void *context, const char *user_external_id,
		const char *endpoint_access_token)
{
	g_message("%s attached", user_external_id);
	return KAA_ERR_NONE;
}

static kaa_error_t on_detached(void *context,
		const char *endpoint_access_token)
{
	g_message("Detached");
	return KAA_ERR_NONE;
}
static kaa_error_t on_attach_success(void *context)
{
	g_message("Successfull attach");
	return KAA_ERR_NONE;
}
static kaa_error_t on_attach_failed(void *context,
		user_verifier_error_code_t error_code, const char *reason)
{
	g_message("Unsuccessfull attach");
	return KAA_ERR_NONE;
}

void attach_endpoint_to_user(kaa_user_manager_t *manager,
		const char *user_external_id, const char *user_access_token)
{
	kaa_error_t error_code;

	kaa_attachment_status_listeners_t attachement_listeners = {
		NULL,
		on_attached,
		on_detached,
		on_attach_success,
		on_attach_failed
	};

	error_code = kaa_user_manager_set_attachment_listeners(manager,
			&attachement_listeners);
	if (error_code) {
		g_critical("Failed to attaching user listeners");
		abort();
	}

	error_code = kaa_user_manager_default_attach_to_user(manager,
			user_external_id,
			user_access_token);
	if (error_code) {
		g_critical("Failed to attaching the user");
		abort();
	}
}
