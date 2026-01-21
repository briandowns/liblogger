/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2026 Brian J. Downs
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define S_LOG_TRACE "trace"
#define S_LOG_DEBUG "debug"
#define S_LOG_INFO  "info"
#define S_LOG_WARN  "warn"
#define S_LOG_ERROR "error"
#define S_LOG_FATAL "fatal"

/**
 * s_log_int is used to add an integer value to the log entry.
 */
struct s_log_field_t*
s_log_int(const char *key, const int value);

/**
 * s_log_int8 is used to add a 8 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_int8(const char *key, const int8_t value);

/**
 * s_log_int16 is used to add a 16 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_int16(const char *key, const int16_t value);

/**
 * s_log_int32 is used to add a 32 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_int32(const char *key, const int32_t value);

/**
 * s_s_log_int64 is used to add a 64 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_int64(const char *key, const int64_t value);

/**
 * s_log_uint is used to add an unsigned integer value to the log entry.
 */
struct s_log_field_t*
s_log_uint(const char *key, const unsigned int value);

/**
 * s_log_uint8 is used to add a 8 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_uint8(const char *key, const uint8_t value);

/**
 * s_log_uint16 is used to add a 16 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_uint16(const char *key, const uint16_t value);

/**
 * s_log_uint32 is used to add a 32 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_uint32(const char *key, const uint32_t value);

/**
 * s_log_uint64 is used to add a 64 bit integer value to the log entry.
 */
struct s_log_field_t*
s_log_uint64(const char *key, const uint64_t value);

/**
 * s_log_float is used to add a float to the log entry.
 */
struct s_log_field_t*
s_log_float(const char *key, const float value);

/**
 * s_log_double is used to add a double to the log entry.
 */
struct s_log_field_t*
s_log_double(const char *key, const double value);

/**
 * s_log_string is used to add a string to the log entry.
 */
struct s_log_field_t*
s_log_string(const char *key, const char *value);

enum {
    S_LOG_OUT_STDERR,
    S_LOG_OUT_STDOUT,
};

/**
 * s_log_init initializes the logger and sets up where the logger writes to.
 */
void
s_log_init(FILE *out);

/**
 * reallog provides the functionality of the logger. Returns the number os
 * bytes written.
 */
void
reallog(char *l, ...);

/**
 * s_log is the main entry point for adding data to the logger to create log
 * entries.
 */
#define s_log(l, ...) ({ reallog(l, __VA_ARGS__, NULL); })

#ifdef __cplusplus
}
#endif
#endif /** end _S_LOGGER_H */
