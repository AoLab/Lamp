/*
 * In The Name Of God
 * ========================================
 * [] File Name : util.h
 *
 * [] Creation Date : 27-02-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#ifndef UTIL_H
#define UTIL_H

#define KAA_RETURN_IF_ERROR(error, message) \
	do { \
		if (error) { \
			printf(message ", error code %d\n", (error)); \
				return error; \
		} \
	} while (0)

#endif
