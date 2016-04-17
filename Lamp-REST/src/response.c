/*
 * In The Name Of God
 * ========================================
 * [] File Name : response.c
 *
 * [] Creation Date : 17-04-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/
#include <libsoup/soup.h>
#include <json-glib/json-glib.h>

JsonNode *lamp_response_build(JsonNode *data,
		const gchar *message, int status)
{
	JsonNode *response_node;
	response_node = json_node_alloc();

	JsonObject *response_object;
	response_object = json_object_new();
	
	if (message) {
		JsonNode *message_node;
		message_node = json_node_alloc();
		message_node = json_node_init_string(message_node, message);
		json_object_set_member(response_object, "message", message_node);
	}

	JsonNode *status_node;
	status_node = json_node_alloc();
	status_node = json_node_init_boolean(status_node, status);
	json_object_set_member(response_object, "status", status_node);
	
	if (data) {
		json_object_set_member(response_object, "data", data);
	}

	response_node = json_node_init_object(response_node, response_object);

	return response_node;
}

void lamp_response_to_msg(JsonNode *response, SoupMessage *msg)
{
	gsize jsize;
	JsonGenerator *jgen;
	gchar *jdata;

	jgen = json_generator_new();
	json_generator_set_root(jgen, response);
	data = json_generator_to_data(jgen, &jsize);
	if (jsize == 0) {
		soup_message_set_status(msg, SOUP_STATUS_INTERNAL_SERVER_ERROR);
	} else {
		soup_message_set_response(msg, "application/json",
				SOUP_MEMORY_TAKE, jdata, jsize);
		soup_message_set_status(msg, SOUP_STATUS_OK);
	}
	g_free(jgen);
	return;
}
