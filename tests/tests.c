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
    int wc = log(LOG_INFO, "msg", log_string("records added successfully"), "count", log_int(2));
    TEST_ASSERT_EQUAL_INT(94, wc);
}

void
test_log_three_fields(void)
{
    log_init(stdout);
    int wc = log(LOG_DEBUG, "field1", log_string("value1"), "field2", log_double(3.14), "field3", log_int64(89));
    TEST_ASSERT_GREATER_OR_EQUAL(100, wc);
}

void
test_log_odd_count_fields(void)
{
    log_init(stdout);
    int wc = log(LOG_DEBUG, "field1", log_string("value1"), log_double(3.14), "field3", log_int64(89));
    TEST_ASSERT_EQUAL_INT(66, wc);
}

int
main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_log_init);
    RUN_TEST(test_log_two_fields);
    RUN_TEST(test_log_three_fields);
    RUN_TEST(test_log_odd_count_fields);

    return UNITY_END();
}
