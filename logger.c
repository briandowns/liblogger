#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <json-c/json.h>

#include "logger.h"

void
log_init(FILE* out)
{
    log_output = out;
}

/**
 * log_field_new allocates memory for a new log field,
 * sets the memory to 0, and returns a pointer to it.
 */
static struct log_field_t*
log_field_new()
{
    struct log_field_t* field = malloc(sizeof(log_field_t));
    if (field == NULL) {
        perror("unable to allocation memory for new field");
        return NULL;
    }
    memset(field, 0, sizeof(log_field_t));
    return field;
}

/**
 * log_field_free frees the memory used by the log_field_t.
 * struct.
 */
static void
log_field_free(struct log_field_t* sf)
{
    if (sf != NULL) {
        free(sf);
    }
}

/**
 * log_field_string_free frees the memory used by the string
 * field and then frees the memory used by the log_field_t struct.
 */
static void
log_field_string_free(struct log_field_t* sf)
{
    if (sf != NULL) {
        if (sf->char_value != NULL) {
            free(sf->char_value);
        }
        log_field_free(sf);
    }
}

struct log_field_t*
log_int(const int value)
{
    struct log_field_t* field = log_field_new();
    field->type = LOG_INT;
    field->int_value = value;
    return field;
}

struct log_field_t*
log_int64(const int64_t value)
{
    struct log_field_t* field = log_field_new();
    field->type = LOG_INT64;
    field->int64_value = value;
    return field;
}

struct log_field_t*
log_double(const double value)
{
    struct log_field_t* field = log_field_new();
    field->type = LOG_DOUBLE;
    field->double_value = value;
    return field;
}

struct log_field_t*
log_string(const char* value)
{
    struct log_field_t* field = log_field_new();
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
    struct json_object* root = json_object_new_object();
    json_object_object_add(root, "timestamp", json_object_new_int64(now));
    json_object_object_add(root, "level", json_object_new_string(l));

    va_start(ap, l);
    for (int i = 1;; i += 2) {
        char* arg1 = va_arg(ap, char*);
        if (arg1 == NULL) {
            break;
        }

        if (i % 2 != 0) {
            struct log_field_t* sf = va_arg(ap, struct log_field_t*);
            if (sf == NULL) {
                break;
            }
            switch (sf->type) {
                case LOG_INT:
                    json_object_object_add(root, arg1, json_object_new_int(sf->int_value));
                    log_field_free(sf);
                    break;
                case LOG_INT64:
                    json_object_object_add(root, arg1, json_object_new_int64(sf->int64_value));
                    log_field_free(sf);
                    break;
                case LOG_DOUBLE:
                    json_object_object_add(root, arg1, json_object_new_double(sf->double_value));
                    log_field_free(sf);
                    break;
                case LOG_STRING:
                    json_object_object_add(root, arg1, json_object_new_string(sf->char_value));
                    log_field_string_free(sf);
            }
            continue;
        }
    }
    va_end(ap);

    int wc = fprintf(log_output, "%s\n", json_object_to_json_string(root));
    json_object_put(root); // decrement the count on the JSON object

    return wc;
}
