#include <stdio.h>

#include "logger.h"

int
main(int argc, char** argv)
{
    log_init(stdout);
    log(LOG_INFO, "msg", log_string("records added successfully"), "count", log_int(2));
    log(LOG_INFO, "msg", log_string("records added successfully"), "count", log_int64(9223372036854775807));
    log(LOG_INFO, "msg", log_string("record added successfully"), "name", log_string("Brian"), "elapsed", log_double(5.76));
}
