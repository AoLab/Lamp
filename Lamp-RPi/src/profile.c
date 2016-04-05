/*
 * In The Name Of God
 * ========================================
 * [] File Name : profile.c
 *
 * [] Creation Date : 06-04-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/
#include <stdint.h>
#include <stdio.h>

#include <kaa/kaa_profile.h>
#include <kaa/gen/kaa_profile_gen.h>

#include "profile.h"
#include "util.h"
#include "config.h"

kaa_error_t kaa_profile_register(kaa_profile_manager_t *manager)
{
	kaa_error_t error_code;
	kaa_profile_t *profile;

	/* Create and update profile */
	profile = kaa_profile_location_info_schema_create();

	profile->room_number = LAMP_ROOM_NUMBER;
	profile->room_owner = kaa_string_move_create(LAMP_ROOM_OWNER, NULL);

	error_code = kaa_profile_manager_update_profile(manager, profile);
	KAA_RETURN_IF_ERROR(error_code, "Failed to register profile");


	profile->destroy(profile);

	return error_code;
}
