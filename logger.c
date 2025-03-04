/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 Brian J. Downs
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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <jansson.h>

#include "logger.h"

/**
 * s_log_field_types is an enum of the supported log field types.
 */
enum { 
    S_LOG_INT, 
    S_LOG_INT8,
    S_LOG_INT16,
    S_LOG_INT32,
    S_LOG_INT64,
    S_LOG_UINT, 
    S_LOG_UINT8,
    S_LOG_UINT16,
    S_LOG_UINT32,
    S_LOG_UINT64,
    S_LOG_FLOAT,
    S_LOG_DOUBLE, 
    S_LOG_STRING
} s_log_field_types;

/**
 * s_log_field_t represents a field in a log entry and it's associated type.
 */
struct s_log_field_t {
    uint8_t type;
    char *key;
    union {
        int int_value;
        int8_t int8_value;
        int16_t int16_value;
        int32_t int32_value;
        int64_t int64_value;
        unsigned int uint_value;
        uint8_t uint8_value;
        uint16_t uint16_value;
        uint32_t uint32_value;
        uint64_t uint64_value;
        float float_value;
        double double_value;
        char *string_value;
    };
} s_log_field_t;

/**
 * log_output contains the location we're going to write our log entries to.
 */
static FILE *log_output;

void
s_log_init(FILE *out)
{
    log_output = out;
}

/**
 * s_log_field_new allocates memory for a new log field, sets the memory to 0,
 * and returns a pointer to it.
 */
static struct s_log_field_t*
s_log_field_new(const char *key)
{
    struct s_log_field_t *field =
        (struct s_log_field_t *)calloc(1, sizeof(s_log_field_t));

    size_t key_len = strlen(key)+1;
    field->key = (char *)calloc(key_len, sizeof(char));
    memcpy(field->key, key, key_len);

    return field;
}

/**
 * log_field_free frees the memory used by the log_field_t struct.
 */
static void
s_log_field_free(struct s_log_field_t *sf)
{
    if (sf != NULL) {
        if (sf->key != NULL) {
            free(sf->key);
        }

        if ((sf->type == S_LOG_STRING) && (sf->string_value != NULL)) {
            free(sf->string_value);
        }

        free(sf);
    }
}

struct s_log_field_t*
s_log_int(const char *key, const int value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT;
    field->int_value = value;

    return field;
}

struct s_log_field_t*
s_log_int8(const char *key, const int8_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT8;
    field->int8_value = value;

    return field;
}

struct s_log_field_t*
s_log_int16(const char *key, const int16_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT16;
    field->int16_value = value;

    return field;
}

struct s_log_field_t*
s_log_int32(const char *key, const int32_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT32;
    field->int32_value = value;

    return field;
}

struct s_log_field_t*
s_log_int64(const char *key, const int64_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT64;
    field->int64_value = value;

    return field;
}

struct s_log_field_t*
s_log_uint(const char *key, const unsigned int value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT;
    field->int_value = value;

    return field;
}

struct s_log_field_t*
s_log_uint8(const char *key, const uint8_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT8;
    field->int8_value = value;

    return field;
}

struct s_log_field_t*
s_log_uint16(const char *key, const uint16_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT16;
    field->int16_value = value;

    return field;
}

struct s_log_field_t*
s_log_uint32(const char *key, const uint32_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT32;
    field->int32_value = value;

    return field;
}

struct s_log_field_t*
s_log_uint64(const char *key, const uint64_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT64;
    field->int64_value = value;

    return field;
}

struct s_log_field_t*
s_log_float(const char *key, const float value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_FLOAT;
    field->float_value = value;

    return field;
}

struct s_log_field_t*
s_log_double(const char *key, const double value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_DOUBLE;
    field->double_value = value;

    return field;
}

struct s_log_field_t*
s_log_string(const char *key, const char *value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_STRING;

    size_t val_len = strlen(value)+1;
    field->string_value = (char *)calloc(val_len, sizeof(char));
    memcpy(field->string_value, value, val_len);

    return field;
}

void
reallog(char* l, ...)
{
    va_list ap;

    // UNIX timestamp format
    unsigned long now = (unsigned long)time(NULL);

    json_t *root = json_object();
    json_object_set_new(root, "level", json_string(l));
    json_object_set_new(root, "timestamp", json_integer(now));

    if (strcmp(l, S_LOG_DEBUG) == 0) {
        json_object_set_new(root, "file", json_string(__FILE__));
        json_object_set_new(root, "line", json_integer(__LINE__));
    }

    va_start(ap, l);

    for (;;) {
        struct s_log_field_t *arg = va_arg(ap, struct s_log_field_t*);
        if (arg == NULL) {
            break;
        }

        switch (arg->type) {
            case S_LOG_INT ... S_LOG_UINT64:
                json_object_set_new(root, arg->key,
                    json_integer(arg->int_value));
                break;
            case S_LOG_FLOAT ... S_LOG_DOUBLE:
                json_object_set_new(root, arg->key,
                    json_real(arg->double_value));
                break;
            case S_LOG_STRING:
                json_object_set_new(root, arg->key,
                    json_string(arg->string_value));
        }

        s_log_field_free(arg);

        continue;
    }

    va_end(ap); 

    int res = json_dumpf(root, log_output, JSON_INDENT(0));
    if (res != 0) {
        // error handler...
    }
    fprintf(log_output, "\n");

    json_decref(root);

    if (strcmp(l, S_LOG_FATAL) == 0) {
        exit(1);
    }
}
