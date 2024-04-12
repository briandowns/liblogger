#include <stdio.h>

#include "unity/unity.h"

#include "../logger.h"

void
test_log_init(void)
{
    s_log_init(stderr);
    TEST_ASSERT_NOT_NULL(log_output);
}

void
test_log_two_fields(void)
{
    s_log_init(stdout);
    int wc = s_log(LOG_INFO, s_log_string("msg", "records added successfully"), s_log_int("count", 2));
    TEST_ASSERT_EQUAL_INT(94, wc);
}

void
test_log_three_fields(void)
{
    s_log_init(stdout);
    int wc = s_log(LOG_DEBUG, s_log_string("field1", "value1"), s_log_double("field2", 3.14), s_log_int64("field3", 89));
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
