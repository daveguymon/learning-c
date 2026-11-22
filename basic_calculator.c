#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256

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

int get_choice(char *choice)
{
    while (1)
    {
        printf("Do you want to continue? (y/n): ");
        if (scanf(" %c", choice) != 1)
        {
            return 0;
        }

        int remaining;
        while ((remaining = getchar()) != '\n' && remaining != EOF)
        {
        }

        if (*choice == 'y' || *choice == 'Y' || *choice == 'n' || *choice == 'N')
        {
            return 1;
        }
        printf("Invalid choice. Please enter 'y' or 'n'.\n");
    }
}

int parse_expression(const char *input, int *first_val, char *operator, int *second_val)
{
    char *end;
    errno = 0;
    long parsed_first = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || parsed_first < INT_MIN || parsed_first > INT_MAX)
    {
        return 0;
    }

    while (isspace((unsigned char)*end))
    {
        end++;
    }
    if (*end == '\0')
    {
        return 0;
    }
    *operator = *end++;

    errno = 0;
    char *second_start = end;
    long parsed_second = strtol(second_start, &end, 10);
    if (end == second_start || errno == ERANGE || parsed_second < INT_MIN || parsed_second > INT_MAX)
    {
        return 0;
    }

    while (isspace((unsigned char)*end))
    {
        end++;
    }
    if (*end != '\0')
    {
        return 0;
    }

    *first_val = (int)parsed_first;
    *second_val = (int)parsed_second;
    return 1;
}

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

int main(void)
{
    int first_val, second_val;
    char operator;
    char choice;
    char input[INPUT_BUFFER_SIZE];

    while (1)
    {
        printf("Enter an expression (for example, 8 + 2): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            if (ferror(stdin))
            {
                perror("Error reading expression");
            }
            else
            {
                fprintf(stderr, "\nInput ended before you entered an expression.\n");
            }
            return 1;
        }

        char *newline = strchr(input, '\n');
        if (newline != NULL)
        {
            *newline = '\0';
        }
        else
        {
            int remaining = getchar();
            if (remaining != '\n' && remaining != EOF)
            {
                while (remaining != '\n' && remaining != EOF)
                {
                    remaining = getchar();
                }
                if (ferror(stdin))
                {
                    perror("Error reading expression");
                    return 1;
                }
                printf("Invalid input.\n");
                continue;
            }
            if (ferror(stdin))
            {
                perror("Error reading expression");
                return 1;
            }
        }

        if (!parse_expression(input, &first_val, &operator, &second_val))
        {
            printf("Invalid input.\n");
            continue;
        }

        CalcResult result = calculate(first_val, operator, second_val);

        if (result.status == CALC_OK)
        {
            printf("Result: %d\n", result.value);
        }
        else if (result.status == CALC_DIVISION_BY_ZERO)
        {
            printf("Error: Division by zero.\n");
        }
        else if (result.status == CALC_OVERFLOW)
        {
            printf("Error: Integer overflow.\n");
        }
        else if (result.status == CALC_UNKNOWN_OPERATOR)
        {
            printf("Error: Unknown operator '%c'.\n", operator);
        }

        if (!get_choice(&choice))
        {
            fprintf(stderr, "\nInput ended before you entered a choice.\n");
            return 1;
        }

        if (choice == 'n' || choice == 'N')
        {
            break;
        }
    }

    return 0;
}
