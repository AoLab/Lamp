/*
 * In The Name Of God
 * ========================================
 * [] File Name : response.h
 *
 * [] Creation Date : 17-04-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/
#ifndef RESPONSE_H
#define RESPONSE_H

JsonNode *lamp_response_build(JsonNode *data, const gchar *message, int status);
void lamp_response_to_msg(JsonNode *response, SoupMessage *msg);

#endif
