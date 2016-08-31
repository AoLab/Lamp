/*
 * In The Name Of God
 * ========================================
 * [] File Name : data.c
 *
 * [] Creation Date : 30-08-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * [] Improved By : Iman Tabrizian (tabrizian@outlook.com)
 * =======================================
 */
/*
 * Copyright (c) 2016 Parham Alvani.
 */
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <kaa/kaa_logging.h>
#include <kaa/kaa_log.h>
#include <kaa/gen/kaa_logging_gen.h>
#include <kaa/platform/kaa_client.h>

#include "notification.h"
#include "util.h"
#include "lamp.h"
#include "log.h"

/*
 * Called if log delivered successfully
 */
static void success_log_delivery_callback(void *context,
		const kaa_log_bucket_info_t *bucket)
{
	LOG_INFO(LOGGER, "Log delivered successfully");
}

/*
 * Called if delivery failed
 */
static void failed_log_delivery_callback(void *context,
		const kaa_log_bucket_info_t *bucket)
{
	LOG_INFO(LOGGER, "Log deliver process failed");
}

/*
 * Called if timeout occurs
 */
static void timeout_log_delivery_callback(void *context,
		const kaa_log_bucket_info_t *bucket)
{
	LOG_INFO(LOGGER, "Log deliver process timed out");
}

kaa_error_t kaa_data_register(kaa_log_collector_t *log_collector, kaa_logger_t looger)
{
	/*
	 * Log delivery listener callbacks.
	 * Each callback called whenever something
	 * happen with a log bucket.
	 */
	kaa_log_delivery_listener_t log_listener = {
		.on_success = success_log_delivery_callback,
		.on_failed  = failed_log_delivery_callback,
		.on_timeout = timeout_log_delivery_callback,
		.ctx        = NULL,
	};

	/*
	 * The internal memory log storage distributed with Kaa SDK
	 */
	kaa_error_t error_code = ext_unlimited_log_storage_create(
			&log_storage_context, logger);
	KAA_RETURN_IF_ERROR(error_code, "Failed log storage creation");

	/*
	 * Specify log bucket size constraints
	 */
	kaa_log_bucket_constraints_t bucket_sizes = {
		/* Bucket size in bytes */
		.max_bucket_size = 512,
		/* Maximum log count in one bucket */
		.max_bucket_log_count = 5,
	};

	/*
	 * Initialize the log storage and strategy (by default it is not set)
	 */
	error_code = kaa_logging_init(log_collector
			, log_storage_context
			, log_upload_strategy_context
			, &bucket_sizes);
	KAA_RETURN_IF_ERROR(error_code, "Failed log storage and strategy initiation");

	/* Add listeners to a log collector */
	kaa_logging_set_listeners(log_collector, &log_listener);

	return error_code;
}

void kaa_log_message(char *message, char *tag)
{
	/* Create and add a log record */

	kaa_user_log_record_t *log_record = kaa_logging_log_data_create();

	log_record->level = ENUM_LEVEL_KAA_TRACE;
	log_record->tag = kaa_string_copy_create(tag);
	log_record->message = kaa_string_copy_create(message);

	/* Log information. Populated when log is added via kaa_logging_add_record() */
	kaa_log_record_info_t log_info;

	/* Add log record */
	error_code = kaa_logging_add_record(log_collector, log_record, &log_info);
	KAA_RETURN_IF_ERROR(error_code, "Failed add log record");

	log_record->destroy(log_record);
}
