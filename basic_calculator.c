#include <stdio.h>

int calculate(int first_val, char operator, int second_val) {
    switch (operator) {
        case '+':
            return first_val + second_val;
        case '-':
            return first_val - second_val;
        case '*':
            return first_val * second_val;
        case '/':
            return first_val / second_val;
        default:
            printf("Unknown operator: %c\n", operator);
            return 0;
    }
}

int main(void) {
    int first_val, second_val;
    char operator;

    printf("Enter an expression (for example, 8 + 2): ");
    if (scanf("%d %c %d", &first_val, &operator, &second_val) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = calculate(first_val, operator, second_val);
    printf("Result: %d\n", result);
    return 0;
}