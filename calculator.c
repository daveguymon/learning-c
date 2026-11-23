#include <limits.h>

#include "calculator.h"

CalcResult calculate(int first_val, char operator, int second_val)
{
    switch (operator)
    {
    case '+':
        if ((second_val > 0 && first_val > INT_MAX - second_val) ||
            (second_val < 0 && first_val < INT_MIN - second_val))
        {
            return (CalcResult){
                .value = 0,
                .status = CALC_OVERFLOW};
        }
        return (CalcResult){
            .value = first_val + second_val,
            .status = CALC_OK};
    case '-':
        if ((second_val > 0 && first_val < INT_MIN + second_val) ||
            (second_val < 0 && first_val > INT_MAX + second_val))
        {
            return (CalcResult){
                .value = 0,
                .status = CALC_OVERFLOW};
        }
        return (CalcResult){
            .value = first_val - second_val,
            .status = CALC_OK};
    case '*':
        if ((first_val > 0 && second_val > 0 && first_val > INT_MAX / second_val) ||
            (first_val > 0 && second_val < 0 && second_val < INT_MIN / first_val) ||
            (first_val < 0 && second_val > 0 && first_val < INT_MIN / second_val) ||
            (first_val < 0 && second_val < 0 && first_val < INT_MAX / second_val))
        {
            return (CalcResult){
                .value = 0,
                .status = CALC_OVERFLOW};
        }
        return (CalcResult){
            .value = first_val * second_val,
            .status = CALC_OK};
    case '/':
        if (second_val == 0)
        {
            return (CalcResult){
                .value = 0,
                .status = CALC_DIVISION_BY_ZERO};
        }
        if (first_val == INT_MIN && second_val == -1)
        {
            return (CalcResult){
                .value = 0,
                .status = CALC_OVERFLOW};
        }
        return (CalcResult){
            .value = first_val / second_val,
            .status = CALC_OK};
    default:
        return (CalcResult){
            .value = 0,
            .status = CALC_UNKNOWN_OPERATOR};
    }
}
