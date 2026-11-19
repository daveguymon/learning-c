#include <stdio.h>
#include <limits.h>

typedef enum {
    CALC_OK,
    CALC_DIVISION_BY_ZERO,
    CALC_OVERFLOW,
    CALC_UNKNOWN_OPERATOR
} CalcStatus;

typedef struct {
    int value;
    CalcStatus status;
} CalcResult;

int get_choice(char *choice) {
    while (1) {
      printf("Do you want to continue? (y/n): ");
      if (scanf(" %c", choice) != 1) {
        return 0;
      }

      if (*choice == 'y' || *choice == 'Y' || *choice == 'n' || *choice == 'N') {
        return 1;
      }
      printf("Invalid choice. Please enter 'y' or 'n'.\n");
    }
}

CalcResult calculate(int first_val, char operator, int second_val) {
    switch (operator) {
        case '+':
            if ((second_val > 0 && first_val > INT_MAX - second_val) ||
                (second_val < 0 && first_val < INT_MIN - second_val)) {
                return (CalcResult) {
                    .value = 0,
                    .status = CALC_OVERFLOW
                };
            }
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
            }
            return (CalcResult) {
                .value = first_val / second_val,
                .status = CALC_OK
            };
        default:
            return (CalcResult) {
                .value = 0,
                .status = CALC_UNKNOWN_OPERATOR
            };
    }
}

int main(void) {
    int first_val, second_val;
    char operator;
    char choice;

    do {
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
        } else if (result.status == CALC_OVERFLOW) {
            printf("Error: Integer overflow.\n");
        } else if (result.status == CALC_UNKNOWN_OPERATOR) {
            printf("Error: Unknown operator '%c'.\n", operator); 
        }

        if(!get_choice(&choice)) {
            fprintf(stderr, "\nInput ended before you entered a choice.\n");
            return 1;
        }
    } while (choice == 'y' || choice == 'Y');
    return 0;
}
