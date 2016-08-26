/*
 * In The Name Of God
 * ========================================
 * [] File Name : user.h
 *
 * [] Creation Date : 23-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#ifndef USER_H
#define USER_H

void attach_endpoint_to_user(kaa_user_manager_t *manager,
		const char *user_external_id,
		const char *user_access_token);

#endif
