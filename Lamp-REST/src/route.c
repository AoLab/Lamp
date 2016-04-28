/*
 * In The Name Of God
 * ========================================
 * [] File Name : route.c
 *
 * [] Creation Date : 15-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#include <libsoup/soup.h>
#include <glib/gprintf.h>
#include <json-glib/json-glib.h>
#include <stdint.h>

#include <kaa/kaa_common.h>

#include "route.h"
#include "event.h"
#include "response.h"

static void on_On_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("Start handling request for %s", path);

	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/On/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/On")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		g_message("Invalid path: %s instead of /Lamp/On", path);
		gchar *message = g_strdup_printf("Invalid path: %s instead of /Lamp/On", path);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	/*
	 * We have On function with POST method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_POST) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		g_message("Invalid method: %s instead of POST", msg->method);
		gchar *message = g_strdup_printf("Invalid method: %s instead of POST", msg->method);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	/*
	 * Try to create JParser in order to parse
	 * input JSON, input JSON must be valid and
	 * contained destination lamp id.
	*/
	JsonParser *jparser = json_parser_new();
	GError *error = NULL;
	if (!json_parser_load_from_data(jparser, msg->request_body->data,
				msg->request_body->length, &error)) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("Invalid JSON: %s", msg->request_body->data);
		gchar *message = g_strdup_printf("Invalid JSON: %s", msg->request_body->data);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	JsonNode *root;
	root = json_parser_get_root(jparser);

	JsonObject *request;
	request = json_node_get_object(root);

	JsonNode *id_node;
	id_node = json_object_get_member(request, "id");
	if (!id_node) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("ID was not found in your JSON");
		gchar *message = g_strdup_printf("ID was not found in your JSON");
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}
	char *id_str = json_node_dup_string(id_node);
}

static void on_Off_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("Start handling request for %s", path);

	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/Off/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/Off")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		g_message("Invalid path: %s instead of /Lamp/Off", path);
		gchar *message = g_strdup_printf("Invalid path: %s instead of /Lamp/Off", path);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	/*
	 * We have Off function with POST method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_POST) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		g_message("Invalid method: %s instead of POST", msg->method);
		gchar *message = g_strdup_printf("Invalid method: %s instead of POST", msg->method);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	/*
	 * Try to create JParser in order to parse
	 * input JSON, input JSON must be valid and
	 * contained destination lamp id.
	*/
	JsonParser *jparser = json_parser_new();
	GError *error = NULL;
	if (!json_parser_load_from_data(jparser, msg->request_body->data,
				msg->request_body->length, &error)) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("Invalid JSON: %s", msg->request_body->data);
		gchar *message = g_strdup_printf("Invalid JSON: %s", msg->request_body->data);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	JsonNode *root;
	root = json_parser_get_root(jparser);

	JsonObject *request;
	request = json_node_get_object(root);

	JsonNode *id_node;
	id_node = json_object_get_member(request, "id");
	if (!id_node) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("ID was not found in your JSON");
		gchar *message = g_strdup_printf("ID was not found in your JSON");
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}
	char *id_str = json_node_dup_string(id_node);
}

static void on_OnI_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("Start handling request for %s", path);

	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/OnI/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/OnI")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		g_message("Invalid path: %s instead of /Lamp/OnI", path);
		return;
	}

	/*
	 * We have OnI function with POST method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_POST) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		g_message("Invalid method: %s instead of POST", msg->method);
		return;
	}

	JsonParser *jparser = json_parser_new();
	GError *error = NULL;
	if (!json_parser_load_from_data(jparser, msg->request_body->data,
				msg->request_body->length, &error)) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("Invalid JSON: %s", msg->request_body->data);
		gchar *message = g_strdup_printf("Invalid JSON :)");
		return;
	}

	JsonNode *root;
	root = json_parser_get_root(jparser);

	JsonObject *request;
	request = json_node_get_object(root);

	JsonNode *interval_node;
	interval_node = json_object_get_member(request, "interval");
	if (!interval_node) {
		soup_message_set_status(msg, SOUP_STATUS_BAD_REQUEST);
		g_message("Interval not found in your JSON");
		gchar *message = g_strdup_printf("Interval not found in your JSON");
		return;
	}
	int64_t interval = json_node_get_int(interval_node);

	request_OnI_event(interval);

	gsize jsize;
	JsonNode *response = lamp_response_build(NULL, NULL, 1);
	JsonGenerator *jgen = json_generator_new();
	json_generator_set_root(jgen, response);
	gchar *jdata = json_generator_to_data(jgen, &jsize);
	if (jsize == 0) {
		soup_message_set_status(msg, SOUP_STATUS_INTERNAL_SERVER_ERROR);
	} else {
		soup_message_set_response(msg, "application/json",
				SOUP_MEMORY_TAKE, jdata, jsize);
		soup_message_set_status(msg, SOUP_STATUS_OK);
	}
}

static void on_List_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("Start handling request for %s", path);

	/*
	 * You must enter the URL currectly we do not
	 * handle /Lamp/List/foo or ... in this function.
	 * We response to invalid URLs with NOT FOUND.
	*/
	if (g_strcmp0(path, "/Lamp/List")) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
		g_message("Invalid path: %s instead of /Lamp/List", path);
		gchar *message = g_strdup_printf("Invalid path: %s instead of /Lamp/List", path);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	/*
	 * We have List function with GET method ONLY :)
	 * so you get NOT IMPLEMENTED error with use other method
	 * on it.
	*/
	if (msg->method != SOUP_METHOD_POST) {
		soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
		g_message("Invalid method: %s instead of POST", msg->method);
		gchar *message = g_strdup_printf("Invalid method: %s instead of POST", msg->method);
		JsonNode *response = lamp_response_build(NULL, message, 0);
		lamp_response_to_msg(response, msg);
		return;
	}

	kaa_endpoint_id *ids = NULL;
	size_t ids_length;

	//request_List_event(&ids, &ids_length);

	/*
	 * Wait until our data collected from server :)
	*/
	//while (!ids);

	int i, j;

	JsonNode *root = json_node_alloc();
	JsonArray *lamps_array = json_array_new();
	for (i = 0; i < 3; i++) {
		/* Get and Set lamp ids :) */
		JsonNode *id_node = json_node_alloc();
		char id_str[10];
		/*

		for (j = 0; j < sizeof(kaa_endpoint_id); j++)
			g_sprintf(id_str + 3 * j, "%02hx ", ids[i][j]);
		*/
		g_sprintf(id_str, "%d", i);

		id_node = json_node_init_string(id_node, id_str);

		JsonObject *lamp_object = json_object_new();
		json_object_set_member(lamp_object, "id", id_node);
		JsonNode *lamp_node = json_node_alloc();
		lamp_node = json_node_init_object(lamp_node, lamp_object);
		json_array_add_element(lamps_array, lamp_node);
	}
	root = json_node_init_array(root, lamps_array);

	JsonNode *response = lamp_response_build(root, NULL, 1);
	lamp_response_to_msg(response, msg);
}

static void default_event_callback(SoupServer *server,
		SoupMessage *msg,
		const char *path,
		GHashTable *query,
		SoupClientContext *client,
		gpointer user_data)
{
	g_message("404 NotFound: %s", path);
	soup_message_set_status(msg, SOUP_STATUS_NOT_FOUND);
}


void rest_route_init(SoupServer *server)
{
	soup_server_add_handler(server, "/Lamp/Off",
			on_Off_event_callback, NULL, NULL);

	soup_server_add_handler(server, "/Lamp/On",
			on_On_event_callback, NULL, NULL);

	soup_server_add_handler(server, "/Lamp/OnI",
			on_OnI_event_callback, NULL, NULL);

	soup_server_add_handler(server, "/Lamp/List",
			on_List_event_callback, NULL, NULL);

	soup_server_add_handler(server, NULL,
			default_event_callback, NULL, NULL);
}
