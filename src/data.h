/*
 * In The Name Of God
 * ========================================
 * [] File Name : data.h
 *
 * [] Creation Date : 30-08-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/
#ifndef DATA_H
#define DATA_H

#include <kaa/kaa_logging.h>

kaa_error_t kaa_data_register(kaa_client_t *kaa_client);
kaa_error_t create_data_collecting_loop(void);

#endif
