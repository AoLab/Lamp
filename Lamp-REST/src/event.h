/*
 * In The Name Of God
 * ========================================
 * [] File Name : event.h
 *
 * [] Creation Date : 23-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#ifndef EVENT_H
#define EVENT_H

void request_OnI_event(int64_t interval);

void request_OnI_event_id(int64_t interval, kaa_endpoint_id id);

void request_On_event(uint32_t id);

void request_Off_event(uint32_t id);

void request_List_event(kaa_endpoint_id **ids, size_t *ids_length);

#endif
