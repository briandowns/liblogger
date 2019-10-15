#include <stdio.h>

#include "logger.h"

int
main(int argc, char **argv)
{
    log_init(stdout);
    log(LOG_INFO, log_string("msg", "records added successfully"), log_int("count", 2));
    log(LOG_INFO, log_string("msg", "records added successfully"), log_int64("count", 9223372036854775807));
    log(LOG_INFO, log_string("msg", "record added successfully"), log_string("name", "Brian"), log_double("elapsed", 5.76));
}
