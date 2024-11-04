#include <stdint.h>
#include <stdio.h>

#include "benchmark.h"
#include "../logger.h"

void
log_out(uint64_t i)
{
    s_log(S_LOG_INFO, 
        s_log_string("msg", "records added successfully"),
        s_log_uint("count", 2));
}

int
main(int argc, char **argv)
{
    FILE *out = fopen("/dev/null", "w");
    s_log_init(out);

    benchmark(100, 1, log_out);
    fclose(out);

    return 0;
}
