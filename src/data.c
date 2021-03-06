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
#include <kaa/gen/kaa_logging_gen.h>
#include <kaa/platform/kaa_client.h>
#include <kaa/platform-impl/common/ext_log_upload_strategies.h>

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

/*
 * Private global variables
 */
static kaa_log_collector_t *log_collector_g;

kaa_error_t kaa_data_register(kaa_client_t *kaa_client)
{
	void *log_storage_context = NULL;
	void *log_upload_strategy_context = NULL;

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

	/* The internal memory log storage distributed with Kaa SDK */
	kaa_error_t error_code = ext_unlimited_log_storage_create(&log_storage_context, kaa_client_get_context(kaa_client)->logger);
	KAA_RETURN_IF_ERROR(error_code, "Failed log storage creation");


	/* Create a strategy based on timeout. */
	error_code = ext_log_upload_strategy_create(
			kaa_client_get_context(kaa_client),
			&log_upload_strategy_context,
			KAA_LOG_UPLOAD_BY_TIMEOUT_STRATEGY);
	KAA_RETURN_IF_ERROR(error_code, "Failed the timeout based strategy");

	/* Strategy will upload logs every 5 seconds. */
	error_code = ext_log_upload_strategy_set_upload_timeout(log_upload_strategy_context, 5);
	KAA_RETURN_IF_ERROR(error_code, "Failed the timeout settings");

	/*
	 * Specify log bucket size constraints
	 */
	kaa_log_bucket_constraints_t bucket_sizes = {
		/* Bucket size in bytes */
		.max_bucket_size = 512,
		/* Maximum log count in one bucket */
		.max_bucket_log_count = 1,
	};

	/*
	 * Initialize the log storage and strategy (by default it is not set)
	 */
	error_code = kaa_logging_init(kaa_client_get_context(kaa_client)->log_collector
			, log_storage_context
			, log_upload_strategy_context
			, &bucket_sizes);
	KAA_RETURN_IF_ERROR(error_code, "Failed log storage and strategy initiation");

	/* Add listeners to a log collector */
	kaa_logging_set_listeners(kaa_client_get_context(kaa_client)->log_collector, &log_listener);

	log_collector_g = kaa_client_get_context(kaa_client)->log_collector;

	return error_code;
}

static void kaa_log_message(char *message, char *tag)
{
	/* Create and add a log record */

	kaa_logging_i1820_t *log_record = kaa_logging_i1820_create();

	log_record->id = 10;
	log_record->type = kaa_string_copy_create(tag);
	log_record->states = kaa_logging_states_create();
	log_record->states->temprature = kaa_logging_union_int_or_null_branch_0_create();

	/* Log information. Populated when log is added via kaa_logging_add_record() */
	kaa_log_record_info_t log_info;

	/* Add log record */
	kaa_logging_add_record(log_collector_g, log_record, &log_info);

	log_record->destroy(log_record);
}

/*
 * Sample task list to be passed to data provider thread
 */
static void *tasks(void *input) {
	while (1) {
		printf("HI\n");
		kaa_log_message("Recieved sth from nrf", "temprature");
		sleep(100);
	}
	return NULL;
}

kaa_error_t create_data_collecting_loop(void) {

	pthread_t data_provider_thread;
	int error_code;

	error_code = pthread_create(&data_provider_thread, NULL, tasks, NULL);
	KAA_RETURN_IF_ERROR(error_code, "Failed to create the pthread");

	return error_code;
}
