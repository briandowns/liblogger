/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Brian J. Downs
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <json-c/json.h>

#include "logger.h"

void
log_init(FILE *out)
{
    log_output = out;
}

/**
 * log_field_new allocates memory for a new log field,
 * sets the memory to 0, and returns a pointer to it.
 */
static struct log_field_t*
log_field_new(const char *key)
{
    struct log_field_t *field = malloc(sizeof(log_field_t));
    if (field == NULL) {
        perror("unable to allocation memory for new field");
        return NULL;
    }
    memset(field, 0, sizeof(log_field_t));
    field->key = malloc(strlen(key)+1);
    strcpy(field->key, key);
    return field;
}

/**
 * log_field_free frees the memory used by the log_field_t.
 * struct.
 */
static void
log_field_free(struct log_field_t *sf)
{
    if (sf != NULL) {
        if (sf->key != NULL) {
            free(sf->key);
        }
        if ((sf->type == LOG_STRING) && (sf->char_value != NULL)) {
            free(sf->char_value);
        }
        free(sf);
    }
}

struct log_field_t*
log_int(const char *key, const int value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_INT;
    field->int_value = value;
    return field;
}

struct log_field_t*
log_int8(const char *key, const int8_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_INT8;
    field->int8_value = value;
    return field;
}

struct log_field_t*
log_int16(const char *key, const int16_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_INT16;
    field->int16_value = value;
    return field;
}

struct log_field_t*
log_int32(const char *key, const int32_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_INT32;
    field->int32_value = value;
    return field;
}

struct log_field_t*
log_int64(const char *key, const int64_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_INT64;
    field->int64_value = value;
    return field;
}

struct log_field_t*
log_uint(const char *key, const unsigned int value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_UINT;
    field->int_value = value;
    return field;
}

struct log_field_t*
log_uint8(const char *key, const uint8_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_UINT8;
    field->int8_value = value;
    return field;
}

struct log_field_t*
log_uint16(const char *key, const uint16_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_UINT16;
    field->int16_value = value;
    return field;
}

struct log_field_t*
log_uint32(const char *key, const uint32_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_UINT32;
    field->int32_value = value;
    return field;
}

struct log_field_t*
log_uint64(const char *key, const uint64_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_UINT64;
    field->int64_value = value;
    return field;
}

struct log_field_t*
log_double(const char *key, const double value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_DOUBLE;
    field->double_value = value;
    return field;
}

struct log_field_t*
log_string(const char *key, const char *value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_STRING;
    field->char_value = malloc(strlen(value) + 1);
    strcpy(field->char_value, value);
    return field;
}

#define JSON_OBJECT_ADD(x) json_object_object_add(root, arg->key, (x)

int
reallog(char* l, ...)
{
    va_list ap;

    unsigned long now = (unsigned long)time(NULL); // UNIX timestamp format

    struct json_object *root = json_object_new_object();
    json_object_object_add(root, "timestamp", json_object_new_int64(now));
    json_object_object_add(root, "level", json_object_new_string(l));

    va_start(ap, l);

    for (int i = 1;; i++) {
        struct log_field_t *arg = va_arg(ap, struct log_field_t*);
        if (arg == NULL) {
            break;
        }

        switch (arg->type) {
            case LOG_INT:
                JSON_OBJECT_ADD(json_object_new_int(arg->int_value)));
                break;
            case LOG_INT64:
                JSON_OBJECT_ADD(json_object_new_int64(arg->int64_value)));
                break;
            case LOG_DOUBLE:
                JSON_OBJECT_ADD(json_object_new_double(arg->double_value)));
                break;
            case LOG_STRING:
                JSON_OBJECT_ADD(json_object_new_string(arg->char_value)));
        }
        log_field_free(arg);
        continue;
    }

    va_end(ap);

    int wc = fprintf(log_output, "%s\n", json_object_to_json_string(root));
    json_object_put(root); // decrement the count on the JSON object

    return wc;
}
