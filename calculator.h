#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum
{
    CALC_OK,
    CALC_DIVISION_BY_ZERO,
    CALC_OVERFLOW,
    CALC_UNKNOWN_OPERATOR
} CalcStatus;

typedef struct
{
    int value;
    CalcStatus status;
} CalcResult;

CalcResult calculate(int first_val, char operator, int second_val);

#endif
