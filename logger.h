/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2024 Brian J. Downs
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

#ifndef _S_LOGGER_H
#define _S_LOGGER_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <json-c/json.h>

#define LOG_TRACE "trace"
#define LOG_DEBUG "debug"
#define LOG_INFO  "info"
#define LOG_WARN  "warn"
#define LOG_ERROR "error"
#define LOG_FATAL "fatal"

/**
 * s_log_field_types is an enum of the supported log field types.
 */
static enum { 
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
    S_LOG_DOUBLE, 
    S_LOG_STRING
} s_log_field_types;

/**
 * s_log_field_t represents a field in a log entry and it's
 * associated type.
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
        double double_value;
        char *char_value;
    };
} s_log_field_t;

/**
 * log_output contains the location we're
 * going to write our log entries to
 */
static FILE *log_output;

enum {
    S_LOG_OUT_STDERR,
    S_LOG_OUT_STDOUT,
};

/**
 * reallog provides the functionality of the logger. Returns
 * the number os bytes written.
 */
int
reallog(char *l, ...);

/**
 * s_log is the main entry point for adding data
 * to the logger to create log entries
 */
#define s_log(l, ...) ({ reallog(l, __VA_ARGS__, NULL); })

/**
 * s_log_init initializes the logger and sets up
 * where the logger writes to.
 */
void
s_log_init(FILE *out)
{
    log_output = out;
}

/**
 * s_log_field_new allocates memory for a new log field,
 * sets the memory to 0, and returns a pointer to it.
 */
static struct s_log_field_t*
s_log_field_new(const char *key)
{
    struct s_log_field_t *field =
        (struct s_log_field_t *)malloc(sizeof(s_log_field_t));
    if (field == NULL) {
        perror("unable to allocation memory for new field");
        return NULL;
    }
    memset(field, 0, sizeof(s_log_field_t));
    field->key = (char *)malloc(strlen(key)+1);
    strcpy(field->key, key);
    return field;
}

/**
 * log_field_free frees the memory used by the log_field_t.
 * struct.
 */
static void
s_log_field_free(struct s_log_field_t *sf)
{
    if (sf != NULL) {
        if (sf->key != NULL) {
            free(sf->key);
        }
        if ((sf->type == S_LOG_STRING) && (sf->char_value != NULL)) {
            free(sf->char_value);
        }
        free(sf);
    }
}

/**
 * s_log_int is used to add an integer value
 * to the log entry.
 */
struct s_log_field_t*
s_log_int(const char *key, const int value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT;
    field->int_value = value;
    return field;
}

/**
 * s_log_int8 is used to add a 8 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_int8(const char *key, const int8_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT8;
    field->int8_value = value;
    return field;
}

/**
 * s_log_int16 is used to add a 16 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_int16(const char *key, const int16_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT16;
    field->int16_value = value;
    return field;
}

/**
 * s_log_int32 is used to add a 32 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_int32(const char *key, const int32_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT32;
    field->int32_value = value;
    return field;
}

/**
 * s_s_log_int64 is used to add a 64 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_int64(const char *key, const int64_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_INT64;
    field->int64_value = value;
    return field;
}

/**
 * s_log_uint is used to add an unsigned integer value
 * to the log entry.
 */
struct s_log_field_t*
s_log_uint(const char *key, const unsigned int value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT;
    field->int_value = value;
    return field;
}

/**
 * s_log_uint8 is used to add a 8 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_uint8(const char *key, const uint8_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT8;
    field->int8_value = value;
    return field;
}

/**
 * s_log_uint16 is used to add a 16 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_uint16(const char *key, const uint16_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT16;
    field->int16_value = value;
    return field;
}

/**
 * s_log_uint32 is used to add a 32 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_uint32(const char *key, const uint32_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT32;
    field->int32_value = value;
    return field;
}

/**
 * s_log_uint64 is used to add a 64 bit integer
 * value to the log entry.
 */
struct s_log_field_t*
s_log_uint64(const char *key, const uint64_t value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_UINT64;
    field->int64_value = value;
    return field;
}

/**
 * s_log_double is used to add a double to the
 * log entry.
 */
struct s_log_field_t*
s_log_double(const char *key, const double value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_DOUBLE;
    field->double_value = value;
    return field;
}

/**
 * s_log_string is used to add a string to the
 * log entry.
 */
struct s_log_field_t*
s_log_string(const char *key, const char *value)
{
    struct s_log_field_t *field = s_log_field_new(key);
    field->type = S_LOG_STRING;
    field->char_value = (char *)malloc(strlen(value) + 1);
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

    for (;;) {
        struct s_log_field_t *arg = va_arg(ap, struct s_log_field_t*);
        if (arg == NULL) {
            break;
        }

        switch (arg->type) {
            case S_LOG_INT:
                JSON_OBJECT_ADD(json_object_new_int(arg->int_value)));
                break;
            case S_LOG_INT64:
                JSON_OBJECT_ADD(json_object_new_int64(arg->int64_value)));
                break;
            case S_LOG_DOUBLE:
                JSON_OBJECT_ADD(json_object_new_double(arg->double_value)));
                break;
            case S_LOG_STRING:
                JSON_OBJECT_ADD(json_object_new_string(arg->char_value)));
        }

        s_log_field_free(arg);

        continue;
    }

    va_end(ap); 

    int wc = fprintf(log_output, "%s\n", json_object_to_json_string(root));
    json_object_put(root); // decrement the count on the JSON object

    if (strcmp(l, LOG_FATAL) == 0) {
        exit(1);
    }

    return wc;
}

#endif /** end _S_LOGGER_H */
