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
log_int64(const char *key, const int64_t value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_INT64;
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
log_string(const char *key, const char* value)
{
    struct log_field_t *field = log_field_new(key);
    field->type = LOG_STRING;
    field->char_value = malloc(strlen(value) + 1);
    strcpy(field->char_value, value);
    return field;
}

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
                json_object_object_add(root, arg->key, json_object_new_int(arg->int_value));
                break;
            case LOG_INT64:
                json_object_object_add(root, arg->key, json_object_new_int64(arg->int64_value));
                break;
            case LOG_DOUBLE:
                json_object_object_add(root, arg->key, json_object_new_double(arg->double_value));
                break;
            case LOG_STRING:
                json_object_object_add(root, arg->key, json_object_new_string(arg->char_value));
        }
        log_field_free(arg);
        continue;
    }
    
    va_end(ap);

    int wc = fprintf(log_output, "%s\n", json_object_to_json_string(root));
    json_object_put(root); // decrement the count on the JSON object

    return wc;
}
