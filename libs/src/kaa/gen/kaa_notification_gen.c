/**
 *  Copyright 2014-2016 CyberVision, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

# include <inttypes.h>
# include <string.h>
# include "../platform/stdio.h"
# include "kaa_notification_gen.h"
# include "../avro_src/avro/io.h"
# include "../avro_src/encoding.h"
# include "../utilities/kaa_mem.h"

/*
 * AUTO-GENERATED CODE
 */




static void kaa_notification_settings_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_notification_settings_t *record = (kaa_notification_settings_t *)data;

        kaa_boolean_serialize(writer, &record->on);
    }
}

static size_t kaa_notification_settings_get_size(void *data)
{
    if (data) {
        size_t record_size = 0;
        kaa_notification_settings_t *record = (kaa_notification_settings_t *)data;

        record_size += kaa_boolean_get_size(&record->on);

        return record_size;
    }

    return 0;
}

kaa_notification_settings_t *kaa_notification_settings_create(void)
{
    kaa_notification_settings_t *record = 
            (kaa_notification_settings_t *)KAA_CALLOC(1, sizeof(kaa_notification_settings_t));

    if (record) {
        record->serialize = kaa_notification_settings_serialize;
        record->get_size = kaa_notification_settings_get_size;
        record->destroy = kaa_data_destroy;
    }

    return record;
}

kaa_notification_settings_t *kaa_notification_settings_deserialize(avro_reader_t reader)
{
    kaa_notification_settings_t *record = 
            (kaa_notification_settings_t *)KAA_MALLOC(sizeof(kaa_notification_settings_t));

    if (record) {
        record->serialize = kaa_notification_settings_serialize;
        record->get_size = kaa_notification_settings_get_size;
        record->destroy = kaa_data_destroy;

        avro_binary_encoding.read_boolean(reader, &record->on);
    }

    return record;
}



static void kaa_notification_i1820_destroy(void *data)
{
    if (data) {
        kaa_notification_i1820_t *record = (kaa_notification_i1820_t *)data;

        if (record->settings && record->settings->destroy) {
            record->settings->destroy(record->settings);
        }
        kaa_string_destroy(record->type);
        kaa_data_destroy(record);
    }
}

static void kaa_notification_i1820_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_notification_i1820_t *record = (kaa_notification_i1820_t *)data;

        kaa_int_serialize(writer, &record->id);
        record->settings->serialize(writer, record->settings);
        kaa_string_serialize(writer, record->type);
    }
}

static size_t kaa_notification_i1820_get_size(void *data)
{
    if (data) {
        size_t record_size = 0;
        kaa_notification_i1820_t *record = (kaa_notification_i1820_t *)data;

        record_size += kaa_int_get_size(&record->id);
        record_size += record->settings->get_size(record->settings);
        record_size += kaa_string_get_size(record->type);

        return record_size;
    }

    return 0;
}

kaa_notification_i1820_t *kaa_notification_i1820_create(void)
{
    kaa_notification_i1820_t *record = 
            (kaa_notification_i1820_t *)KAA_CALLOC(1, sizeof(kaa_notification_i1820_t));

    if (record) {
        record->serialize = kaa_notification_i1820_serialize;
        record->get_size = kaa_notification_i1820_get_size;
        record->destroy = kaa_notification_i1820_destroy;
    }

    return record;
}

kaa_notification_i1820_t *kaa_notification_i1820_deserialize(avro_reader_t reader)
{
    kaa_notification_i1820_t *record = 
            (kaa_notification_i1820_t *)KAA_MALLOC(sizeof(kaa_notification_i1820_t));

    if (record) {
        record->serialize = kaa_notification_i1820_serialize;
        record->get_size = kaa_notification_i1820_get_size;
        record->destroy = kaa_notification_i1820_destroy;

        avro_binary_encoding.read_int(reader, &record->id);
        record->settings = kaa_notification_settings_deserialize(reader);
        record->type = kaa_string_deserialize(reader);
    }

    return record;
}

