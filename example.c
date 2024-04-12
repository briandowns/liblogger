#include <stdio.h>

#include "logger.h"

int
main(int argc, char **argv)
{
    s_log_init(stdout); 
    s_log(LOG_INFO, 
        s_log_string("msg", "records added successfully"), 
        s_log_uint("count", 2));
    s_log(LOG_INFO, 
        s_log_string("msg", "records added successfully"), 
        s_log_int64("count", 9223372036854775807));
    s_log(LOG_INFO, 
        s_log_string("msg", "record added successfully"), 
        s_log_string("name", "Brian"), 
        s_log_double("elapsed", 5.76));
    s_log(LOG_FATAL, s_log_string("msg", "dead :("));   
}
