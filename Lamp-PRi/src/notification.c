/*
 * In The Name Of God
 * ========================================
 * [] File Name : notification.c
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
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <kaa/kaa_notification_manager.h>

#include "notification.h"
#include "util.h"
#include "serial.h"

static void on_notification(void *context, uint64_t *topic_id, kaa_notification_t *notification)
{
	int interval = notification->interval;

	printf("Notification for topic id '%lu' received\n", *topic_id);
	printf("Notification interval: %d\n", interval);

	writechar('1');

	sleep(interval);

	writechar('0');
}

static void on_topics_received(void *context, kaa_list_t *topics)
{
	printf("Topic list was updated\n");
	if (!topics || !kaa_list_get_size(topics)) {
		printf("Topic list is empty");
		return;
	}

	kaa_list_node_t *it = kaa_list_begin(topics);

	while (it) {
		kaa_topic_t *topic = (kaa_topic_t *)kaa_list_get_data(it);

		printf("Topic: id '%lu', name: %s\n", topic->id, topic->name);
		it = kaa_list_next(it);
	}
}


kaa_error_t kaa_notification_register(kaa_notification_manager_t *manager)
{
	kaa_error_t error_code;

	kaa_topic_listener_t topic_listener = {
		.callback = on_topics_received,
		.context = NULL,
	};
	kaa_notification_listener_t notification_listener = {
		.callback = on_notification,
		.context = NULL,
	};

	uint32_t topic_listener_id = 0;
	uint32_t notification_listener_id = 0;

	error_code = kaa_add_topic_list_listener(manager,
			&topic_listener,
			&topic_listener_id);
	KAA_RETURN_IF_ERROR(error_code, "Failed add topic listener");

	error_code = kaa_add_notification_listener(manager,
			&notification_listener,
			&notification_listener_id);
	KAA_RETURN_IF_ERROR(error_code, "Failed add notification listener");

	return error_code;
}
