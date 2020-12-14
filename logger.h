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

#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_TRACE "trace"
#define LOG_DEBUG "debug"
#define LOG_INFO "info"
#define LOG_WARN "warn"
#define LOG_ERROR "error"
#define LOG_FATAL "fatal"

/**
 * log field types is an enum of the supported log field types.
 */
static enum { 
    LOG_INT, 
    LOG_INT8,
    LOG_INT16,
    LOG_INT32,
    LOG_INT64,
    LOG_UINT, 
    LOG_UINT8,
    LOG_UINT16,
    LOG_UINT32,
    LOG_UINT64,
    LOG_DOUBLE, 
    LOG_STRING
} log_field_types;

/**
 * log_field_t represents a field in a log entry and it's
 * associated type.
 */
struct log_field_t {
    uint8_t type;
    char *key;
    union {
        int int_value;
        int8_t int8_value;
        int16_t int16_value;
        int32_t int32_value;
        int64_t int64_value;
        double double_value;
        char *char_value;
    };
} log_field_t;

/**
 * log_int is used to add an integer value
 * to the log entry.
 */
struct log_field_t*
log_int(const char *key, const int value);

/**
 * log_int8 is used to add a 8 bit integer
 * value to the log entry.
 */
struct log_field_t*
log_int8(const char *key, const int8_t value);

/**
 * log_int16 is used to add a 16 bit integer
 * value to the log entry.
 */
struct log_field_t*
log_int16(const char *key, const int16_t value);

/**
 * log_int32 is used to add a 32 bit integer
 * value to the log entry.
 */
struct log_field_t*
log_int32(const char *key, const int32_t value);
/**
 * log_int64 is used to add a 64 bit integer
 * value to the log entry.
 */
struct log_field_t*
log_int64(const char *key, const int64_t value);

/**
 * log_double is used to add a double to the
 * log entry.
 */
struct log_field_t*
log_double(const char *key, const double value);

/**
 * log_string is used to add a string to the
 * log entry.
 */
struct log_field_t*
log_string(const char *key, const char *value);

/**
 * log_output contains the location we're
 * going to write our log entries to
 */
FILE *log_output;

enum {
    LOG_OUT_STDERR,
    LOG_OUT_STDOUT,
};

/**
 * log_init initializes the logger and sets up
 * where the logger writes to.
 */
void
log_init(FILE *out);

/**
 * reallog provides the functionality of the logger. Returns
 * the number os bytes written.
 */
int
reallog(char *l, ...);

/**
 * log is the main entry point for adding data
 * to the logger to create log entries
 */
#define log(l, ...) ({ reallog(l, __VA_ARGS__, NULL); })

#endif /* end _LOGGER_H */
