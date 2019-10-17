#include <stdio.h>

#include "unity/unity.h"

#include "../logger.h"

void
test_log_init(void)
{
    log_init(stderr);
    TEST_ASSERT_NOT_NULL(log_output);
}

void
test_log_two_fields(void)
{
    log_init(stdout);
    int wc = log(LOG_INFO, log_string("msg", "records added successfully"), log_int("count", 2));
    TEST_ASSERT_EQUAL_INT(94, wc);
}

void
test_log_three_fields(void)
{
    log_init(stdout);
    int wc = log(LOG_DEBUG, log_string("field1", "value1"), log_double("field2", 3.14), log_int64("field3", 89));
    TEST_ASSERT_GREATER_OR_EQUAL(100, wc);
}

int
main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_log_init);
    RUN_TEST(test_log_two_fields);
    RUN_TEST(test_log_three_fields);

    return UNITY_END();
}
