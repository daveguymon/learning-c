#include <assert.h>
#include <limits.h>

#include "calculator.h"

static void assert_result(CalcResult result, int expected_value, CalcStatus expected_status)
{
    assert(result.status == expected_status);
    if (expected_status == CALC_OK)
    {
        assert(result.value == expected_value);
    }
}

static void test_successful_operations(void)
{
    assert_result(calculate(8, '+', 2), 10, CALC_OK);
    assert_result(calculate(8, '-', 2), 6, CALC_OK);
    assert_result(calculate(6, '*', 7), 42, CALC_OK);
    assert_result(calculate(20, '/', 3), 6, CALC_OK);
    assert_result(calculate(0, '+', INT_MIN), INT_MIN, CALC_OK);
    assert_result(calculate(INT_MAX, '+', 0), INT_MAX, CALC_OK);
    assert_result(calculate(INT_MIN, '-', 0), INT_MIN, CALC_OK);
    assert_result(calculate(INT_MAX, '-', 0), INT_MAX, CALC_OK);
    assert_result(calculate(1, '*', INT_MIN), INT_MIN, CALC_OK);
    assert_result(calculate(-1, '*', INT_MAX), -INT_MAX, CALC_OK);
    assert_result(calculate(0, '*', INT_MIN), 0, CALC_OK);
    assert_result(calculate(INT_MIN, '/', 1), INT_MIN, CALC_OK);
    assert_result(calculate(INT_MIN, '/', INT_MIN), 1, CALC_OK);
    assert_result(calculate(INT_MAX, '/', INT_MAX), 1, CALC_OK);
}

static void test_calculation_errors(void)
{
    assert_result(calculate(10, '/', 0), 0, CALC_DIVISION_BY_ZERO);
    assert_result(calculate(10, '^', 2), 0, CALC_UNKNOWN_OPERATOR);
}

static void test_addition_and_subtraction_overflow(void)
{
    assert_result(calculate(INT_MAX, '+', 1), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MIN, '+', -1), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MIN, '-', 1), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MAX, '-', -1), 0, CALC_OVERFLOW);
}

static void test_multiplication_overflow(void)
{
    assert_result(calculate(INT_MAX, '*', 2), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MIN, '*', 2), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MAX, '*', -2), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MIN, '*', -2), 0, CALC_OVERFLOW);
    assert_result(calculate(INT_MIN, '*', -1), 0, CALC_OVERFLOW);
    assert_result(calculate(-INT_MAX, '*', -1), INT_MAX, CALC_OK);
}

static void test_division_overflow(void)
{
    assert_result(calculate(INT_MIN, '/', -1), 0, CALC_OVERFLOW);
}

int main(void)
{
    test_successful_operations();
    test_calculation_errors();
    test_addition_and_subtraction_overflow();
    test_multiplication_overflow();
    test_division_overflow();
    return 0;
}
