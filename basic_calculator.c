#include <stdio.h>

typedef enum {
    CALC_OK,
    CALC_DIVISION_BY_ZERO,
    CALC_UNKNOWN_OPERATOR
} CalcStatus;

typedef struct {
    int value;
    CalcStatus status;
} CalcResult;

CalcResult calculate(int first_val, char operator, int second_val) {
    switch (operator) {
        case '+':
            return (CalcResult) {
                .value = first_val + second_val,
                .status = CALC_OK
            };
        case '-':
            return (CalcResult) {
                .value = first_val - second_val,
                .status = CALC_OK
            };
        case '*':
            return (CalcResult) {
                .value = first_val * second_val,
                .status = CALC_OK
            };
        case '/':
            if (second_val == 0) {
                return (CalcResult) {
                    .value = 0,
                    .status = CALC_DIVISION_BY_ZERO
                };
            };
            return (CalcResult) {
                .value = first_val / second_val,
                .status = CALC_OK
            };
        default:
            return (CalcResult) {
                .value = 0,
                .status = CALC_UNKNOWN_OPERATOR
            };
    };
}

int main(void) {
    int first_val, second_val;
    char operator;

    printf("Enter an expression (for example, 8 + 2): ");
    if (scanf("%d %c %d", &first_val, &operator, &second_val) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    CalcResult result = calculate(first_val, operator, second_val);
    if (result.status == CALC_OK) {
        printf("Result: %d\n", result.value);
    } else if (result.status == CALC_DIVISION_BY_ZERO) {
        printf("Error: Division by zero.\n");
    } else if (result.status == CALC_UNKNOWN_OPERATOR) {
        printf("Error: Unknown operator '%c'.\n", operator);
    }
    return 0;
}